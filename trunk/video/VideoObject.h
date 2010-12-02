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
// VideoObject.h
// Authors:  Andrew Dieffenbach
// Date:     August 9, 2010
// Description:
// 
// NOTE:  This version uses SDL and OpenGL
// 
//================================================================================

// Watch for multiple inclusions
#ifndef VIDEO_OBJECT
#define VIDEO_OBJECT

// INCLUDES ======================================================================

// DEFINES =======================================================================

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif


// TYPES =========================================================================

// VideoObject base class.
class VideoObject
{
public:
	VideoObject();
	~VideoObject();
	
	virtual void draw( VideoObject &videoObject );

private:

protected:
};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
