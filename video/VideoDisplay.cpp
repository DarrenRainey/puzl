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
// VideoDisplay.cpp
// Authors:  Andrew Dieffenbach
// Date:     March 28, 2004
// Description:
// DisplayBuffer class derives from the VideoBuffer class
// NOTE:  This version uses SDL and OpenGL
// 
//================================================================================

// INCLUDES ======================================================================

// Add the SDL and OpenGL header files for appropriate OS builds

//#include "puzl/video/VideoBuffer.h"		// VideoBuffer header file
#include "puzl/video/VideoDisplay.h"		// VideoDisplay header file

#include <iostream>
using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// Name: VideoDisplay::VideoDisplay()
// Description:
// 
//--------------------------------------------------------------------------------
VideoDisplay::VideoDisplay( void )
{
	// Clear data members
	fullScreen = false;
	
	attributes = 0;
}


//--------------------------------------------------------------------------------
// Name: VideoDisplay::~VideoDisplay()
// Description:
// 
//--------------------------------------------------------------------------------
VideoDisplay::~VideoDisplay()
{
	
}


//--------------------------------------------------------------------------------
// Name: VideoDisplay::initialize()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoDisplay::initialize( int width, int height, int attributes )
{
	*realWidth = *( this->width ) = width;
	*realHeight = *( this->height ) = height;
	this->attributes = attributes;
	
	if( initializeSDLAndOpenGL( attributes ) < 0 )
	{
		return -1;
	}
	
	glViewport( 0, 0, width, height );		// Set up viewport

	glMatrixMode( GL_PROJECTION );			// Set up projection matrix
	glLoadIdentity();				// and
	glOrtho( 0, width,
		 height, 0,
		 -1, 1 );
	
	glEnable( GL_TEXTURE_2D );			// Enable texture mapping
	
	return 0;
}


//--------------------------------------------------------------------------------
// Name: VideoDisplay::initializeSDLAndOpenGL()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoDisplay::initializeSDLAndOpenGL( int attributes )
{
	int bitdepth;
	// Get video information about current video mode
	const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
	if( !videoInfo )
	{
		return -1;
	}
	
	if( attributes != 0 )
	{
		// Indicate SDL to use OpenGL.
		attributes |= SDL_OPENGL;// | DISPLAY_ATTRIBUTE_DOUBLE_BUFFER;
		
		// If bitdepth was not specified, use the current video state
		bitdepth = videoInfo->vfmt->BitsPerPixel;

		// Check if the system can use hardware surfaces
		if( videoInfo->hw_available )
		{
			attributes |= SDL_HWSURFACE;
		}
		else
		{
			attributes |= SDL_SWSURFACE;
		}
		
		// Check for hardware blitting
		if( videoInfo->blit_hw )
		{
			attributes |= SDL_HWACCEL;
		}
		
		if( attributes & DISPLAY_ATTRIBUTE_FULLSCREEN )
		{
			fullScreen = true;
		}
		else
		{
			fullScreen = false;
		}
		
		this->attributes = attributes;
	}
	else
	{
		attributes = this->attributes;
	}
	
	// Set OpenGL attributes accordingly
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );	// 5 bits of red
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );	// 5 bits of green
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );	// 5 bits of blue
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 5 );	// 5 bits of alpha
	//SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
	
	//SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
	
	/*
	if( bitdepth > 16 )
	{
		SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 1 );	// 5 bits of alpha
	}
	else
	{
		SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 0 );
	}*/
	
	//SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );	// 16 bit depth (3D)
	
	
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );	// Turn on double buffer (MUST?)
	SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 1 );

	// Initialize SDL video
	surface = SDL_SetVideoMode( *realWidth, *realHeight, bitdepth, attributes );
	if( surface == NULL )
	{
		return -1;
	}
	
	//int alpha_size;
	//SDL_GL_GetAttribute( SDL_GL_ALPHA_SIZE, &alpha_size );
	
	// Set up OpenGL video
	glShadeModel( GL_SMOOTH );			// Shading model = Gouraud

	glCullFace( GL_BACK );				// Standard culling
	glFrontFace( GL_CCW );				// 
	glEnable( GL_CULL_FACE );			// 
	
	//glEnable( GL_BLEND );
	//glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	//glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );
	
	//glEdgeFlag( false );

	glClearColor( 0, 0, 0, 0 );			// Clear color = black
	
	return 0;
}


