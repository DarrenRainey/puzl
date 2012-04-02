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

#ifndef SDL_OGL_GAME_SHELL_H
#define SDL_OGL_GAME_SHELL_H

// INCLUDES ======================================================================
#include <puzl/utility/CoreGameShell.h>
#include <puzl/video/SdlOglVideoSystem.h>
#include <puzl/video/SdlOglVideoDisplay.h>
#include <puzl/audio/SdlOglAudioSystem.h>
#include <puzl/input/SdlOglInputSystem.h>

#include <string>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================
class SdlOglGameShell: public CoreGameShell
{
  
public:
  SdlOglGameShell( const GameShellSettings& gameShellSettings );
  ~SdlOglGameShell( void );
  
  virtual int shellInitialize( void );
  virtual int shellShutdown( void );
  virtual void shellLoop( void );
  
  virtual int initialize( void );
  virtual int shutdown( void );
  
  virtual void loop( void );
  virtual void draw( const float& interpolation = 0.0f );
  
protected:
  SdlOglVideoSystem* videoSystem;
  SdlOglAudioSystem* audioSystem;
  SdlOglInputSystem* inputSystem;

  SdlOglVideoDisplay* display;

  SdlOglInputKeyboard** keyboards;
  SdlOglInputKeyboard* keyboard;
  
  SdlOglInputMouse** mice;
  SdlOglInputJoystick** joysticks;

  //int numberOfNetwork;
  
  int initializeVideo( void );
  int shutdownVideo( void );

  virtual int releaseVideo( void );
  virtual int reloadVideo( void );

  int initializeInput( void );
  int shutdownInput( void );
  
  int initializeAudio( void );
  int shutdownAudio( void );
  
  void setCaption( string caption );
  void setIcon( string filePath );
  
private:
  unsigned int nowTime;
  unsigned int lastTime;
  unsigned int nextTime;
  
  int updateSystem( void );
};

#endif
