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

#ifndef CORE_VIDEO_SPRITE
#define CORE_VIDEO_SPRITE

// INCLUDES ======================================================================
#include <puzl/video/CoreVideoImage.h>
#include <puzl/video/CoreVideoDisplay.h>
#include <puzl/utility/Operation.h>

// DEFINES =======================================================================
#define SPRITE_STATE_ANIM_RUNNING	     1	 // Sprite is done animating
#define SPRITE_STATE_ANIM_DONE		     2	 // Sprite is currently animating
#define SPRITE_STATE_ANIM_RESET		     4	 // Sprite is has reset animation
#define SPRITE_STATE_DEAD		           8	 // Sprite is dead
#define SPRITE_STATE_ALIVE		         16	 // Sprite is alive
#define SPRITE_STATE_DYING		         32	 // Sprite is dying
#define SPRITE_STATE_CUSTOM_0		       64	 // Custom state for sprite 0.
#define SPRITE_STATE_CUSTOM_1		       128 // Custom state for sprite 1.
#define SPRITE_STATE_CUSTOM_2		       256 // Custom state for sprite 2.
#define SPRITE_STATE_CUSTOM_3		       512 // Custom state for sprite 3.

#define SPRITE_ATTRIBUTE_SINGLE_FRAME	 1	  // Sprite has single frame
#define SPRITE_ATTRIBUTE_MULTI_FRAME	 2	  // Sprite has multiple frames
#define SPRITE_ATTRIBUTE_MULTI_ANIM	   4	  // Sprite has multiple animations
#define SPRITE_ATTRIBUTE_ANIM_ONE_SHOT 8	  // Sprite will perform the animation once
#define SPRITE_ATTRIBUTE_VISIBLE	     16	  // Sprite is visible
#define SPRITE_ATTRIBUTE_BOUNCE		     32	  // Sprite bounces off edges
#define SPRITE_ATTRIBUTE_WRAPAROUND	   64	  // Sprite wraps around edges
#define SPRITE_ATTRIBUTE_LOADED		     128  // Sprite has been loaded
#define SPRITE_ATTRIBUTE_CLONE		     256  // Sprite is a clone

#define SPRITE_ATTRIBUTE_TRANSPARENCY	 512	// Indicates sprite with transparency
#define SPRITE_ATTRIBUTE_ALPHABLEND	   1024	// Indicates sprite with alpha/semi transparency
#define SPRITE_ATTRIBUTE_COLOR		     2048	// Indicates sprite with color modulation

#define SPRITE_COLLISION_RECT		       0	// Only check if two sprite rectangles intersect
#define SPRITE_COLLISION_PIXEL		     1	// Also check if pixels from two sprite intersect

#define EXTRACT_MODE_CELL		           0	// Mode to extract a cell from a bitmap for sprite
#define EXTRACT_MODE_ABS		           1	// Mode to extract the bitmap for a sprite

// TYPES =========================================================================
class CoreVideoSprite: public CoreVideoImage
{
public:
	CoreVideoSprite( CoreVideoImage& videoImage, int width, int height, int numberOfFrames, int attributes );
	~CoreVideoSprite( void );
	
	virtual int destroy( void );
	
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
	
	virtual int getXPosition( void );			                 // Get virtual X coordinate
	virtual int getYPosition( void );			                 // Get virtual Y coordinate
	
	virtual void setXPosition( int xPosition );	           // Set horizontal position
	virtual void setYPosition( int yPosition );	           // Set vertical position
	
	virtual void setPosition( int xPosition, int yPosition );	// Set virtual X/Y coordinates
	
	virtual int getXVelocity( void );			                 // Get horizontal velocity/speed/delta
	virtual int getYVelocity( void );			                 // Get vertical velocity/speed/delta
	
	virtual void setXVelocity( int xVelocity );	           // Set horizontal velocity
	virtual void setYVelocity( int yVelocity );	           // Set vertical velocity
	
	virtual void setVelocity( int xVelocity, int yVelocity ); // Set horizontal/vertical velocities
	
	virtual void move( void );				                     // Moves sprite based on position/velocity
	
	virtual int getAngularVelocity( void );
	virtual void setAngularVelocity( float angularVelocity );
	
	virtual void rotate( void );
	
	virtual int getState( void );				                   // Get state of sprite
	virtual void setState( int state );		                 // Set state of sprite
	
	virtual int show( void );				                       // Makes sprite visible
	virtual int hide( void );				                       // Makes sprite invisible
	
	virtual void draw( void );

	int loadFrame( int frameIndex, int cellx, int celly, int mode );
	
	int loadAnimation( int animationIndex, int numberOfFrames, int *sequence );
	
	int getAnimation( void );			                 // Get the current animation set
	void setAnimation( int animationIndex );	     // Set the current animation set
	
	void setAnimationSpeed( int speed );	         // Set the animation speed (cycles per frame)
	int getAnimationSpeed( void );		             // Get the animation speed (cycles per frame)
	
	int getAnimationCounter( void );		           // Get the time elapsed between animation frames
	
	int animate( void );				                   // Changes image frame based on animation settings
	
	int getCurrentFrame( void );			             // Gets the current frame to be drawn
	void setCurrentFrame( int frameIndex );	       // Sets the current frame to be drawn
	
	int getFrameIndex( void );			               //
	void setFrameIndex( int frameIndex );	         //
	
	int getNumberOfFrames( void );
	
	void setDisplay( CoreVideoDisplay* display );
	CoreVideoDisplay* getDisplay( void );
	
protected:
	int destinationRect[4];
	
	int* width;
	int* height;
	
	int realWidth;
	int realHeight;
	
	bool scale;
	float xScale;
	float yScale;
	
	int* xPosition;				                        // Virtual X coordinate
	int* yPosition;				                        // Virtual Y coordinate (upper left corner)
	
	int xVelocity;				                        // Horizontal speed/delta
	int yVelocity;				                        // Vertical speed/delta
	
	float angularVelocity;
	
	int state;				                            // General state of sprite
	int attributes;				                        // Attributes concerning sprite
	
	Operation animation;			                    // Animation scripting service
	int currentFrame;
	
	int** frame;				                          //
	int numberOfFrames;
	
	CoreVideoDisplay* display;
};

#endif
