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
  #define BUTTON_STATE_UP        INPUT_STATE_UP
  #define BUTTON_STATE_RELEASED  INPUT_STATE_RELEASED
  #define BUTTON_STATE_DOWN      INPUT_STATE_DOWN
  #define BUTTON_STATE_PRESSED   INPUT_STATE_PRESSED
#endif

#define INPUT_TYPE_JOYSTICK_BUTTON   INPUT_TYPE_BOOLEAN
#define INPUT_TYPE_JOYSTICK_AXIS     INPUT_TYPE_AXIS

// Axis state defines
#ifndef AXIS_STATE
  #define AXIS_STATE_UP        INPUT_STATE_UP
  #define AXIS_STATE_RELEASED  INPUT_STATE_RELEASED
  #define AXIS_STATE_DOWN      INPUT_STATE_DOWN
  #define AXIS_STATE_PRESSED   INPUT_STATE_PRESSED
#endif

#define AXIS_VALUE_MIN			    -32768
#define AXIS_VALUE_MAX				   32768

#define AXIS_CENTER_VALUE_MIN	  -800
#define AXIS_CENTER_VALUE_MID    0
#define AXIS_CENTER_VALUE_MAX	   800

// Axis index 'standards'
#define X_AXIS					         0
#define Y_AXIS					         1

// TYPES =========================================================================
class CoreInputJoystick: public CoreInputDevice
{
public:
  CoreInputJoystick( void );
	~CoreInputJoystick( void );

	virtual int initialize( void );       // Initialize this object for use
	virtual int shutdown( void );         // Shut down this object

	virtual int getAxisState( int axis );	    // Get state of an axis (direction-pad)
	virtual int getXAxisState( void );         // Get state of the X axis
	virtual int getYAxisState( void );	        // Get state of the Y axis

	virtual int getAxisValue( int axis );
  virtual int getXAxisValue( void );
  virtual int getYAxisValue( void );

	virtual int getButtonState( int button );	// Get state of a button
	virtual bool checkButton( int button );
	
protected:
	string name;				                  // Name of this joystick device

	Input* buttonState;
	Input* axisState;

	int axisStateInputOffset;

	static int count;
};

#endif
