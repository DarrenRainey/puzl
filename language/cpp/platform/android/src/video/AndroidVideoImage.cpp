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
#include <puzl/video/AndroidVideoImage.h>
#include <puzl/video/AndroidVideoDisplay.h>

#include <iostream>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
AndroidVideoImage::AndroidVideoImage( void ): CoreVideoImage()
{
  
}

//--------------------------------------------------------------------------------
AndroidVideoImage::AndroidVideoImage( AndroidVideoImage& videoImage ): CoreVideoImage( videoImage )
{

}

//--------------------------------------------------------------------------------
AndroidVideoImage::~AndroidVideoImage( void )
{

}

//--------------------------------------------------------------------------------
void AndroidVideoImage::setRealDimensions( int width, int height )
{
  CoreVideoImage::setRealDimensions( width, height );
}

//--------------------------------------------------------------------------------
int AndroidVideoImage::create( int width, int height, int attributes, int numberOfColorKeys )
{
  return 0;
}

//--------------------------------------------------------------------------------
int AndroidVideoImage::destroy( void )
{
  return CoreVideoImage::destroy();
}

//--------------------------------------------------------------------------------
int AndroidVideoImage::release( void )
{
  return CoreVideoImage::release();
}

//--------------------------------------------------------------------------------
int AndroidVideoImage::load( string fileName, int numberOfColorKeys, int** colorKey )
{
  return 0;
}

//--------------------------------------------------------------------------------
int AndroidVideoImage::reload( void )
{
  return 0;
}

//--------------------------------------------------------------------------------
void AndroidVideoImage::draw( AndroidVideoDisplay* destinationDisplay )
{
  CoreVideoImage::draw( destinationDisplay ); // TODO: Needed?
}

//--------------------------------------------------------------------------------
void AndroidVideoImage::draw( AndroidVideoDisplay* destinationDisplay, int* sourceRect, int* destinationRect )
{
  // TODO: Implement.
}

//--------------------------------------------------------------------------------
void AndroidVideoImage::draw( AndroidVideoImage* destinationBitmap, int* sourceRect, int* destinationRect )
{
  // TODO: Implement.
}

//--------------------------------------------------------------------------------
void AndroidVideoImage::clear( void )
{
  // TODO: Implement.
}
