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
// VideoImage.cpp
// Authors:  Andrew Dieffenbach
// Date:     March 28, 2004
// Description:
//
// NOTE:  This version uses SDL and OpenGL
// 
//================================================================================

// INCLUDES ======================================================================

// Add the SDL and OpenGL header files for appropriate OS builds

#include "puzl/video/VideoImage.h"		// VideoImage header file
#include "puzl/video/VideoDisplay.h"

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
// Name: VideoImage::VideoImage()
// Description:
// Default Constructor
//--------------------------------------------------------------------------------
VideoImage::VideoImage()
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
	
	//static int defaultColor[] = { 255, 255, 255, 255 };	// Default color for color blending
	setColorBlend( false );
	//setColor( defaultColor );
	
	attributes = IMAGE_ATTRIBUTE_SIMPLE;
	
	transparency = true;
	
	numberOfColorKeys = 0;
	colorKey = NULL;
	colorKeyIndex = 0;
	
	setAlphaLevel( 255 );
	
	surface = NULL;
	texture = NULL;
	
	fileName = "";
	clone = NULL;
	cloneReferenceCounter = 0;
}


//--------------------------------------------------------------------------------
// Name: VideoImage::VideoImage()
// Description:
// Copy Constructor
//--------------------------------------------------------------------------------
VideoImage::VideoImage( VideoImage &videoImage )
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
	
	texelWidth = 1.0f / ( float )*realWidth;
	texelHeight = 1.0f / ( float )*realHeight;
	
	scale = videoImage.isScaled();
	scaleType = videoImage.getScaleType();
	
	setColorBlend( videoImage.hasColorBlend() );
	
	this->colorKeyIndex = videoImage.colorKeyIndex;
	
	// Create and copy colors.
	numberOfColorKeys = videoImage.numberOfColorKeys;
	
	if( numberOfColorKeys > 0 )
	{
		color = new int* [numberOfColorKeys];
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
		color = new int* [1];
		color[0] = new int[3];
		color[0][0] = 255; // Default white.
		color[0][1] = 255;
		color[0][2] = 255;
		
		setColor( videoImage.getColor( 0 ), 0 );
	}
	
	this->colorKey = videoImage.colorKey;
	
	this->attributes = videoImage.attributes;
	
	transparency = videoImage.hasTransparency();
	
	setAlphaLevel( videoImage.getAlphaLevel() );
	
	surface = videoImage.surface;
	texture = videoImage.texture;
	
	fileName = "";
	
	// Check if the source VideoImage is also a clone.
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
// Name: VideoImage::~VideoImage()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
VideoImage::~VideoImage()
{
	//destroy();
}

/*
//--------------------------------------------------------------------------------
// Name: VideoImage::draw()
// Description:
// Draws this bitmap on top of the destination bitmap
// No positioning is used (hopefully, this can be optimized and used with SDL_Rect's
// This allows for faster blitting (designed for frontbuffer/backbuffer flipping)
//--------------------------------------------------------------------------------
void VideoImage::draw( VideoImage &videoObject2D )
{
	
}
*/

//--------------------------------------------------------------------------------
// Name: VideoImage::getWidth()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoImage::getWidth()
{
	return *width;
}

//--------------------------------------------------------------------------------
// Name: VideoImage::getHeight()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoImage::getHeight()
{
	return *height;
}

