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
#include <puzl/input/CoreInputKeyboard.h>

#include <iostream>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================
//--------------------------------------------------------------------------------
CoreInputKeyboard::CoreInputKeyboard( void )
{
  int index;

	stateChangeBufferSize = 10;	// TODO: Determine this somehow (constructor?).
	stateChange = new Input*[stateChangeBufferSize];
	for( index = 0; index < stateChangeBufferSize; index++ )
	{
		stateChange[index] = NULL;
	}
	
	numberOfStateChanges = 0;
}

//--------------------------------------------------------------------------------
CoreInputKeyboard::~CoreInputKeyboard( void )
{
	delete [] stateChange;
	stateChange = NULL;
}

//--------------------------------------------------------------------------------
bool CoreInputKeyboard::checkKey( int key )
{
	return check( key );
}

//--------------------------------------------------------------------------------
int CoreInputKeyboard::getKeyState( int key )
{
	return getState( key );
}

//--------------------------------------------------------------------------------
int CoreInputKeyboard::getLastKeyPress( void )
{
	return getLastInputId();
}

//--------------------------------------------------------------------------------
Input** CoreInputKeyboard::getCurrentKeyEvents( void )
{
	return stateChange;
}

//--------------------------------------------------------------------------------
int CoreInputKeyboard::getNumberOfCurrentKeyEvents( void )
{
	return numberOfStateChanges;
}

//--------------------------------------------------------------------------------
int CoreInputKeyboard::getLastInputId( void )
{
	return lastInputId;
}
