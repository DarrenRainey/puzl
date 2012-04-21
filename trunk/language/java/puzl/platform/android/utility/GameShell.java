/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package puzl.platform.android.utility;


import android.app.Activity;
import android.os.Bundle;
import android.os.SystemClock;
import android.util.Log;
import android.view.KeyEvent;

public class GameShell extends Activity
{
  static
  {
    System.loadLibrary( "puzl" );
  }

  public static native void nativeInitialize();
  //public static native void nativeShutdown();
  public static native void nativeInitializeVideo( int width, int height );
  public static native void nativeLoop();
  public static native void nativeDraw( float interpolation );
  
  public static native void nativeOnKeyDown( int keyCode );
  public static native void nativeOnKeyUp( int keyCode );
  
  public static native void nativeTouchDown( int id, int xPosition, int yPosition );
  public static native void nativeTouchUp( int id, int xPosition, int yPosition );
  public static native void nativeTouchMove( int id, int xPosition, int yPosition );
  
  GameShellView gameShellView;
  protected GameShellThread gameShellThread;

  @Override
  protected void onCreate( Bundle icicle )
  {
    super.onCreate( icicle );
    
    Log.v("puzl", "GameShell.onCreate()");
    
    gameShellView = new GameShellView( this );
    setContentView( gameShellView );
    
    gameShellThread = new GameShellThread( gameShellView );
    if( !gameShellThread.getRunning() )
    {
      initialize();
      gameShellThread.start();
    }
    else
    {
      // Run the garbage collector.
      Runtime runtime = Runtime.getRuntime();
      runtime.gc();
    }
  }

  @Override
  protected void onPause()
  {
    super.onPause();
    
    gameShellView.onPause();
    gameShellThread.onPause();
  }
  
  @Override
  protected void onResume()
  {
    super.onResume();
    
    gameShellView.onResume();
    gameShellThread.onResume();
  }

  public void onDrawFrame()
  {
    nativeDraw( gameShellThread.interpolation );
    //nativeLoop();
  }

  public void initializeVideo( int width, int height )
  {
    Log.v("puzl", "GameShell.initializeVideo()");
    nativeInitializeVideo( width, height );
  }

  public void initialize()
  {
    Log.v("puzl", "GameShell.initialize()");
    nativeInitialize();
  }
  
  @Override
  public boolean onKeyDown( int keyCode, KeyEvent event )
  {
    super.onKeyDown( keyCode, event );
    nativeOnKeyDown( keyCode );

    return true;
  }
  
  @Override
  public boolean onKeyUp( int keyCode, KeyEvent event )
  {
    super.onKeyUp( keyCode, event );
    nativeOnKeyUp( keyCode );
    
    return true;
  }
  
  public void touchDown( int id, int xPosition, int yPosition )
  {
    nativeTouchDown( id, xPosition, yPosition );
  }
  
  public void touchUp( int id, int xPosition, int yPosition )
  {
    nativeTouchUp( id, xPosition, yPosition );
  }
  
  public void touchMove( int id, int xPosition, int yPosition )
  {
    nativeTouchMove( id, xPosition, yPosition );
  }
  
  protected class GameShellThread extends Thread
  {
    private boolean running;
    private boolean suspended;
    private long lastTime;
    private Object suspendLock;
    
    final static long TICKS_PER_SECOND = 60;
    final static long SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    final static long MAX_FRAMESKIP = 5;
    
    public float interpolation;
    
    GameShellView gameShellView;
    
    public GameShellThread( GameShellView gameShellView )
    {
      setName( "GameShellThread" );
      suspendLock = new Object();
      suspended   = false;
      
      //lastTime = SystemClock.uptimeMillis();
      running  = false;
      
      this.gameShellView = gameShellView;
    }

    @Override
    public void start()
    {
      setRunning( true );
      super.start();
    }
    
    @Override
    public void run()
    {
      Log.v("puzl", "GameShellThread.run():" + this.getId() + " " + "started...");

      //long nextTime = SystemClock.uptimeMillis();
      //lastTime = nextTime;
      //int loops;
      
      interpolation = 0;

      while( running )
      {
        //Log.v( "puzl", "GameShellThread.run(): running " + SystemClock.uptimeMillis() );
        
        gameShellView.gameShellRenderer.waitDrawingComplete();
        
        //Log.v( "puzl", "GameShellThread.run(): begin processing logic " + SystemClock.uptimeMillis() );
        
        /*loops = 0;
        while( SystemClock.uptimeMillis() > nextTime && loops < MAX_FRAMESKIP )
        {*/
          nativeLoop();

          /*nextTime += SKIP_TICKS;
          loops++;
        }*/

        //interpolation = ( float )( SystemClock.uptimeMillis() + SKIP_TICKS - nextTime ) / ( float )SKIP_TICKS;
        
        //Log.v( "puzl", "GameShellThread.run(): finished processing logic " + SystemClock.uptimeMillis() );
        
        gameShellView.gameShellRenderer.setDrawReady();
        gameShellView.requestRender();

        final long time = SystemClock.uptimeMillis();
        final long timeDelta = time - lastTime;
        lastTime = time;

        if( timeDelta < SKIP_TICKS )
        {
          //Log.v( "puzl", "GameShellThread.run(): going to sleep " + SystemClock.uptimeMillis() );
          final long sleepTime = SKIP_TICKS - timeDelta;
          //if( sleepTime < SKIP_TICKS / 2 )
          {
            //Log.v( "puzl", "GameShellThread.run(): sleep time: " + sleepTime );
            try
            {
              //Thread.sleep( SKIP_TICKS - timeDelta );
              Thread.sleep( sleepTime );
            }
            catch( InterruptedException e )
            {
              // Interruptions here are no big deal.
            }
          }
          //Log.v( "puzl", "GameShellThread.run(): waking up " + SystemClock.uptimeMillis() );
          
        }
        
        //lastTime = SystemClock.uptimeMillis();
        
        //Log.v( "puzl", "GameShellThread.run(): total time: " + ( SystemClock.uptimeMillis() - time + timeDelta ) );

        // Check if should wait
        synchronized( suspendLock )
        {
          if( suspended )
          {
            // Do initial pausing stuff.
            Log.v("puzl", "GameShellThread.run():" + this.getId() + " " + "suspended...");

            // Wait while suspended.
            while( suspended )
            {
              try
              {
                suspendLock.wait();
              }
              catch( Exception e )
              {

              }
            }

            Log.v("puzl", "GameShellThread.run():" + this.getId() + " " + "unsuspended");
          }
        }
      }

      Log.v("puzl", "GameShellThread.run():" + this.getId() + " " + "finished");
    }
    
    public void onStop()
    {
      synchronized( suspendLock )
      {
        suspended = false;
        running   = false;
        suspendLock.notifyAll();
      }
    }
    
    public void onPause()
    {
      synchronized( suspendLock )
      {
        suspended = true;
      }
    }
    
    public void onResume()
    {
      synchronized( suspendLock )
      {
        suspended = false;
        suspendLock.notifyAll();
      }
    }
    
    public void setRunning( boolean running )
    {
      synchronized( suspendLock )
      {
        this.running = running;
        if( !running )
        {
          //suspended = false;
          suspendLock.notify();
        }
        else
        {
          
        }
      }
    }
    
    public boolean getRunning()
    {
      return( running );
    }
    
    public void setSuspended( boolean pause )
    {
      synchronized( suspendLock )
      {
        this.suspended = pause;
        if( !suspended )
        {
          suspendLock.notify();
        }
      }
    }
    
    public boolean getSuspended()
    {
      return( suspended );
    }
  }
}
