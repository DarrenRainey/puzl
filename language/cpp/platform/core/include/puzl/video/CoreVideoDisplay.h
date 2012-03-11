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

#ifndef CORE_VIDEO_DISPLAY
#define CORE_VIDEO_DISPLAY

// INCLUDES ======================================================================
#include <puzl/video/CoreVideoImage.h>

// DEFINES =======================================================================

// TYPES =========================================================================
class CoreVideoDisplay: public CoreVideoImage
{
public:
  CoreVideoDisplay( void );
	~CoreVideoDisplay( void );

	virtual int initialize( int width, int height, int attributes = 0 );
	virtual int shutdown( void );
	virtual int reset( int width, int height, int bitdepth, int attributes );
		   
	virtual void setDimensions( int width, int height );
	virtual void setRealDimensions( int width, int height );

	virtual bool isFullscreen( void );
  
  virtual void setBackgroundColor( int red, int green, int blue );
	virtual void setForegroundColor( int red, int green, int blue );
  
	virtual void drawRectangle( int xPosition, int yPosition,
	                            int width, int height,
	                            int red, int green, int blue,
	                            int alpha = 255 );
	
	virtual void drawRectangle( int xPosition, int yPosition,
	                            int width, int height,
	                            int color[] );
  
  virtual void drawRectangle( int xPosition, int yPosition,
                              int width, int height );

	virtual void clear( void );

protected:
	bool fullScreen;

  int backgroundColor[3];
  int foregroundColor[4];
  
private:
	int attributes;
};

#endif
