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

#ifndef SDL_OGL_AUDIO_SYSTEM
#define SDL_OGL_AUDIO_SYSTEM

// INCLUDES ======================================================================
#include <puzl/audio/CoreAudioSystem.h>
#include <puzl/audio/SdlOglAudioSample.h>

#include "SDL/SDL.h"

#if defined(_WIN64) || defined(_WIN32)
  #include "SDL/SDL_mixer.h"
#elif defined(__APPLE__) || defined(__MACH__)
  #include <SDL_mixer/SDL_mixer.h>
#elif defined(__linux) || defined(__unix) || defined(__posix)
  #include <SDL/SDL_mixer.h>
#else
  #include <SDL/SDL_mixer.h>
#endif

// DEFINES =======================================================================

// TYPES =========================================================================
class SdlOglAudioSystem: public CoreAudioSystem
{
public:
  SdlOglAudioSystem( void );
	~SdlOglAudioSystem( void );

	int initialize( int bitRate, int numberOfChannels, int numberOfBuffers );
	int shutdown( void );
};

#endif
