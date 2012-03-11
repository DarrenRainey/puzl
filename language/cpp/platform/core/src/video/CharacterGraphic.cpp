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
#include <puzl/video/CharacterGraphic.h>

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
CharacterGraphic::CharacterGraphic( BlockGraphic& blockGraphic, int* map )
{
	if( map == NULL )
	{
		cout << "CharacterGraphic requires a valid map in which to link" << endl;
	}
	
	this->blockGraphic = &blockGraphic;
	numberOfFrames = blockGraphic.getNumberOfFrames();
	
	this->map = map;
}

//--------------------------------------------------------------------------------
int CharacterGraphic::getWidth( void )
{
	return blockGraphic->getWidth();
}

//--------------------------------------------------------------------------------
int CharacterGraphic::getHeight( void )
{
	return blockGraphic->getHeight();
}

//--------------------------------------------------------------------------------
void CharacterGraphic::setDimensions( int width, int height )
{
	blockGraphic->setDimensions( width, height );
}

//--------------------------------------------------------------------------------
int CharacterGraphic::getMode( void )
{
	return blockGraphic->getMode();
}

//--------------------------------------------------------------------------------
void CharacterGraphic::setMode( int mode )
{
	blockGraphic->setMode( mode );
}

//--------------------------------------------------------------------------------
int* CharacterGraphic::getColor( void )
{
	return blockGraphic->getColor( 0 );
}

//--------------------------------------------------------------------------------
void CharacterGraphic::setColor( int color[] )
{
	// Set the color modulation RGB components of this CoreVideoImage (TODO: OPTIMIZE LATER)
	blockGraphic->setColor( color );
}

//--------------------------------------------------------------------------------
void CharacterGraphic::print( const char* text, int xPosition, int yPosition, int attributes )
{
	string tempText = text; // TODO: Optimize.
	print( tempText, xPosition, yPosition, attributes );
}

//--------------------------------------------------------------------------------
void CharacterGraphic::print( string text, int xPosition, int yPosition, int attributes )
{
	if( blockGraphic->getMode() == BLOCK_MODE_CELL )
	{
		if( attributes == PRINT_ATTR_ALIGN_LEFT )
		{
			int textLength = text.length();
			for( int charIndex = 0; charIndex < textLength; charIndex++ )
			{
				char letter = text[charIndex];
				if( letter < numberOfFrames )
				{
					blockGraphic->draw( map[( int )letter], xPosition, yPosition );
				}
				
				xPosition++;
			}
		}
		else
		//if( attributes == PRINT_ATTR_ALIGN_RIGHT )
		{
			int textLength = text.length();
			xPosition -= textLength;
			for( int charIndex = 0; charIndex < textLength; charIndex++ )
			{
				char letter = text[charIndex];
				if( letter < numberOfFrames )
				{
					blockGraphic->draw( map[( int )letter], xPosition, yPosition );
				}
				
				xPosition++;
			}
		}
	}
	else //( blockGraphic->getMode() == BLOCK_MODE_ABSOLUTE )
	{
		// NOTE: The only key difference between align left and right is the starting position--that's it.
		// TODO: Meaning we could optimize here.
		if( attributes == PRINT_ATTR_ALIGN_LEFT )
		{
			int textLength = text.length();
			int blockWidth = blockGraphic->getWidth();
			int currentXPosition = xPosition;
			for( int charIndex = 0; charIndex < textLength; charIndex++ )
			{
				char letter = text[charIndex];
				if( letter < numberOfFrames )
				{
					blockGraphic->draw( map[( int )letter], currentXPosition, yPosition );
				}
				
				currentXPosition += blockWidth;
			}
		}
		else
		//if( attributes == PRINT_ATTR_ALIGN_RIGHT )
		{
			int textLength = text.length();
			int blockWidth = blockGraphic->getWidth();
			int currentXPosition = xPosition - ( textLength * blockWidth );	// TODO: Needs testing.
			xPosition -= textLength;
			for( int charIndex = 0; charIndex < textLength; charIndex++ )
			{
				char letter = text[charIndex];
				if( letter < numberOfFrames )
				{
					blockGraphic->draw( map[( int )letter], currentXPosition, yPosition );
				}
				
				currentXPosition += blockWidth;
			}
		}
	}
}

//--------------------------------------------------------------------------------
void CharacterGraphic::print( int number, int xPosition, int yPosition, int attributes )
{
	// NOTE: Probably best just to not use this function and convert numbers to strings as needed.
	stringstream ss( stringstream::in | stringstream::out );
	ss << number;
	print( ss.str(), xPosition, yPosition, attributes );
}
