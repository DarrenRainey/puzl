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
// VideoObject.cpp
// Authors:  Andrew Dieffenbach
// Date:     March 28, 2004
// Description:
//
// NOTE:  This version uses SDL and OpenGL
// 
//================================================================================

// INCLUDES ======================================================================

// Add the SDL and OpenGL header files for appropriate OS builds
#include <SDL/SDL.h>

#ifdef WINDOWS
	#include <windows.h>
	#include <SDL/SDL_image.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif
#ifdef MACOSX
	#include <SDL_image/SDL_image.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#endif
#ifdef LINUX
	#include <SDL/SDL_image.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include "puzl/video/VideoObject.h"		// VideoObject header file

// DEFINES =======================================================================

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// Name: VideoObject::VideoObject()
// Description:
// Default Constructor
//--------------------------------------------------------------------------------
VideoObject::VideoObject( void )
{
	
}


//--------------------------------------------------------------------------------
// Name: VideoObject::~VideoObject()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
VideoObject::~VideoObject( void )
{
	
}


//--------------------------------------------------------------------------------
// Name: VideoObject::draw()
// Description:
// Draws this bitmap on top of the destination bitmap
// No positioning is used (hopefully, this can be optimized and used with SDL_Rect's
// This allows for faster blitting (designed for frontbuffer/backbuffer flipping)
//--------------------------------------------------------------------------------
void VideoObject::draw( VideoObject &videoObject )
{
/*
	SDL_Rect sourceRect;
	SDL_Rect destinationRect;
	
	// Check for a valid bitmaps
	// If they are not valid, exit function with error code
	if( ( Surface == NULL ) || ( DestinationBuffer->Surface == NULL ) )
		return( FAILURE );
	
	// Set region of the source bitmap to blit with
	sourceRect.x		= 0;
	sourceRect.y		= 0;
	sourceRect.w		= Width;
	sourceRect.h		= Height;
	
	// Set region of the destination bitmap to blit to
	destinationRect.x	= 0;
	destinationRect.y	= 0;
	destinationRect.w	= DestinationBuffer->Width;
	destinationRect.h	= DestinationBuffer->Height;
	
	// Blit the selected source region of the source bitmap
	// to the selected destination region of the destination bitmap
	return( SDL_BlitSurface( Surface, &sourceRect,
				 DestinationBuffer->Surface, &destinationRect ) );
*/
}

/*
//--------------------------------------------------------------------------------
// Name: VideoObject::Clear()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoObject::Clear( int color )
{
	//return( SDL_FillRect( Surface, NULL, color ) );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  // Clears just the screen!

	return( SUCCESS );
}


*/
