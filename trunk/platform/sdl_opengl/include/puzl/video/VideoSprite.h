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
// VideoSprite.h
// Authors:  Andrew Dieffenbach
// Date:     March 28, 2004
// Description:
// Display class inherits from Bitmap
//
// NOTE:  This version uses SDL and OpenGL
// 
//================================================================================

// Watch for multiple inclusions
#ifndef VIDEO_SPRITE
#define VIDEO_SPRITE

// INCLUDES ======================================================================

// Add the SDL and OpenGL header files for appropriate OS builds
//#include <SDL/SDL.h>
//#include <SDL/SDL_opengl.h>

/*
#ifdef WINDOWS
	#include <windows.h>
	#include <SDL/SDL_image.h>
#endif
#ifdef MACOSX
	#include <SDL_image/SDL_image.h>
#endif
#ifdef LINUX
	#include <SDL/SDL_image.h>
#endif
*/
#include "puzl/video/VideoImage.h"			// VideoImage class header file
#include "puzl/video/VideoDisplay.h"			// VideoDisplay class header file
#include "puzl/utility/Script.h"				// Script class header file

// DEFINES =======================================================================

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif

#define SPRITE_STATE_ANIM_RUNNING	1	// Sprite is done animating
#define SPRITE_STATE_ANIM_DONE		2	// Sprite is currently animating
#define SPRITE_STATE_ANIM_RESET		4	// Sprite is has reset animation
#define SPRITE_STATE_DEAD		8	// Sprite is dead
#define SPRITE_STATE_ALIVE		16	// Sprite is alive
#define SPRITE_STATE_DYING		32	// Sprite is dying
#define SPRITE_STATE_CUSTOM_0		64	// Custom state for sprite 0.
#define SPRITE_STATE_CUSTOM_1		128	// Custom state for sprite 1.
#define SPRITE_STATE_CUSTOM_2		256	// Custom state for sprite 2.
#define SPRITE_STATE_CUSTOM_3		512	// Custom state for sprite 3.

#define SPRITE_ATTRIBUTE_SINGLE_FRAME	1	// Sprite has single frame
#define SPRITE_ATTRIBUTE_MULTI_FRAME	2	// Sprite has multiple frames
#define SPRITE_ATTRIBUTE_MULTI_ANIM	4	// Sprite has multiple animations
#define SPRITE_ATTRIBUTE_ANIM_ONE_SHOT	8	// Sprite will perform the animation once
#define SPRITE_ATTRIBUTE_VISIBLE	16	// Sprite is visible
#define SPRITE_ATTRIBUTE_BOUNCE		32	// Sprite bounces off edges
#define SPRITE_ATTRIBUTE_WRAPAROUND	64	// Sprite wraps around edges
#define SPRITE_ATTRIBUTE_LOADED		128	// Sprite has been loaded
#define SPRITE_ATTRIBUTE_CLONE		256	// Sprite is a clone

#define SPRITE_ATTRIBUTE_TRANSPARENCY	512	// Indicates sprite with transparency
#define SPRITE_ATTRIBUTE_ALPHABLEND	1024	// Indicates sprite with alpha/semi transparency
#define SPRITE_ATTRIBUTE_COLOR		2048	// Indicates sprite with color modulation

#define SPRITE_COLLISION_RECT		0	// Only check if two sprite rectangles intersect
#define SPRITE_COLLISION_PIXEL		1	// Also check if pixels from two sprite intersect

#define EXTRACT_MODE_CELL		0	// Mode to extract a cell from a bitmap for sprite
#define EXTRACT_MODE_ABS		1	// Mode to extract the bitmap for a sprite

// TYPES =========================================================================

// VideoSprite class
class VideoSprite : public VideoImage
{
public:
	//VideoSprite();
	VideoSprite( VideoImage &videoImage, int width, int height, int numberOfFrames, int attributes );
	~VideoSprite();
	
	int destroy();				// Remove the sprite
	
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
	
	int getXPosition();			// Get virtual X coordinate
	int getYPosition();			// Get virtual Y coordinate
	
	void setXPosition( int xPosition );	// Set horizontal position
	void setYPosition( int yPosition );	// Set vertical position
	
	void setPosition( int xPosition,	// Set virtual X/Y coordinates
			  int yPosition );	// 
	
	int getXVelocity();			// Get horizontal velocity/speed/delta
	int getYVelocity();			// Get vertical velocity/speed/delta
	
	void setXVelocity( int xVelocity );	// Set horizontal velocity
	void setYVelocity( int yVelocity );	// Set vertical velocity
	
	void setVelocity( int xVelocity,	// Set horizontal/vertical velocities
			  int yVelocity );	// 
	
	void move();				// Moves sprite based on position/velocity
	
	int getAngularVelocity();
	void setAngularVelocity( float angularVelocity );
	
	void rotate();
	
	int getState();				// Get state of sprite
	void setState( int state );		// Set state of sprite
	
	int show();				// Makes sprite visible
	int hide();				// Makes sprite invisible
	
	//int getAttributes( int attributes );	// Get the attributes of the sprite
	
	int loadFrame( int frameIndex,		 // 
		       int cellx, int celly,	 // 
		       int mode );		 // 
	
	int loadAnimation( int animationIndex,	// Load an animation script
			   int numberOfFrames,	// 
			   int *sequence );	// 
	
	int getAnimation();			// Get the current animation set
	void setAnimation( int animationIndex );	// Set the current animation set
	
	void setAnimationSpeed( int speed );	// Set the animation speed (cycles per frame)
	int getAnimationSpeed();		// Get the animation speed (cycles per frame)
	
	int getAnimationCounter();		// Get the time elapsed between animation frames
	
	int animate();				// Changes image frame based on animation settings
	
	int getCurrentFrame();			// Gets the current frame to be drawn
	void setCurrentFrame( int frameIndex );	// Sets the current frame to be drawn
	
	int getFrameIndex();			// 
	void setFrameIndex( int frameIndex );	// 
	
	int getNumberOfFrames();
	
	void setDisplay( VideoDisplay* display );
	VideoDisplay* getDisplay();
	
	void draw();
	
protected:
	int destinationRect[4];
	
	int* width;
	int* height;
	
	int realWidth;
	int realHeight;
	
	bool scale;
	float xScale;
	float yScale;
	
	int* xPosition;				// Virtual X coordinate
	int* yPosition;				// Virtual Y coordinate (upper left corner)
	
	int xVelocity;				// Horizontal speed/delta
	int yVelocity;				// Vertical speed/delta
	
	float angularVelocity;
	
	int state;				// General state of sprite
	int attributes;				// Attributes concerning sprite
	
	Script animation;			// Animation scripting service
	int currentFrame;
	
	int** frame;				// 
	int numberOfFrames;
	
	VideoDisplay* display;
};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
