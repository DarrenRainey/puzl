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

#ifndef CORE_INPUT_DEVICE
#define CORE_INPUT_DEVICE

// INCLUDES ======================================================================

// DEFINES =======================================================================
// Input state defines
#define INPUT_STATE_UP			   0		// 00b
#define INPUT_STATE_RELEASED	 2		// 10b
#define INPUT_STATE_DOWN		   1		// 01b
#define INPUT_STATE_PRESSED		 3		// 11b

// TYPES =========================================================================
struct Input
{
	int state;
	int type;
	int id;
};

class CoreInputDevice
{
public:
  CoreInputDevice( void );
	~CoreInputDevice( void );

	virtual int initialize( void );
	virtual int shutdown( void );
	
 	bool check( int inputId );
	int getState( int inputId );
	virtual int getLastInputId( void );

	virtual void age( void );
		
protected:
	int id;                         // ID number of this device.
	Input** input;
	
	Input** stateChange;
	int stateChangeBufferSize;
	int numberOfStateChanges;

	int lastInputId;
	int lastInputType;
};

#endif
