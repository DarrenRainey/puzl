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

// Mouse/Touch event types
#define TOUCH_EVENT_TYPE_DOWN 0
#define TOUCH_EVENT_TYPE_UP   1
#define TOUCH_EVENT_TYPE_MOVE 2

// TYPES =========================================================================

struct TouchInput: Input
{
  int xPosition;
  int yPosition;
};

class AndroidInputMouse: public CoreInputMouse
{
public:
  AndroidInputMouse( void );
  ~AndroidInputMouse( void );

  void setLock( bool lock );

  void warp( int x, int y );

  void touchDown( const int& id, const int& xPosition, const int& yPosition );
  void touchUp( const int& id, const int& xPosition, const int& yPosition );
  void touchMove( const int& id, const int& xPosition, const int& yPosition );

protected:

private:
  void queueEvent( const int& eventType, const int& id, const int& xPosition, const int& yPosition );
  void update( void );

  int numberOfBufferedInputs;

  TouchInput* inputBuffer;

  friend class AndroidInputSystem;
};

#endif
