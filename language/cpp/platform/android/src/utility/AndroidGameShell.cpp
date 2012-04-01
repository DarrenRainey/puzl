/*
Copyright (c) 2012, Andrew Dieffenbach. All rights reserved.

This file is part of puzl.

puzl is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

puzl is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301  USA
*/

// INCLUDES ======================================================================
#include <puzl/utility/AndroidGameShell.h>
#include <puzl/video/AndroidVideoDisplay.h>

#include <string>
#include <iostream>
//#include <sstream>
//#include <time.h>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

AndroidGameShell* _GameShell;
GameShellSettings _GameShellSettings;

// FUNCTIONS =====================================================================
//--------------------------------------------------------------------------------
AndroidGameShell::AndroidGameShell( const GameShellSettings& gameShellSettings ): CoreGameShell( gameShellSettings )
{

}

//--------------------------------------------------------------------------------
AndroidGameShell::~AndroidGameShell( void )
{

}

//--------------------------------------------------------------------------------
int AndroidGameShell::initialize( void )
{
  return 0;
}

//--------------------------------------------------------------------------------
int AndroidGameShell::shutdown( void )
{
  return 0;
}

//--------------------------------------------------------------------------------
void AndroidGameShell::loop( void )
{

}

//--------------------------------------------------------------------------------
void AndroidGameShell::draw( void )
{
  display->update();
}

//--------------------------------------------------------------------------------
int AndroidGameShell::shellInitialize( void )
{
  cout << "AndroidGameShell::shellInitialize()" << endl;

  initializeVideo();
  initializeInput();
  initializeAudio();

  return initialize();
}

//--------------------------------------------------------------------------------
int AndroidGameShell::initializeVideo( void )
{
  cout << "AndroidGameShell::initializeVideo()" << endl;
  videoSystem = new AndroidVideoSystem();
  if( videoSystem->initialize( gameShellSettings.screenWidth, gameShellSettings.screenHeight, DISPLAY_ATTRIBUTE_RESIZABLE ) < 0 )
  {
    cout << "GameShell::initializeVideo(): Failed to initialize video system." << endl;
    delete videoSystem;
    return -1;
  }

  display = ( AndroidVideoDisplay* )( videoSystem->getDisplay() );
  if( display == NULL )
  {
    cout << "GameShell::initializeVideo(): Failed to initialize video display." << endl;
    videoSystem->shutdown();
    delete videoSystem;
    return -1;
  }

  return 0;
}

//--------------------------------------------------------------------------------
int AndroidGameShell::reloadVideo( const GameShellSettings& gameShellSettings )
{
  this->gameShellSettings = gameShellSettings;

  shutdownVideo();
  initializeVideo();

  return 0;
}

//--------------------------------------------------------------------------------
int AndroidGameShell::releaseVideo( void )
{
  return 0;
}

//--------------------------------------------------------------------------------
int AndroidGameShell::reloadVideo( void )
{
  return 0;
}

//--------------------------------------------------------------------------------
int AndroidGameShell::initializeInput( void )
{
  inputSystem = new AndroidInputSystem();
  if( inputSystem->initialize() < 0 )
  {
    cout << "GameShell::initializeInput(): Failed to initialize input system." << endl;
    delete inputSystem;
    return -1;
  }

  keyboards = ( AndroidInputKeyboard** )( inputSystem->getKeyboards() );
  //keyboard = keyboards[0]; // TODO: Check if exists.

  mice = ( AndroidInputMouse** )( inputSystem->getMice() );
  joysticks = ( AndroidInputJoystick** )( inputSystem->getJoysticks() );

  return 0;
}

//--------------------------------------------------------------------------------
int AndroidGameShell::initializeAudio( void )
{
  audioSystem = new AndroidAudioSystem();
  if( audioSystem->initialize( 44100, 2, 4096 ) < 0 )
  {
    cout << "GameShell::initializeAudio(): Failed to initialize audio system." << endl;
    delete audioSystem;
    return -1;
  }

  return 0;
}

//--------------------------------------------------------------------------------
int AndroidGameShell::shellShutdown( void )
{
  cout << "shellShutdown" << endl;
  shutdown();

  shutdownAudio();
  shutdownInput();
  shutdownVideo();

  return 0;
}

//--------------------------------------------------------------------------------
int AndroidGameShell::shutdownInput( void )
{
  /*cout << "shutdownInput" << endl;
  if( inputSystem->shutdown() < 0 )
  {
    cout << "GameShell::shutdownInput(): Failed to shut down input system." << endl;
    delete inputSystem;
    return -1;
  }
  else
  {
    delete inputSystem;
    return 0;
  }*/
}

//--------------------------------------------------------------------------------
int AndroidGameShell::shutdownAudio( void )
{
  cout << "shutdownAudio" << endl;
  if( audioSystem->shutdown() < 0 )
  {
    cout << "GameShell::shutdownInput(): Failed to shut down audio system." << endl;
    delete audioSystem;
    return -1;
  }
  else
  {
    delete audioSystem;
    return 0;
  }
}

//--------------------------------------------------------------------------------
int AndroidGameShell::shutdownVideo( void )
{
  cout << "AndroidGameShell::shutdownVideo()" << endl;
  if( videoSystem->shutdown() < 0 )
  {
    cout << "GameShell::shutdownInput(): Failed to shut down video system." << endl;
    delete videoSystem;
    return -1;
  }
  else
  {
    delete videoSystem;
    return 0;
  }
}