//--------------------------------------------------------------------------------
// Name: VideoImage::setDimensions()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoImage::setDimensions( int width, int height )
{
	*( this->width ) = width;
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
// Name: VideoImage::getRealWidth()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoImage::getRealWidth()
{
	// TODO: Change to inherit?
	return *realWidth;
}

//--------------------------------------------------------------------------------
// Name: VideoImage::getRealHeight()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoImage::getRealHeight()
{
	// TODO: Change to inherit?
	return *realHeight;
}

//--------------------------------------------------------------------------------
// Name: VideoImage::setRealDimensions()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoImage::setRealDimensions( int width, int height )
{
	*realWidth = width;
	*realHeight = height;
	
	texelWidth = 1.0f / ( float )*realWidth;
	texelHeight = 1.0f / ( float )*realHeight;
}


//--------------------------------------------------------------------------------
// Name: VideoImage::setScale()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoImage::setScale( bool scale )
{
	this->scale = scale;
	
	// NOTE: Needed? scale with indicate ignorance of x/y scale values.
	if( !scale )
	{
		xScale = 1.0f;
		yScale = 1.0f;
	}
}

//--------------------------------------------------------------------------------
// Name: VideoImage::isScaled()
// Description:
// 
//--------------------------------------------------------------------------------
bool VideoImage::isScaled()
{
	return scale;
}

//--------------------------------------------------------------------------------
// Name: VideoImage::getXScale()
// Description:
// 
//--------------------------------------------------------------------------------
float VideoImage::getXScale()
{
	return xScale;
}

//--------------------------------------------------------------------------------
// Name: VideoImage::getYScale()
// Description:
// 
//--------------------------------------------------------------------------------
float VideoImage::getYScale()
{
	return yScale;
}

//--------------------------------------------------------------------------------
// Name: VideoImage::getScaleType()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoImage::getScaleType()
{
	return scaleType;
}

//--------------------------------------------------------------------------------
// Name: VideoImage::setScaleType()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoImage::setScaleType( int scaleType )
{
	this->scaleType = scaleType;
}



//--------------------------------------------------------------------------------
// Name: VideoImage::create()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoImage::create( int width, int height, int attributes, int numberOfColorKeys )
{
	int rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	
	SDL_Surface *temporarySurface;
	
	const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo();
	int bitdepth = videoInfo->vfmt->BitsPerPixel;
	temporarySurface = SDL_CreateRGBSurface( SDL_HWSURFACE, width, height, 32, rmask, gmask, bmask, amask );
	
	// Convert the surface format to that of main display
	surface = SDL_DisplayFormatAlpha( temporarySurface );
	SDL_FreeSurface( temporarySurface );

	// Exit if the surface buffer was created unsuccessfully
	if( surface == NULL )
	{
		cout << "Error creating VideoImage." << endl;
		return -1;
	}
	else
	{
		this->attributes = attributes;
		this->numberOfColorKeys = numberOfColorKeys;
		
		if( numberOfColorKeys > 0 )
		{
			color = new int* [numberOfColorKeys];
			for( int index = 0; index < numberOfColorKeys; index++ )
			{
				color[index] = new int[3];
				color[index][0] = 255; // Default white.
				color[index][1] = 255;
				color[index][2] = 255;
			}
		}
		else
		{
			color = new int* [0];
			color[0] = new int[3];
			color[0][0] = 255; // Default white.
			color[0][1] = 255;
			color[0][2] = 255;
		}
		
		*( this->width ) = surface->w;
		*( this->height ) = surface->h;
		
		// Clear the new surface ( with green )
		SDL_FillRect( surface, NULL , SDL_MapRGBA( surface->format, 0, 255, 0, 0 ) );	// TODO: Alpha?

		if( attributes != IMAGE_ATTRIBUTE_SIMPLE )
		{
			// Check if a bitmap with a transparency.
			if( attributes & IMAGE_ATTRIBUTE_TRANSPARENCY )
			{
				transparency = true;
			}
			else
			{
				transparency = false;
			}

			// Check if a bitmap with a alpha transparency was requested
			if( attributes & IMAGE_ATTRIBUTE_ALPHABLEND )
			{
				// Set alpha blending to default
				alphaBlend = true;	// Create function for this?!?!?!?!?!
			}
			
			// Check if a bitmap with a color blend/modulation was requested
			if( attributes & IMAGE_ATTRIBUTE_COLOR )
			{
				// Set color blending/modulation to default
				setColorBlend( true );
			}
			
			colorKey = NULL;
		}
		else
		{
			colorKey = NULL;
		}
		
		// Create the OpenGL texture from the SDL surface
		createTexture();
	}
	
	return 0;
}


//--------------------------------------------------------------------------------
// Name: VideoImage::destroy()
// Description:
// Releases the memory reserved for this VideoImage.
//--------------------------------------------------------------------------------
int VideoImage::destroy()
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
					glDeleteTextures( 1, &texture[index] );
					
					delete colorKey[index];
					delete color[index];
				}
				
				delete [] colorKey;
			}
			else
			{
				glDeleteTextures( 1, &texture[0] );
				delete color[0];
			}
			
			delete [] color;
			delete [] texture;
			texture = NULL;
		}
		else
		{
			//cout << "Warning: attempting to destroy clone VideoImage clone originator with active clones." << endl;
		}
	}
	
	return 0;
}


