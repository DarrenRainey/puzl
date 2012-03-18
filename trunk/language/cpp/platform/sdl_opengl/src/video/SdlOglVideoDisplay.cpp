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
#include <puzl/video/SdlOglVideoDisplay.h>

#include <iostream>
using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
SdlOglVideoDisplay::SdlOglVideoDisplay( void ): CoreVideoDisplay()
{
  
}

//--------------------------------------------------------------------------------
SdlOglVideoDisplay::~SdlOglVideoDisplay( void )
{
  
}

//--------------------------------------------------------------------------------
int SdlOglVideoDisplay::initialize( int width, int height, int attributes )
{
  cout << "SdlOglVideoDisplay::initialize()" << endl;
  if( CoreVideoDisplay::initialize( width, height, attributes ) < 0 )
  {
    return -1;
  }

  if( initializeSDLAndOpenGL( attributes ) < 0 )
  {
    return -1;
  }
  
  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho( 0, width,
           height, 0,
           -1, 1 );
  
  glEnable( GL_TEXTURE_2D );
  
  return 0;
}

//--------------------------------------------------------------------------------
int SdlOglVideoDisplay::initializeSDLAndOpenGL( int attributes )
{
  int bitdepth;

  // Get video information about current video mode
  const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
  if( !videoInfo )
  {
    return -1;
  }
  
  if( attributes != 0 )
  {
    // Indicate SDL to use OpenGL.
    attributes |= SDL_OPENGL;// | DISPLAY_ATTRIBUTE_DOUBLE_BUFFER;
    
    // If bitdepth was not specified, use the current video state
    bitdepth = videoInfo->vfmt->BitsPerPixel;

    // Check if the system can use hardware surfaces
    if( videoInfo->hw_available )
    {
      attributes |= SDL_HWSURFACE;
    }
    else
    {
      attributes |= SDL_SWSURFACE;
    }
    
    // Check for hardware blitting
    if( videoInfo->blit_hw )
    {
      attributes |= SDL_HWACCEL;
    }
    
    if( attributes & DISPLAY_ATTRIBUTE_FULLSCREEN )
    {
      fullScreen = true;
    }
    else
    {
      fullScreen = false;
    }
    
    this->attributes = attributes;
  }
  else
  {
    attributes = this->attributes;
  }
  
  // Set OpenGL attributes accordingly
  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );  // 5 bits of red
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );  // 5 bits of green
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 ); // 5 bits of blue
  SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 5 );  // 5 bits of alpha
  //SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
  
  //SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
  
  /*
  if( bitdepth > 16 )
  {
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 1 );  // 5 bits of alpha
  }
  else
  {
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 0 );
  }*/
  
  //SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 ); // 16 bit depth (3D)
  
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );  // Turn on double buffer (MUST?)
  SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 1 );

  // Initialize SDL video.
  surface = SDL_SetVideoMode( *realWidth, *realHeight, bitdepth, attributes );
  if( surface == NULL )
  {
    return -1;
  }
  
  //int alpha_size;
  //SDL_GL_GetAttribute( SDL_GL_ALPHA_SIZE, &alpha_size );
  
  // Set up OpenGL video
  glShadeModel( GL_SMOOTH );      // Shading model = Gouraud

  glCullFace( GL_BACK );        // Standard culling
  glFrontFace( GL_CCW );        // 
  glEnable( GL_CULL_FACE );     // 
  
  //glEnable( GL_BLEND );
  //glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  
  //glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );
  
  //glEdgeFlag( false );

  //glClearColor( 0, 0, 0, 0 );     // Clear color = black
  
  return 0;
}

//--------------------------------------------------------------------------------
void SdlOglVideoDisplay::setDimensions( int width, int height )
{
  CoreVideoDisplay::setDimensions( width, height );
  
  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho( 0, width,
           height, 0,
           -1, 1 );

  glEnable( GL_TEXTURE_2D );
}

//--------------------------------------------------------------------------------
void SdlOglVideoDisplay::setRealDimensions( int width, int height )
{
  CoreVideoDisplay::setRealDimensions( width, height );
  
  if( initializeSDLAndOpenGL( attributes ) < 0 )
  {
    return;
  }
  
  glViewport( 0, 0, width, height );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho( 0, *( this->width ),
           *( this->height ), 0,
           -1, 1 );

  glEnable( GL_TEXTURE_2D );
}

//--------------------------------------------------------------------------------
int SdlOglVideoDisplay::shutdown( void )
{
  return CoreVideoDisplay::shutdown();
}

//--------------------------------------------------------------------------------
int SdlOglVideoDisplay::reset( int width, int height, int bitdepth, int attributes )
{
  /*
  if( attributes == 0 )
  {
    //attributes = SDL_OPENGL | SDL_HWPALETTE | SDL_RLEACCEL | SDL_RESIZABLE | SDL_ANYFORMAT;
    attributes = SDL_OPENGL | SDL_HWSURFACE | SDL_HWACCEL | SDL_RESIZABLE;
  }
  
  surface = SDL_SetVideoMode( width, height, bitdepth, attributes );
  if( surface == NULL )
  {
    return -1;
  }
  
  glViewport( 0, 0, width, height );
  
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  
  glEnable( GL_TEXTURE_2D );
  */
  
  return 0;
}

//--------------------------------------------------------------------------------
void SdlOglVideoDisplay::setBackgroundColor( int red, int green, int blue )
{
  CoreVideoDisplay::setBackgroundColor( red, green, blue );
  glClearColor( ( float )red / 255.0f, ( float )green / 255.0f, ( float )blue / 255.0f, 1.0f );
}

//--------------------------------------------------------------------------------
void SdlOglVideoDisplay::drawRectangle( int xPosition, int yPosition,
                                        int width, int height,
                                        int red, int green, int blue, int alpha )
{ 
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity(); // Reset The matrix
  
  glDisable( GL_TEXTURE_2D );
  
  // Get current OpenGL color and back it up temporarily  
  glColor4ub( red, green, blue, alpha ); // NOTE This is where we utilize alphablending!!!
  
  // Set the position where the rectangle is to drawn on the display
  glTranslatef( ( float )xPosition, ( float )yPosition, 0.0f );

  // Draw the 'tile' to the screen
  glBegin( GL_QUADS );
    
    // Display the top left vertice
    glVertex2i( 0, 0 );
    
    // Display the bottom left vertice
    glVertex2i( 0, height );
    
    // Display the bottom right vertice
    glVertex2i( width, height );
    
    // Display the top right vertice
    glVertex2i( width, 0 );
  
  glEnd();
  
  glEnable( GL_TEXTURE_2D );
}

//--------------------------------------------------------------------------------
void SdlOglVideoDisplay::drawRectangle( int xPosition, int yPosition,
                                        int width, int height )
{
  CoreVideoDisplay::drawRectangle( xPosition, yPosition, width, height );
}

//--------------------------------------------------------------------------------
void SdlOglVideoDisplay::clear( void )
{
  //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glClear( GL_COLOR_BUFFER_BIT );  // Just clears the screen!
}

//--------------------------------------------------------------------------------
void SdlOglVideoDisplay::present( void )
{
  SDL_GL_SwapBuffers();
}
