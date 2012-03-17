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
#include <puzl/input/CoreInputJoystick.h>

#include <iostream>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================
int CoreInputJoystick::count = 0;

// FUNCTIONS =====================================================================
//--------------------------------------------------------------------------------
CoreInputJoystick::CoreInputJoystick( void ): CoreInputDevice()
{

}

//--------------------------------------------------------------------------------
CoreInputJoystick::~CoreInputJoystick( void )
{
	#ifdef DEBUG
	if( id != -1 )
	{
		cout << "Joystick(" << id << ") was not shutdown!" << endl; 
	}
	#endif
}

//--------------------------------------------------------------------------------
int CoreInputJoystick::initialize( void )
{
	// Increase the reference counter for a 'new' joystick.
	// TODO: Get the unique system-level ID of this joystick.
	id = count++;

	#ifdef DEBUG
	cout << "id " << id;
	#endif

	return 0;
}

//--------------------------------------------------------------------------------
int CoreInputJoystick::shutdown( void )
{
	--count;
	id = -1;
	
	return 0;
}

//--------------------------------------------------------------------------------
int CoreInputJoystick::getAxis( int axis )
{
	return axisState[axis].state;
}

//--------------------------------------------------------------------------------
int CoreInputJoystick::getXAxis( void )
{
	return getAxis( X_AXIS );
}

//--------------------------------------------------------------------------------
int CoreInputJoystick::getYAxis( void )
{
	return getAxis( Y_AXIS );
}

//--------------------------------------------------------------------------------
int CoreInputJoystick::getButton( int button )
{
	return getState( button );
}
