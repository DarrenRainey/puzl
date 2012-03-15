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

#ifndef CORE_INPUT_KEYBOARD
#define CORE_INPUT_KEYBOARD

// INCLUDES ======================================================================
#include <puzl/input/CoreInputDevice.h>

// DEFINES =======================================================================
// English key code aliases
/*
#define KEY_BACKSPACE
#define KEY_TAB
#define KEY_ENTER
#define KEY_ESCAPE
#define KEY_SPACE
#define KEY_QUOTE
#define KEY_MINUS
#define KEY_EQUAL
#define KEY_COMMA
#define KEY_PERIOD
#define KEY_FORWARDSLASH

#define KEY_0
#define KEY_1
#define KEY_2
#define KEY_3
#define KEY_4
#define KEY_5
#define KEY_6
#define KEY_7
#define KEY_8
#define KEY_9

#define KEY_SEMICOLON
#define KEY_LEFTBRACKET
#define KEY_BACKSLASH
#define KEY_RIGHTBRACKET
#define KEY_BACKQUOTE

#define KEY_A
#define KEY_B
#define KEY_C
#define KEY_D
#define KEY_E
#define KEY_F
#define KEY_G
#define KEY_H
#define KEY_I
#define KEY_J
#define KEY_K
#define KEY_L
#define KEY_M
#define KEY_N
#define KEY_O
#define KEY_P
#define KEY_Q
#define KEY_R
#define KEY_S
#define KEY_T
#define KEY_U
#define KEY_V
#define KEY_W
#define KEY_X
#define KEY_Y
#define KEY_Z

#define KEY_KP_0
#define KEY_KP_1
#define KEY_KP_2
#define KEY_KP_3
#define KEY_KP_4
#define KEY_KP_5
#define KEY_KP_6
#define KEY_KP_7
#define KEY_KP_8
#define KEY_KP_9
#define KEY_KP_PERIOD
#define KEY_KP_DIVIDE
#define KEY_KP_MULTIPLY
#define KEY_KP_MINUS
#define KEY_KP_PLUS
#define KEY_KP_ENTER
#define KEY_KP_EQUALS

#define KEY_LEFT
#define KEY_RIGHT
#define KEY_UP
#define KEY_DOWN

#define KEY_INSERT
#define KEY_DELETE
#define KEY_HOME
#define KEY_END
#define KEY_PAGEUP
#define KEY_PAGEDOWN

#define KEY_F1
#define KEY_F2
#define KEY_F3
#define KEY_F4
#define KEY_F5
#define KEY_F6
#define KEY_F7
#define KEY_F8
#define KEY_F9
#define KEY_F10
#define KEY_F11
#define KEY_F12
#define KEY_F13
#define KEY_F14
#define KEY_F15

#define KEY_NUMLOCK
#define KEY_CAPSLOCK
#define KEY_SCROLLOCK
#define KEY_RIGHTSHIFT
#define KEY_LEFTSHIFT
#define KEY_RIGHTCTRL
#define KEY_LEFTCTRL
#define KEY_RIGHTALT
#define KEY_LEFTALT
#define KEY_LEFTWINDOWS
#define KEY_RIGHTWINDOWS

#define KEY_SYSREQ
#define KEY_BREAK
*/

// Key state defines
#define KEY_STATE_UP			  INPUT_STATE_UP
#define KEY_STATE_RELEASED	INPUT_STATE_RELEASED
#define KEY_STATE_DOWN			INPUT_STATE_DOWN
#define KEY_STATE_PRESSED		INPUT_STATE_PRESSED

#define INPUT_TYPE_KEYBOARD_KEY		0

// TYPES =========================================================================
class CoreInputKeyboard: public CoreInputDevice
{
public:
  CoreInputKeyboard( void );
	~CoreInputKeyboard( void );

	virtual bool checkKey( int key );			  // Check if the key is up or down.
	virtual int getKeyState( int key );			// Get current state of a key.
	virtual int getLastInputId( void );
	virtual int getLastKeyPress( void );

	virtual Input** getCurrentKeyEvents( void );
	virtual int getNumberOfCurrentKeyEvents( void );
		
protected:
	Input* keyState;
};

#endif
