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
#include <puzl/input/AndroidInputMouse.h>

#include <iostream>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================
//--------------------------------------------------------------------------------
AndroidInputMouse::AndroidInputMouse( void ): CoreInputMouse()
{
  input = new Input*[NUM_MOUSE_BUTTONS + NUM_MOUSE_DELTAS];

  int index;

  buttonState = new Input[NUM_MOUSE_BUTTONS];
  for( index = 0; index < NUM_MOUSE_BUTTONS; index++ )
  {
    buttonState[index].id    = index;
    buttonState[index].type  = INPUT_TYPE_MOUSE_BUTTON;
    buttonState[index].state = BUTTON_STATE_UP;
    buttonState[index].value = 0;

    input[index] = &buttonState[index];
  }

  deltaStateInputOffset = NUM_MOUSE_BUTTONS;
  deltaState = new Input[NUM_MOUSE_DELTAS];
  for( index = 0; index < NUM_MOUSE_DELTAS; index++ )
  {
    deltaState[index].id    = index;
    deltaState[index].type  = INPUT_TYPE_MOUSE_DELTA;
    deltaState[index].state = INPUT_STATE_UP;
    deltaState[index].value = 0;

    input[deltaStateInputOffset + index] = &deltaState[index];
  }
}

//--------------------------------------------------------------------------------
AndroidInputMouse::~AndroidInputMouse( void )
{
  delete [] buttonState;
  buttonState = NULL;

  delete [] deltaState;
  deltaState = NULL;

  delete [] input;
  input = NULL;
}

//--------------------------------------------------------------------------------
void AndroidInputMouse::setLock( bool lock )
{
  CoreInputMouse::setLock( lock );
}

//--------------------------------------------------------------------------------
void AndroidInputMouse::warp( int x, int y )
{

}

//--------------------------------------------------------------------------------
void AndroidInputMouse::touchDown( int id, int xPosition, int yPosition )
{
  buttonState[id].state = BUTTON_STATE_PRESSED;

  this->xPosition = xPosition;
  this->yPosition = yPosition;

  stateChange[numberOfStateChanges++] = input[id];
}

//--------------------------------------------------------------------------------
void AndroidInputMouse::touchUp( int id, int xPosition, int yPosition )
{
  buttonState[id].state = BUTTON_STATE_RELEASED;

  this->xPosition = xPosition;
  this->yPosition = yPosition;

  stateChange[numberOfStateChanges++] = input[id];
}

//--------------------------------------------------------------------------------
void AndroidInputMouse::touchMove( int id, int xPosition, int yPosition )
{
  if( numberOfStateChanges + 1 > stateChangeBufferSize )
  {
    return;
  }

  if( lock == LOCK_STATE_OFF )
  {
    deltaState[0].value = this->xPosition - xPosition;
    deltaState[1].value = this->yPosition - yPosition;
  }
  else
  if( lock != LOCK_STATE_START )
  {
    deltaState[0].value = 0;
    deltaState[1].value = 0;

    //lock = LOCK_STATE_ON;
  }

  this->xPosition = xPosition;
  this->yPosition = yPosition;

  deltaState[0].state = INPUT_STATE_PRESSED;
  deltaState[1].state = INPUT_STATE_PRESSED;

  stateChange[numberOfStateChanges++] = input[deltaStateInputOffset];
  stateChange[numberOfStateChanges++] = input[deltaStateInputOffset + 1];
}
