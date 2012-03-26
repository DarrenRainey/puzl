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

#ifndef ANDROID_VIDEO_IMAGE
#define ANDROID_VIDEO_IMAGE

// INCLUDES ======================================================================
#include <puzl/video/CoreVideoImage.h>

#include <string>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

class AndroidVideoDisplay;

class AndroidVideoImage: public CoreVideoImage
{
public:
  AndroidVideoImage( void );
  AndroidVideoImage( AndroidVideoImage& videoImage );
  ~AndroidVideoImage( void );

  void draw( AndroidVideoDisplay* destinationDisplay );
  void draw( AndroidVideoDisplay* destinationDisplay, int* sourceRect, int* destinationRect );
  void draw( AndroidVideoImage* destinationImage, int* sourceRect = NULL, int* destinationRect = NULL );

  void clear( void );

  void setRealDimensions( int width, int height );

  int create( int width, int height, int attributes = IMAGE_ATTRIBUTE_SIMPLE, int numberOfColorKeys = 0 );
  int destroy( void );
  int release( void );
  int load( string fileName, int numberOfColorKeys = 0, int** colorKey = NULL );
  int reload( void );

private:
};

#endif