//--------------------------------------------------------------------------------
// Name: VideoImage::release()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoImage::release()
{
	if( texture == NULL )
	{
		return -1;
	}
	else
	{
		texture = NULL;
		return 0;
	}
}


//--------------------------------------------------------------------------------
// Name: VideoImage::load()
// Description:
// Loads a graphics file (BMP, PNG; etc.) into this VideoImage.
//--------------------------------------------------------------------------------
int VideoImage::load( string fileName, int numberOfColorKeys, int** colorKey )
{
	SDL_Surface *temporarySurface;
	
	if( surface )
	{
		destroy();
	}
	
	// Load the image from file.
	temporarySurface = IMG_Load( fileName.c_str() );
	
	// Convert the surface format to that of the passed 'ExampleBuffer'.
	surface = SDL_DisplayFormatAlpha( temporarySurface );
	SDL_FreeSurface( temporarySurface );

	// Exit if the surface buffer was created unsuccessfully.
	if( surface == NULL )
	{
		cout << "Failed to load VideoImage" << endl;
		return -1;
	}
	else
	{
		this->fileName = fileName;
		this->numberOfColorKeys = numberOfColorKeys;
		this->colorKey = colorKey;
		
		if( numberOfColorKeys > 0 )
		{
			color = new int* [numberOfColorKeys];
			for( int index = 0; index < numberOfColorKeys; index++ )
			{
				color[index] = new int[3];
				color[index][0] = 255; // Default white.
				color[index][1] = 255;
				color[index][2] = 255;
			}
		}
		else
		{
			// Just set up one color for a VideoImage with no color keys.
			color = new int* [1];
			color[0] = new int[3];
			color[0][0] = 255; // Default white.
			color[0][1] = 255;
			color[0][2] = 255;
		}
		
		*width = surface->w;
		*height = surface->h;
		return createTexture();
	}
}


//--------------------------------------------------------------------------------
// Name: VideoImage::reload()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoImage::reload()
{
	if( texture != NULL )
	{
		cout << "Attempting to reload VideoImage that has not been released." << endl;
		return -1;
	}
	
	if( clone != NULL )
	{
		// This VideoImage is a clone. So, just adjust the texture pointer.
		if( clone->texture == NULL )
		{
			cout << "Attempting to reload VideoImage clone of a VideoImage that does not have a valid texture/surface." << endl;
			return -1;
		}
		else
		{
			texture = clone->texture;
			return 0;
		}
	}
	else
	if( fileName != "" )
	{
		// This VideoImage is not a clone and was originally loaded from a graphic file.
		return load( fileName, numberOfColorKeys, colorKey );
	}
	else
	{
		// This VideoImage is not a clone and is one that was created without loading a graphic file.
		return create( *width, *height, attributes, numberOfColorKeys );
	}
}


