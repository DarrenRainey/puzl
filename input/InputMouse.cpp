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
// InputMouse.cpp
// Authors:  Andrew Dieffenbach
// Date:     April 20, 2004
// Description:
//
//================================================================================

// INCLUDES ======================================================================

// Add the SDL header files for appropriate OS build
#include <SDL/SDL.h>

#include "puzl/input/InputMouse.h"		// InputMouse class header file for mouse input


// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// Name: InputMouse()
// Description:
// Default constructor
//--------------------------------------------------------------------------------
InputMouse::InputMouse()
{
	int index;

	XPosition = 0;
	YPosition = 0;
	XDelta	  = 0;
	YDelta	  = 0;

	for( index = 0; index < NUM_MOUSE_BUTTONS; index++ )
		ButtonState[index] = BUTTON_STATE_UP;

	Lock = LOCK_STATE_OFF;
	//doWarp = false;
}


//--------------------------------------------------------------------------------
// Name: ~InputMouse()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
InputMouse::~InputMouse()
{

}


//--------------------------------------------------------------------------------
// Name: GetXPosition()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::GetXPosition( void )
{
	return( XPosition );
}


//--------------------------------------------------------------------------------
// Name: GetYPosition()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::GetYPosition( void )
{
	return( YPosition );
}


//--------------------------------------------------------------------------------
// Name: GetXDelta()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::GetXDelta( void )
{
	return( XDelta );
}


//--------------------------------------------------------------------------------
// Name: GetYDelta()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::GetYDelta( void )
{
	return( YDelta );
}


//--------------------------------------------------------------------------------
// Name: ClearDeltas()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::ClearDeltas( void )
{
	XDelta = YDelta = 0;
	
	return( 0 );
}


//--------------------------------------------------------------------------------
// Name: GetButton()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::GetButton( int button )
{
	return( ButtonState[button] );
}


//--------------------------------------------------------------------------------
// Name: getLastInputId()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::getLastInputId()
{
	return lastInputId;
}


//--------------------------------------------------------------------------------
// Name: Lock()
// Description:
// 
//--------------------------------------------------------------------------------
void InputMouse::SetLock( bool state )
{
	if( state )
	{
		SDL_ShowCursor( 0 );
		SDL_WM_GrabInput( SDL_GRAB_ON );
		
		Lock = LOCK_STATE_START;
	}
	else
	{
		SDL_ShowCursor( 1 );			// TODO Conditional check here if program has its own cursor
		SDL_WM_GrabInput( SDL_GRAB_OFF );
		
		Lock = LOCK_STATE_OFF;
	}
}


//--------------------------------------------------------------------------------
// Name: GetLock()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::GetLock( void )
{
	return( Lock );
}


//--------------------------------------------------------------------------------
// Name: Warp()
// Description:
// 
//--------------------------------------------------------------------------------
void InputMouse::Warp( int x, int y )
{
	int index;
	
	//doWarp = true;
	
	SDL_WarpMouse( x, y );
	
	SDL_PumpEvents();
	int numberOfEvents = SDL_PeepEvents( EventBuffer, MOUSE_BUFFER_SIZE, SDL_GETEVENT,
					 SDL_EVENTMASK( SDL_MOUSEMOTION ) );
}


//--------------------------------------------------------------------------------
// Name: Update()
// Description:
// 
//--------------------------------------------------------------------------------
void InputMouse::update( SDL_Event *event )
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
		
			XPosition = event->motion.x;
			YPosition = event->motion.y;
			
			if( Lock != LOCK_STATE_START )
			{
				XDelta	  = 0;
				YDelta	  = 0;
				
				//Lock = LOCK_STATE_ON;
			}
			else
			{
				XDelta	  = event->motion.xrel;
				YDelta	  = event->motion.yrel;
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

			ButtonState[event->button.button] = BUTTON_STATE_DOWN;

			XPosition = event->button.x;
			YPosition = event->button.y;
		} break;

		// A button was just released
		case SDL_MOUSEBUTTONUP:
		{
			#ifdef DEBUG
			cout << "Mouse:  "
				<< "Button(" << ( int )( event->button.button ) << ")"
				<< " Up" << endl;
			#endif

			ButtonState[event->button.button] = BUTTON_STATE_UP;

			XPosition = event->button.x;
			YPosition = event->button.y;
		} break;
	}
}
