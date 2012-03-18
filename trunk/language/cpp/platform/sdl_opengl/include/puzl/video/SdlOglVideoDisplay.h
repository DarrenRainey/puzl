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

#ifndef SDL_OGL_VIDEO_DISPLAY
#define SDL_OGL_VIDEO_DISPLAY

// INCLUDES ======================================================================
#include <puzl/video/CoreVideoDisplay.h>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#if defined(_WIN64) || defined(_WIN32)
  #include <windows.h>
  #include <SDL/SDL_image.h>
#elif defined(__APPLE__) || defined(__MACH__)
  #include <SDL_image/SDL_image.h>
#elif defined(__linux) || defined(__unix) || defined(__posix)
  #include <SDL/SDL_image.h>
#else
  #include <SDL/SDL_image.h>
#endif

// DEFINES =======================================================================
#define DISPLAY_ATTRIBUTE_EMULATE         SDL_ANYFORMAT
#define DISPLAY_ATTRIBUTE_PALETTE         SDL_HWPALETTE
#define DISPLAY_ATTRIBUTE_DOUBLE_BUFFER   SDL_DOUBLEBUF
#define DISPLAY_ATTRIBUTE_FULLSCREEN      SDL_FULLSCREEN
#define DISPLAY_ATTRIBUTE_RESIZABLE       SDL_RESIZABLE
#define DISPLAY_ATTRIBUTE_NOFRAME         SDL_NOFRAME

// TYPES =========================================================================
class SdlOglVideoDisplay: public CoreVideoDisplay
{
public:
  SdlOglVideoDisplay( void );
	~SdlOglVideoDisplay( void );

	int initialize( int width, int height, int attributes = 0 );
	int shutdown( void );
	int reset( int width, int height, int bitdepth, int attributes );
		   
	void setDimensions( int width, int height );
	void setRealDimensions( int width, int height );
  
  void setBackgroundColor( int red, int green, int blue );
  
	void drawRectangle( int x0, int y0,
                      int x1, int y1,
                      int red, int green, int blue,
                      int a = 255 );

	void drawRectangle( int xPosition, int yPosition,
	                    int width, int height );

	void clear( void );

private:
	void present( void );
	
	int initializeSDLAndOpenGL( int attributes = 0 );

	SDL_Surface* surface;

	friend class SdlOglGameShell;
};

#endif
