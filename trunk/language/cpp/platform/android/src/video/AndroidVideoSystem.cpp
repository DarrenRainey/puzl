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
#include <puzl/video/AndroidVideoSystem.h>
#include <puzl/video/AndroidVideoDisplay.h>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================
//--------------------------------------------------------------------------------
AndroidVideoSystem::AndroidVideoSystem( void ): CoreVideoSystem()
{
  // Initialize the video system.
  cout << "AndroidVideoSystem()" << endl;
}

//--------------------------------------------------------------------------------
AndroidVideoSystem::~AndroidVideoSystem( void )
{
  
}

//--------------------------------------------------------------------------------
int AndroidVideoSystem::initialize( int displayWidth, int displayHeight, int displayAttributes )
{
  cout << "AndroidVideoSystem::initialize()" << endl;
  display = new AndroidVideoDisplay();
  return display->initialize( displayWidth, displayHeight, displayAttributes );
}

//--------------------------------------------------------------------------------
int AndroidVideoSystem::shutdown( void )
{
  display->shutdown();
  delete display;
  return 0;
}
