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
#include <puzl/input/SdlOglInputMouse.h>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================
//--------------------------------------------------------------------------------
SdlOglInputMouse::SdlOglInputMouse( void ): CoreInputMouse()
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
SdlOglInputMouse::~SdlOglInputMouse( void )
{
  delete [] buttonState;
  buttonState = NULL;

  delete [] deltaState;
  deltaState = NULL;

  delete [] input;
  input = NULL;
}

//--------------------------------------------------------------------------------
void SdlOglInputMouse::setLock( bool lock )
{
  CoreInputMouse::setLock( lock );
	if( lock )
	{
		SDL_ShowCursor( 0 );
		SDL_WM_GrabInput( SDL_GRAB_ON );
	}
	else
	{
		SDL_ShowCursor( 1 );			// TODO: Conditional check here if program has its own cursor.
		SDL_WM_GrabInput( SDL_GRAB_OFF );
	}
}

//--------------------------------------------------------------------------------
void SdlOglInputMouse::warp( int x, int y )
{
	//doWarp = true;
	SDL_WarpMouse( x, y );
	
	SDL_PumpEvents();
	
	// TODO: Need this here?
	SDL_PeepEvents( eventBuffer, MOUSE_BUFFER_SIZE, SDL_GETEVENT,
	                SDL_EVENTMASK( SDL_MOUSEMOTION ) );
}

//--------------------------------------------------------------------------------
void SdlOglInputMouse::update( SDL_Event* event )
{
	// Process the mouse events
	switch( event->type )
	{
		// The mouse was moved
		case SDL_MOUSEMOTION:
		{
			#ifdef DEBUG
			cout << "Mouse:  "
				<< "(" << event->motion.x     << ","
				<< event->motion.y 	       << ") "
				<< "[" << event->motion.xrel  << ","
				<< event->motion.xrel 	       << "]"
				<< " Motion" << endl;
			#endif
			
			if( numberOfStateChanges + 1 > stateChangeBufferSize )
      {
        return;
      }

			xPosition = event->motion.x;
			yPosition = event->motion.y;

			if( lock == LOCK_STATE_OFF )
			{
			  deltaState[0].value = event->motion.xrel;
			  deltaState[1].value = event->motion.yrel;
      }
			else
			if( lock != LOCK_STATE_START )
			{
			  deltaState[0].value = 0;
			  deltaState[1].value = 0;
				
				//lock = LOCK_STATE_ON;
			}
			
			deltaState[0].state = INPUT_STATE_PRESSED;
			deltaState[1].state = INPUT_STATE_PRESSED;

			stateChange[numberOfStateChanges++] = input[deltaStateInputOffset];
			stateChange[numberOfStateChanges++] = input[deltaStateInputOffset + 1];

			break;
		}

		// A button was just pressed
		case SDL_MOUSEBUTTONDOWN:
		{
		  if( numberOfStateChanges > stateChangeBufferSize )
      {
        return;
      }

			#ifdef DEBUG
			cout << "Mouse:  "
				<< "Pressed(" << ( int )( event->button.button ) << ")"
				<< " Down" << endl;
			#endif

			static unsigned char& buttonId = event->button.button;
			buttonState[buttonId - 1].state = BUTTON_STATE_PRESSED;

			xPosition = event->button.x;
			yPosition = event->button.y;

			deltaState[0].value = deltaState[1].value = 0;

			stateChange[numberOfStateChanges++] = input[buttonId - 1];

			break;
		}

		// A button was just released
		case SDL_MOUSEBUTTONUP:
		{
		  if( numberOfStateChanges > stateChangeBufferSize )
      {
        return;
      }

			#ifdef DEBUG
			cout << "Mouse:  "
				<< "Button(" << ( int )( event->button.button ) << ")"
				<< " Released" << endl;
			#endif

			static unsigned char& buttonId = event->button.button;
			buttonState[buttonId - 1].state = BUTTON_STATE_RELEASED;

			xPosition = event->button.x;
			yPosition = event->button.y;

			deltaState[0].value = deltaState[1].value = 0;

			stateChange[numberOfStateChanges++] = input[buttonId - 1];

			break;
		}
	}
}
