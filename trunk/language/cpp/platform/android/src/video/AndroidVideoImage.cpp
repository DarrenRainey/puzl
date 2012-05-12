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

#include <puzl/utility/AndroidGameShell.h>
#include <puzl/video/AndroidVideoDisplay.h>

#include <iostream>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

extern AndroidGameShell* _GameShell;

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
  if( textureID != 0 )
  {
    glDeleteTextures( 1, &textureID );
    textureID = 0;
  }

  return CoreVideoImage::release();
}

//--------------------------------------------------------------------------------
int AndroidVideoImage::load( string fileName, int numberOfColorKeys, int** colorKey )
{
  textureID = _GameShell->createTextureFromFile( fileName, realWidth, realHeight );
  setRealDimensions( *realWidth, *realHeight );
  setDimensions( *realWidth, *realHeight );
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
  AndroidVideoImage::draw( destinationDisplay, sourceRect, destinationRect );
}

//--------------------------------------------------------------------------------
void AndroidVideoImage::draw( AndroidVideoDisplay* destinationDisplay, int* sourceRect, int* destinationRect )
{
  static GLfloat quad[] =
  {
    0.0f, 0.0f, // 0, 0,
    0.0f, 0.0f, // 0, height,
    0.0f, 0.0f, // width, height,
    0.0f, 0.0f  // width, 0
  };

  static GLfloat textureQuad[] =
  {
    0.0f, 0.0f, // 0, 0,
    0.0f, 1.0f, // 0, height,
    1.0f, 1.0f, // width, height,
    1.0f, 0.0f  // width, 0
  };

  quad[3] = ( GLfloat )( destinationRect[RECT_INDEX_HEIGHT] ); // height
  quad[4] = ( GLfloat )( destinationRect[RECT_INDEX_WIDTH] ); // width
  quad[5] = quad[3]; //quad[5] = ( float )height;
  quad[6] = quad[4]; //quad[6] = ( float )width;

  glBindTexture( GL_TEXTURE_2D, textureID );

  glEnable( GL_TEXTURE_2D );

  glEnableClientState( GL_TEXTURE_COORD_ARRAY );

  glVertexPointer( 2, GL_FLOAT, 0, quad );
  glTexCoordPointer( 2, GL_FLOAT, 0, textureQuad );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glTranslatef( ( GLfloat )destinationRect[RECT_INDEX_X_POSITION],
                ( GLfloat )destinationRect[RECT_INDEX_Y_POSITION],
                0.0f );

  glColor4ub( 255, 255, 255, 255 );

  glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
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
