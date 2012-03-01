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
// VideoDisplay.h
// Authors:  Andrew Dieffenbach
// Date:     March 28, 2004
// Description:
// DisplayBuffer class inherits from VideoBuffer
//
// NOTE:  This version uses SDL and OpenGL
// 
//================================================================================

// Watch for multiple inclusions
#ifndef VIDEO_DISPLAY
#define VIDEO_DISPLAY

// INCLUDES ======================================================================

// Add the SDL and OpenGL header files for appropriate OS builds
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#ifdef WINDOWS
	#include <windows.h>
	#include <SDL/SDL_image.h>
	//#include <GL/gl.h>
	//#include <GL/glu.h>
#endif
#ifdef MACOSX
	#include <SDL_image/SDL_image.h>
	//#include <OpenGL/gl.h>
	//#include <OpenGL/glu.h>
#endif
#ifdef LINUX
	#include <SDL/SDL_image.h>
	//#include <GL/gl.h>
	//#include <GL/glu.h>
#endif

#include "puzl/video/VideoImage.h"		// VideoBuffer class header file


// DEFINES =======================================================================

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif

#define DISPLAY_ATTRIBUTE_EMULATE		SDL_ANYFORMAT
#define DISPLAY_ATTRIBUTE_PALETTE		SDL_HWPALETTE
#define DISPLAY_ATTRIBUTE_DOUBLE_BUFFER		SDL_DOUBLEBUF
#define DISPLAY_ATTRIBUTE_FULLSCREEN		SDL_FULLSCREEN
#define DISPLAY_ATTRIBUTE_RESIZABLE		SDL_RESIZABLE
#define DISPLAY_ATTRIBUTE_NOFRAME		SDL_NOFRAME

// TYPES =========================================================================

// VideoDisplay class (inherits from the VideoImage class)
class VideoDisplay : public VideoImage
{
public:
	VideoDisplay();
	~VideoDisplay();

	int initialize( int width, int height,		// Initializes the display
			int attributes = 0 );
	int shutdown();					// Closes the display
	int reset( int width, int height,		// Resets the display to another style
		   int bitdepth, int attributes );
		   
	void setDimensions( int width, int height );
	int setRealDimensions( int width, int height );

	bool isFullscreen();				// Check if this display is fullscreen
  
  void setBackgroundColor( int r, int g, int b );
	void setForegroundColor( int r, int g, int b );
  
	void drawRectangle( int x0, int y0,		// Draw a basic rectangle (2D, no alpha)
			   int x1, int y1,
			   int r, int g, int b,
			   int a = 255 );
	
	void drawRectangle( int x0, int y0,
			   int x1, int y1,
			   int color[] );
  
  void drawRectangle( int xPosition, int yPosition,
                      int width, int height );

	void clear();					// Clears the primary buffer with a color
	void present();					// Draws out the primary buffer

protected:
	bool fullScreen;				// Indicates if display is fullscreen

  int backgroundColor[3];
  int foregroundColor[3];
  
private:
	int attributes;
	
	int initializeSDLAndOpenGL( int attributes = 0 );

};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
