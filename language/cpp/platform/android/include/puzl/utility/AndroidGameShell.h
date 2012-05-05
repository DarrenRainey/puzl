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

#ifndef ANDROID_GAME_SHELL_H
#define ANDROID_GAME_SHELL_H

// INCLUDES ======================================================================
#include <puzl/utility/CoreGameShell.h>
#include <puzl/video/AndroidVideoSystem.h>
#include <puzl/video/AndroidVideoDisplay.h>
#include <puzl/audio/AndroidAudioSystem.h>
#include <puzl/input/AndroidInputSystem.h>

#include <jni.h>
#include <android/log.h>

#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  LOG_TAG_PUZL    "libpuzl"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG_PUZL,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG_PUZL,__VA_ARGS__)

#include <string>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================
class AndroidGameShell: public CoreGameShell
{

public:
  AndroidGameShell( const GameShellSettings& gameShellSettings );
  ~AndroidGameShell( void );

  virtual int shellInitialize( void );
  virtual int shellShutdown( void );

  virtual int initialize( void );
  virtual int shutdown( void );

  virtual void loop( void );
  virtual void draw( const float& interpolation = 0.0f );

  int reloadVideo( const GameShellSettings& gameShellSettings );

  void onKeyDown( int keyCode );
  void onKeyUp( int keyCode );

  void touchDown( int id, int xPosition, int yPosition );
  void touchUp( int id, int xPosition, int yPosition );
  void touchMove( int id, int xPosition, int yPosition );

  void inputSystemUpdate( void );

  int createTextureFromFile( string fileName, int* width = NULL, int* height = NULL );

protected:
  AndroidVideoSystem* videoSystem;
  AndroidAudioSystem* audioSystem;
  AndroidInputSystem* inputSystem;

  AndroidVideoDisplay* display;

  AndroidInputKeyboard** keyboards;
  AndroidInputKeyboard* keyboard;

  AndroidInputMouse** mice;
  AndroidInputJoystick** joysticks;

  int initializeVideo( void );
  int shutdownVideo( void );

  int initializeInput( void );
  int shutdownInput( void );

  int initializeAudio( void );
  int shutdownAudio( void );

  virtual int releaseVideo( void );
  virtual int reloadVideo( void );

  void setCaption( string caption );
  void setIcon( string filePath );
};

// -------------------------------------------------------------------------------
extern "C"
{
  JNIEXPORT jint JNICALL JNI_OnLoad( JavaVM* vm, void* reserved );

  JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeInitialize( JNIEnv* env, jobject obj );
  JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeInitializeVideo( JNIEnv* env, jobject obj, jint width, jint height );
  JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeDraw( JNIEnv* env, jobject obj, jfloat interpolation );
  JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeLoop( JNIEnv* env, jobject obj );

  JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeTouchDown( JNIEnv* env, jobject obj, jint id, jint xPosition, jint yPosition );
  JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeTouchUp( JNIEnv* env, jobject obj, jint id, jint xPosition, jint yPosition );
  JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeTouchMove( JNIEnv* env, jobject obj, jint id, jint xPosition, jint yPosition );

  JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeOnKeyDown( JNIEnv* env, jobject obj, jint keyCode );
  JNIEXPORT void JNICALL Java_puzl_platform_android_utility_GameShell_nativeOnKeyUp( JNIEnv* env, jobject obj, jint keyCode );
};

// -------------------------------------------------------------------------------
void SetGameShell( AndroidGameShell* gameShell );

#endif