//--------------------------------------------------------------------------------
// Name: VideoImage::createTexture()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoImage::createTexture()
{
	int index;
	
	// Set our VideoImage's dimensions
	if( surface != NULL )
	{
		*realWidth  = surface->w;
		*realHeight = surface->h;
		
		texelWidth = 1.0f / ( float )*realWidth;
		texelHeight = 1.0f / ( float )*realHeight;
		
		//cout << this->width << ":" << this->realWidth << endl;
		//cout << realWidth << endl;
		//cout << realHeight << endl;
		//cout << width << endl;
		//cout << height << endl;
	}
	else
	{
		cout << "createTexture failure" << endl;
		return -1;
	}
	
	int channels = 4; // R,G,B,A
	
	unsigned char *data    = ( unsigned char * )( surface->pixels );
	unsigned char *newData = new unsigned char[*realWidth * *realHeight * channels];
	
	// Get video information about current video mode
	const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
	if( !videoInfo )
	{
		SDL_FreeSurface( surface );
		cout << "createTexture failure" << endl;
		return( -1 );
	}
	
	int bitdepth = videoInfo->vfmt->BitsPerPixel;
	int bytesPerPixel = surface->format->BytesPerPixel;
	
	// Flip the surface data
	for( index = 0; index < ( *realHeight / 2 ); ++index )
	{
		for( int j = 0; j < *realWidth * bytesPerPixel; j += bytesPerPixel )
		{
			for( int k = 0; k < bytesPerPixel; ++k )
			{
				swap( data[( index * *realWidth * bytesPerPixel ) + j + k],
				data[ ( ( *realHeight - index - 1 ) * *realWidth * bytesPerPixel ) + j + k] );
			}
		}
	}
	
	int textureIndex;
	bool colorKeyNeedsDestroy;
	if( numberOfColorKeys > 0 )
	{
		texture = new GLuint [numberOfColorKeys];
		glGenTextures( numberOfColorKeys, texture );
		
		colorKeyNeedsDestroy = false;
		if( colorKey == NULL )
		{
			colorKey = new int* [numberOfColorKeys];
			
			static int defaultColorKey[] = {0xFF, 0xFF, 0xFF};
			for( int colorKeyIndex = 0; colorKeyIndex < numberOfColorKeys; colorKeyIndex++ )
			{
				colorKey[colorKeyIndex] = defaultColorKey;
			}
			
			colorKeyNeedsDestroy = true;
		}
	}
	else
	{
		texture = new GLuint [0];
		glGenTextures( 1, texture );
		colorKeyNeedsDestroy = false;
	}
	
	// NOTE: Temporary fix for VideoImages with no color keys.
	int numberOfTextures;
	if( numberOfColorKeys > 0 )
	{
		numberOfTextures = numberOfColorKeys;
	}
	else
	{
		numberOfTextures = 1;
	}
	
	for( textureIndex = 0; textureIndex < numberOfTextures; textureIndex++ )
	{
		// The following lines extract R,G and B values from any bitmap
		Uint32 pixelValue = 0;			// 32 bit unsigned int (as dictated by SDL)
		for( index = 0; index < ( *realWidth * *realHeight ); ++index )
		{
			char r, g, b, a;			// R, G, and B that we will put into pImage
			pixelValue = 0;				// reset pixel , else we get incorrect values of r,g,b

			// the following loop extracts the pixel (however wide it is 8,16,24 or 32) and 
			// creates a long with all these bytes taken together.
			for( int j = bytesPerPixel - 1; j >= 0; --j )
			{
				// for each byte in the pixel (from the right)
				// left shift pixel value by 8 bits
				pixelValue = pixelValue << 8;
				
				// then make the last 8 bits of pixel
				// value  = the byte that we extract from pBitmap's data
				pixelValue = pixelValue | data[( index * bytesPerPixel ) + j]; 
			}							

			// here we get r,g,b from pixel_value which is stored
			// in the form specified by pBitmap->format
			SDL_GetRGBA( pixelValue, surface->format,
				( Uint8* )( &r ),		
				( Uint8* )( &g ),	
				( Uint8* )( &b ),		
				( Uint8* )( &a ) );

			// In our tImage classes we store r first then g and finally b (for bmps - three channels only)
			
			// TODO Try to adjust these series of if statements to accommodate alphablending too
			
			// Sort out color key for this texture.
			if( numberOfColorKeys > 0 )
			{
				if(	( ( int )( r & 0xFF ) == colorKey[textureIndex][0] ) &&
					( ( int )( g & 0xFF ) == colorKey[textureIndex][1] ) &&
					( ( int )( b & 0xFF ) == colorKey[textureIndex][2] ) )
				{
					newData[( index * channels ) + 0] = r = 255;
					newData[( index * channels ) + 1] = g = 255;
					newData[( index * channels ) + 2] = b = 255;
				}
				else
				{
					newData[( index * channels ) + 0] = r = 0;
					newData[( index * channels ) + 1] = g = 0;
					newData[( index * channels ) + 2] = b = 0;
					newData[( index * channels ) + 2] = a = 0;
				}
			}
			else
			{
				newData[( index * channels ) + 0] = r;
				newData[( index * channels ) + 1] = g;
				newData[( index * channels ) + 2] = b;
			}
			
			// TODO: If alphaBlend?
			newData[( index * channels ) + 3] = a;
		}
		
		// Bind and initialize the texture
		glBindTexture( GL_TEXTURE_2D, texture[textureIndex] );
		
		// Build Mipmaps (builds different versions of the picture for distances - looks better)
		//gluBuild2DMipmaps( GL_TEXTURE_2D, 3, Width, Height, GL_RGB, GL_UNSIGNED_BYTE, newData );
		
		if( scaleType == SCALE_TYPE_EXACT )
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		}
		else
		if( scaleType == SCALE_TYPE_SMOOTH )
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		}
		else //( scaleType == SCALE_TYPE_REALLY_SMOOTH )
		{
			// NOTE: For backwards compatibility.
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		}
		
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, *realWidth, *realHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, newData );
	}

	// Now we need to free the bitmap data that we loaded since openGL stored it as a texture
	delete [] newData;
	SDL_FreeSurface( surface );
	
	if( colorKeyNeedsDestroy )
	{
		delete [] colorKey;
		colorKey = NULL;
	}
	
	return 0;
}


