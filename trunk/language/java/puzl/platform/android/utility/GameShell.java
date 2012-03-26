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
  public static native void nativeDraw();
  
  public static native void nativeOnKeyDown( int keyCode );
  public static native void nativeOnKeyUp( int keyCode );
  
  public static native void nativeTouchDown( int id, int xPosition, int yPosition );
  public static native void nativeTouchUp( int id, int xPosition, int yPosition );
  public static native void nativeTouchMove( int id, int xPosition, int yPosition );
  
  GameShellView gameShellView;

  @Override
  protected void onCreate( Bundle icicle )
  {
    super.onCreate( icicle );
    
    gameShellView = new GameShellView( this );
    setContentView( gameShellView );
  }

  @Override
  protected void onPause()
  {
    super.onPause();
    
    gameShellView.onPause();
  }
  
  @Override
  protected void onResume()
  {
    super.onResume();
    
    gameShellView.onResume();
  }

  public void onDrawFrame()
  {
    nativeDraw();
    nativeLoop();
  }

  public void initializeVideo( int width, int height )
  {
    nativeInitializeVideo( width, height );
  }

  public void initialize()
  {
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
}
