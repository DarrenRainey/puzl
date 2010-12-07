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
// VideoSystem.h
// Authors:  Andrew Dieffenbach
// Date:     March 28, 2004
// Description:
// NOTE:  This version uses SDL and OpenGL
//
//================================================================================

// Watch for multiple inclusions
#ifndef VIDEO_SYSTEM
#define VIDEO_SYSTEM

// INCLUDES ======================================================================

// Add the SDL and OpenGL header files for appropriate OS builds
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#ifdef WINDOWS
	#include <windows.h>
	#include <SDL/SDL_image.h>
	//#include <GL/gl.h>
	//#include <GL/glu.h>
#endif
#ifdef MACOSX
	#include <SDL_image/SDL_image.h>
	//#include <OpenGL/gl.h>
	//#include <OpenGL/glu.h>
#endif
#ifdef LINUX
	#include <SDL/SDL_image.h>
	//#include <GL/gl.h>
	//#include <GL/glu.h>
#endif

//#include <string>
//#include "puzl/video/VideoObject.h"		// VideoObject header file
#include "puzl/video/VideoDisplay.h"		// VideoDisplay header file
#include "puzl/video/VideoImage.h"		// VideoImage header file
#include "puzl/video/VideoSprite.h"		// VideoSprite header file
#include "puzl/video/BlockGraphic.h"
#include "puzl/video/CharacterGraphic.h"


// DEFINES =======================================================================

//using namespace std;

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif

// TYPES =========================================================================

// VideoSystemtem class
// Used as container class for everything to do with video/graphics
class VideoSystem
{
public:
	VideoSystem();
	~VideoSystem();
	
	int initialize( int displayWidth, int displayHeight, int displayAttributes );
	int shutdown();
	
	VideoDisplay* getDisplay();
	
protected:
	VideoDisplay* display;		// Main video display

private:
};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
