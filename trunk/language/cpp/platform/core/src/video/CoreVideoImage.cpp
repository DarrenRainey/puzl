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

// INCLUDES ======================================================================
#include <puzl/video/CoreVideoImage.h>
#include <puzl/video/CoreVideoDisplay.h>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
CoreVideoImage::CoreVideoImage( void )
{
	width = &destinationRect[RECT_INDEX_WIDTH];
	height = &destinationRect[RECT_INDEX_HEIGHT];
	*width  = 0;
	*height = 0;
	
	sourceRect[RECT_INDEX_SOURCE_X_START] = 0;
	sourceRect[RECT_INDEX_SOURCE_Y_START] = 0;
	realWidth = &sourceRect[RECT_INDEX_SOURCE_X_END];
	realHeight = &sourceRect[RECT_INDEX_SOURCE_Y_END];
	
	setScale( false );
	scaleType = SCALE_TYPE_EXACT;
	
	angle = 0.0f;
	
	setColorBlend( false );
	//setColor( defaultColor );
	
	attributes = IMAGE_ATTRIBUTE_SIMPLE;
	
	transparency = true;
	
	numberOfColorKeys = 0;
	colorKey = NULL;
	colorKeyIndex = 0;
	
	setAlphaLevel( 255 );
	
	fileName = "";
	clone = NULL;
	cloneReferenceCounter = 0;
}

//--------------------------------------------------------------------------------
CoreVideoImage::CoreVideoImage( CoreVideoImage& videoImage )
{
	destinationRect[RECT_INDEX_X_POSITION] = 0;
	destinationRect[RECT_INDEX_Y_POSITION] = 0;
	width = &destinationRect[RECT_INDEX_WIDTH];
	height = &destinationRect[RECT_INDEX_HEIGHT];
	*width  = videoImage.getWidth();
	*height = videoImage.getHeight();
	
	sourceRect[RECT_INDEX_SOURCE_X_START] = 0;
	sourceRect[RECT_INDEX_SOURCE_Y_START] = 0;
	realWidth = &sourceRect[RECT_INDEX_SOURCE_X_END];
	realHeight = &sourceRect[RECT_INDEX_SOURCE_Y_END];
	*realWidth = videoImage.getRealWidth();
	*realHeight = videoImage.getRealHeight();
	
	scale = videoImage.isScaled();
	scaleType = videoImage.getScaleType();
	
	setColorBlend( videoImage.hasColorBlend() );
	
	this->colorKeyIndex = videoImage.colorKeyIndex;
	
	// Create and copy colors.
	numberOfColorKeys = videoImage.numberOfColorKeys;
	
	if( numberOfColorKeys > 0 )
	{
		color = new int*[numberOfColorKeys];
		for( int index = 0; index < numberOfColorKeys; index++ )
		{
			color[index] = new int[3];
			color[index][0] = 255; // Default white.
			color[index][1] = 255;
			color[index][2] = 255;
			
			setColor( videoImage.getColor( index ), index );
		}
	}
	else
	{
		color = new int*[1];
		color[0] = new int[3];
		color[0][0] = 255; // Default white.
		color[0][1] = 255;
		color[0][2] = 255;
		
		setColor( videoImage.getColor( 0 ), 0 );
	}
	
	this->colorKey   = videoImage.colorKey;
	this->attributes = videoImage.attributes;
	transparency     = videoImage.hasTransparency();
	setAlphaLevel( videoImage.getAlphaLevel() );
	
	fileName = "";
	
	// Check if the source CoreVideoImage is also a clone.
	if( videoImage.clone )
	{
		clone = videoImage.clone;
	}
	else
	{
		clone = &videoImage;
	}
	
	videoImage.cloneReferenceCounter++;
}

//--------------------------------------------------------------------------------
CoreVideoImage::~CoreVideoImage( void )
{

}

//--------------------------------------------------------------------------------
int CoreVideoImage::getWidth( void )
{
	return *width;
}

//--------------------------------------------------------------------------------
int CoreVideoImage::getHeight( void )
{
	return *height;
}

//--------------------------------------------------------------------------------
void CoreVideoImage::setDimensions( int width, int height )
{
	*( this->width )  = width;
	*( this->height ) = height;
	
	if( ( *realWidth == width ) && ( *realHeight == height ) )
	{
		setScale( false );
	}
	else
	{
		setScale( true );
		
		if( realWidth == 0 )
		{
			xScale = 0;
		}
		else
		{
			xScale = ( ( float )width / ( float )*realWidth );
		}
		
		if( realHeight == 0 )
		{
			yScale = 0;
		}
		else
		{
			yScale = ( ( float )height / ( float )*realHeight );
		}
	}
}

//--------------------------------------------------------------------------------
int CoreVideoImage::getRealWidth( void )
{
	// TODO: Change to inherit?
	return *realWidth;
}

//--------------------------------------------------------------------------------
int CoreVideoImage::getRealHeight( void )
{
	// TODO: Change to inherit?
	return *realHeight;
}

//--------------------------------------------------------------------------------
void CoreVideoImage::setRealDimensions( int width, int height )
{
	*realWidth = width;
	*realHeight = height;
}

