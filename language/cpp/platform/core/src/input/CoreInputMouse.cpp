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
#include <puzl/input/CoreInputMouse.h>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
CoreInputMouse::CoreInputMouse( void )
{
	xPosition = 0;
	yPosition = 0;
	xDelta	  = 0;
	yDelta	  = 0;

	int index;
	for( index = 0; index < NUM_MOUSE_BUTTONS; index++ )
	{
		buttonState[index] = BUTTON_STATE_UP;
	}

	lock = LOCK_STATE_OFF;
	doWarp = false;
}

//--------------------------------------------------------------------------------
CoreInputMouse::~CoreInputMouse( void )
{

}

//--------------------------------------------------------------------------------
int CoreInputMouse::getXPosition( void )
{
	return( xPosition );
}

//--------------------------------------------------------------------------------
int CoreInputMouse::getYPosition( void )
{
	return( yPosition );
}

//--------------------------------------------------------------------------------
int CoreInputMouse::getXDelta( void )
{
	return( xDelta );
}

//--------------------------------------------------------------------------------
int CoreInputMouse::getYDelta( void )
{
	return( yDelta );
}

//--------------------------------------------------------------------------------
int CoreInputMouse::clearDeltas( void )
{
	return xDelta = yDelta = 0;
}

//--------------------------------------------------------------------------------
int CoreInputMouse::getButton( int button )
{
	return buttonState[button];
}

//--------------------------------------------------------------------------------
int CoreInputMouse::getLastInputId( void )
{
	return lastInputId;
}

//--------------------------------------------------------------------------------
void CoreInputMouse::setLock( bool lock )
{
	if( lock )
	{
		this->lock = LOCK_STATE_START;
	}
	else
	{
		this->lock = LOCK_STATE_OFF;
	}
}

//--------------------------------------------------------------------------------
int CoreInputMouse::getLock( void )
{
	return lock;
}

//--------------------------------------------------------------------------------
void CoreInputMouse::warp( int x, int y )
{
	//doWarp = true;
}
