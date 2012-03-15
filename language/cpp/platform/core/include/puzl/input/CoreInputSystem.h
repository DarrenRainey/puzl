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

#ifndef CORE_INPUT_SYS
#define CORE_INPUT_SYS

// INCLUDES ======================================================================
#include <puzl/input/CoreInputDevice.h>
#include <puzl/input/CoreInputKeyboard.h>
#include <puzl/input/CoreInputMouse.h>
#include <puzl/input/CoreInputJoystick.h>

// DEFINES =======================================================================

// TYPES =========================================================================
class CoreInputSystem
{
public:
  CoreInputSystem( void );
	~CoreInputSystem( void );

	virtual int initialize( void );
	virtual int shutdown( void );

	CoreInputKeyboard** getKeyboards( void );
	CoreInputMouse** getMice( void );
	CoreInputJoystick** getJoysticks( void );
	
	virtual int getNumberOfKeyboards( void );
	virtual int getNumberOfMice( void );
	virtual int getNumberOfJoysticks( void );

protected:
	virtual void age( void );

	CoreInputKeyboard** keyboards;
	CoreInputMouse** mice;
	CoreInputJoystick** joysticks;
	
	int numberOfKeyboards;
	int numberOfMice;
	int numberOfJoysticks;

	friend class CoreGameShell;
};

#endif
