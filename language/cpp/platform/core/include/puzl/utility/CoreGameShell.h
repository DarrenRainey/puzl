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

#ifndef CORE_GAME_SHELL_H
#define CORE_GAME_SHELL_H

// INCLUDES ======================================================================
#include <puzl/input/CoreInputSystem.h>
#include <puzl/video/CoreVideoSystem.h>
#include <puzl/audio/CoreAudioSystem.h>

#include <string>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================
struct GameShellSettings
{
  int screenWidth;
  int screenHeight;
};

class CoreGameShell
{
public:
  CoreGameShell( const GameShellSettings& gameShellSettings );
  ~CoreGameShell( void );
  
  virtual int shellInitialize( void );
  virtual int shellShutdown( void );
  virtual void shellLoop( void );
  
  virtual int initialize( void );
  virtual int shutdown( void );
  
  virtual void loop( void );
  virtual void draw( const float& interpolation = 0.0f );
  
  int run( void );
  
protected:
  virtual int releaseVideo( void );
  virtual int reloadVideo( void );

  virtual void setCaption( string caption );
  virtual void setIcon( string iconFilename );

  CoreInputSystem* inputSystem;     // Input system object
  CoreVideoSystem* videoSystem;     // Video system object
  CoreAudioSystem* audioSystem;     // Audio system object

  CoreInputKeyboard** keyboards;    // Keyboard object
  CoreInputKeyboard* keyboard;
  
  CoreInputMouse** mice;            // Mouse objects
  CoreInputJoystick** joysticks;    // Joystick objects

  //int numberOfNetwork;            // Number of network client/players

  CoreVideoDisplay* display;        // Main video display

  GameShellSettings gameShellSettings;
  
  bool quit;                        // Program terminator flag

  string caption;
  string iconFilename;
};

#endif
