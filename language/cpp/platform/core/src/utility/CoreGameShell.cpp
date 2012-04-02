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
#include <puzl/utility/CoreGameShell.h>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

// ===============================================================================
//--------------------------------------------------------------------------------
CoreGameShell::CoreGameShell( const GameShellSettings& gameShellSettings )
{
	this->gameShellSettings = gameShellSettings;
  
	inputSystem = NULL;
  videoSystem = NULL;
	audioSystem = NULL;

	display   = NULL;

	keyboards = NULL;
  keyboard  = NULL;
  
	mice      = NULL;
	joysticks = NULL;
	
	quit = false;
}

//--------------------------------------------------------------------------------
CoreGameShell::~CoreGameShell( void )
{

}

//--------------------------------------------------------------------------------
void CoreGameShell::shellLoop( void )
{
  
}

//--------------------------------------------------------------------------------
int CoreGameShell::initialize( void )
{
  return 0;
}

//--------------------------------------------------------------------------------
int CoreGameShell::shutdown( void )
{
  return 0;
}

//--------------------------------------------------------------------------------
void CoreGameShell::loop( void )
{

}

//--------------------------------------------------------------------------------
void CoreGameShell::draw( const float& interpolation )
{

}

//--------------------------------------------------------------------------------
int CoreGameShell::run( void )
{
  cout << "CoreGameShell::run()" << endl;
  shellInitialize();
  shellLoop();
  return shellShutdown();
}

//--------------------------------------------------------------------------------
int CoreGameShell::shellInitialize( void )
{
  cout << "CoreGameShell::shellInitialize()" << endl;
  return initialize();
}

//--------------------------------------------------------------------------------
int CoreGameShell::releaseVideo( void )
{
	return 0;
}

//--------------------------------------------------------------------------------
int CoreGameShell::reloadVideo( void )
{
  return 0;
}

//--------------------------------------------------------------------------------
int CoreGameShell::shellShutdown( void )
{
  shutdown();

  return 0;
}

//--------------------------------------------------------------------------------
void CoreGameShell::setCaption( string caption )
{
  this->caption = caption;
}

//--------------------------------------------------------------------------------
void CoreGameShell::setIcon( string iconFilename )
{
  this->iconFilename = iconFilename;
}
