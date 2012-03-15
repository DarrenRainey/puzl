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

#ifndef CORE_INPUT_MOUSE
#define CORE_INPUT_MOUSE

// INCLUDES ======================================================================
#include <puzl/input/CoreInputDevice.h>

// DEFINES =======================================================================
// Button state defines
#ifndef BUTTON_STATE
  #define BUTTON_STATE_UP        INPUT_STATE_UP
  #define BUTTON_STATE_RELEASED  INPUT_STATE_RELEASED
  #define BUTTON_STATE_DOWN      INPUT_STATE_DOWN
  #define BUTTON_STATE_PRESSED   INPUT_STATE_PRESSED
#endif

#define INPUT_TYPE_MOUSE_BUTTON   1

#define LOCK_STATE_OFF				    0
#define LOCK_STATE_START			   -1
#define LOCK_STATE_ON				      1

// TYPES =========================================================================
class CoreInputMouse: public CoreInputDevice
{
public:
	CoreInputMouse( void );
	~CoreInputMouse( void );

	virtual int getXPosition( void );
	virtual int getYPosition( void );

	virtual int getXDelta( void );
	virtual int getYDelta( void );
	
	virtual int clearDeltas( void );

	virtual int getButton( int button );
	virtual int getLastInputId( void );
	
	virtual void setLock( bool state );
	virtual int getLock( void );
	
	virtual void warp( int x, int y );
	
protected:
	int xPosition;
	int yPosition;
	int xDelta;
	int yDelta;

	int lock;
	bool doWarp;

	Input* buttonState;
};

#endif
