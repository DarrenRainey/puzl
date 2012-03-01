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
// AudioSample.h
// Authors:  Andrew Dieffenbach
// Date:     August 8, 2010
// Description:
// 
//================================================================================

// Watch for multiple inclusions
#ifndef AUDIO_SAMPLE
#define AUDIO_SAMPLE

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

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

// DEFINES =======================================================================

using namespace std;

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif

// TYPES =========================================================================

// AudioSample class for basic audio buffers
class AudioSample
{
public:
	AudioSample();
	~AudioSample();
	
	int load( string fileName );
	int play();
	int pause();
	int stop();
	int setLoop( bool set );
	bool getLoop();
	int setNumberOfLoops( int numberOfLoops );
	int getStatus();

private:
	Mix_Chunk *sample;
	int channel;
	int numberOfLoops;
	bool loop;
	
};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
