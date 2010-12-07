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
// InputSystem.h
// Authors:  Andrew Dieffenbach
// Date:     April 12, 2004
// Description:
//
//================================================================================

// Watch for multiple inclusions
#ifndef INPUT_SYS
#define INPUT_SYS

// INCLUDES ======================================================================

// Add the SDL header files for appropriate OS build
#include <SDL/SDL.h>

//#include <string>
#include "puzl/input/InputDevice.h"	// InputDevice header file
#include "puzl/input/InputKeyboard.h"	// InputKeyboard header file
#include "puzl/input/InputMouse.h"	// InputMouse header file
#include "puzl/input/InputJoystick.h"	// InputJoystick header file

// DEFINES =======================================================================

//using namespace std;

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif

// TYPES =========================================================================

// InputSystem class
// Used as container class for everything to do with device input
class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	int initialize();
	int shutdown();
	
	InputKeyboard** getKeyboards();
	InputMouse** getMice();
	InputJoystick** getJoysticks();
	
	void update( SDL_Event *event );
	void age();
	
	int getNumberOfKeyboards();
	int getNumberOfMice();
	int getNumberOfJoysticks();

protected:
	InputKeyboard** keyboard;	// Keyboard object
	InputMouse** mouse;		// Mouse object
	InputJoystick** joystick;	// Joystick objects (maximum)
	
	int numberOfKeyboards;		// NOTE: Assuming only one keyboard
	int numberOfMice;		// NOTE: Assuming only one mouse
	int numberOfJoysticks;		// Actual number of joysticks found
private:

};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
