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
// VideoSprite.cpp
// Authors:  Andrew Dieffenbach
// Date:     March 28, 2004
// Description:
// Display class derives from Bitmap
// NOTE:  This version uses SDL and OpenGL
// 
//================================================================================

// INCLUDES ======================================================================

// Add the SDL and OpenGL header files for appropriate OS builds

#include "puzl/video/VideoImage.h"		// VideoImage header file
#include "puzl/video/VideoDisplay.h"		// VideoDisplay header file
#include "puzl/video/VideoSprite.h"		// VideoSprite header file
//#include "puzl/utility/Script.h"			// Script hearder file

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

/*
//--------------------------------------------------------------------------------
// Name: VideoSprite::VideoSprite()
// Description:
// Default Constructor
//--------------------------------------------------------------------------------
VideoSprite::VideoSprite()
{
	// Clear data members
	xPosition  = 0;
	yPosition  = 0;

	xVelocity  = 0;
	yVelocity  = 0;

	state	   = 0;
	attributes = 0;
	
	//animation
	
	frame = NULL;
}
*/

//--------------------------------------------------------------------------------
// Name: VideoSprite::VideoSprite()
// Description:
// Constructor
//--------------------------------------------------------------------------------
VideoSprite::VideoSprite( VideoImage &videoImage, int width, int height, int numberOfFrames, int attributes ) : VideoImage( videoImage )
{
	xPosition = &destinationRect[RECT_INDEX_X_POSITION];
	yPosition = &destinationRect[RECT_INDEX_Y_POSITION];
	
	this->width = &destinationRect[RECT_INDEX_WIDTH];
	this->height = &destinationRect[RECT_INDEX_HEIGHT];
	
	*( this->width ) = this->realWidth = width;
	*( this->height ) = this->realHeight = height;
	
	// Clear data members
	*xPosition  = 0;
	*yPosition  = 0;

	xVelocity  = 0;
	yVelocity  = 0;
	
	// Set the number of frames available to the Animation script
	animation.setNumberOfFrames( numberOfFrames );
	currentFrame = 0;
	
	this->numberOfFrames = numberOfFrames;
	
	int index;
	frame = new int* [numberOfFrames];
	for( index = 0; index < numberOfFrames; index++ )
	{
		frame[index] = new int[4];
		
		frame[index][RECT_INDEX_SOURCE_X_START] = 0;
		frame[index][RECT_INDEX_SOURCE_Y_START] = 0;
		frame[index][RECT_INDEX_SOURCE_X_END] = 0;
		frame[index][RECT_INDEX_SOURCE_Y_END] = 0;
	}
	
	// Set default state and specified attributes of sprite
	state			= SPRITE_STATE_ALIVE;
	this->attributes	= attributes;

	// Set attributes of the animation
	if( attributes & SPRITE_ATTRIBUTE_SINGLE_FRAME )
	{
		//cout << "Set as SPRITE_ATTRIBUTE_SINGLE_FRAME" << endl;
		animation.setAttributes( SCRIPT_ATTRIBUTE_SINGLE_FRAME );
	}
	else
	if( attributes & SPRITE_ATTRIBUTE_MULTI_FRAME )
	{
		//cout << "Set as SPRITE_ATTRIBUTE_MULTI_FRAME" << endl;
		animation.setAttributes( SCRIPT_ATTRIBUTE_MULTI_FRAME );
	}
	else
	if( attributes & SPRITE_ATTRIBUTE_MULTI_ANIM )
	{
		if( attributes & SPRITE_ATTRIBUTE_ANIM_ONE_SHOT )
		{
			animation.setAttributes( SCRIPT_ATTRIBUTE_MULTI_SEQUENCE &
						 SCRIPT_ATTRIBUTE_ONE_SHOT	      );
			//cout << "Set as SPRITE_ATTRIBUTE_MULTI_FRAME" << endl;
		}
		else
		{
			animation.setAttributes( SCRIPT_ATTRIBUTE_MULTI_SEQUENCE );
			//cout << "Set as multi sequence" << endl;
		}
	}
	
	display = NULL;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::~VideoSprite()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
VideoSprite::~VideoSprite()
{
	//destroy();
}

/*
//--------------------------------------------------------------------------------
// Name: VideoSprite::create()
// Description:
// 
//--------------------------------------------------------------------------------
VideoSprite* VideoSprite::create( int width, int height, int numberOfFrames, int attributes )
{
	int index;
	int tempAttributes;			// Holds a newly formed VideoImage attribute

	// Set default state and specified attributes of sprite
	state			= SPRITE_STATE_ALIVE;
	this->attributes	= attributes;

	// Set attributes of the animation
	if( this->attributes & SPRITE_ATTRIBUTE_SINGLE_FRAME )
	{
		animation.setAttributes( SCRIPT_ATTRIBUTE_SINGLE_FRAME );
	}
	else
	if( this->attributes & SPRITE_ATTRIBUTE_MULTI_FRAME )
	{
		animation.setAttributes( SCRIPT_ATTRIBUTE_MULTI_FRAME );
	}
	else
	if( this->attributes & SPRITE_ATTRIBUTE_MULTI_ANIM )
	{
		if( this->attributes & SPRITE_ATTRIBUTE_ANIM_ONE_SHOT )
		{
			animation.setAttributes( SCRIPT_ATTRIBUTE_MULTI_SEQUENCE &
						 SCRIPT_ATTRIBUTE_ONE_SHOT	      );
		}
		else
		{
			animation.setAttributes( SCRIPT_ATTRIBUTE_MULTI_SEQUENCE );
		}
	}
	
	// Allocate number of pointers to internal bitmaps (for each frame)
	frame = new int* [numberOfFrames];

	// Set the number of frames available to the Animation script
	animation.setNumberOfFrames( numberOfFrames );

	// Reserve space for both sprite and its internal bitmaps
	for( index = 0; index < numberOfFrames; index++ )
	{
		if( !( frame[index] = new int ) )
		{
			return -1;
		}

		// Set default Bitmap attribute of being hardware (we hope!)
		tempAttributes = SDL_HWSURFACE;

		// Check if a sprite with transparency was requested
		if( attributes & SPRITE_ATTRIBUTE_TRANSPARENCY )
		{
			tempAttributes |= IMAGE_ATTRIBUTE_TRANSPARENCY;
		}

		// Check if a sprite with alpha channel/semi-transparency was requested
		if( attributes & SPRITE_ATTRIBUTE_ALPHABLEND )
		{
			tempAttributes |= IMAGE_ATTRIBUTE_ALPHABLEND;
		}
			
		// Check if a sprite with color modulation/blending was requested
		if( attributes & SPRITE_ATTRIBUTE_COLOR )
		{
			tempAttributes |= IMAGE_ATTRIBUTE_COLOR;
		}
	}

	return NULL;
}
*/

//--------------------------------------------------------------------------------
// Name: VideoSprite::destroy()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::destroy()
{
	int index;

	// Destroy every frame.
	for( index = 0; index < animation.getNumberOfFrames(); index++ )
	{
		if( frame[index] )
		{
			delete [] frame[index];
			frame[index] = NULL;
		}
	}
	
	// Free memory for each pointer to a VideoImage
	delete [] frame;
	frame = NULL;

	return 0;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::getWidth()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getWidth()
{
	return *width;
}

//--------------------------------------------------------------------------------
// Name: VideoSprite::getHeight()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getHeight()
{
	return *height;
}

//--------------------------------------------------------------------------------
// Name: VideoSprite::setDimensions()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::setDimensions( int width, int height )
{
	*( this->width ) = width;
	*( this->height ) = height;
	
	if( ( realWidth == width ) && ( realHeight == height ) )
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
			xScale = ( ( float )width / ( float )realWidth );
		}
		
		if( realHeight == 0 )
		{
			yScale = 0;
		}
		else
		{
			yScale = ( ( float )height / ( float )realHeight );
		}
	}
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::getRealWidth()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getRealWidth()
{
	// TODO: Change to inherit?
	return realWidth;
}

//--------------------------------------------------------------------------------
// Name: VideoSprite::getRealHeight()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getRealHeight()
{
	// TODO: Change to inherit?
	return realHeight;
}

//--------------------------------------------------------------------------------
// Name: VideoSprite::setRealDimensions()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::setRealDimensions( int width, int height )
{
	realWidth = width;
	realHeight = height;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::setScale()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::setScale( bool scale )
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
// Name: VideoSprite::isScaled()
// Description:
// 
//--------------------------------------------------------------------------------
bool VideoSprite::isScaled()
{
	return scale;
}

//--------------------------------------------------------------------------------
// Name: VideoSprite::getXScale()
// Description:
// 
//--------------------------------------------------------------------------------
float VideoSprite::getXScale()
{
	return xScale;
}

//--------------------------------------------------------------------------------
// Name: VideoSprite::getYScale()
// Description:
// 
//--------------------------------------------------------------------------------
float VideoSprite::getYScale()
{
	return yScale;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::getXPosition()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getXPosition()
{
	return *xPosition;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::getYPosition()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getYPosition()
{
	return *yPosition;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::setXPosition()
// Description:
// 
//-----------------------------------------
void VideoSprite::setXPosition( int xPosition )
{
	*( this->xPosition ) = xPosition;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::setYPosition()
// Description:
// 
//-----------------------------------------
void VideoSprite::setYPosition( int yPosition )
{
	*( this->yPosition ) = yPosition;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::setPosition()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::setPosition( int xPosition, int yPosition )
{
	*( this->xPosition ) = xPosition;
	*( this->yPosition ) = yPosition;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::getXVelocity()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getXVelocity()
{
	return xVelocity;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::getYVelocity()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getYVelocity()
{
	return yVelocity;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::setXVelocity()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::setXVelocity( int xVelocity )
{
	this->xVelocity = xVelocity;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::setYVelocity()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::setYVelocity( int yVelocity )
{
	this->yVelocity = yVelocity;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::setVelocity()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::setVelocity( int xVelocity, int yVelocity )
{
	this->xVelocity = xVelocity;
	this->yVelocity = yVelocity;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::move()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::move()
{
	*xPosition += xVelocity;
	*yPosition += yVelocity;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::getState()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getState()
{
	return state;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::SetState()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::setState( int state )
{
	this->state = state;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::show()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::show()
{
	// Set the visibility bit
	attributes |= SPRITE_ATTRIBUTE_VISIBLE;

	return 0;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::hide()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::hide()
{
	// Clear the visibility bit
	attributes &= ~SPRITE_ATTRIBUTE_VISIBLE;

	return 0;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::loadFrame()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::loadFrame( int frameIndex,
			    int cellx, int celly, int mode )
{
	// Test the mode of extraction, cell based or absolute
	if( mode == EXTRACT_MODE_CELL )
	{
		// Re-compute x and y
		cellx = ( cellx * ( realWidth  + 1 ) ) + 1;
		celly = ( celly * ( realHeight + 1 ) ) + 1;
	}
    
	if( frame[frameIndex] != NULL )
	{
		// TODO: Figure out mirroring!
		frame[frameIndex][RECT_INDEX_SOURCE_X_START] = cellx;
		frame[frameIndex][RECT_INDEX_SOURCE_Y_START] = celly;
		
		frame[frameIndex][RECT_INDEX_SOURCE_X_END] = realWidth;
		frame[frameIndex][RECT_INDEX_SOURCE_Y_END] = realHeight;
		
		/*
		cout << "loading frame: " << frame[frameIndex][0] << ":" <<
					     frame[frameIndex][1] << ":" <<
					     frame[frameIndex][2] << ":" <<
					     frame[frameIndex][3] << endl;
		*/
		
		return 0;
	}
	else
	{
		return -1;
	}
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::loadAnimation()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::loadAnimation( int animationIndex, int numberOfFrames, int *sequence )
{
	// Load in data for animation
	animation.load( animationIndex, sequence );

	return( 0 );
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::getAnimation()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getAnimation()
{
	return animation.getCurrentSequence();
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::setAnimation()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::setAnimation( int animationIndex )
{
	// Set the animation index
	animation.setCurrentSequence( animationIndex );
	currentFrame = animation.getCurrentFrame();
}

//--------------------------------------------------------------------------------
// Name: VideoSprite::setAnimationSpeed()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::setAnimationSpeed( int speed )
{
	// Set speed
	animation.setSpeed( speed );
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::getAnimationSpeed()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getAnimationSpeed()
{
	return animation.getSpeed();
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::getAnimationCounter()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getAnimationCounter()
{
	return animation.getCounter();
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::animate()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::animate()
{
	// Animate with current animation sequence
	int animationState = animation.read();
	currentFrame = animation.getCurrentFrame();
	
	return animationState;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::getCurrentFrame()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getCurrentFrame()
{
	// Optimize here.
	currentFrame = animation.getCurrentFrame();
	return currentFrame;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::setCurrentFrame()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::setCurrentFrame( int frameIndex )
{
	animation.setCurrentFrame( frameIndex );
	currentFrame = animation.getCurrentFrame();
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::getFrameIndex()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getFrameIndex()
{
	// Optimize here?
	return animation.getFrameIndex();
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::setFrameIndex()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::setFrameIndex( int frameIndex )
{
	animation.setFrameIndex( frameIndex );
	currentFrame = animation.getCurrentFrame();
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::getNumberOfFrames()
// Description:
// 
//--------------------------------------------------------------------------------
int VideoSprite::getNumberOfFrames()
{
	return numberOfFrames;
}


//--------------------------------------------------------------------------------
// Name: VideoSprite::setDisplay()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::setDisplay( VideoDisplay* display )
{
	this->display = display;
}


//--------------------------------------------------------------------------------
// Name: VideoImage::draw()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoSprite::draw()
{
	if( display != NULL )
	{
		VideoImage::draw( display, frame[currentFrame], destinationRect );
	}
}


