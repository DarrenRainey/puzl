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
#include <puzl/video/AndroidVideoDisplay.h>

#include <GLES/gl.h>
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>

#include <iostream>
using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
AndroidVideoDisplay::AndroidVideoDisplay( void ): CoreVideoDisplay()
{

}

//--------------------------------------------------------------------------------
AndroidVideoDisplay::~AndroidVideoDisplay( void )
{

}

//--------------------------------------------------------------------------------
int AndroidVideoDisplay::initialize( int width, int height, int attributes )
{
  cout << "AndroidVideoDisplay::initialize()" << endl;
  if( CoreVideoDisplay::initialize( width, height, attributes ) < 0 )
  {
    return -1;
  }

  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrthof( 0, width,
            height, 0,
            -1, 1 );

  glEnableClientState( GL_VERTEX_ARRAY );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glEnable( GL_CULL_FACE );
  glFrontFace( GL_CCW );
  glCullFace( GL_BACK );
  glEnable( GL_BLEND );
  glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NEAREST );

  return 0;
}

//--------------------------------------------------------------------------------
void AndroidVideoDisplay::setDimensions( int width, int height )
{
  CoreVideoDisplay::setDimensions( width, height );
}

//--------------------------------------------------------------------------------
void AndroidVideoDisplay::setRealDimensions( int width, int height )
{
  CoreVideoDisplay::setRealDimensions( width, height );
}

//--------------------------------------------------------------------------------
int AndroidVideoDisplay::shutdown( void )
{
  return CoreVideoDisplay::shutdown();
}

//--------------------------------------------------------------------------------
int AndroidVideoDisplay::reset( int width, int height, int bitdepth, int attributes )
{
  return 0;
}

//--------------------------------------------------------------------------------
void AndroidVideoDisplay::setBackgroundColor( int red, int green, int blue )
{
  CoreVideoDisplay::setBackgroundColor( red, green, blue );

  glClearColor( ( float )red / 255.0f , ( float )green / 255.0f, ( float )blue / 255.0f, 1.0f );
}

//--------------------------------------------------------------------------------
void AndroidVideoDisplay::drawRectangle( int xPosition, int yPosition,
                                         int width, int height,
                                         int red, int green, int blue, int alpha )
{
  static GLfloat quad[] =
  {
    0.0f, 0.0f, // 0, 0,
    0.0f, 0.0f, // 0, height,
    0.0f, 0.0f, // width, height,
    0.0f, 0.0f  // width, 0
  };

  quad[3] = ( float )height;
  quad[4] = ( float )width;
  quad[5] = ( float )height;
  quad[6] = ( float )width;

  glVertexPointer( 2, GL_FLOAT, 0, quad );

  glDisable( GL_TEXTURE_2D );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glTranslatef( ( float )xPosition, ( float )yPosition, 0.0f );

  glColor4ub( red, green, blue, alpha );

  glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );
}

//--------------------------------------------------------------------------------
void AndroidVideoDisplay::drawRectangle( int xPosition, int yPosition,
                                         int width, int height )
{
  drawRectangle( xPosition, yPosition,
                 width, height,
                 backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3] );
}

//--------------------------------------------------------------------------------
void AndroidVideoDisplay::clear( void )
{
  glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
}
