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

#ifndef CORE_INPUT_JOYSTICK
#define CORE_INPUT_JOYSTICK

// INCLUDES ======================================================================
#include <puzl/input/CoreInputDevice.h>

#include <string>

using namespace std;

// DEFINES =======================================================================
// Button state defines
#ifndef BUTTON_STATE
	#define BUTTON_STATE_UP			   0
	#define BUTTON_STATE_DOWN		   1
#endif

// Axis state defines
#define AXIS_STATE_MIN			    -32768
#define AXIS_STATE_MAX				   32768

#define AXIS_STATE_CENTER_MIN	  -800
#define AXIS_STATE_CENTER			   0
#define AXIS_STATE_CENTER_MAX	   800

// Axis index 'standards'
#define X_AXIS					         0
#define Y_AXIS					         1

// Buffer defines
#define NUM_JOYSTICK_BUTTONS			255
#define NUM_JOYSTICK_AXES			    5
#define JOYSTICK_BUFFER_SIZE			10

// TYPES =========================================================================
class CoreInputJoystick: public CoreInputDevice
{
public:
  CoreInputJoystick( void );
	~CoreInputJoystick( void );

	virtual int initialize( void );       // Initialize this object for use
	virtual int shutdown( void );         // Shut down this object

	virtual int read( void );

	virtual int getAxis( int axis );	    // Get state of an axis (direction-pad)
	virtual int getXAxis( void );         // Get state of the X axis
	virtual int getYAxis( void );	        // Get state of the Y axis

	virtual int getButton( int button );	// Get state of a button
	
	virtual int getLastInputId( void );
	
protected:
	string name;				                  // Name of this joystick device

	int buttonState[NUM_JOYSTICK_BUTTONS];	     // States of joystick buttons
	int axisState[NUM_JOYSTICK_AXES];	           // States of joystick axes

	static int count;
};

#endif
