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

// INCLUDES ======================================================================
#include <puzl/video/BlockGraphic.h>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// TODO: Set default attributes and always bitwise OR it with MULTI_FRAME, as block graphics are always multiframe?
BlockGraphic::BlockGraphic( CoreVideoImage& videoImage, int width, int height, int attributes ) :
CoreVideoSprite( videoImage, width, height,
                 ( videoImage.getRealWidth() / ( width + 1 ) ) * ( videoImage.getRealHeight() / ( height + 1 ) ),
                 attributes )
{
	// TODO: Figure out a way not to have to recalculate this?
	int tileWidth  = videoImage.getRealWidth()  / ( width  + 1 );
	int tileHeight = videoImage.getRealHeight() / ( height + 1 );
	
	int index;
	for( index = 0; index < numberOfFrames; index++ )
	{
		loadFrame( index, index % tileWidth, index / tileHeight, EXTRACT_MODE_CELL );
	}
	
	mode = BLOCK_MODE_CELL;
}

//--------------------------------------------------------------------------------
int BlockGraphic::getMode( void )
{
	return mode;
}

//--------------------------------------------------------------------------------
void BlockGraphic::setMode( int mode )
{
	this->mode = mode;
}

//--------------------------------------------------------------------------------
void BlockGraphic::draw( CoreVideoImage* destinationImage, int tileIndex, int xPosition, int yPosition )
{
	// NOTE: Performance hit, good idea to check bounds?
	if( ( tileIndex > -1 ) && ( tileIndex < numberOfFrames ) )
	{
		if( mode == BLOCK_MODE_CELL )
		{
			// NOTE: Sucks that multiplication has to exist here.
			*( this->xPosition ) = xPosition * *width;
			*( this->yPosition ) = yPosition * *height;
			
			CoreVideoImage::draw( destinationImage,
			                      frame[tileIndex],
			                      destinationRect );
		}
		else
		{
			*( this->xPosition ) = xPosition;
			*( this->yPosition ) = yPosition;
			
			CoreVideoImage::draw( destinationImage,
			                      frame[tileIndex],
			                      destinationRect );
		}
	}
}

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
			
			CoreVideoImage::draw( display,
			                      frame[tileIndex],
			                      destinationRect );
		}
		else
		{
			*( this->xPosition ) = xPosition;
			*( this->yPosition ) = yPosition;
			
			CoreVideoImage::draw( display,
			                      frame[tileIndex],
			                      destinationRect );
		}
	}
}

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
