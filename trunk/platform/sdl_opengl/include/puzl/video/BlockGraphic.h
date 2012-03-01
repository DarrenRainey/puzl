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
// BlockGraphic.h
// Authors:  Andrew Dieffenbach
// Date:     September 03, 2010
// Description:
// 
// 
//================================================================================

// Watch for multiple inclusions
#ifndef BLOCK_GRAPHIC
#define BLOCK_GRAPHIC

// INCLUDES ======================================================================

#include "puzl/video/VideoSprite.h"		// VideoSprite header file

// DEFINES =======================================================================

#define BLOCK_MODE_CELL		0
#define BLOCK_MODE_ABSOLUTE	1

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif

// TYPES =========================================================================

// BlockGraphic class
class BlockGraphic : public VideoSprite
{
public:
	//BlockGraphic();
	BlockGraphic( VideoImage &videoImage, int width, int height, int attributes );
	//~BlockGraphic();
	
	int getMode();
	void setMode( int mode );
	
	void draw( VideoImage* destinationImage, int tileIndex, int xPosition, int yPosition );
	void draw( int tileIndex, int xPosition, int yPosition );
	
	void print( char text[], int xPosition, int yPosition );
	
protected:
	int mode;
};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
