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
// GameShell.h
// Authors:  Andrew Dieffenbach
// Date:     August 8, 2010
// Description:
// 
// 
// 
//================================================================================

// Watch for multiple inclusions
#ifndef GAME_SHELL_H
#define GAME_SHELL_H

// INCLUDES ======================================================================

// Add the SDL and OpenGL header files for appropriate OS builds
#include <SDL/SDL.h>

#ifdef WINDOWS
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif
#ifdef MACOSX
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#endif
#ifdef LINUX
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include "puzl/video/VideoSystem.h"		// VideoSystem header file
//#include "puzl/audio/AudioSystem.h"		// AudioSystem header file
#include "puzl/input/InputSystem.h"		// InputSystem header file

#include <string>		// Standard string class
#include <iostream>		// Standard stream class
#include <sstream>		// Standard string stream class
//#include <vector>		// Standard vector class
#include <time.h>

// DEFINES =======================================================================

using namespace std;

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif

// TYPES =========================================================================
class GameShell
{
	
public:
	GameShell();
	~GameShell();
	
	int run();
	
protected:
	VideoSystem* videoSystem;		// Video system object
	//AudioSystem* audioSystem;		// Audio system object
	InputSystem* inputSystem;		// Input system object

	VideoDisplay* display;			// Main video display

	InputKeyboard** keyboards;		// Keyboard object
	InputKeyboard* keyboard;
	
	//InputMouse** mice;			// Mouse object
	//InputJoystick** joysticks;		// Joystick objects (maximum)

	//int numberOfNetwork;			// Number of network client/players

	int screenWidth;
	int screenHeight;
	
	bool quit;				// Program terminator flag
	
	virtual int initializeVideo();
	virtual int shutdownVideo();
	virtual int releaseVideo();
	virtual int reloadVideo();

	virtual int initializeInput();
	virtual int shutdownInput();
	
	virtual int initializeAudio();
	virtual int shutdownAudio();
	
	void setCaption( string caption );
	void setIcon( string filePath );
	
private:
	unsigned int nowTime;
	unsigned int lastTime;
	unsigned int nextTime;
	
	int initialize();
	int shutdown();
	
	virtual void loop() = 0;
	virtual void draw() = 0;
	
	int updateSystem();
};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
