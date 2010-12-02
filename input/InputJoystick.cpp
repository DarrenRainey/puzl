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

int InputJoystick::Count = 0;


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
	
	// Make this joystick object invalid initially
	ID = -1;

	// Clear the button states
	for( index = 0; index < NUM_JOYSTICK_BUTTONS; index++ )
		ButtonState[index] = BUTTON_STATE_UP;

	// Clear the axis states
	for( index = 0; index < NUM_JOYSTICK_AXES; index++ )
		AxisState[index] = AXIS_STATE_CENTER;
}


//--------------------------------------------------------------------------------
// Name: ~InputJoystick()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
InputJoystick::~InputJoystick()
{
	#ifdef DEBUG
	if( ID != -1 )
		cout << "Joystick(" << ID << ") was not shutdown!" << endl; 
	#endif
}


//--------------------------------------------------------------------------------
// Name: Initialize()
// Description:
// 
//--------------------------------------------------------------------------------
InputJoystick* InputJoystick::Initialize( void )
{
	// Increase the reference counter for a 'new' joystick
	// Get the unique system-level ID of this joystick
	ID = Count++;

	#ifdef DEBUG
	cout << "ID#" << ID << " ";
	#endif

	// Switch on the joystick event system
	if( Count == 1 )
		SDL_JoystickEventState( SDL_ENABLE );

	// Open this joystick device for SDL
	Joystick = SDL_JoystickOpen( ID );

	// Check if this is a valid joystick; else fill default values
	if( Joystick == NULL )
	{
		#ifdef DEBUG
		cout << "Invalid Joystick(" <<
			ID <<
			")" << endl;
		#endif

		Count--;

		if( Count == 0 )
			SDL_JoystickEventState( SDL_IGNORE );

		return( NULL );
	}
	else
	{
		// Get name of this joystick
		Name = SDL_JoystickName( ID );

		#ifdef DEBUG
		cout << Name << endl;
		#endif
	}

	return( this );
}


//--------------------------------------------------------------------------------
// Name: Shutdown()
// Description:
// 
//--------------------------------------------------------------------------------
int InputJoystick::Shutdown( void )
{
	SDL_JoystickClose( Joystick );

	Count--;

	// If this is the last active joystick, switch off the joystick event system
	if( Count == 0 )
		SDL_JoystickEventState( SDL_IGNORE );

	// Make this joystick object invalid
	ID = -1;
	
	return( 0 );
}


//--------------------------------------------------------------------------------
// Name: GetAxis()
// Description:
// 
//--------------------------------------------------------------------------------
int InputJoystick::GetAxis( int axis )
{
	return( AxisState[axis] );
}

//--------------------------------------------------------------------------------
// Name: GetXAxis()
// Description:
// 
//--------------------------------------------------------------------------------
int InputJoystick::GetXAxis( void )
{
	return( GetAxis( X_AXIS ) );
}

//--------------------------------------------------------------------------------
// Name: GetYAxis()
// Description:
// 
//--------------------------------------------------------------------------------
int InputJoystick::GetYAxis( void )
{
	return( GetAxis( Y_AXIS ) );
}


//--------------------------------------------------------------------------------
// Name: GetButton()
// Description:
// 
//--------------------------------------------------------------------------------
int InputJoystick::GetButton( int button )
{
	return( ButtonState[button] );
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
// Name: Update()
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
				AxisState[event->jaxis.axis] =
					AXIS_STATE_CENTER;
			else
				AxisState[event->jaxis.axis] =
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

			ButtonState[event->jbutton.button] = BUTTON_STATE_DOWN;
		} break;

		// A button was just released
		case SDL_JOYBUTTONUP:
		{
			#ifdef DEBUG
			cout << "Joystick(" << ( int )( event->jbutton.which  ) << "):  "
				<< "Button("   << ( int )( event->jbutton.button )<< ")"
				<< " Up" << endl;
			#endif

			ButtonState[event->jbutton.button] = BUTTON_STATE_UP;
		} break;
	}
}

