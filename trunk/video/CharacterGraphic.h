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
// CharacterGraphic.h
// Authors:  Andrew Dieffenbach
// Date:     September 11, 2010
// Description:
// 
// 
//================================================================================

// Watch for multiple inclusions
#ifndef CHARACTER_GRAPHIC
#define CHARACTER_GRAPHIC

// INCLUDES ======================================================================

#include <string>
#include <sstream>

#include "BlockGraphic.h"		// BlockGraphic header file

// DEFINES =======================================================================

using namespace std;

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif

#define PRINT_ATTR_ALIGN_LEFT		0
#define PRINT_ATTR_ALIGN_RIGHT		1


// TYPES =========================================================================

// BlockGraphic class
class CharacterGraphic
{
public:
	//CharacterGraphic();
	CharacterGraphic( BlockGraphic &blockGraphic, int* map );
	//~CharacterGraphic();
	
	int* getColor();
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

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
