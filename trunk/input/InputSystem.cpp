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
// InputSystem.cpp
// Authors:  Andrew Dieffenbach
// Date:     April 12, 2004
// Description:
//
//================================================================================

// INCLUDES ======================================================================

// Add the SDL header files for appropriate OS build
#include <SDL/SDL.h>

#include "puzl/input/InputSystem.h"		// InputSystem class header file for main input system


// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// Name: InputSystem()
// Description:
// Default constructor
//--------------------------------------------------------------------------------
InputSystem::InputSystem()
{
	// Initialize the input system
	// note that for SDL, the input (keyboard/mouse)
	// system is fused with the video system
//	if( !SDL_WasInit( SDL_INIT_VIDEO ) )		// Make sure not to
//		SDL_Init( SDL_INIT_VIDEO );		// initialize twice

	SDL_InitSubSystem( SDL_INIT_JOYSTICK );
}


//--------------------------------------------------------------------------------
// Name: ~InputSystem()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
InputSystem::~InputSystem()
{
	SDL_QuitSubSystem( SDL_INIT_JOYSTICK );

//	if( !SDL_WasInit( SDL_INIT_VIDEO ) )
//		SDL_Quit();					// THIS A GOOD IDEA?
								// For now, No, because
								// input system requires
								// video system
}


//--------------------------------------------------------------------------------
// Name: InputSystem::initialize()
// Description:
// 
//--------------------------------------------------------------------------------
int InputSystem::initialize()
{
	numberOfKeyboards	= 1;			// NOTE Assume (just) one
	numberOfMice		= 1;			// TODO check for this?
	numberOfJoysticks 	= SDL_NumJoysticks();	// 

	int index;
	
	keyboard = new InputKeyboard* [numberOfKeyboards];
	for( index = 0; index < numberOfKeyboards; index++ )
	{
		keyboard[index] = new InputKeyboard();
		keyboard[index]->initialize();
	}
	
	mouse = new InputMouse* [numberOfMice];
	for( index = 0; index < numberOfMice; index++ )
	{
		mouse[index] = new InputMouse();
		mouse[index]->initialize();
	}
	
	joystick = new InputJoystick* [numberOfJoysticks];
	for( index = 0; index < numberOfJoysticks; index++ )
	{
		joystick[index] = new InputJoystick();
		joystick[index]->initialize();
	}
}


//--------------------------------------------------------------------------------
// Name: InputSystem::shutdown()
// Description:
// 
//--------------------------------------------------------------------------------
int InputSystem::shutdown()
{
	int index;
	
	for( index = 0; index < numberOfKeyboards; index++ )
	{
		keyboard[index]->shutdown();
		delete keyboard[index];
	}
	delete [] keyboard;
	
	for( index = 0; index < numberOfMice; index++ )
	{
		mouse[index]->shutdown();
		delete mouse[index];
	}
	delete [] mouse;
	
	for( index = 0; index < numberOfJoysticks; index++ )
	{
		joystick[index]->shutdown();
		delete joystick[index];
	}
	delete [] joystick;
	
	return 0;
}


//--------------------------------------------------------------------------------
// Name: InputSystem::getKeyboards()
// Description:
// 
//--------------------------------------------------------------------------------
InputKeyboard** InputSystem::getKeyboards()
{
	return keyboard;
}


//--------------------------------------------------------------------------------
// Name: InputSystem::getMice()
// Description:
// 
//--------------------------------------------------------------------------------
InputMouse** InputSystem::getMice()
{
	return mouse;
}


//--------------------------------------------------------------------------------
// Name: InputSystem::getJoysticks()
// Description:
// 
//--------------------------------------------------------------------------------
InputJoystick** InputSystem::getJoysticks()
{
	return joystick;
}


//--------------------------------------------------------------------------------
// Name: InputSystem::getNumberOfKeyboards()
// Description:
// 
//--------------------------------------------------------------------------------
int InputSystem::getNumberOfKeyboards()
{
	return numberOfKeyboards;
}


//--------------------------------------------------------------------------------
// Name: InputSystem::getNumberOfMice()
// Description:
// 
//--------------------------------------------------------------------------------
int InputSystem::getNumberOfMice()
{
	return numberOfMice;
}


//--------------------------------------------------------------------------------
// Name: InputSystem::getNumberOfJoysticks()
// Description:
// 
//--------------------------------------------------------------------------------
int InputSystem::getNumberOfJoysticks()
{
	return numberOfJoysticks;
}


//--------------------------------------------------------------------------------
// Name: InputSystem::update()
// Description:
// 
//--------------------------------------------------------------------------------
void InputSystem::update( SDL_Event *event )
{
	switch( event->type )
	{
		// Keyboard
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		{
			keyboard[0]->update( event );	// NOTE Assuming just one keyboard
		} break;

		// Mouse
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		{
			mouse[0]->update( event );	// NOTE Assuming just one mouse
		} break;

		// Joystick
		case SDL_JOYAXISMOTION:
		{
			joystick[event->jaxis.which]->update( event );
		} break;

		case SDL_JOYBALLMOTION:
		{
			joystick[event->jball.which]->update( event );
		} break;

		case SDL_JOYHATMOTION:
		{
			joystick[event->jhat.which]->update( event );
		} break;

		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
		{
			joystick[event->jbutton.which]->update( event );
		} break;
	}
}

//--------------------------------------------------------------------------------
// Name: InputSystem::age()
// Description:
// 
//--------------------------------------------------------------------------------
void InputSystem::age()
{
	int index;
	
	for( index = 0; index < numberOfKeyboards; index++ )
	{
		keyboard[index]->age();
	}
	
	for( index = 0; index < numberOfMice; index++ )
	{
		mouse[index]->age();
	}
	
	for( index = 0; index < numberOfJoysticks; index++ )
	{
		joystick[index]->age();
	}
}