//--------------------------------------------------------------------------------
// Name: VideoDisplay::setDimensions()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoDisplay::setDimensions( int width, int height )
{
	*( this->width ) = width;
	*( this->height ) = height;
	
	glViewport( 0, 0, width, height );		// Set up viewport

	glMatrixMode( GL_PROJECTION );			// Set up projection matrix
	glLoadIdentity();				// and
	glOrtho( 0, width,
		 height, 0,
		 -1, 1 );

	glEnable( GL_TEXTURE_2D );			// Enable texture mapping
}


//--------------------------------------------------------------------------------
// Name: VideoDisplay::setDimensions()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoDisplay::setRealDimensions( int width, int height )
{
	VideoImage::setRealDimensions( width, height );
	
	if( initializeSDLAndOpenGL( attributes ) < 0 )
	{
		return -1;
	}
	
	glViewport( 0, 0, width, height );		// Set up viewport

	glMatrixMode( GL_PROJECTION );			// Set up projection matrix
	glLoadIdentity();				// and
	glOrtho( 0, *( this->width ),
		 *( this->height ), 0,
		 -1, 1 );

	glEnable( GL_TEXTURE_2D );			// Enable texture mapping
	
	return 0;
}


//--------------------------------------------------------------------------------
// Name: VideoDisplay::shutdown()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoDisplay::shutdown()
{
	fullScreen = false;
	return SUCCESS;
}


//--------------------------------------------------------------------------------
// Name: VideoDisplay::reset()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoDisplay::reset( int width, int height,
			 int bitdepth, int attributes )
{
	/*
	if( attributes == 0 )
	{
		//attributes = SDL_OPENGL | SDL_HWPALETTE | SDL_RLEACCEL | SDL_RESIZABLE | SDL_ANYFORMAT;
		attributes = SDL_OPENGL | SDL_HWSURFACE | SDL_HWACCEL | SDL_RESIZABLE;
	}
	
	surface = SDL_SetVideoMode( width, height, bitdepth, attributes );
	if( surface == NULL )
	{
		return -1;
	}
	
	glViewport( 0, 0, width, height );
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	glEnable( GL_TEXTURE_2D );
	*/
	
	return 0;
}


//--------------------------------------------------------------------------------
// Name: VideoDisplay::isFullscreen()
// Description:
// 
//--------------------------------------------------------------------------------
bool VideoDisplay::isFullscreen()
{
	return fullScreen;
}


//--------------------------------------------------------------------------------
// Name: VideoDisplay::drawRectangle()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoDisplay::drawRectangle( int x0, int y0,
				 int x1, int y1,
				 int r, int g, int b, int a )
{	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();	// Reset The matrix
	
	glDisable( GL_TEXTURE_2D );
	
	// Get current OpenGL color and back it up temporarily	
	glColor4ub( r, g, b, a ); // NOTE This is where we utilize alphablending!!!
	
	// Set the position where the rectangle is to drawn on the display
	glTranslatef( ( float )x0, ( float )y0, 0.0f );

	// Draw the 'tile' to the screen
	glBegin( GL_QUADS );
		
		// Display the top left vertice
		glVertex2i( 0, 0 );
		
		// Display the bottom left vertice
		glVertex2i( 0, y1 );
		
		// Display the bottom right vertice
		glVertex2i( x1, y1 );
		
		// Display the top right vertice
		glVertex2i( x1, 0 );
	
	glEnd();
	
	glEnable( GL_TEXTURE_2D );
}

//--------------------------------------------------------------------------------
// Name: VideoDisplay::drawRectangle()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoDisplay::drawRectangle( int x0, int y0,
				 int x1, int y1,
				 int color[] )
{
	drawRectangle( x0, y0,
			x1, y1,
			color[0], color[1], color[2] );
}

//--------------------------------------------------------------------------------
// Name: VideoDisplay::Clear()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoDisplay::clear()
{
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  // Just clears the screen!
	glClear( GL_COLOR_BUFFER_BIT );  // Just clears the screen!
}


//--------------------------------------------------------------------------------
// Name: VideoDisplay::present()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoDisplay::present()
{
	SDL_GL_SwapBuffers();
}


