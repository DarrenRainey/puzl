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
#include <puzl/input/AndroidInputKeyboard.h>

#include <iostream>

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
AndroidInputKeyboard::AndroidInputKeyboard( void ): CoreInputKeyboard()
{
  int index;

  keyState = new Input[NUM_KEY_CODES];
  input    = new Input*[NUM_KEY_CODES];

  for( index = 0; index < NUM_KEY_CODES; index++ )
  {
    keyState[index].id    = index;
    keyState[index].type  = INPUT_TYPE_KEYBOARD_KEY;
    keyState[index].state = KEY_STATE_UP;
    keyState[index].value = 0;

    input[index] = &keyState[index];
  }
}

//--------------------------------------------------------------------------------
AndroidInputKeyboard::~AndroidInputKeyboard( void )
{
  delete [] keyState;
  keyState = NULL;

  delete [] input;
  input = NULL;
}

//--------------------------------------------------------------------------------
void AndroidInputKeyboard::onKeyDown( int keyCode )
{
  if( numberOfStateChanges > stateChangeBufferSize )
  {
    return;
  }

  if( numberOfStateChanges == 0 )
  {
    lastInputId = keyCode;
  }

  keyState[keyCode].state = KEY_STATE_PRESSED;

  stateChange[numberOfStateChanges++] = input[keyCode];
}

//--------------------------------------------------------------------------------
void AndroidInputKeyboard::onKeyUp( int keyCode )
{
  keyState[keyCode].state = KEY_STATE_RELEASED;

  stateChange[numberOfStateChanges++] = input[keyCode];
}
