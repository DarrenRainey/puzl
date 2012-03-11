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

#ifndef BLOCK_GRAPHIC
#define BLOCK_GRAPHIC

// INCLUDES ======================================================================
#include <puzl/video/CoreVideoSprite.h>

// DEFINES =======================================================================
#define BLOCK_MODE_CELL		0
#define BLOCK_MODE_ABSOLUTE	1

// TYPES =========================================================================
class BlockGraphic: public CoreVideoSprite
{
public:
	BlockGraphic( CoreVideoImage& videoImage, int width, int height, int attributes );
	//~BlockGraphic( void );
	
	int getMode( void );
	void setMode( int mode );
	
	void draw( CoreVideoImage* destinationImage, int tileIndex, int xPosition, int yPosition );
	void draw( int tileIndex, int xPosition, int yPosition );
	
	void print( char text[], int xPosition, int yPosition );
	
protected:
	int mode;
};

#endif
