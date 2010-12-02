//================================================================================
// VideoBitmap.cpp
// Authors:  Andrew Dieffenbach
// Date:     March 28, 2004
// Description:
// Display class derives from Bitmap
// 
// NOTE:  This version uses SDL and OpenGL
// 
//================================================================================

// INCLUDES ======================================================================

// Add the SDL and OpenGL header files for appropriate OS builds
#include <SDL/SDL.h>

#ifdef WINDOWS
	#include <windows.h>
	#include <SDL/SDL_image.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif
#ifdef MACOSX
	#include <SDL_image/SDL_image.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#endif
#ifdef LINUX
	#include <SDL/SDL_image.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include "puzl/video/VideoBuffer.h"		// VideoBuffer header file
#include "puzl/video/VideoBitmap.h"		// VideoBitmap header file
#include "puzl/video/VideoDisplay.h"		// VideoDisplay header file

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// Name: VideoBitmap::VideoBitmap()
// Description:
// Default Constructor
//--------------------------------------------------------------------------------
VideoBitmap::VideoBitmap( void )
{
	int defaultColor[] = { 255, 255, 255, 255 };	// Default color for color blending
	
	// Set default values
	SetAlphaLevel( 255 );
	
	SetColorBlend( false );
	SetColor( defaultColor );
	
	ColorKey = true;
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::~VideoBitmap()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
VideoBitmap::~VideoBitmap( void )
{
	Destroy();
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::GetSurface()
// Description:
// DEFUNCT?
//--------------------------------------------------------------------------------
SDL_Surface* VideoBitmap::GetSurface( void )
{
	SDL_Surface *Surface = NULL;

	return( Surface );	// NOTE FIX!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

//--------------------------------------------------------------------------------
// Name: VideoBitmap::Create()
// Description:
// 
// Creates or initializes this VideoBitmap
//--------------------------------------------------------------------------------
int VideoBitmap::Create( int width, int height,
			 int bitdepth, int attributes )
{
	int rmask, gmask, bmask, amask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif
	
	// Check to see if this bitmap's surface buffer is "clear" to use
//	if( !Surface )
	
	if( 1 )
	{
		//SDL_Surface *Surface;

		SDL_Surface *temporarySurface;
		
		if( bitdepth == 0 )
		{
			const SDL_VideoInfo *video_info = SDL_GetVideoInfo();
			
			bitdepth = video_info->vfmt->BitsPerPixel;
		}
		
		temporarySurface = SDL_CreateRGBSurface( SDL_HWSURFACE,
							 width, height, bitdepth,
							 rmask, gmask, bmask, amask );
		
		// Convert the surface format to that of main display
		Surface = SDL_DisplayFormat( temporarySurface );
		SDL_FreeSurface( temporarySurface );

		// Exit if the surface buffer was created unsuccessfully
		if( Surface == NULL )
			return( FAILURE );
		else
		{
			// Clear our new surface ( black = 0 )
			SDL_FillRect( Surface, NULL , SDL_MapRGB( Surface->format, 0, 255, 0 ) );
	
			// Check if a bitmap with a transparent color key was requested
			if( attributes & BITMAP_TRANSPARENCY )
			{
				// Set default transparent color to black RGB(0,0,0)
				ColorKey = true;
			}
			else
				ColorKey = false;
	
			// Check if a bitmap with a alpha transparency was requested
			if( attributes & BITMAP_ALPHABLEND )
			{
				// Set alpha blending to default
				AlphaBlend = true;	// Create function for this?!?!?!?!?!
			}
			
			// Check if a bitmap with a color blend/modulation was requested
			if( attributes & BITMAP_COLOR )
			{
				// Set color blending/modulation to default
				SetColorBlend( true );
			}
			
			// Create the OpenGL texture from the SDL surface
			return( CreateTexture( Surface, ColorKey ) );
		}
	}
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::Destroy()
// Description:
// Releases the memory reserved for this VideoBitmap
//--------------------------------------------------------------------------------
int VideoBitmap::Destroy( void )
{
/*
	// Check to see if this bitmap is valid to "destroy"
	if( Surface != NULL )
	{
		// Free memory used by surface
		SDL_FreeSurface( Surface );
		
		// Check for successful freeing of memory
		if( Surface )
			return( -1 );
		else
			return( 0 );

	}
	else
	{
		Surface = NULL;

		return( 0 );
	}
*/
	// Get video information about current video mode
	const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
	if( !videoInfo )
		return( FAILURE );
	
	int bitdepth = videoInfo->vfmt->BitsPerPixel;
	
	if( bitdepth > 16 )
	{
		
	}
	else
	{	
		// Release the SDL surface
		if( Surface )
		{
			SDL_FreeSurface( Surface );
			Surface = NULL;
		}
	}
	
	glDeleteTextures( 1, &Texture );
	Texture = 0;
	
	return( SUCCESS );
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::Load()
// Description:
// Loads a graphics file (BMP, PNG; etc.) into this VideoBitmap
//--------------------------------------------------------------------------------
int VideoBitmap::Load( string fileName )
{
	SDL_Surface *temporarySurface;
	
	if( Surface )
		Destroy();
	
	// Load the image from file
	temporarySurface = IMG_Load( fileName.c_str() );
	
	// Convert the surface format to that of the passed 'ExampleBuffer'
	Surface = SDL_DisplayFormat( temporarySurface );
	
	SDL_FreeSurface( temporarySurface );

	// Exit if the surface buffer was created unsuccessfully
	if( Surface == NULL )
		return( FAILURE );
	else
		return( CreateTexture( Surface, true ) );
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::HasColorKey()
// Description:
// 
//--------------------------------------------------------------------------------
bool VideoBitmap::HasColorKey( void )
{
	return( ColorKey );
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::ToggleColorKey()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoBitmap::ToggleColorKey( bool setting )
{/*
	if( Texture == NULL )
		return;
	
	if( ColorKey )
	{
		
	}
	else
	{
		
}*/
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::HasAlphaBlend()
// Description:
// 
// Test to see if alpha-blending is enabled for this VideoBitmap
//--------------------------------------------------------------------------------
bool VideoBitmap::HasAlphaBlend( void )
{
	return( AlphaBlend );
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::GetAlphaLevel()
// Description:
// 
// Gets the alpha-blending level specified for this VideoBitmap
//--------------------------------------------------------------------------------
int VideoBitmap::GetAlphaLevel( void )
{
	return( AlphaLevel );
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::SetAlphaLevel()
// Description:
// 
// Sets the alpha-blending level for this VideoBitmap
//--------------------------------------------------------------------------------
void VideoBitmap::SetAlphaLevel( int level )
{
	AlphaLevel = level;

	//SDL_SetAlpha( Surface, SDL_SRCALPHA, AlphaLevel );
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::HasColorBlend()
// Description:
// 
//--------------------------------------------------------------------------------
bool VideoBitmap::HasColorBlend( void )
{
	return( ColorBlend );
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::SetColorBlend()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoBitmap::SetColorBlend( bool setting )
{
	ColorBlend = setting;	
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::GetColor()
// Description:
// 
//--------------------------------------------------------------------------------
int* VideoBitmap::GetColor( void )
{
	return( Color );
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::SetColor()
// Description:
// 
//--------------------------------------------------------------------------------
void VideoBitmap::SetColor( int color[] )
{
	// Set the color modulation RGB components of this VideoBitmap (OPTIMIZE LATER)
	Color[0] = color[0];
	Color[1] = color[1];
	Color[2] = color[2];
	Color[3] = color[3];
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::CreateTexture()
// Description:
// 
// Creates an OpenGL texture from a SDL Surface.
// Currently sets mipmap with the GL_NEAREST option (no smoothening).
//--------------------------------------------------------------------------------
int VideoBitmap::CreateTexture( SDL_Surface *surface, bool hasTransparency )
{
	int index;
	
	// Generate a texture into the Texture ID TODO This really how I should do this (needed?)?
	//if( Texture )
	//	glDeleteTextures( 1, &Texture );
	//	Texture = 0;
	
	glGenTextures( 1, &Texture );
	
	// Bind and initialize the texture
	glBindTexture( GL_TEXTURE_2D, Texture );
	
	// Set our VideoBitmap's dimensions
	Width  = surface->w;
	Height = surface->h;
	
	int channels = 4; // R,G,B,A
	
	unsigned char *data    = ( unsigned char * )( surface->pixels );
	unsigned char *newData = new unsigned char[Width * Height * channels];
	
	// Get video information about current video mode
	const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
	if( !videoInfo )
		return( FAILURE );
	int bitdepth = videoInfo->vfmt->BitsPerPixel;
	
	int BytesPerPixel = surface->format->BytesPerPixel;
	
	// Flip the surface data
	for( index = 0; index < ( Height / 2 ); ++index )
		for( int j = 0; j < Width * BytesPerPixel; j += BytesPerPixel )
			for( int k = 0; k < BytesPerPixel; ++k )
			{
				swap( data[( index * Width * BytesPerPixel) + j + k],
				data[ ( ( Height - index - 1 ) * Width * BytesPerPixel ) + j + k] );
			}
	
	// the following lines extract R,G and B values from any bitmap
	Uint32 pixel_value = 0;			// 32 bit unsigned int (as dictated by SDL)
	for( index = 0; index < ( Width * Height ); ++index )
	{
		char r, g, b, a;			// R, G, and B that we will put into pImage
		pixel_value = 0;		// reset pixel , else we get incorrect values of r,g,b

		// the following loop extracts the pixel (however wide it is 8,16,24 or 32) and 
		// creates a long with all these bytes taken together.
		for( int j = BytesPerPixel - 1; j >= 0; --j )
		{
			// for each byte in the pixel (from the right)
			// left shift pixel value by 8 bits
			pixel_value = pixel_value << 8;
			
			// then make the last 8 bits of pixel
			// value  = the byte that we extract from pBitmap's data
			pixel_value = pixel_value | data[( index * BytesPerPixel ) + j]; 
		}							

		// here we get r,g,b from pixel_value which is stored
		// in the form specified by pBitmap->format
		SDL_GetRGBA( pixel_value, surface->format,
			    ( Uint8 * )( &r ),		
			    ( Uint8 * )( &g ),	
			    ( Uint8 * )( &b ),		
			    ( Uint8 * )( &a ) );

		// in our tImage classes we store r first then g and finally b (for bmps - three channels only)
		newData[( index * channels ) + 0] = r;
		newData[( index * channels ) + 1] = g;
		newData[( index * channels ) + 2] = b;
		
		// TODO Try to adjust these series of if statements to accommodate alphablending too
		
		// Check and adjust for alpha color-key
		if( hasTransparency )
		{
			if( ( r | g | b ) )
				newData[( index * channels ) + 3] = a;
			else
				newData[( index * channels ) + 3] = 0;
		}
		else
			newData[( index * channels ) + 3] = a;
		
		//newData[( index * channels ) + 3] = 128;
	}
	
	// Build Mipmaps (builds different versions of the picture for distances - looks better)
	//gluBuild2DMipmaps( GL_TEXTURE_2D, 3, Width, Height, GL_RGB, GL_UNSIGNED_BYTE, newData );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, newData );
	
	// If we do not have a 16 bit screen depth
	if( bitdepth > 16 )
	{
		// Release the SDL surface
		if( surface )
			SDL_FreeSurface( surface );
	}
	else
	{
		// Flip the surface data again! (so it's not upside down!) TODO FUNCTIONALIZE?
		for( index = 0; index < ( Height / 2 ); ++index )
			for( int j = 0; j < Width * BytesPerPixel; j += BytesPerPixel )
				for( int k = 0; k < BytesPerPixel; ++k )
				{
					swap( data[( index * Width * BytesPerPixel) + j + k],
					data[ ( ( Height - index - 1 ) * Width * BytesPerPixel ) + j + k] );
				}	
	}

	// Now we need to free the bitmap data that we loaded since openGL stored it as a texture
	delete [] newData;
	
	return( SUCCESS );
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap:Draw()
// Description:
// 
// Draws to another VideoBitmap at a specified position.
//--------------------------------------------------------------------------------
int VideoBitmap::Draw( VideoBitmap *destinationBitmap,
		       int xposition, int yposition )
{
	return( Draw( destinationBitmap,
		      xposition, yposition,
		      0, 0,
		      Width, Height,
		      Width, Height ) );	// DOES CHANGING THESE LAST PARAMS DO NOTHING?
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::Draw()
// Description:
// 
// Draws to a specified VideoDisplay (mainly to support future expansion of
// engine features and multi-monitor support with OpenGL) at a specified position.
//--------------------------------------------------------------------------------
int VideoBitmap::Draw( VideoDisplay *destinationDisplay,
		       int xposition, int yposition )
{
	return( DrawPrimary( destinationDisplay->GetWidth(), destinationDisplay->GetHeight(),
			     xposition, yposition,
			     0, 0,
			     Width, Height,
			     Width, Height ) );
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::Draw()
// Description:
// 
// Draws a section (defined by offsets and width/height) of this VideoBitmap to a
// specified VideoDisplay (mainly to support future expansion of
// engine features and multi-monitor support with OpenGL) at a specified position.
//--------------------------------------------------------------------------------
int VideoBitmap::Draw( VideoDisplay *destinationDisplay,
		       int xposition, int yposition,
		       int x_source_start, int y_source_start,
		       int x_source_end, int y_source_end,
		       int width, int height )
{
	// Draw straight to the primary display
	return( DrawPrimary( destinationDisplay->GetWidth(), destinationDisplay->GetHeight(),
			     xposition, yposition,
			     x_source_start, y_source_start,
			     x_source_end, y_source_end,
			     width, height ) );	// DOES CHANGING THESE LAST PARAMS DO NOTHING?
}
	  

//--------------------------------------------------------------------------------
// Name: VideoBitmap::Draw()
// Description:
// 
// Draws a section (defined by offsets and width/height) of this VideoBitmap to
// another VideoBitmap at a specified position.
//--------------------------------------------------------------------------------
int VideoBitmap::Draw( VideoBitmap *destinationBitmap,
		       int xposition, int yposition,
		       int x_source_start, int y_source_start,
		       int x_source_end, int y_source_end,
		       int width, int height )
{
	// Get video information about current video mode
	const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
	if( !videoInfo )
		return( FAILURE );
	
	int bitdepth = videoInfo->vfmt->BitsPerPixel;
	
	if( bitdepth > 16 )
	{
		GLint viewport[4];			// Backup space for current OpenGL viewport
		
		// Get current screen/viewport before we alter it for accelerated texture copying
		glGetIntegerv( GL_VIEWPORT, viewport );
		
		int destinationWidth  = destinationBitmap->GetWidth();
		int destinationHeight = destinationBitmap->GetHeight();
		
		// Set screen viewport to dimensions of the destinationBitmap
		glViewport( 0, 0, destinationWidth, destinationHeight );
		
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		// Draw our bitmap on the screen
		DrawPrimary( destinationWidth, destinationHeight,
			xposition, yposition,
			x_source_start, y_source_start,
			x_source_end, y_source_end,
			width, height );
		
		// Use this VideoBitmap's 'Texture' (OpenGL) member as the texture to draw to
		glBindTexture( GL_TEXTURE_2D, destinationBitmap->Texture );
		
		// Render the screen to the texture we specified
		glCopyTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
				0, 0,
				x_source_end, y_source_end,	// NOTE This correct?
				0 );
		
		// Return screen/display to original/previous dimensions
		glViewport( viewport[0], viewport[1],
			    viewport[2], viewport[3] );
	}
	else
	{
		SDL_Rect sourceRect, destinationRect;
		
		sourceRect.x = x_source_start;
		sourceRect.y = y_source_start;
		sourceRect.w = x_source_end - x_source_start + 1;
		sourceRect.h = y_source_end - y_source_start + 1;
		
		destinationRect.x = xposition;
		destinationRect.y = yposition;
		destinationRect.w = width;
		destinationRect.h = height;
		
		SDL_BlitSurface( Surface, &sourceRect, destinationBitmap->Surface, &destinationRect );
		
		destinationBitmap->CreateTexture( destinationBitmap->Surface, true ); // Change to specify alhpa transparency!
	}

	return( SUCCESS );
}


//--------------------------------------------------------------------------------
// Name: VideoBitmap::DrawPrimary()
// Description:
// 
// Draws this VideoBitmap straight to the default primary display.
//--------------------------------------------------------------------------------
int VideoBitmap::DrawPrimary( int primaryWidth, int primaryHeight,
			      int xposition, int yposition,
			      int x_source_start, int y_source_start,
			      int x_source_end, int y_source_end,
			      int width, int height )
{
	// Set up Ortho view
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();

	glOrtho( 0, primaryWidth,
		 primaryHeight, 0,
		 -1, 1 );
	
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();	// Reset The matrix
	
	// Set the position where the image is to drawn on the display
	glTranslated( xposition, yposition, 0 );

	// Bind the texture stored as the Texture ID for use
	glBindTexture( GL_TEXTURE_2D, Texture );

	// If this bitmap has color blend, backup current OpenGL color setting
	// and set the color to this VideoBitmap's Color
	GLint color[3];		// Backup space for current OpenGL color
	if( HasColorBlend() )
	{
		// Get current OpenGL color and back it up temporarily
		glGetIntegerv( GL_CURRENT_COLOR, color );
		
		if( !HasAlphaBlend() )
			glColor4ub( Color[0], Color[1], Color[2], 255 );
		else
			glColor4ub( Color[0], Color[1], Color[2], AlphaLevel );
	}
	else
		if( !HasAlphaBlend() )
			glColor4ub( 255, 255, 255, 255 );
		else
			glColor4ub( 255, 255, 255, AlphaLevel );

	if( !HasColorKey() )
	{
		//glDisable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ZERO );
	}

	// Preprocess / optimize the scaling of the image
	float dx0, dx1, dy0, dy1;
	dx0 = ( float )( x_source_start  ) / ( float )( Width );
	dx1 = ( float )( x_source_start  + x_source_end  ) / ( float )( Width );

	dy0 = ( float )( Height - ( y_source_start + y_source_end )  ) / ( float )( Height );
	dy1 = ( float )( Height - y_source_start  ) / ( float )( Height );
	
	// Draw the 'tile' to the screen
	glBegin( GL_QUADS );
		
		// Display the top left vertice
		glTexCoord2f( dx0, dy1 );
		glVertex2i( 0, 0 );
		
		// Display the bottom left vertice
		glTexCoord2f( dx0, dy0 );
		glVertex2i( 0, height );
		
		// Display the bottom right vertice
		glTexCoord2f( dx1, dy0 );
		glVertex2i( width, height );
		
		// Display the top right vertice
		glTexCoord2f( dx1, dy1 );
		glVertex2i( width, 0 );
	
	glEnd();

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	
	// If this VideoBitmap has color blending/modulation,
	// then restore OpenGL color back to whatever it was
	if( HasColorBlend() )
		glColor3iv( color );
	
	if( HasColorKey() )
	{
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}
	
	return( SUCCESS );
}
