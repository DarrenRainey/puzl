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
// InputKeyboard.h
// Authors:  Andrew Dieffenbach
// Date:     April 20, 2004
// Description:
//
//================================================================================

// Watch for multiple inclusions
#ifndef INPUT_KEYBOARD
#define INPUT_KEYBOARD

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

// English key code aliases
#define KEY_BACKSPACE			SDLK_BACKSPACE
#define KEY_TAB				SDLK_TAB
#define KEY_ENTER			SDLK_RETURN
#define KEY_ESCAPE			SDLK_ESCAPE
#define KEY_SPACE			SDLK_SPACE
#define KEY_QUOTE			SDLK_QUOTE
#define KEY_MINUS			SDLK_MINUS
#define KEY_EQUAL			SDLK_EQUALS
#define KEY_COMMA			SDLK_COMMA
#define KEY_PERIOD			SDLK_PERIOD
#define KEY_FORWARDSLASH		SDLK_SLASH

#define KEY_0				SDLK_0
#define KEY_1				SDLK_1
#define KEY_2				SDLK_2
#define KEY_3				SDLK_3
#define KEY_4				SDLK_4
#define KEY_5				SDLK_5
#define KEY_6				SDLK_6
#define KEY_7				SDLK_7
#define KEY_8				SDLK_8
#define KEY_9				SDLK_9

#define KEY_SEMICOLON			SDLK_SEMICOLON
#define KEY_LEFTBRACKET			SDLK_LEFTBRACKET
#define KEY_BACKSLASH			SDLK_BACKSLASH
#define KEY_RIGHTBRACKET		SDLK_RIGHTBRACKET
#define KEY_BACKQUOTE			SDLK_BACKQUOTE

#define KEY_A				SDLK_a
#define KEY_B				SDLK_b
#define KEY_C				SDLK_c
#define KEY_D				SDLK_d
#define KEY_E				SDLK_e
#define KEY_F				SDLK_f
#define KEY_G				SDLK_g
#define KEY_H				SDLK_h
#define KEY_I				SDLK_i
#define KEY_J				SDLK_j
#define KEY_K				SDLK_k
#define KEY_L				SDLK_l
#define KEY_M				SDLK_m
#define KEY_N				SDLK_n
#define KEY_O				SDLK_o
#define KEY_P				SDLK_p
#define KEY_Q				SDLK_q
#define KEY_R				SDLK_r
#define KEY_S				SDLK_s
#define KEY_T				SDLK_t
#define KEY_U				SDLK_u
#define KEY_V				SDLK_v
#define KEY_W				SDLK_w
#define KEY_X				SDLK_x
#define KEY_Y				SDLK_y
#define KEY_Z				SDLK_z

#define KEY_KP_0			SDLK_KP0
#define KEY_KP_1			SDLK_KP1
#define KEY_KP_2			SDLK_KP2
#define KEY_KP_3			SDLK_KP3
#define KEY_KP_4			SDLK_KP4
#define KEY_KP_5			SDLK_KP5
#define KEY_KP_6			SDLK_KP6
#define KEY_KP_7			SDLK_KP7
#define KEY_KP_8			SDLK_KP8
#define KEY_KP_9			SDLK_KP9
#define KEY_KP_PERIOD			SDLK_KP_PERIOD
#define KEY_KP_DIVIDE			SDLK_KP_DIVIDE
#define KEY_KP_MULTIPLY			SDLK_KP_MULTIPLY
#define KEY_KP_MINUS			SDLK_KP_MINUS
#define KEY_KP_PLUS			SDLK_KP_PLUS
#define KEY_KP_ENTER			SDLK_KP_ENTER
#define KEY_KP_EQUALS			SDLK_KP_EQUALS

#define KEY_LEFT			SDLK_LEFT
#define KEY_RIGHT			SDLK_RIGHT
#define KEY_UP				SDLK_UP
#define KEY_DOWN			SDLK_DOWN

#define KEY_INSERT			SDLK_INSERT
#define KEY_DELETE			SDLK_DELETE
#define KEY_HOME			SDLK_HOME
#define KEY_END				SDLK_END
#define KEY_PAGEUP			SDLK_PAGEUP
#define KEY_PAGEDOWN			SDLK_PAGEDOWN

#define KEY_F1				SDLK_F1
#define KEY_F2				SDLK_F2
#define KEY_F3				SDLK_F3
#define KEY_F4				SDLK_F4
#define KEY_F5				SDLK_F5
#define KEY_F6				SDLK_F6
#define KEY_F7				SDLK_F7
#define KEY_F8				SDLK_F8
#define KEY_F9				SDLK_F9
#define KEY_F10				SDLK_F10
#define KEY_F11				SDLK_F11
#define KEY_F12				SDLK_F12
#define KEY_F13				SDLK_F13
#define KEY_F14				SDLK_F14
#define KEY_F15				SDLK_F15

#define KEY_NUMLOCK			SDLK_NUMLOCK
#define KEY_CAPSLOCK			SDLK_CAPSLOCK
#define KEY_SCROLLOCK			SDLK_SCROLLOCK
#define KEY_RIGHTSHIFT			SDLK_RSHIFT
#define KEY_LEFTSHIFT			SDLK_LSHIFT
#define KEY_RIGHTCTRL			SDLK_RCTRL
#define KEY_LEFTCTRL			SDLK_LCTRL
#define KEY_RIGHTALT			SDLK_RALT
#define KEY_LEFTALT			SDLK_LALT
#define KEY_LEFTWINDOWS			SDLK_LSUPER	/* Left "Windows" key */
#define KEY_RIGHTWINDOWS		SDLK_RSUPER	/* Right "Windows" key */

#define KEY_SYSREQ			SDLK_SYSREQ
#define KEY_BREAK			SDLK_BREAK

// Key state defines
#define KEY_STATE_UP			INPUT_STATE_UP
#define KEY_STATE_RELEASED		INPUT_STATE_RELEASED
#define KEY_STATE_DOWN			INPUT_STATE_DOWN
#define KEY_STATE_PRESSED		INPUT_STATE_PRESSED

#define INPUT_TYPE_KEYBOARD_KEY		0

// Buffer defines
#define NUM_KEY_CODES			322		// Number of possible key codes (SDL)

// TYPES =========================================================================

// InputKeyboard class
class InputKeyboard : public InputDevice
{
public:
	InputKeyboard();
	~InputKeyboard();

	bool checkKey( int key );			// Check if the key is up or down.
	int getKeyState( int key );			// Get current state of a key.
	int getLastInputId();
	int getLastKeyPress();
	Input** getCurrentKeyEvents();
	int getNumberOfCurrentKeyEvents();
		
private:
	void update( SDL_Event *event );		// Update the state of keyboard
	Input keyState[NUM_KEY_CODES];

	friend class InputSystem;			// InputSys is omniscent of InputKeyboard's data
};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
