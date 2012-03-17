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
#include <puzl/input/SdlOglInputKeyboard.h>

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
SdlOglInputKeyboard::SdlOglInputKeyboard( void ): CoreInputKeyboard()
{
	int index;
	
	keyState = new Input[NUM_KEY_CODES];
	input    = new Input*[NUM_KEY_CODES];

	for( index = 0; index < NUM_KEY_CODES; index++ )
	{
		keyState[index].id    = index;
		keyState[index].state = KEY_STATE_UP;
		keyState[index].type  = INPUT_TYPE_KEYBOARD_KEY;
		
		input[index] = &keyState[index];
	}
}

//--------------------------------------------------------------------------------
SdlOglInputKeyboard::~SdlOglInputKeyboard( void )
{
  delete [] keyState;
  keyState = NULL;

	delete [] input;
	input = NULL;
}

//--------------------------------------------------------------------------------
void SdlOglInputKeyboard::update( SDL_Event* event )
{
	if( numberOfStateChanges > stateChangeBufferSize )
	{
		return;
	}
	
	static SDLKey& key = event->key.keysym.sym;
	
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

			break;
		}

		// A key was just released
		case SDL_KEYUP:
		{
			#ifdef DEBUG
			cout << "Keyboard:  "
				<< ( int )( key )
				<< " Release" << endl;
			#endif
					
			keyState[key].state = KEY_STATE_RELEASED;

			break;
		}
	}
	
	stateChange[numberOfStateChanges++] = input[key];
}
