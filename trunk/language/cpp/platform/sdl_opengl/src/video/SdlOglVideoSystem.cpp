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
#include <puzl/video/SdlOglVideoSystem.h>
#include <puzl/video/SdlOglVideoDisplay.h>

#include <SDL/SDL.h>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================
//--------------------------------------------------------------------------------
SdlOglVideoSystem::SdlOglVideoSystem( void ): CoreVideoSystem()
{
	// Initialize the video system.
  cout << "SdlOglVideoSystem()" << endl;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
	  cout << "Failed to initialize video system" << endl;
		atexit( SDL_Quit );
	}
}

//--------------------------------------------------------------------------------
SdlOglVideoSystem::~SdlOglVideoSystem( void )
{
	SDL_Quit();
}

//--------------------------------------------------------------------------------
int SdlOglVideoSystem::initialize( int displayWidth, int displayHeight, int displayAttributes )
{
  cout << "SdlOglVideoSystem::initialize()" << endl;
  display = new SdlOglVideoDisplay();
  return display->initialize( displayWidth, displayHeight, displayAttributes );
}

//--------------------------------------------------------------------------------
int SdlOglVideoSystem::shutdown( void )
{
  display->shutdown();
  delete display;
  return 0;
}
