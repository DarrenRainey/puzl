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
#include <puzl/input/CoreInputSystem.h>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================
//--------------------------------------------------------------------------------
CoreInputSystem::CoreInputSystem( void )
{

}

//--------------------------------------------------------------------------------
CoreInputSystem::~CoreInputSystem( void )
{

}

//--------------------------------------------------------------------------------
int CoreInputSystem::initialize( void )
{
	numberOfKeyboards	= 1;			// NOTE Assume (just) one
	numberOfMice		  = 1;			// TODO check for this?
	numberOfJoysticks = 0;
	
	int index;

	keyboards = new CoreInputKeyboard*[numberOfKeyboards];
	for( index = 0; index < numberOfKeyboards; index++ )
	{
		keyboards[index] = new CoreInputKeyboard();
		keyboards[index]->initialize();
	}
	
	mice = new CoreInputMouse*[numberOfMice];
	for( index = 0; index < numberOfMice; index++ )
	{
		mice[index] = new CoreInputMouse();
		mice[index]->initialize();
	}
	
	joysticks = new CoreInputJoystick*[numberOfJoysticks];
	for( index = 0; index < numberOfJoysticks; index++ )
	{
		joysticks[index] = new CoreInputJoystick();
		joysticks[index]->initialize();
	}
}

//--------------------------------------------------------------------------------
int CoreInputSystem::shutdown( void )
{
	int index;

	for( index = 0; index < numberOfKeyboards; index++ )
	{
		keyboards[index]->shutdown();
		delete keyboards[index];
	}
	delete [] keyboards;
	
	for( index = 0; index < numberOfMice; index++ )
	{
	  mice[index]->shutdown();
		delete mice[index];
	}
	delete [] mice;
	
	for( index = 0; index < numberOfJoysticks; index++ )
	{
		joysticks[index]->shutdown();
		delete joysticks[index];
	}
	delete [] joysticks;

	return 0;
}

//--------------------------------------------------------------------------------
CoreInputKeyboard** CoreInputSystem::getKeyboards( void )
{
	return keyboards;
}

//--------------------------------------------------------------------------------
CoreInputMouse** CoreInputSystem::getMice( void )
{
	return mice;
}

//--------------------------------------------------------------------------------
CoreInputJoystick** CoreInputSystem::getJoysticks( void )
{
	return joysticks;
}

//--------------------------------------------------------------------------------
int CoreInputSystem::getNumberOfKeyboards( void )
{
	return numberOfKeyboards;
}

//--------------------------------------------------------------------------------
int CoreInputSystem::getNumberOfMice( void )
{
	return numberOfMice;
}

//--------------------------------------------------------------------------------
int CoreInputSystem::getNumberOfJoysticks( void )
{
	return numberOfJoysticks;
}

//--------------------------------------------------------------------------------
void CoreInputSystem::age( void )
{
	int index;
	
	for( index = 0; index < numberOfKeyboards; index++ )
	{
		keyboards[index]->age();
	}
	
	for( index = 0; index < numberOfMice; index++ )
	{
		mice[index]->age();
	}
	
	for( index = 0; index < numberOfJoysticks; index++ )
	{
		joysticks[index]->age();
	}
}
