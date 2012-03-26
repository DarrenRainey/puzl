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
#include <puzl/audio/AndroidAudioSample.h>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
AndroidAudioSample::AndroidAudioSample( void ): CoreAudioSample()
{
  
}

//--------------------------------------------------------------------------------
AndroidAudioSample::~AndroidAudioSample( void )
{
  
}

//--------------------------------------------------------------------------------
int AndroidAudioSample::load( string fileName )
{
  CoreAudioSample::load( fileName );

  return 0;
}

//--------------------------------------------------------------------------------
int AndroidAudioSample::play( void )
{
  CoreAudioSample::play();

  return 0;
}

//--------------------------------------------------------------------------------
int AndroidAudioSample::pause( void )
{
  // TODO: Needs to be implemented.
  return CoreAudioSample::pause();
}

//--------------------------------------------------------------------------------
int AndroidAudioSample::stop( void )
{
  CoreAudioSample::stop();

  return 0;
}

//--------------------------------------------------------------------------------
int AndroidAudioSample::getStatus( void )
{
  // TODO: Needs to be implemented.
  return CoreAudioSample::getStatus();
}
