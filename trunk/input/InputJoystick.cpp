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
// InputJoystick.cpp
// Authors:  Andrew Dieffenbach
// Date:     May 9, 2004
// Description:
//
//================================================================================

// INCLUDES ======================================================================

// Add the SDL header files for appropriate OS build
#include <SDL/SDL.h>

#include "puzl/input/InputJoystick.h"		// InputJoystick class header file for joystick input


// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

int InputJoystick::count = 0;


// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// Name: InputJoystick()
// Description:
// Default constructor
//--------------------------------------------------------------------------------
InputJoystick::InputJoystick()
{
	int index;
	
	// Make this joystick object invalid initially.
	id = -1;

	// Clear the button states.
	for( index = 0; index < NUM_JOYSTICK_BUTTONS; index++ )
	{
		buttonState[index] = BUTTON_STATE_UP;
	}

	// Clear the axis states
	for( index = 0; index < NUM_JOYSTICK_AXES; index++ )
	{
		axisState[index] = AXIS_STATE_CENTER;
	}
}


//--------------------------------------------------------------------------------
// Name: ~InputJoystick()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
InputJoystick::~InputJoystick()
{
	#ifdef DEBUG
	if( id != -1 )
	{
		cout << "Joystick(" << id << ") was not shutdown!" << endl; 
	}
	#endif
}


//--------------------------------------------------------------------------------
// Name: initialize()
// Description:
// 
//--------------------------------------------------------------------------------
int InputJoystick::initialize()
{
	// Increase the reference counter for a 'new' joystick.
	// Get the unique system-level ID of this joystick.
	id = count++;

	#ifdef DEBUG
	cout << "id " << id;
	#endif

	// Switch on the joystick event system.
	if( count == 1 )
	{
		SDL_JoystickEventState( SDL_ENABLE );
	}

	// Open this joystick device for SDL.
	joystick = SDL_JoystickOpen( id );

	// Check if this is a valid joystick; else fill default values.
	if( joystick == NULL )
	{
		#ifdef DEBUG
		cout << "Invalid Joystick(" <<
			id <<
			")" << endl;
		#endif
		
		if( --count == 0 )
		{
			SDL_JoystickEventState( SDL_IGNORE );
		}

		return -1;
	}
	else
	{
		// Get name of this joystick.
		name = SDL_JoystickName( id );

		#ifdef DEBUG
		cout << name << endl;
		#endif
	}

	return 0;
}


//--------------------------------------------------------------------------------
// Name: shutdown()
// Description:
// 
//--------------------------------------------------------------------------------
int InputJoystick::shutdown()
{
	SDL_JoystickClose( joystick );

	// If this is the last active joystick, switch off the joystick event system.
	if( --count == 0 )
	{
		SDL_JoystickEventState( SDL_IGNORE );
	}

	// Make this joystick object invalid.
	id = -1;
	
	return 0;
}


//--------------------------------------------------------------------------------
// Name: getAxis()
// Description:
// 
//--------------------------------------------------------------------------------
int InputJoystick::getAxis( int axis )
{
	return axisState[axis];
}

//--------------------------------------------------------------------------------
// Name: getXAxis()
// Description:
// 
//--------------------------------------------------------------------------------
int InputJoystick::getXAxis()
{
	return getAxis( X_AXIS );
}

//--------------------------------------------------------------------------------
// Name: getYAxis()
// Description:
// 
//--------------------------------------------------------------------------------
int InputJoystick::getYAxis()
{
	return getAxis( Y_AXIS );
}


//--------------------------------------------------------------------------------
// Name: getButton()
// Description:
// 
//--------------------------------------------------------------------------------
int InputJoystick::getButton( int button )
{
	return buttonState[button];
}


//--------------------------------------------------------------------------------
// Name: getLastInputId()
// Description:
// 
//--------------------------------------------------------------------------------
int InputJoystick::getLastInputId()
{
	return lastInputId;
}


//--------------------------------------------------------------------------------
// Name: update()
// Description:
// 
//--------------------------------------------------------------------------------
void InputJoystick::update( SDL_Event *event )
{
	switch( event->type )
	{
		// A joystick axis was moved
		case SDL_JOYAXISMOTION:
		{
			#ifdef DEBUG
			cout << "Joystick(" << ( int )( event->jaxis.which ) << "):  "
				<< "Axis("     << ( int )( event->jaxis.axis  ) << ") "
				<< event->jaxis.value
				<< " Motion" << endl;
			#endif

			if( ( event->jaxis.value >= AXIS_STATE_CENTER_MIN ) &&
			    ( event->jaxis.value <= AXIS_STATE_CENTER_MAX )	   )
				axisState[event->jaxis.axis] =
					AXIS_STATE_CENTER;
			else
				axisState[event->jaxis.axis] =
					( int )( event->jaxis.value );

		} break;

		// A button was just pressed
		case SDL_JOYBUTTONDOWN:
		{
			#ifdef DEBUG
			cout << "Joystick(" << ( int )( event->jbutton.which  ) << "):  "
				<< "Button("   << ( int )( event->jbutton.button )<< ")"
				<< " Down" << endl;
			#endif

			buttonState[event->jbutton.button] = BUTTON_STATE_DOWN;
		} break;

		// A button was just released
		case SDL_JOYBUTTONUP:
		{
			#ifdef DEBUG
			cout << "Joystick(" << ( int )( event->jbutton.which  ) << "):  "
				<< "Button("   << ( int )( event->jbutton.button )<< ")"
				<< " Up" << endl;
			#endif

			buttonState[event->jbutton.button] = BUTTON_STATE_UP;
		} break;
	}
}