//--------------------------------------------------------------------------------
// Name: VideoImage::hasTransparency()
// Description:
// 
// 
//--------------------------------------------------------------------------------
bool VideoImage::hasTransparency()
{
	return transparency;
}


//--------------------------------------------------------------------------------
// Name: VideoImage::hasAlphaBlend()
// Description:
// 
// Test to see if alpha-blending is enabled for this VideoImage
//--------------------------------------------------------------------------------
bool VideoImage::hasColorKey()
{
	/*
	if( colorKey != NULL )
	{
		return true;
	}
	else
	{
		return false;
	}
	*/
	return true;
}

/*
//--------------------------------------------------------------------------------
// Name: VideoImage::setColorKey()
// Description:
// 
// Test to see if alpha-blending is enabled for this VideoImage
//--------------------------------------------------------------------------------
void VideoImage::setColorKey( bool setting )
{
	colorKey = setting;
}
*/


//--------------------------------------------------------------------------------
// Name: VideoImage::getNumberOfColorKeys()
// Description:
// 
// 
//--------------------------------------------------------------------------------
int VideoImage::getNumberOfColorKeys()
{
	return numberOfColorKeys;
}


//--------------------------------------------------------------------------------
// Name: VideoImage::hasAlphaBlend()
// Description:
// 
// Test to see if alpha-blending is enabled for this VideoImage
//--------------------------------------------------------------------------------
bool VideoImage::hasAlphaBlend()
{
	return alphaBlend;
}


//--------------------------------------------------------------------------------
// Name: VideoImage::getAlphaLevel()
// Description:
// 
// Gets the alpha-blending level specified for this VideoImage
//--------------------------------------------------------------------------------
int VideoImage::getAlphaLevel()
{
	return alphaLevel;
}


//--------------------------------------------------------------------------------
// Name: VideoImage::setAlphaLevel()
// Description:
// 
// Sets the alpha-blending level for this VideoImage
//--------------------------------------------------------------------------------
void VideoImage::setAlphaLevel( int level )
{
	alphaLevel = level;
	
	if( alphaLevel == 0 )
	{
		alphaBlend = false;
	}
	else
	{
		alphaBlend = true;
	}

	//SDL_SetAlpha( Surface, SDL_SRCALPHA, AlphaLevel );
}


//--------------------------------------------------------------------------------
// Name: VideoImage::hasColorBlend()
// Description:
// 
//--------------------------------------------------------------------------------
bool VideoImage::hasColorBlend()
{
	return colorBlend;
}


//--------------------------------------------------------------------------------
// Name: VideoImage::setColorBlend()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoImage::setColorBlend( bool setting )
{
	colorBlend = setting;	
}


//--------------------------------------------------------------------------------
// Name: VideoImage::getColor()
// Description:
// 
//--------------------------------------------------------------------------------
int* VideoImage::getColor( int colorIndex )
{
	return color[colorIndex];
}


