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
  numberOfKeyboards  = 0;
  numberOfMice       = 0;
  numberOfJoysticks  = 0;

  keyboards = NULL;
  mice      = NULL;
  joysticks = NULL;
}

//--------------------------------------------------------------------------------
CoreInputSystem::~CoreInputSystem( void )
{

}

//--------------------------------------------------------------------------------
int CoreInputSystem::initialize( void )
{
  return 0;
}

//--------------------------------------------------------------------------------
int CoreInputSystem::shutdown( void )
{
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
