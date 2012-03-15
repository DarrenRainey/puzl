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
  input = new Input*[NUM_MOUSE_BUTTONS];

  int index;
  buttonState = new Input[NUM_MOUSE_BUTTONS];
  for( index = 0; index < NUM_MOUSE_BUTTONS; index++ )
  {
    buttonState[index].id    = index;
    buttonState[index].state = BUTTON_STATE_UP;
    buttonState[index].type  = INPUT_TYPE_MOUSE_BUTTON;

    input[index] = &buttonState[index];
  }

  // TODO: Add states for mouse/touch deltas (similar to joysticks).
}

//--------------------------------------------------------------------------------
SdlOglInputMouse::~SdlOglInputMouse( void )
{
  delete [] buttonState;
  buttonState = NULL;

  delete [] input;
  input = NULL;
}

//--------------------------------------------------------------------------------
void SdlOglInputMouse::setLock( bool lock )
{
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
		
			xPosition = event->motion.x;
			yPosition = event->motion.y;
			
			if( lock != LOCK_STATE_START )
			{
				xDelta	  = 0;
				yDelta	  = 0;
				
				//lock = LOCK_STATE_ON;
			}
			else
			{
				xDelta	  = event->motion.xrel;
				yDelta	  = event->motion.yrel;
			}
			
		} break;

		// A button was just pressed
		case SDL_MOUSEBUTTONDOWN:
		{
			#ifdef DEBUG
			cout << "Mouse:  "
				<< "Button(" << ( int )( event->button.button ) << ")"
				<< " Down" << endl;
			#endif

			buttonState[event->button.button].state = BUTTON_STATE_DOWN;

			xPosition = event->button.x;
			yPosition = event->button.y;
		} break;

		// A button was just released
		case SDL_MOUSEBUTTONUP:
		{
			#ifdef DEBUG
			cout << "Mouse:  "
				<< "Button(" << ( int )( event->button.button ) << ")"
				<< " Up" << endl;
			#endif

			buttonState[event->button.button].state = BUTTON_STATE_UP;

			xPosition = event->button.x;
			yPosition = event->button.y;
		} break;
	}
}
