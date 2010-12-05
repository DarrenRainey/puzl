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
// BlockGraphic.cpp
// Authors:  Andrew Dieffenbach
// Date:     September 03, 2010
// Description:
// 
// 
//================================================================================

// INCLUDES ======================================================================

#include "BlockGraphic.h"		// BlockGraphic header file

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// Name: BlockGraphic::BlockGraphic()
// Description:
// Constructor
//--------------------------------------------------------------------------------
BlockGraphic::BlockGraphic( VideoImage &videoImage, int width, int height, int attributes ) :
VideoSprite( videoImage,
	     width, height,
	     ( videoImage.getRealWidth() / ( width + 1 ) ) * ( videoImage.getRealHeight() / ( height + 1 ) ),
	     attributes )
{
	// TODO: Figure out a way not to have to recalculate this?
	int tileWidth = videoImage.getRealWidth() / ( width + 1 );
	int tileHeight = videoImage.getRealHeight() / ( height + 1 );
	
	int index;
	for( index = 0; index < numberOfFrames; index++ )
	{
		loadFrame( index, index % tileWidth, index / tileHeight, EXTRACT_MODE_CELL );
	}
	
	mode = BLOCK_MODE_CELL;
}

/*
//--------------------------------------------------------------------------------
// Name: BlockGraphic::~BlockGraphic()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
BlockGraphic::~BlockGraphic()
{
	destroy();
}
*/


//--------------------------------------------------------------------------------
// Name: BlockGraphic::getMode()
// Description:
// 
//--------------------------------------------------------------------------------
int BlockGraphic::getMode()
{
	return mode;
}


//--------------------------------------------------------------------------------
// Name: BlockGraphic::setMode()
// Description:
// 
//--------------------------------------------------------------------------------
void BlockGraphic::setMode( int mode )
{
	this->mode = mode;
}


//--------------------------------------------------------------------------------
// Name: BlockGraphic::draw()
// Description:
// 
//--------------------------------------------------------------------------------
void BlockGraphic::draw( VideoImage* destinationImage, int tileIndex, int xPosition, int yPosition )
{
	// NOTE: Performance hit, good idea to check bounds?
	if( ( tileIndex > -1 ) && ( tileIndex < numberOfFrames ) )
	{
		if( mode == BLOCK_MODE_CELL )
		{
			// NOTE: Sucks that multiplication has to exist here.
			*( this->xPosition ) = xPosition * *width;
			*( this->yPosition ) = yPosition * *height;
			
			VideoImage::draw( destinationImage,
					  frame[tileIndex],
					  destinationRect );
		}
		else
		{
			*( this->xPosition ) = xPosition;
			*( this->yPosition ) = yPosition;
			
			VideoImage::draw( destinationImage,
					  frame[tileIndex],
					  destinationRect );
		}
	}
}


//--------------------------------------------------------------------------------
// Name: BlockGraphic::draw()
// Description:
// 
//--------------------------------------------------------------------------------
void BlockGraphic::draw( int tileIndex, int xPosition, int yPosition )
{
	// NOTE: Performance hit, good idea to check bounds?
	if( ( tileIndex > -1 ) && ( tileIndex < numberOfFrames ) )
	{
		if( mode == BLOCK_MODE_CELL )
		{
			// NOTE: Sucks that multiplication has to exist here.
			*( this->xPosition ) = xPosition * *width;
			*( this->yPosition ) = yPosition * *height;
			
			VideoImage::draw( display,
					  frame[tileIndex],
					  destinationRect );
		}
		else
		{
			*( this->xPosition ) = xPosition;
			*( this->yPosition ) = yPosition;
			
			VideoImage::draw( display,
					  frame[tileIndex],
					  destinationRect );
		}
	}
}


//--------------------------------------------------------------------------------
// Name: BlockGraphic::print()
// Description:
// 
//--------------------------------------------------------------------------------
void BlockGraphic::print( char text[], int xPosition, int yPosition )
{
	int charIndex = 0;
	char letter = text[charIndex];
	while( letter )
	{
		// TODO: This is just a big number... fix it.
		if( letter < 196 )
		{
			draw( ( int )letter, xPosition, yPosition );
		}
		
		xPosition++;
		charIndex++;
		letter = text[charIndex];
	}
}

