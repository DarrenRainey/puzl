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
// InputMouse.h
// Authors:  Andrew Dieffenbach
// Date:     April 20, 2004
// Description:
//
//================================================================================

// Watch for multiple inclusions
#ifndef INPUT_MOUSE
#define INPUT_MOUSE

// INCLUDES ======================================================================

// Add the SDL header files for appropriate OS build
#include <SDL/SDL.h>

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

#include "puzl/input/InputDevice.h"

// DEFINES =======================================================================

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

// Buffer defines
#define NUM_MOUSE_BUTTONS			255		// Hardcoded! (within SDL)
#define MOUSE_BUFFER_SIZE			7		// Five fingers and two directions?

#define LOCK_STATE_OFF				0
#define LOCK_STATE_START			-1
#define LOCK_STATE_ON				1

// TYPES =========================================================================

// InputMouse class
class InputMouse : public InputDevice
{
public:
	InputMouse();
	~InputMouse();

	int Read( void );

	int GetXPosition( void );
	int GetYPosition( void );

	int GetXDelta( void );
	int GetYDelta( void );
	
	int ClearDeltas( void );

	int GetButton( int button );
	int getLastInputId();
	
	void SetLock( bool state );
	int GetLock( void );
	
	void Warp( int x, int y );
	
private:
	void update( SDL_Event *event );			// Update the state of mouse

	int XPosition;
	int YPosition;
	int XDelta;
	int YDelta;

	int Lock;
	bool doWarp;

	int ButtonState[NUM_MOUSE_BUTTONS];		// States of mouse buttons

	SDL_Event EventBuffer[MOUSE_BUFFER_SIZE];	// Buffers mouse events

	friend class InputSystem;				// InputSys is omniscent of InputMouse's data
};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
