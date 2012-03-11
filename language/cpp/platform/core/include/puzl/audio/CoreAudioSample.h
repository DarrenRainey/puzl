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

#ifndef CORE_AUDIO_SAMPLE
#define CORE_AUDIO_SAMPLE

// INCLUDES ======================================================================
#include <string>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================
class CoreAudioSample
{
public:
  CoreAudioSample( void );
	~CoreAudioSample( void );
	
	virtual int load( string fileName );
	virtual int play( void );
	virtual int pause( void );
	virtual int stop( void );
	virtual int setLoop( bool loop );
	virtual bool getLoop( void );
	virtual int setNumberOfLoops( int numberOfLoops );
	virtual int getStatus( void );

protected:
	int numberOfLoops;
	bool loop;
};

#endif
