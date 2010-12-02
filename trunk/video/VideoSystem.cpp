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
// VideoSystem.cpp
// Authors:  Andrew Dieffenbach
// Date:     March 28, 2004
// Description:
// NOTE:  This version uses SDL and OpenGL
//
//================================================================================

// INCLUDES ======================================================================

// Add the SDL and OpenGL header files for appropriate OS builds

#include "puzl/video/VideoSystem.h"		// VideoSystem class header file for main video system
//#include "puzl/video/VideoBitmap.h"	// VideoBitmap class header for bitmap surface buffers
//#include "puzl/video/VideoDisplay.h"	// VideoDisplay class header for primary display

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// Name: VideoSystem()
// Description:
// Default constructor
//--------------------------------------------------------------------------------
VideoSystem::VideoSystem()
{
	// Initialize the video system
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		atexit( SDL_Quit );			// INVESTIGATE
	}
}


//--------------------------------------------------------------------------------
// Name: ~VideoSystem()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
VideoSystem::~VideoSystem()
{
	SDL_Quit();					// THIS A GOOD IDEA?
}


