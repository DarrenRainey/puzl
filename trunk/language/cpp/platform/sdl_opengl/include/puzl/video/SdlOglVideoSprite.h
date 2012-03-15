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

#ifndef SDL_OGL_VIDEO_SPRITE
#define SDL_OGL_VIDEO_SPRITE

// INCLUDES ======================================================================
#include <puzl/video/CoreVideoSprite.h>
#include <puzl/video/CoreVideoImage.h>

// DEFINES =======================================================================

// TYPES =========================================================================
class SdlOglVideoSprite: public CoreVideoSprite
{
public:
  SdlOglVideoSprite( CoreVideoImage& videoImage, int width, int height, int numberOfFrames, int attributes );
	~SdlOglVideoSprite( void );
};

#endif
