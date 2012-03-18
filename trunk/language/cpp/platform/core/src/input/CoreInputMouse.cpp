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

#include <iostream>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
CoreInputMouse::CoreInputMouse( void ): CoreInputDevice()
{
	xPosition = 0;
	yPosition = 0;

	deltaStateInputOffset = 0;

	lock   = LOCK_STATE_OFF;
	doWarp = false;
}

//--------------------------------------------------------------------------------
CoreInputMouse::~CoreInputMouse( void )
{

}

//--------------------------------------------------------------------------------
int CoreInputMouse::getXPosition( void )
{
	return xPosition;
}

//--------------------------------------------------------------------------------
int CoreInputMouse::getYPosition( void )
{
	return yPosition;
}

//--------------------------------------------------------------------------------
int CoreInputMouse::getXDelta( void )
{
  return deltaState[0].value;
}

//--------------------------------------------------------------------------------
int CoreInputMouse::getYDelta( void )
{
  return deltaState[1].value;
}

//--------------------------------------------------------------------------------
int CoreInputMouse::clearDeltas( void )
{
  return deltaState[1].value = deltaState[0].value = 0;
}

//--------------------------------------------------------------------------------
int CoreInputMouse::getButtonState( int button )
{
  //cout << "CoreInputMouse::getButtonState(): " << getState( button ) << endl;
	return getState( button );
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