//--------------------------------------------------------------------------------
void AndroidGameShell::setCaption( string caption )
{
  CoreGameShell::setCaption( caption );
}

//--------------------------------------------------------------------------------
void AndroidGameShell::setIcon( string filePath )
{
  CoreGameShell::setIcon( filePath );
}

//--------------------------------------------------------------------------------
void AndroidGameShell::onKeyDown( int keyCode )
{
  keyboard->onKeyDown( keyCode );
}

//--------------------------------------------------------------------------------
void AndroidGameShell::onKeyUp( int keyCode )
{
  keyboard->onKeyUp( keyCode );
}

//--------------------------------------------------------------------------------
void AndroidGameShell::touchDown( int id, int xPosition, int yPosition )
{
  mice[id]->touchDown( id, xPosition, yPosition );
}

//--------------------------------------------------------------------------------
void AndroidGameShell::touchUp( int id, int xPosition, int yPosition )
{
  mice[id]->touchUp( id, xPosition, yPosition );
}

//--------------------------------------------------------------------------------
void AndroidGameShell::touchMove( int id, int xPosition, int yPosition )
{
  mice[id]->touchMove( id, xPosition, yPosition );
}

//--------------------------------------------------------------------------------
void AndroidGameShell::inputSystemUpdate( void )
{
  inputSystem->age();
  inputSystem->update();
}

// -------------------------------------------------------------------------------
void SetGameShell( AndroidGameShell* gameShell )
{
  _GameShell = gameShell;
}

//--------------------------------------------------------------------------------
inline int GameShellInitialize( void )
{
  LOGI("Android::GameShellInitialize()");
  //_GameShellSettings.screenWidth  = 0;
  //_GameShellSettings.screenHeight = 0;
  //_GameShell = new AndroidGameShell( _GameShellSettings );

  _GameShell->shellInitialize();

  //LOGI("GL %s = %s\n", name, v);
  return 0;
}

//--------------------------------------------------------------------------------
inline int GameShellInitializeVideo( int screenWidth, int screenHeight )
{
  /*if( _GameShell == NULL )
  {
    return -1;
  }

  LOGI( "GameShellInitializeVideo(): not null" );*/

  _GameShellSettings.screenWidth  = screenWidth;
  _GameShellSettings.screenHeight = screenHeight;
  _GameShell->reloadVideo( _GameShellSettings );

  //LOGI("GL %s = %s\n", name, v);
  return 0;
}

//--------------------------------------------------------------------------------
inline void GameShellDraw( void )
{
  /*if( _GameShell == NULL )
  {
    return;
  }

  LOGI( "GameShellDraw(): not null" );*/
  _GameShell->draw();
}

//--------------------------------------------------------------------------------
inline void GameShellLoop( void )
{
  /*if( _GameShell == NULL )
  {
    return;
  }

  LOGI( "GameShellLoop(): not null" );*/

  _GameShell->inputSystemUpdate();
  _GameShell->loop();
}

//--------------------------------------------------------------------------------
inline void GameShellOnKeyDown( int keyCode )
{
  _GameShell->onKeyDown( keyCode );
}

//--------------------------------------------------------------------------------
inline void GameShellOnKeyUp( int keyCode )
{
  _GameShell->onKeyUp( keyCode );
}

//--------------------------------------------------------------------------------
inline void GameShellTouchDown( int id, int xPosition, int yPosition )
{
  _GameShell->touchDown( id, xPosition, yPosition );
}

//--------------------------------------------------------------------------------
inline void GameShellTouchUp( int id, int xPosition, int yPosition )
{
  _GameShell->touchUp( id, xPosition, yPosition );
}

//--------------------------------------------------------------------------------
inline void GameShellTouchMove( int id, int xPosition, int yPosition )
{
  _GameShell->touchMove( id, xPosition, yPosition );
}

//--------------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeInitialize( JNIEnv* env, jobject obj )
{
  GameShellInitialize();
}

//--------------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeInitializeVideo( JNIEnv* env, jobject obj, jint width, jint height )
{
  GameShellInitializeVideo( width, height );
}

//--------------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeLoop( JNIEnv* env, jobject obj )
{
  GameShellLoop();
}

//--------------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeDraw( JNIEnv* env, jobject obj )
{
  GameShellDraw();
}

//--------------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeOnKeyDown( JNIEnv* env, jobject obj, jint keyCode )
{
  GameShellOnKeyDown( keyCode );
}

//--------------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeOnKeyUp( JNIEnv* env, jobject obj, jint keyCode )
{
  GameShellOnKeyUp( keyCode );
}

//--------------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeTouchDown( JNIEnv* env, jobject obj, jint id, jint xPosition, jint yPosition )
{
  GameShellTouchDown( id, xPosition, yPosition );
}

//--------------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeTouchUp( JNIEnv* env, jobject obj, jint id, jint xPosition, jint yPosition )
{
  GameShellTouchUp( id, xPosition, yPosition );
}

//--------------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeTouchMove( JNIEnv* env, jobject obj, jint id, jint xPosition, jint yPosition )
{
  GameShellTouchMove( id, xPosition, yPosition );
}
