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

#ifndef ANDROID_VIDEO_DISPLAY
#define ANDROID_VIDEO_DISPLAY

// INCLUDES ======================================================================
#include <puzl/video/CoreVideoDisplay.h>

// DEFINES =======================================================================
#define DISPLAY_ATTRIBUTE_EMULATE         0
#define DISPLAY_ATTRIBUTE_PALETTE         1
#define DISPLAY_ATTRIBUTE_DOUBLE_BUFFER   2
#define DISPLAY_ATTRIBUTE_FULLSCREEN      3
#define DISPLAY_ATTRIBUTE_RESIZABLE       4
#define DISPLAY_ATTRIBUTE_NOFRAME         5

// TYPES =========================================================================
class AndroidVideoDisplay: public CoreVideoDisplay
{
public:
  AndroidVideoDisplay( void );
  ~AndroidVideoDisplay( void );

  int initialize( int width, int height, int attributes = 0 );
  int shutdown( void );
  int reset( int width, int height, int bitdepth, int attributes );

  void setDimensions( int width, int height );
  void setRealDimensions( int width, int height );

  void setBackgroundColor( int red, int green, int blue );

  void drawRectangle( int x0, int y0,
                      int x1, int y1,
                      int red, int green, int blue,
                      int a = 255 );

  void drawRectangle( int xPosition, int yPosition,
                      int width, int height );

  void clear( void );

  void update( void );

private:
  bool updateBackgroundColor;
};

#endif
