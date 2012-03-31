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
  int index;

  inputBuffer = new TouchInput[MOUSE_BUFFER_SIZE];
  for( index = 0; index < MOUSE_BUFFER_SIZE; index++ )
  {
    inputBuffer[index].id    = 0;
    inputBuffer[index].type  = 0;
    inputBuffer[index].state = 0;
    inputBuffer[index].value = 0;

    inputBuffer[index].xPosition = 0;
    inputBuffer[index].yPosition = 0;
  }
  numberOfBufferedInputs = 0;

  input = new Input*[NUM_MOUSE_BUTTONS + NUM_MOUSE_DELTAS];

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

  delete [] inputBuffer;
  inputBuffer = NULL;
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
void AndroidInputMouse::queueEvent( const int& eventType, const int& id, const int& xPosition, const int& yPosition )
{
  if( numberOfBufferedInputs > MOUSE_BUFFER_SIZE )
  {
    return;
  }

  static TouchInput* currentBufferedInput = NULL;
  currentBufferedInput = &inputBuffer[numberOfBufferedInputs++];

  currentBufferedInput->type      = eventType;
  currentBufferedInput->id        = id;
  currentBufferedInput->xPosition = xPosition;
  currentBufferedInput->yPosition = yPosition;

  /*switch( eventType )
  {
    case TOUCH_EVENT_TYPE_DOWN:
    {
      //currentBufferedInput->state = INPUT_STATE_PRESSED;

      break;
    }

    case TOUCH_EVENT_TYPE_UP:
    {
      //currentBufferedInput->state = INPUT_STATE_RELEASED;
      break;
    }

    case TOUCH_EVENT_TYPE_MOVE:
    {
      //currentBufferedInput->state = INPUT_STATE_PRESSED;
      break;
    }
  }*/
}

//--------------------------------------------------------------------------------
void AndroidInputMouse::update( void )
{
  static TouchInput* currentBufferedInput = NULL;

  int index;
  for( index = 0; index < numberOfBufferedInputs; index++ )
  {
    currentBufferedInput = &inputBuffer[index];
    switch( currentBufferedInput->type )
    {
      case TOUCH_EVENT_TYPE_DOWN:
      {
        if( numberOfStateChanges > stateChangeBufferSize )
        {
          break;
        }

        buttonState[currentBufferedInput->id].state = INPUT_STATE_PRESSED;

        this->xPosition = currentBufferedInput->xPosition;
        this->yPosition = currentBufferedInput->yPosition;

        stateChange[numberOfStateChanges++] = input[currentBufferedInput->id];
        break;
      }

      case TOUCH_EVENT_TYPE_UP:
      {
        if( numberOfStateChanges > stateChangeBufferSize )
        {
          break;
        }

        buttonState[currentBufferedInput->id].state = INPUT_STATE_RELEASED;

        this->xPosition = currentBufferedInput->xPosition;
        this->yPosition = currentBufferedInput->yPosition;

        stateChange[numberOfStateChanges++] = input[currentBufferedInput->id];
        break;
      }

      case TOUCH_EVENT_TYPE_MOVE:
      {
        if( numberOfStateChanges + 1 > stateChangeBufferSize )
        {
          break;
        }

        if( lock == LOCK_STATE_OFF )
        {
          deltaState[0].value = currentBufferedInput->xPosition - this->xPosition;
          deltaState[1].value = currentBufferedInput->yPosition - this->yPosition;
        }
        else
        if( lock != LOCK_STATE_START )
        {
          deltaState[0].value = 0;
          deltaState[1].value = 0;

          //lock = LOCK_STATE_ON;
        }

        this->xPosition = currentBufferedInput->xPosition;
        this->yPosition = currentBufferedInput->yPosition;

        deltaState[0].state = INPUT_STATE_PRESSED;
        deltaState[1].state = INPUT_STATE_PRESSED;

        stateChange[numberOfStateChanges++] = input[deltaStateInputOffset];
        stateChange[numberOfStateChanges++] = input[deltaStateInputOffset + 1];
        break;
      }
    }
  }

  numberOfBufferedInputs = 0;
}

//--------------------------------------------------------------------------------
void AndroidInputMouse::touchDown( const int& id, const int& xPosition, const int& yPosition )
{
  queueEvent( TOUCH_EVENT_TYPE_DOWN, id, xPosition, yPosition );
}

//--------------------------------------------------------------------------------
void AndroidInputMouse::touchUp( const int& id, const int& xPosition, const int& yPosition )
{
  queueEvent( TOUCH_EVENT_TYPE_UP, id, xPosition, yPosition );
}

//--------------------------------------------------------------------------------
void AndroidInputMouse::touchMove( const int& id, const int& xPosition, const int& yPosition )
{
  queueEvent( TOUCH_EVENT_TYPE_MOVE, id, xPosition, yPosition );
}
