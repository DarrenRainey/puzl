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
#include <puzl/video/CoreVideoDisplay.h>

#include <iostream>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================
//--------------------------------------------------------------------------------
CoreVideoDisplay::CoreVideoDisplay( void )
{
  fullScreen = false;
  attributes = 0;
}


//--------------------------------------------------------------------------------
CoreVideoDisplay::~CoreVideoDisplay( void )
{

}

//--------------------------------------------------------------------------------
int CoreVideoDisplay::initialize( int width, int height, int attributes )
{
  *realWidth = *( this->width ) = width;
  *realHeight = *( this->height ) = height;
  this->attributes = attributes;
  
  return 0;
}

//--------------------------------------------------------------------------------
void CoreVideoDisplay::setDimensions( int width, int height )
{
  *( this->width ) = width;
  *( this->height ) = height;
}

//--------------------------------------------------------------------------------
void CoreVideoDisplay::setRealDimensions( int width, int height )
{
  CoreVideoImage::setRealDimensions( width, height );
}

//--------------------------------------------------------------------------------
int CoreVideoDisplay::shutdown( void )
{
  fullScreen = false;
  return 0;
}

//--------------------------------------------------------------------------------
int CoreVideoDisplay::reset( int width, int height, int bitdepth, int attributes )
{
  return 0;
}

//--------------------------------------------------------------------------------
bool CoreVideoDisplay::isFullscreen( void )
{
  return fullScreen;
}

//--------------------------------------------------------------------------------
void CoreVideoDisplay::setBackgroundColor( int red, int green, int blue )
{
  backgroundColor[0] = red;
  backgroundColor[1] = green;
  backgroundColor[2] = blue;
}

//--------------------------------------------------------------------------------
void CoreVideoDisplay::setForegroundColor( int red, int green, int blue )
{
  foregroundColor[0] = red;
  foregroundColor[1] = green;
  foregroundColor[2] = blue;
}

//--------------------------------------------------------------------------------
void CoreVideoDisplay::drawRectangle( int xPosition, int yPosition,
                                      int width, int height,
                                      int red, int green, int blue, int alpha )
{
  
}

//--------------------------------------------------------------------------------
void CoreVideoDisplay::drawRectangle( int xPosition, int yPosition,
                                      int width, int height,
                                      int color[] )
{
  drawRectangle( xPosition, yPosition,
                 width, height,
                 color[0], color[1], color[2] );
}

//--------------------------------------------------------------------------------
void CoreVideoDisplay::drawRectangle( int xPosition, int yPosition,
                                      int width, int height )
{
  drawRectangle( xPosition, yPosition,
                 width, height,
                 foregroundColor[0], foregroundColor[1], foregroundColor[2] );
}

//--------------------------------------------------------------------------------
void CoreVideoDisplay::clear( void )
{

}
