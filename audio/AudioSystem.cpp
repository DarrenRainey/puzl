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
// AudioSystem.cpp
// Authors:  Andrew Dieffenbach
// Date:     August 8, 2010
// Description:
// 
//================================================================================

// INCLUDES ======================================================================

#include <cstdlib>

#include "puzl/audio/AudioSystem.h"		// AudioSystem class header file for main audio system
//#include "puzl/audio/AudioSample.h"	// Audio buffer class header


// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// Name: AudioSystem()
// Description:
// Default constructor
//--------------------------------------------------------------------------------
AudioSystem::AudioSystem()
{
	if( SDL_InitSubSystem( SDL_INIT_AUDIO ) != 0 )
	{
		cout << "Error: Unable to set up sound system." << endl;
		
		SDL_QuitSubSystem( SDL_INIT_AUDIO );
		Mix_CloseAudio();
	}
}


//--------------------------------------------------------------------------------
// Name: ~AudioSystem()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
AudioSystem::~AudioSystem()
{
	SDL_QuitSubSystem( SDL_INIT_AUDIO );
	Mix_CloseAudio();
}


//--------------------------------------------------------------------------------
// Name: AudioSystem::initialize()
// Description:
// 
//--------------------------------------------------------------------------------
int AudioSystem::initialize( int bitRate, int numberOfChannels, int numberOfBuffers )
{
	if( Mix_OpenAudio( bitRate, AUDIO_S16SYS, numberOfChannels, numberOfBuffers ) != 0 )
	{
		cout << "Error: Unable to set up sound system mixer." << endl;
		return -1;
	}
	
	return 0;
}


//--------------------------------------------------------------------------------
// Name: AudioSystem::shutdown()
// Description:
// 
//--------------------------------------------------------------------------------
int AudioSystem::shutdown()
{
	
}


