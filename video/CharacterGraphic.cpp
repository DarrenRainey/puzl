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
// CharacterGraphic.cpp
// Authors:  Andrew Dieffenbach
// Date:     September 11, 2010
// Description:
// 
// 
//================================================================================

// INCLUDES ======================================================================

#include "CharacterGraphic.h"		// CharacterGraphic header file

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// Name: BlockGraphic::CharacterGraphic()
// Description:
// Constructor
//--------------------------------------------------------------------------------
CharacterGraphic::CharacterGraphic( BlockGraphic &blockGraphic, int* map )
{
	if( map == NULL )
	{
		cout << "CharacterGraphic requires a valid map in which to link" << endl;
	}
	
	this->blockGraphic = &blockGraphic;
	numberOfFrames = blockGraphic.getNumberOfFrames();
	
	this->map = map;
}

/*
//--------------------------------------------------------------------------------
// Name: CharacterGraphic::~CharacterGraphic()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
CharacterGraphic::~CharacterGraphic()
{
	//destroy();
}
*/


//--------------------------------------------------------------------------------
// Name: CharacterGraphic::getWidth()
// Description:
// 
//--------------------------------------------------------------------------------
int CharacterGraphic::getWidth()
{
	return blockGraphic->getWidth();
}


//--------------------------------------------------------------------------------
// Name: CharacterGraphic::getHeight()
// Description:
// 
//--------------------------------------------------------------------------------
int CharacterGraphic::getHeight()
{
	return blockGraphic->getHeight();
}


//--------------------------------------------------------------------------------
// Name: CharacterGraphic::setDimensions()
// Description:
// 
//--------------------------------------------------------------------------------
void CharacterGraphic::setDimensions( int width, int height )
{
	blockGraphic->setDimensions( width, height );
}


//--------------------------------------------------------------------------------
// Name: CharacterGraphic::getMode()
// Description:
// 
//--------------------------------------------------------------------------------
int CharacterGraphic::getMode()
{
	return blockGraphic->getMode();
}


//--------------------------------------------------------------------------------
// Name: CharacterGraphic::setMode()
// Description:
// 
//--------------------------------------------------------------------------------
void CharacterGraphic::setMode( int mode )
{
	blockGraphic->setMode( mode );
}


//--------------------------------------------------------------------------------
// Name: CharacterGraphic::getColor()
// Description:
// 
//--------------------------------------------------------------------------------
int* CharacterGraphic::getColor()
{
	return blockGraphic->getColor( 0 );
}


//--------------------------------------------------------------------------------
// Name: CharacterGraphic::setColor()
// Description:
// 
//--------------------------------------------------------------------------------
void CharacterGraphic::setColor( int color[] )
{
	// Set the color modulation RGB components of this VideoImage (TODO: OPTIMIZE LATER)
	blockGraphic->setColor( color );
}


//--------------------------------------------------------------------------------
// Name: CharacterGraphic::print()
// Description:
// 
//--------------------------------------------------------------------------------
void CharacterGraphic::print( const char* text, int xPosition, int yPosition, int attributes )
{
	string tempText = text;
	print( tempText, xPosition, yPosition, attributes );
}

//--------------------------------------------------------------------------------
// Name: CharacterGraphic::print()
// Description:
// 
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
// Name: CharacterGraphic::print()
// Description:
// 
//--------------------------------------------------------------------------------
void CharacterGraphic::print( int number, int xPosition, int yPosition, int attributes )
{
	// NOTE: Probably best just to not use this function and convert numbers to strings as needed.
	stringstream ss( stringstream::in | stringstream::out );
	ss << number;
	print( ss.str(), xPosition, yPosition, attributes );
}
