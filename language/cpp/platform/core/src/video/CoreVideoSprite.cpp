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
#include <puzl/video/CoreVideoSprite.h>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================
//--------------------------------------------------------------------------------
CoreVideoSprite::CoreVideoSprite( CoreVideoImage &videoImage, int width, int height, int numberOfFrames, int attributes ) : CoreVideoImage( videoImage )
{
	xPosition = &destinationRect[RECT_INDEX_X_POSITION];
	yPosition = &destinationRect[RECT_INDEX_Y_POSITION];
	
	this->width = &destinationRect[RECT_INDEX_WIDTH];
	this->height = &destinationRect[RECT_INDEX_HEIGHT];
	
	*( this->width ) = this->realWidth = width;
	*( this->height ) = this->realHeight = height;
	
	// Clear data members
	*xPosition = 0;
	*yPosition = 0;

	xVelocity  = 0;
	yVelocity  = 0;
	
	angle = 0.0f;
	
	angularVelocity = 0.0f;
	
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
	state			        = SPRITE_STATE_ALIVE;
	this->attributes	= attributes;

	// Set attributes of the animation
	if( attributes & SPRITE_ATTRIBUTE_SINGLE_FRAME )
	{
		//cout << "Set as SPRITE_ATTRIBUTE_SINGLE_FRAME" << endl;
		animation.setAttributes( OPERATION_ATTRIBUTE_SINGLE_FRAME );
	}
	else
	if( attributes & SPRITE_ATTRIBUTE_MULTI_FRAME )
	{
		//cout << "Set as SPRITE_ATTRIBUTE_MULTI_FRAME" << endl;
		animation.setAttributes( OPERATION_ATTRIBUTE_MULTI_FRAME );
	}
	else
	if( attributes & SPRITE_ATTRIBUTE_MULTI_ANIM )
	{
		if( attributes & SPRITE_ATTRIBUTE_ANIM_ONE_SHOT )
		{
			animation.setAttributes( OPERATION_ATTRIBUTE_MULTI_SEQUENCE &
			                         OPERATION_ATTRIBUTE_ONE_SHOT );
			//cout << "Set as SPRITE_ATTRIBUTE_MULTI_FRAME" << endl;
		}
		else
		{
			animation.setAttributes( OPERATION_ATTRIBUTE_MULTI_SEQUENCE );
			//cout << "Set as multi sequence" << endl;
		}
	}
	
	display = NULL;
}

//--------------------------------------------------------------------------------
CoreVideoSprite::~CoreVideoSprite( void )
{
	//destroy();
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::destroy( void )
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
	
	// Free memory for each pointer to a CoreVideoImage
	delete [] frame;
	frame = NULL;

	return 0;
}


//--------------------------------------------------------------------------------
int CoreVideoSprite::getWidth( void )
{
	return *width;
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::getHeight( void )
{
	return *height;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setDimensions( int width, int height )
{
	*( this->width )  = width;
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
int CoreVideoSprite::getRealWidth( void )
{
	// TODO: Change to inherit?
	return realWidth;
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::getRealHeight( void )
{
	// TODO: Change to inherit?
	return realHeight;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setRealDimensions( int width, int height )
{
	realWidth = width;
	realHeight = height;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setScale( bool scale )
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
bool CoreVideoSprite::isScaled( void )
{
	return scale;
}

//--------------------------------------------------------------------------------
float CoreVideoSprite::getXScale( void )
{
	return xScale;
}

//--------------------------------------------------------------------------------
float CoreVideoSprite::getYScale( void )
{
	return yScale;
}


//--------------------------------------------------------------------------------
int CoreVideoSprite::getXPosition( void )
{
	return *xPosition;
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::getYPosition( void )
{
	return *yPosition;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setXPosition( int xPosition )
{
	*( this->xPosition ) = xPosition;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setYPosition( int yPosition )
{
	*( this->yPosition ) = yPosition;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setPosition( int xPosition, int yPosition )
{
	*( this->xPosition ) = xPosition;
	*( this->yPosition ) = yPosition;
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::getXVelocity( void )
{
	return xVelocity;
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::getYVelocity( void )
{
	return yVelocity;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setXVelocity( int xVelocity )
{
	this->xVelocity = xVelocity;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setYVelocity( int yVelocity )
{
	this->yVelocity = yVelocity;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setVelocity( int xVelocity, int yVelocity )
{
	this->xVelocity = xVelocity;
	this->yVelocity = yVelocity;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::move( void )
{
	*xPosition += xVelocity;
	*yPosition += yVelocity;
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::getAngularVelocity( void )
{
	return angularVelocity;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setAngularVelocity( float angularVelocity )
{
	this->angularVelocity = angularVelocity;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::rotate( void )
{
	angle += angularVelocity;
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::getState( void )
{
	return state;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setState( int state )
{
	this->state = state;
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::show( void )
{
	// Set the visibility bit.
	attributes |= SPRITE_ATTRIBUTE_VISIBLE;

	return 0;
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::hide( void )
{
	// Clear the visibility bit
	attributes &= ~SPRITE_ATTRIBUTE_VISIBLE;

	return 0;
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::loadFrame( int frameIndex, int cellx, int celly, int mode )
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
		
		frame[frameIndex][RECT_INDEX_SOURCE_X_END]   = realWidth;
		frame[frameIndex][RECT_INDEX_SOURCE_Y_END]   = realHeight;
		
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
int CoreVideoSprite::loadAnimation( int animationIndex, int numberOfFrames, int* sequence )
{
	// Load in data for animation
	animation.load( animationIndex, sequence );

	return 0;
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::getAnimation( void )
{
	return animation.getCurrentSequence();
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setAnimation( int animationIndex )
{
	// Set the animation index
	animation.setCurrentSequence( animationIndex );
	currentFrame = animation.getCurrentFrame();
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setAnimationSpeed( int speed )
{
	animation.setSpeed( speed );
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::getAnimationSpeed( void )
{
	return animation.getSpeed();
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::getAnimationCounter( void )
{
	return animation.getCounter();
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::animate( void )
{
	// Animate with current animation sequence
	int animationState = animation.read();
	currentFrame = animation.getCurrentFrame();
	
	return animationState;
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::getCurrentFrame( void )
{
	// Optimize here.
	currentFrame = animation.getCurrentFrame();
	return currentFrame;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setCurrentFrame( int frameIndex )
{
	animation.setCurrentFrame( frameIndex );
	currentFrame = animation.getCurrentFrame();
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::getFrameIndex( void )
{
	// Optimize here?
	return animation.getFrameIndex();
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setFrameIndex( int frameIndex )
{
	animation.setFrameIndex( frameIndex );
	currentFrame = animation.getCurrentFrame();
}

//--------------------------------------------------------------------------------
int CoreVideoSprite::getNumberOfFrames( void )
{
	return numberOfFrames;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::setDisplay( CoreVideoDisplay* display )
{
	this->display = display;
}

//--------------------------------------------------------------------------------
CoreVideoDisplay* CoreVideoSprite::getDisplay( void )
{
	return display;
}

//--------------------------------------------------------------------------------
void CoreVideoSprite::draw( void )
{
	if( display != NULL )
	{
		CoreVideoImage::draw( display, frame[currentFrame], destinationRect );
	}
}
