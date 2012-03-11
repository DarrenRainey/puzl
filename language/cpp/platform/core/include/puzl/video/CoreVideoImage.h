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

#ifndef CORE_VIDEO_IMAGE
#define CORE_VIDEO_IMAGE

// INCLUDES ======================================================================
#include <iostream>
#include <string>

using namespace std;

// DEFINES =======================================================================
#define SCALE_TYPE_EXACT		          0
#define SCALE_TYPE_SMOOTH		          1
#define SCALE_TYPE_REALLY_SMOOTH	    2

#define IMAGE_ATTRIBUTE_SIMPLE		    0
#define IMAGE_ATTRIBUTE_TRANSPARENCY  1
#define IMAGE_ATTRIBUTE_ALPHABLEND	  2
#define IMAGE_ATTRIBUTE_COLOR		      4
#define IMAGE_ATTRIBUTE_ROTATABLE	    8

#define RECT_INDEX_SOURCE_X_START	    0
#define RECT_INDEX_SOURCE_Y_START	    1
#define RECT_INDEX_SOURCE_X_END		    2
#define RECT_INDEX_SOURCE_Y_END		    3

#define RECT_INDEX_X_POSITION		      0
#define RECT_INDEX_Y_POSITION		      1
#define RECT_INDEX_WIDTH		          2
#define RECT_INDEX_HEIGHT		          3

// TYPES =========================================================================
class CoreVideoDisplay;

class CoreVideoImage
{
public:
  CoreVideoImage( void );
  CoreVideoImage( CoreVideoImage& videoImage );
	~CoreVideoImage( void );

	virtual void draw( CoreVideoDisplay* destinationDisplay );
	virtual void draw( CoreVideoDisplay* destinationDisplay, int* sourceRect, int* destinationRect );
	virtual void draw( CoreVideoImage* destinationBitmap, int* sourceRect = NULL, int* destinationRect = NULL );
	
	virtual void clear( void );
	
	virtual int getWidth( void );
	virtual int getHeight( void );
	virtual void setDimensions( int width, int height );

	virtual int getRealWidth( void );
	virtual int getRealHeight( void );
	virtual void setRealDimensions( int width, int height );
	
	virtual void setScale( bool scale );
	virtual bool isScaled( void );
	virtual float getXScale( void );
	virtual float getYScale( void );
	virtual int getScaleType( void );
	virtual void setScaleType( int scaleType );
	
	virtual float getAngle( void );
	virtual void setAngle( float angle );
	
	virtual bool hasTransparency( void );
	
	virtual bool hasColorKey( void );			                          // Returns whether bitmap has transparent color keying
	virtual int getNumberOfColorKeys( void );
	
	virtual bool hasAlphaBlend( void );			                        // Returns whether this bitmap uses alpha
	virtual int getAlphaLevel( void );			                        // Gets the alpha/transparency (0-255)
	virtual void setAlphaLevel( int level );		                    // Sets the alpha/transparency (0-255)
	
	virtual bool hasColorBlend( void );			                        // Returns whether bitmap uses color blending
	virtual void setColorBlend( bool setting );		                  // Sets whether bitmap uses color blending
	virtual int* getColor( int colorIndex = 0 );				            // Gets the color for color blending
	virtual void setColor( int color[], int colorIndex = 0 );       // Sets the color for color blending
	
	virtual int create( int width, int height, int attributes = IMAGE_ATTRIBUTE_SIMPLE, int numberOfColorKeys = 0 );
	virtual int destroy( void );
	virtual int release( void );
	virtual int load( string fileName, int numberOfColorKeys = 0, int** colorKey = NULL );
	virtual int reload( void );
	
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
	int** color;					  // Color for color blend/modulation (RGBA)
	
	float angle;

	string fileName;
	CoreVideoImage* clone;
	int cloneReferenceCounter;
};

#endif
