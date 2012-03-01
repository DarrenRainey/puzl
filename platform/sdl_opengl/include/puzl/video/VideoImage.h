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
// VideoImage.h
// Authors:  Andrew Dieffenbach
// Date:     August 9, 2010
// Description:
// 
// NOTE:  This version uses SDL and OpenGL
// 
//================================================================================

// Watch for multiple inclusions
#ifndef VIDEO_IMAGE
#define VIDEO_IMAGE

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

#include <iostream>
#include <string>

//#include "puzl/video/VideoObject.h"


using namespace std;

// DEFINES ="."======================================================================

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif

#define SCALE_TYPE_EXACT		0
#define SCALE_TYPE_SMOOTH		1
#define SCALE_TYPE_REALLY_SMOOTH	2

#define IMAGE_ATTRIBUTE_SIMPLE		0
#define IMAGE_ATTRIBUTE_TRANSPARENCY	1
#define IMAGE_ATTRIBUTE_ALPHABLEND	2
#define IMAGE_ATTRIBUTE_COLOR		4
#define IMAGE_ATTRIBUTE_ROTATABLE	8

#define RECT_INDEX_SOURCE_X_START	0
#define RECT_INDEX_SOURCE_Y_START	1
#define RECT_INDEX_SOURCE_X_END		2
#define RECT_INDEX_SOURCE_Y_END		3

#define RECT_INDEX_X_POSITION		0
#define RECT_INDEX_Y_POSITION		1
#define RECT_INDEX_WIDTH		2
#define RECT_INDEX_HEIGHT		3

// TYPES =========================================================================

class VideoDisplay;

// VideoImage
class VideoImage// : public VideoObject
{
public:
	VideoImage();
	VideoImage( VideoImage &videoImage );
	~VideoImage();

	void draw( VideoDisplay *destinationDisplay );
	void draw( VideoDisplay *destinationDisplay, int* sourceRect, int* destinationRect );
	void draw( VideoImage *destinationBitmap, int* sourceRect = NULL, int* destinationRect = NULL );
	
	void clear();
	
	int getWidth();
	int getHeight();
	void setDimensions( int width, int height );

	int getRealWidth();
	int getRealHeight();
	void setRealDimensions( int width, int height );
	
	void setScale( bool scale );
	bool isScaled();
	float getXScale();
	float getYScale();
	int getScaleType();
	void setScaleType( int scaleType );
	
	float getAngle();
	void setAngle( float angle );
	
	bool hasTransparency();
	
	bool hasColorKey();			// Returns whether bitmap has transparent color keying
	//void setColorKey( bool setting );		// Sets Color-Keying or not
	int getNumberOfColorKeys();
	
	bool hasAlphaBlend();			// Returns whether this bitmap uses alpha
	int getAlphaLevel();			// Gets the alpha/transparency (0-255)
	void setAlphaLevel( int level );		// Sets the alpha/transparency (0-255)
	
	bool hasColorBlend();			// Returns whether bitmap uses color blending
	void setColorBlend( bool setting );		// Sets whether bitmap uses color blending
	int* getColor( int colorIndex = 0 );				// Gets the color for color blending
	void setColor( int color[], int colorIndex = 0 );			// Sets the color for color blending
	
	int create( int width, int height, int attributes = IMAGE_ATTRIBUTE_SIMPLE, int numberOfColorKeys = 0 );
	int destroy();
	int release();
	int load( string fileName, int numberOfColorKeys = 0, int** colorKey = NULL );
	int reload();
	
	int colorKeyIndex;

protected:
	int sourceRect[4];
	int* realWidth;
	int* realHeight;
	
	int destinationRect[4];
	int* width;
	int* height;
	
	bool scale;
	float xScale;
	float yScale;
	int scaleType;
	
	int attributes;
	
	bool transparency;
	
	int** colorKey;					// 
	int numberOfColorKeys;

	bool alphaBlend;				// Indicates if bitmap has alpha
	int alphaLevel;					// Alpha/transparency 0-255

	bool colorBlend;				// Indicates if bitmap has color modulation
	int** color;					// Color for color blend/modulation (RGBA)
	
	float angle;

	SDL_Surface* surface;
	GLuint* texture;					// OpenGL texture ID
	
	string fileName;
	VideoImage* clone;
	int cloneReferenceCounter;
	
private:
	float texelWidth;
	float texelHeight;
	
	int createTexture();	// Create Texture (OpenGL) from the SDL surface
	
	void drawPrimary( int* sourceRect = NULL, int* destinationRect = NULL );
};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