//--------------------------------------------------------------------------------
// Name: VideoImage::setColor()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoImage::setColor( int color[], int colorIndex )
{
	// Set the color modulation RGB components of this VideoImage (OPTIMIZE LATER)
	this->color[colorIndex][0] = color[0];
	this->color[colorIndex][1] = color[1];
	this->color[colorIndex][2] = color[2];
}


//--------------------------------------------------------------------------------
// Name: VideoImage::draw()
// Description:
// 
// Draws a section (defined by offsets and width/height) of this VideoImage to a
// specified VideoDisplay (mainly to support future expansion of
// engine features and multi-monitor support with OpenGL) at a specified position.
//--------------------------------------------------------------------------------
void VideoImage::draw( VideoDisplay *destinationDisplay )
{
	destinationRect[RECT_INDEX_X_POSITION] = 0;
	destinationRect[RECT_INDEX_Y_POSITION] = 0;
	
	// Draw straight to the primary display
	drawPrimary( sourceRect, destinationRect );

}


//--------------------------------------------------------------------------------
// Name: VideoImage::draw()
// Description:
// 
// Draws a section (defined by offsets and width/height) of this VideoImage to a
// specified VideoDisplay (mainly to support future expansion of
// engine features and multi-monitor support with OpenGL) at a specified position.
//--------------------------------------------------------------------------------
void VideoImage::draw( VideoDisplay *destinationDisplay, int* sourceRect, int* destinationRect )
{
	drawPrimary( sourceRect, destinationRect );
}


//--------------------------------------------------------------------------------
// Name: VideoImage::draw()
// Description:
// 
// Draws a section (defined by offsets and width/height) of this VideoImage to
// another VideoImage at a specified position.
//--------------------------------------------------------------------------------
void VideoImage::draw( VideoImage *destinationBitmap, int* sourceRect, int* destinationRect )
{
	GLint viewport[4];			// Backup space for current OpenGL viewport
	
	// Get current screen/viewport before we alter it for accelerated texture copying
	glGetIntegerv( GL_VIEWPORT, viewport );
	
	int destinationWidth  = destinationBitmap->getWidth();
	int destinationHeight = destinationBitmap->getHeight();
	
	// Set screen viewport to dimensions of the destinationBitmap
	glViewport( 0, 0, destinationWidth, destinationHeight );
	
	// Set up Ortho view
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();

	glOrtho( 0, destinationWidth,
		 destinationHeight, 0,
		 -1, 1 );
	
	// Check to see if these VideoImages' number of color keys match.
	if( destinationBitmap->getNumberOfColorKeys() == numberOfColorKeys )
	{
		// Draw all layers on the destination VideoImage's corresponding layer.
		bool restoreColorBlend = colorBlend;
		colorBlend = false;
		
		// Draw the bitmap on the screen.
		drawPrimary( sourceRect, destinationRect );

		glMatrixMode( GL_PROJECTION );
		glPopMatrix();
		
		// Use this VideoImage's 'Texture' (OpenGL) member as the texture to draw to
		glBindTexture( GL_TEXTURE_2D, destinationBitmap->texture[colorKeyIndex] );	// NOTE Default to first image (for now)?

		// Render the screen to the texture we specified
		glCopyTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
					0, 0,
					destinationWidth, destinationHeight,
					0 );
		
		colorBlend = restoreColorBlend;
	}
	else
	{
		// TODO: Add case for VideoImages with no color keys.
		// Draw all layers on to first texture only.
		colorKeyIndex = 0;
		while( colorKeyIndex < numberOfColorKeys )
		{
			// Draw the bitmap on the screen.
			drawPrimary( sourceRect, destinationRect );
			colorKeyIndex++;
		}
		colorKeyIndex = 0;

		glMatrixMode( GL_PROJECTION );
		glPopMatrix();
		
		// Use this VideoImage's 'Texture' (OpenGL) member as the texture to draw to
		glBindTexture( GL_TEXTURE_2D, destinationBitmap->texture[0] );	// NOTE Default to first image (for now)?

		// Render the screen to the texture we specified
		glCopyTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
				0, 0,
				//destinationRect[2], destinationRect[3],	// NOTE This correct?
				destinationWidth, destinationHeight,
				0 );
	}

	// Return screen/display to original/previous dimensions
	glViewport( viewport[0], viewport[1],
		    viewport[2], viewport[3] );
}


