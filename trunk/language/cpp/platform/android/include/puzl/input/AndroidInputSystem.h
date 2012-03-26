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

#ifndef ANDROID_INPUT_SYS
#define ANDROID_INPUT_SYS

// INCLUDES ======================================================================
#include <puzl/input/CoreInputSystem.h>
#include <puzl/input/AndroidInputKeyboard.h>
#include <puzl/input/AndroidInputMouse.h>
#include <puzl/input/AndroidInputJoystick.h>

// DEFINES =======================================================================

// TYPES =========================================================================
class AndroidInputSystem: public CoreInputSystem
{
public:
  AndroidInputSystem( void );
  ~AndroidInputSystem( void );

  int initialize( void );
  int shutdown( void );

private:

  friend class AndroidGameShell;
};

#endif
