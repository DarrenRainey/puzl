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

#ifndef SDL_OGL_VIDEO_IMAGE
#define SDL_OGL_VIDEO_IMAGE

// INCLUDES ======================================================================
#include <puzl/video/CoreVideoImage.h>

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

#include <string>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

class SdlOglVideoDisplay;

class SdlOglVideoImage: public CoreVideoImage
{
public:
  SdlOglVideoImage( void );
  SdlOglVideoImage( SdlOglVideoImage& videoImage );
	~SdlOglVideoImage( void );

	void draw( SdlOglVideoDisplay* destinationDisplay );
	void draw( SdlOglVideoDisplay* destinationDisplay, int* sourceRect, int* destinationRect );
	void draw( SdlOglVideoImage* destinationImage, int* sourceRect = NULL, int* destinationRect = NULL );
	
	void clear( void );

	void setRealDimensions( int width, int height );
	
	int create( int width, int height, int attributes = IMAGE_ATTRIBUTE_SIMPLE, int numberOfColorKeys = 0 );
	int destroy( void );
	int release( void );
	int load( string fileName, int numberOfColorKeys = 0, int** colorKey = NULL );
	int reload( void );

private:
	SDL_Surface* surface;
	GLuint* texture;
	
	float texelWidth;
	float texelHeight;
	
	int createTexture( void );
	
	void drawPrimary( int* sourceRect = NULL, int* destinationRect = NULL );
};

#endif
