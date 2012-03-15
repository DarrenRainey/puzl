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
#include <puzl/audio/SdlOglAudioSample.h>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
SdlOglAudioSample::SdlOglAudioSample( void ): CoreAudioSample()
{
	sample  = NULL;
	channel = -1;
}

//--------------------------------------------------------------------------------
SdlOglAudioSample::~SdlOglAudioSample( void )
{
	Mix_HaltChannel( channel );
	Mix_FreeChunk( sample );
}

//--------------------------------------------------------------------------------
int SdlOglAudioSample::load( string fileName )
{
  CoreAudioSample::load( fileName );

	sample = Mix_LoadWAV( fileName.c_str() );
	if( sample == NULL )
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

//--------------------------------------------------------------------------------
int SdlOglAudioSample::play( void )
{
  CoreAudioSample::play();

	channel = Mix_PlayChannel( -1, sample, numberOfLoops );
	if( channel == -1 )
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

//--------------------------------------------------------------------------------
int SdlOglAudioSample::pause( void )
{
  // TODO: Needs to be implemented.
	return CoreAudioSample::pause();
}

//--------------------------------------------------------------------------------
int SdlOglAudioSample::stop( void )
{
  CoreAudioSample::stop();

	return Mix_HaltChannel( channel );
}

//--------------------------------------------------------------------------------
/*int SdlOglAudioSample::setLoop( bool loop )
{
  return CoreAudioSample::setLoop( loop );
}*/

//--------------------------------------------------------------------------------
/*bool SdlOglAudioSample::getLoop()
{
  return CoreAudioSample::getLoop();
}*/

//--------------------------------------------------------------------------------
/*int SdlOglAudioSample::setNumberOfLoops( int numberOfLoops )
{
  return CoreAudioSample::setNumberOfLoops();
}*/

//--------------------------------------------------------------------------------
int SdlOglAudioSample::getStatus( void )
{
  // TODO: Needs to be implemented.
  return CoreAudioSample::getStatus();
}
