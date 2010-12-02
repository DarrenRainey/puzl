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
// AudioSample.cpp
// Authors:  Andrew Dieffenbach
// Date:     August 8, 2010
// Description:
// 
//================================================================================

// INCLUDES ======================================================================

#include <puzl/audio/AudioSample.h>		// AudioSample class header file for basic audio buffers

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// Name: AudioSample()
// Description:
// Default constructor
//--------------------------------------------------------------------------------
AudioSample::AudioSample()
{
	sample = NULL;
	channel = -1;
	setLoop( false );
}


//--------------------------------------------------------------------------------
// Name: ~AudioSample()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
AudioSample::~AudioSample()
{
	Mix_HaltChannel( channel );
	Mix_FreeChunk( sample );
}


//--------------------------------------------------------------------------------
// Name: load()
// Description:
// 
//--------------------------------------------------------------------------------
int AudioSample::load( string fileName )
{
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
// Name: play()
// Description:
// 
//--------------------------------------------------------------------------------
int AudioSample::play()
{
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
// Name: pause()
// Description:
// 
//--------------------------------------------------------------------------------
int AudioSample::pause()
{
	return -1;
}


//--------------------------------------------------------------------------------
// Name: stop()
// Description:
// 
//--------------------------------------------------------------------------------
int AudioSample::stop()
{
	Mix_HaltChannel( channel );
	
	return 0;
}


//--------------------------------------------------------------------------------
// Name: setLoop()
// Description:
// 
//--------------------------------------------------------------------------------
int AudioSample::setLoop( bool set )
{
	this->loop = set;
	
	if( set )
	{
		numberOfLoops = 0;
	}
	else
	{
		numberOfLoops = -1;
	}
}


//--------------------------------------------------------------------------------
// Name: setLoop()
// Description:
// 
//--------------------------------------------------------------------------------
bool AudioSample::getLoop()
{
	return loop;
}

//--------------------------------------------------------------------------------
// Name: setNumberOfLoops()
// Description:
// 
//--------------------------------------------------------------------------------
int AudioSample::setNumberOfLoops( int numberOfLoops )
{
	this->numberOfLoops = numberOfLoops;
	
	if( numberOfLoops == 0 )
	{
		loop = false;
	}
	else
	{
		loop = true;
	}
}


//--------------------------------------------------------------------------------
// Name: getStatus()
// Description:
// 
//--------------------------------------------------------------------------------
int AudioSample::getStatus()
{
	return -1;
}
