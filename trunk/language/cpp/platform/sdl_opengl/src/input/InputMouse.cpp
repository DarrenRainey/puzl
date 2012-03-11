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

	xPosition = 0;
	yPosition = 0;
	xDelta	  = 0;
	yDelta	  = 0;

	for( index = 0; index < NUM_MOUSE_BUTTONS; index++ )
	{
		buttonState[index] = BUTTON_STATE_UP;
	}

	lock = LOCK_STATE_OFF;
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
// Name: getXPosition()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::getXPosition()
{
	return( xPosition );
}


//--------------------------------------------------------------------------------
// Name: getYPosition()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::getYPosition()
{
	return( yPosition );
}


//--------------------------------------------------------------------------------
// Name: getXDelta()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::getXDelta()
{
	return( xDelta );
}


//--------------------------------------------------------------------------------
// Name: getYDelta()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::getYDelta()
{
	return( yDelta );
}


//--------------------------------------------------------------------------------
// Name: clearDeltas()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::clearDeltas()
{
	return xDelta = yDelta = 0;
}


//--------------------------------------------------------------------------------
// Name: getButton()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::getButton( int button )
{
	return buttonState[button];
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
// Name: setLock()
// Description:
// 
//--------------------------------------------------------------------------------
void InputMouse::setLock( bool state )
{
	if( state )
	{
		SDL_ShowCursor( 0 );
		SDL_WM_GrabInput( SDL_GRAB_ON );
		
		lock = LOCK_STATE_START;
	}
	else
	{
		SDL_ShowCursor( 1 );			// TODO Conditional check here if program has its own cursor.
		SDL_WM_GrabInput( SDL_GRAB_OFF );
		
		lock = LOCK_STATE_OFF;
	}
}


//--------------------------------------------------------------------------------
// Name: getLock()
// Description:
// 
//--------------------------------------------------------------------------------
int InputMouse::getLock()
{
	return lock;
}


//--------------------------------------------------------------------------------
// Name: warp()
// Description:
// 
//--------------------------------------------------------------------------------
void InputMouse::warp( int x, int y )
{
	int index;
	
	//doWarp = true;
	
	SDL_WarpMouse( x, y );
	
	SDL_PumpEvents();
	
	// NOTE: Need numberOfEvents here?
	int numberOfEvents = SDL_PeepEvents( eventBuffer, MOUSE_BUFFER_SIZE, SDL_GETEVENT,
					     SDL_EVENTMASK( SDL_MOUSEMOTION ) );
}


//--------------------------------------------------------------------------------
// Name: update()
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

			buttonState[event->button.button] = BUTTON_STATE_DOWN;

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

			buttonState[event->button.button] = BUTTON_STATE_UP;

			xPosition = event->button.x;
			yPosition = event->button.y;
		} break;
	}
}