//--------------------------------------------------------------------------------
void CoreVideoImage::setScale( bool scale )
{
	this->scale = scale;
	
	// NOTE: Needed? Scale with indicate ignorance of x/y scale values.
	if( !scale )
	{
		xScale = 1.0f;
		yScale = 1.0f;
	}
}

//--------------------------------------------------------------------------------
bool CoreVideoImage::isScaled( void )
{
	return scale;
}

//--------------------------------------------------------------------------------
float CoreVideoImage::getXScale( void )
{
	return xScale;
}

//--------------------------------------------------------------------------------
float CoreVideoImage::getYScale( void )
{
	return yScale;
}

//--------------------------------------------------------------------------------
int CoreVideoImage::getScaleType( void )
{
	return scaleType;
}

//--------------------------------------------------------------------------------
void CoreVideoImage::setScaleType( int scaleType )
{
	this->scaleType = scaleType;
}

//--------------------------------------------------------------------------------
float CoreVideoImage::getAngle( void )
{
	return angle;
}


//--------------------------------------------------------------------------------
void CoreVideoImage::setAngle( float angle )
{
	if( angle > 360.0f )
	{
		this->angle = 360.0f - angle;
	}
	else
	if( angle < 0.0f )
	{
		this->angle = 360.0f + angle;
	}
	else
	{
		this->angle = angle;
	}
}

//--------------------------------------------------------------------------------
int CoreVideoImage::create( int width, int height, int attributes, int numberOfColorKeys )
{
	return -1;
}

//--------------------------------------------------------------------------------
int CoreVideoImage::destroy( void )
{
	if( clone != NULL )
	{
		// Make sure this clone isn't also cloned indirectly.
		//if( cloneReferenceCounter == 0 )
		{
			clone->cloneReferenceCounter--;
			clone = NULL;
		}
	}
	else
	{
		if( cloneReferenceCounter == 0 )
		{
			if( colorKey != NULL )
			{
				int index;
				for( index = 0; index < numberOfColorKeys; index++ )
				{
					delete colorKey[index];
					delete color[index];
				}
				
				delete [] colorKey;
			}
			else
			{
				delete color[0];
			}
			
			delete [] color;
		}
		else
		{
			//cout << "Warning: attempting to destroy clone VideoImage clone originator with active clones." << endl;
		}
	}
	
	return 0;
}

//--------------------------------------------------------------------------------
int CoreVideoImage::release( void )
{
	return 0;
}

//--------------------------------------------------------------------------------
int CoreVideoImage::load( string fileName, int numberOfColorKeys, int** colorKey )
{
	return -1;
}

//--------------------------------------------------------------------------------
int CoreVideoImage::reload( void )
{
	return 0;
}

//--------------------------------------------------------------------------------
bool CoreVideoImage::hasTransparency( void )
{
	return transparency;
}

//--------------------------------------------------------------------------------
bool CoreVideoImage::hasColorKey( void )
{
	return false;
}

//--------------------------------------------------------------------------------
int CoreVideoImage::getNumberOfColorKeys( void )
{
	return numberOfColorKeys;
}

//--------------------------------------------------------------------------------
bool CoreVideoImage::hasAlphaBlend( void )
{
	return alphaBlend;
}

//--------------------------------------------------------------------------------
int CoreVideoImage::getAlphaLevel( void )
{
	return alphaLevel;
}

//--------------------------------------------------------------------------------
void CoreVideoImage::setAlphaLevel( int alphaLevel )
{
	this->alphaLevel = alphaLevel;
	if( alphaLevel == 0 )
	{
		alphaBlend = false;
	}
	else
	{
		alphaBlend = true;
	}
}

//--------------------------------------------------------------------------------
bool CoreVideoImage::hasColorBlend( void )
{
	return colorBlend;
}

//--------------------------------------------------------------------------------
void CoreVideoImage::setColorBlend( bool colorBlend )
{
	this->colorBlend = colorBlend;
}

//--------------------------------------------------------------------------------
int* CoreVideoImage::getColor( int colorIndex )
{
	return color[colorIndex];
}

//--------------------------------------------------------------------------------
void CoreVideoImage::setColor( int color[], int colorIndex )
{
	// Set the color modulation RGB components of this CoreVideoImage (OPTIMIZE LATER)
	this->color[colorIndex][0] = color[0];
	this->color[colorIndex][1] = color[1];
	this->color[colorIndex][2] = color[2];
}

//--------------------------------------------------------------------------------
void CoreVideoImage::draw( CoreVideoDisplay* destinationDisplay )
{
	destinationRect[RECT_INDEX_X_POSITION] = 0; // TODO: Is this the correct thing to do?
	destinationRect[RECT_INDEX_Y_POSITION] = 0;
}

//--------------------------------------------------------------------------------
void CoreVideoImage::draw( CoreVideoDisplay* destinationDisplay, int* sourceRect, int* destinationRect )
{

}

//--------------------------------------------------------------------------------
void CoreVideoImage::draw( CoreVideoImage* destinationBitmap, int* sourceRect, int* destinationRect )
{
	
}

//--------------------------------------------------------------------------------
void CoreVideoImage::clear( void )
{

}
