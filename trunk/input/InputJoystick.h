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
// InputJoystick.h
// Authors:  Andrew Dieffenbach
// Date:     May 9, 2004
// Description:
//
//================================================================================

// Watch for multiple inclusions
#ifndef INPUT_JOYSTICK
#define INPUT_JOYSTICK

// INCLUDES ======================================================================

// Add the SDL header files for appropriate OS build
#include <SDL/SDL.h>

#ifdef DEBUG
#include <iostream>
#endif

#include <string>

#include "puzl/input/InputDevice.h"

// DEFINES =======================================================================

using namespace std;

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif

// Button state defines
#ifndef BUTTON_STATE
	#define BUTTON_STATE_UP			0
	#define BUTTON_STATE_DOWN		1
#endif

// Axis state defines
#define AXIS_STATE_MIN			       -32768
#define AXIS_STATE_MAX				32768

#define AXIS_STATE_CENTER_MIN		       -800
#define AXIS_STATE_CENTER			0
#define AXIS_STATE_CENTER_MAX			800

// Axis index 'standards'
#define X_AXIS					0
#define Y_AXIS					1

// Buffer defines
#define NUM_JOYSTICK_BUTTONS			255		// Hardcoded! (within SDL)
#define NUM_JOYSTICK_AXES			5		// ???
#define JOYSTICK_BUFFER_SIZE			10		// Ten fingers?


// TYPES =========================================================================

// InputJoystick class for joystick input
class InputJoystick : public InputDevice
{
public:
	InputJoystick();
	~InputJoystick();

	InputJoystick* Initialize( void );	// Initialize this object for use
	int Shutdown( void );			// Shut down this object

	int Read( void );

	int GetAxis( int axis );		// Get state of an axis (direction-pad)
	int GetXAxis( void );			// Get state of the X axis
	int GetYAxis( void );			// Get state of the Y axis

	int GetButton( int button );		// Get state of a button
	
	int getLastInputId();
	
private:
	void update( SDL_Event *event  );	// Update the state of joystick

	int ID;					// ID number of this joystick device
						// on the current system

	string Name;				// Name of this joystick device

	int ButtonState[NUM_JOYSTICK_BUTTONS];	// States of joystick buttons
	int AxisState[NUM_JOYSTICK_AXES];	// States of joystick axes

	SDL_Event EventBuffer[JOYSTICK_BUFFER_SIZE];// Buffers joystick events

	SDL_Joystick* Joystick;			// Joystick device object (SDL)

	static int Count;

	friend class InputSystem;		// InputSys is omniscent of InputJoystick's data
};


// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
