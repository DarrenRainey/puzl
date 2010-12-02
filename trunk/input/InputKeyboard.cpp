/*
Copyright (C) 2010 Andrew Dieffenbach (www.puzzud.com).

This file is part of puzl.

puzl is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with puzl; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

//================================================================================
// InputKeyboard.cpp
// Authors:  Andrew Dieffenbach
// Date:     April 20, 2004
// Description:
//
//================================================================================

// INCLUDES ======================================================================

// Add the SDL header files for appropriate OS build
#include <SDL/SDL.h>

#include "puzl/input/InputKeyboard.h"		// InputKeyboard class header file for keyboard input


// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// Name: InputKeyboard()
// Description:
// Default constructor
//--------------------------------------------------------------------------------
InputKeyboard::InputKeyboard()
{
	int index;
	
	input = new Input* [NUM_KEY_CODES];
	for( index = 0; index < NUM_KEY_CODES; index++ )
	{
		keyState[index].id = index;
		keyState[index].state = KEY_STATE_UP;
		keyState[index].type = INPUT_TYPE_KEYBOARD_KEY;
		
		input[index] = &keyState[index];
	}
	
	stateChangeBufferSize = 10;	// TODO: Determine this somehow (constructor?).
	stateChange = new Input* [stateChangeBufferSize];
	for( index = 0; index < stateChangeBufferSize; index++ )
	{
		stateChange[index] = NULL;
	}
	
	numberOfStateChanges = 0;
}


//--------------------------------------------------------------------------------
// Name: ~InputKeyboard()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
InputKeyboard::~InputKeyboard()
{
	delete [] input;
	input = NULL;
	
	delete [] stateChange;
	stateChange = NULL;
}


//--------------------------------------------------------------------------------
// Name: checkKey()
// Description:
// 
//--------------------------------------------------------------------------------
bool InputKeyboard::checkKey( int key )
{
	return check( key );
}


//--------------------------------------------------------------------------------
// Name: getKeyState()
// Description:
// 
//--------------------------------------------------------------------------------
int InputKeyboard::getKeyState( int key )
{
	return getState( key );
}


//--------------------------------------------------------------------------------
// Name: getLastInputId()
// Description:
// 
//--------------------------------------------------------------------------------
int InputKeyboard::getLastKeyPress()
{
	return getLastInputId();
}


//--------------------------------------------------------------------------------
// Name: getLastInputId()
// Description:
// 
//--------------------------------------------------------------------------------
Input** InputKeyboard::getCurrentKeyEvents()
{
	return stateChange;
}


//--------------------------------------------------------------------------------
// Name: getLastInputId()
// Description:
// 
//--------------------------------------------------------------------------------
int InputKeyboard::getNumberOfCurrentKeyEvents()
{
	return numberOfStateChanges;
}


//--------------------------------------------------------------------------------
// Name: getLastInputId()
// Description:
// 
//--------------------------------------------------------------------------------
int InputKeyboard::getLastInputId()
{
	return lastInputId;
}


//--------------------------------------------------------------------------------
// Name: update()
// Description:
// 
//--------------------------------------------------------------------------------
void InputKeyboard::update( SDL_Event *event )
{
	if( numberOfStateChanges > stateChangeBufferSize )
	{
		return;
	}
	
	int key = event->key.keysym.sym;
	
	// Process the keyboard events
	switch( event->type )
	{
		// A key was just pressed
		case SDL_KEYDOWN:
		{
			#ifdef DEBUG
			cout << "Keyboard:  "
				<< ( int )( key )
				<< " Press" << endl;
			#endif
			
			if( numberOfStateChanges == 0 )
			{
				lastInputId = key;
			}
		
			keyState[key].state = KEY_STATE_PRESSED;
		} break;

		// A key was just released
		case SDL_KEYUP:
		{
			#ifdef DEBUG
			cout << "Keyboard:  "
				<< ( int )( key )
				<< " Release" << endl;
			#endif
					
			keyState[key].state = KEY_STATE_RELEASED;
		} break;
	}
	
	stateChange[numberOfStateChanges++] = input[key];
}
