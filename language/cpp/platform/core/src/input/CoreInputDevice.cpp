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
#include <puzl/input/CoreInputDevice.h>

#include <iostream>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
CoreInputDevice::CoreInputDevice( void )
{
	input                 = NULL;
	stateChange           = NULL;
	stateChangeBufferSize = 0;
	numberOfStateChanges  = 0;
	
	lastInputId           = -1;
	lastInputType         = 0;
}

//--------------------------------------------------------------------------------
CoreInputDevice::~CoreInputDevice( void )
{
  // Make this joystick object invalid initially.
  id = -1;
}

//--------------------------------------------------------------------------------
int CoreInputDevice::initialize( void )
{
	return 0;
}

//--------------------------------------------------------------------------------
int CoreInputDevice::shutdown( void )
{
	return 0;
}

//--------------------------------------------------------------------------------
bool CoreInputDevice::check( int inputId )
{
	return input[inputId]->state & INPUT_STATE_DOWN ? true : false;
}

//--------------------------------------------------------------------------------
int CoreInputDevice::getState( int inputId )
{
	return input[inputId]->state;
}

//--------------------------------------------------------------------------------
int CoreInputDevice::getLastInputId( void )
{
	return lastInputId;
}

//--------------------------------------------------------------------------------
void CoreInputDevice::age( void )
{
	int index;
	for( index = 0; index < numberOfStateChanges; index++ )
	{
		Input* tempStateChange = stateChange[index];
		if( tempStateChange->state == INPUT_STATE_RELEASED )
		{
			tempStateChange->state = INPUT_STATE_UP;
		}
		else
		if( tempStateChange->state == INPUT_STATE_PRESSED )
		{
			tempStateChange->state = INPUT_STATE_DOWN;
		}
	}
	
	numberOfStateChanges = 0;
	lastInputId          = -1;
}
