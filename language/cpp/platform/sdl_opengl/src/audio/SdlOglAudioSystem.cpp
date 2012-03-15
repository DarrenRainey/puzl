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
#include <puzl/audio/SdlOglAudioSystem.h>

#include <iostream>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
SdlOglAudioSystem::SdlOglAudioSystem( void ): CoreAudioSystem()
{
	if( SDL_InitSubSystem( SDL_INIT_AUDIO ) != 0 )
	{
		cout << "Error: Unable to set up sound system." << endl;
		
		SDL_QuitSubSystem( SDL_INIT_AUDIO ); // TODO: Needed?
		Mix_CloseAudio();
	}
}

//--------------------------------------------------------------------------------
SdlOglAudioSystem::~SdlOglAudioSystem( void )
{
	SDL_QuitSubSystem( SDL_INIT_AUDIO );
	Mix_CloseAudio();
}

//--------------------------------------------------------------------------------
int SdlOglAudioSystem::initialize( int bitRate, int numberOfChannels, int numberOfBuffers )
{
  if( CoreAudioSystem::initialize( bitRate, numberOfChannels, numberOfBuffers ) < 0 )
  {
    return -1;
  }

	if( Mix_OpenAudio( bitRate, AUDIO_S16SYS, numberOfChannels, numberOfBuffers ) != 0 )
	{
		cout << "Error: Unable to set up sound system mixer." << endl;
		return -1;
	}
	
	return 0;
}

//--------------------------------------------------------------------------------
int SdlOglAudioSystem::shutdown( void )
{
	return CoreAudioSystem::shutdown();
}
