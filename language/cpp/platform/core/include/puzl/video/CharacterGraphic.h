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

#ifndef CHARACTER_GRAPHIC
#define CHARACTER_GRAPHIC

// INCLUDES ======================================================================
#include <string>
#include <sstream>

#include <puzl/video/BlockGraphic.h>

using namespace std;

// DEFINES =======================================================================
#define CHARACTER_MODE_CELL		    BLOCK_MODE_CELL
#define CHARACTER_MODE_ABSOLUTE		BLOCK_MODE_ABSOLUTE

#define PRINT_ATTR_ALIGN_LEFT		  0
#define PRINT_ATTR_ALIGN_RIGHT		1

// TYPES =========================================================================
class CharacterGraphic
{
public:
	CharacterGraphic( BlockGraphic& blockGraphic, int* map );
	//~CharacterGraphic( void );
	
	int getWidth( void );
	int getHeight( void );
	
	void setDimensions( int width, int height );
	
	int getMode( void );
	void setMode( int mode );
	
	int* getColor( void );
	void setColor( int color[] );
	
	void print( const char* text, int xPosition, int yPosition, int attributes = PRINT_ATTR_ALIGN_LEFT );
	void print( string text, int xPosition, int yPosition, int attributes = PRINT_ATTR_ALIGN_LEFT );
	void print( int number, int xPosition, int yPosition, int attributes = PRINT_ATTR_ALIGN_LEFT );
	
protected:
	BlockGraphic* blockGraphic;
	int* map;

private:
	int numberOfFrames;
};

#endif
