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
// AudioSystem.h
// Authors:  Andrew Dieffenbach
// Date:     August 8, 2010
// Description:
// 
//================================================================================

// Watch for multiple inclusions
#ifndef AUDIO_SYSTEM
#define AUDIO_SYSTEM

// INCLUDES ======================================================================

#include "SDL/SDL.h"

#ifdef WINDOWS
	#include "SDL/SDL_mixer.h"
#endif
#ifdef MACOSX
        #include <SDL_mixer/SDL_mixer.h>
#endif
#ifdef LINUX
        #include <SDL/SDL_mixer.h>
#endif


//#include <string>
#include "puzl/audio/AudioSample.h"		// Audio buffer class header

// DEFINES =======================================================================

//using namespace std;

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif

#define MAX_AUDIO_SAMPLES		100;		// Hardcoded number of sounds

// TYPES =========================================================================

// AudioSystem class
// Used as container class for everything to do with audio
class AudioSystem
{
public:
	AudioSystem();
	~AudioSystem();

	int initialize( int bitRate, int numberOfChannels, int numberOfBuffers );
	int shutdown();
	
	//int Play( int id );			// Plays a sound from the pool with a certain ID

private:
	//AudioSample AudioPool[MAX_AUDIO_SAMPLES];// Pool of sounds

};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
