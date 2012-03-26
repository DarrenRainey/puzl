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

#ifndef ANDROID_INPUT_MOUSE
#define ANDROID_INPUT_MOUSE

// INCLUDES ======================================================================
#include <puzl/input/CoreInputMouse.h>

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

// DEFINES =======================================================================
// Buffer defines
#define NUM_MOUSE_BUTTONS     255    // Hardcoded! (within SDL)
#define NUM_MOUSE_DELTAS      2      // (X,Y).
#define MOUSE_BUFFER_SIZE     7      // Five fingers and two directions?

// TYPES =========================================================================
class AndroidInputMouse: public CoreInputMouse
{
public:
  AndroidInputMouse( void );
  ~AndroidInputMouse( void );

  void setLock( bool lock );

  void warp( int x, int y );

  void touchDown( int id, int xPosition, int yPosition );
  void touchUp( int id, int xPosition, int yPosition );
  void touchMove( int id, int xPosition, int yPosition );

protected:

private:
};

#endif