//--------------------------------------------------------------------------------
// Name: VideoImage::clear()
// Description:
// 
// 
//--------------------------------------------------------------------------------
void VideoImage::clear()
{
	// TODO: Needs to clear each texture when more than one color key.
	for( int index = 0; index < numberOfColorKeys; index++ )
	{
		glClear( GL_COLOR_BUFFER_BIT );
		glBindTexture( GL_TEXTURE_2D, texture[index] );
		glCopyTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
				0, 0,
				*realWidth, *realHeight,// NOTE This correct?
				0 );
	}
}


//--------------------------------------------------------------------------------
// Name: VideoImage::drawPrimary()
// Description:
// 
// Draws this VideoImage straight to the default primary display.
//--------------------------------------------------------------------------------
inline void VideoImage::drawPrimary( int* sourceRect, int* destinationRect )
{
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();	// Reset The matrix
	
	// Set the position where the image is to drawn on the display
	// TODO: Preprocess this?
	glTranslatef( ( float )destinationRect[RECT_INDEX_X_POSITION], ( float )destinationRect[RECT_INDEX_Y_POSITION], 0 );

	// Bind the texture stored as the Texture ID for use
	// TODO: Is this (more) effecient?
	//static GLuint lastTextureUsed = 0;
	//if( lastTextureUsed != texture[colorKeyIndex] )
	//{
		//glBindTexture( GL_TEXTURE_2D, texture[0] );
		glBindTexture( GL_TEXTURE_2D, texture[colorKeyIndex] );
	//	lastTextureUsed = texture[colorKeyIndex];
	//}

	// If this bitmap has color blend,
	// set the color to this VideoImage's Color
	if( colorBlend )
	{
		if( !alphaBlend )
		{
			glColor4ub( color[colorKeyIndex][0], color[colorKeyIndex][1], color[colorKeyIndex][2], 255 );
		}
		else
		{
			glColor4ub( color[colorKeyIndex][0], color[colorKeyIndex][1], color[colorKeyIndex][2], alphaLevel );
		}
	}
	else
	{
		if( !alphaBlend )
		{
			// NOTE: Is this correct?
			glColor4ub( 255, 255, 255, 255 );
		}
		else
		{
			// NOTE: Is this correct?
			glColor4ub( 255, 255, 255, alphaLevel );
		}
	}

	if( transparency )
	{
		// TODO: Check to see if color blending is active?
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}
	else
	{
		glDisable( GL_BLEND );
	}
	
	glMatrixMode( GL_TEXTURE );
	glLoadIdentity();
	
	glScalef( texelWidth, texelHeight, 1.0f );
	
	// TODO Still needs (can) preprocess?
	int dx0, dx1;
	int dy0, dy1;
	
	dx0 = sourceRect[RECT_INDEX_SOURCE_X_START];
	dx1 = sourceRect[RECT_INDEX_SOURCE_X_START] + sourceRect[RECT_INDEX_SOURCE_X_END];
	
	dy0 = *realHeight - sourceRect[RECT_INDEX_SOURCE_Y_START] - sourceRect[RECT_INDEX_SOURCE_Y_END];
	dy1 = *realHeight - sourceRect[RECT_INDEX_SOURCE_Y_START];
	
	// Draw the 'tile' to the screen
	glBegin( GL_QUADS );
		
		// Display the top left vertice
		glTexCoord2i( dx0, dy1 );
		glVertex2i( 0, 0 );
		
		// Display the bottom left vertice
		glTexCoord2i( dx0, dy0 );
		glVertex2i( 0, destinationRect[RECT_INDEX_HEIGHT] );
		
		// Display the bottom right vertice
		glTexCoord2i( dx1, dy0 );
		glVertex2i( destinationRect[RECT_INDEX_WIDTH], destinationRect[RECT_INDEX_HEIGHT] );
		
		// Display the top right vertice
		glTexCoord2i( dx1, dy1 );
		glVertex2i( destinationRect[RECT_INDEX_WIDTH], 0 );
	
	glEnd();
}

