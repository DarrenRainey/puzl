//================================================================================
// VideoBitmap.h
// Authors:  Andrew Dieffenbach
// Date:     March 28, 2004
// Description:
// Display class inherits from Bitmap
//
// NOTE:  This version uses SDL and OpenGL
// 
//================================================================================

// Watch for multiple inclusions
#ifndef VIDEO_BITMAP
#define VIDEO_BITMAP

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

#include "puzl/video/VideoBuffer.h"		// VideoBuffer class header file
#include "puzl/video/VideoDisplay.h"

#include <string>


// DEFINES =======================================================================

using namespace std;

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif

#define BITMAP_TRANSPARENCY	1
#define BITMAP_ALPHABLEND	2
#define BITMAP_COLOR		4


// TYPES =========================================================================

// VideoBitmap class (inherits from VideoBuffer class)
class VideoBitmap : public virtual VideoBuffer
{
public:
	VideoBitmap();
	~VideoBitmap();
	
	int Create( int width, int height,		// Reserves memory for bitmap
		    int bitdepth = 32,			// CHANGE FROM 32!
		    int attributes = 0 );		// 

	int Destroy( void );				// Releases memory from bitmap

	int Load( string fileName );			// Load bitmap data from a file
	
	bool HasColorKey( void );			// Returns whether bitmap has transparent color keying
	void ToggleColorKey( bool setting );		// Sets Color-Keying or not

	bool HasAlphaBlend( void );			// Returns whether this bitmap uses alpha
	int GetAlphaLevel( void );			// Gets the alpha/transparency (0-255)
	void SetAlphaLevel( int level );		// Sets the alpha/transparency (0-255)
	
	bool HasColorBlend( void );			// Returns whether bitmap uses color blending
	void SetColorBlend( bool setting );		// Sets whether bitmap uses color blending
	int* GetColor( void );				// Gets the color for color blending
	void SetColor( int color[] );			// Sets the color for color blending

	int Draw( VideoBitmap *destinationBitmap,	// Draw bitmap on another bitmap
		  int xposition = 0,			// at a specific position
		  int yposition = 0 );			// 
	
	int Draw( VideoDisplay *destinationDisplay,	// Draw bitmap on a display
		  int xposition = 0,			// at a specific position
		  int yposition = 0 );			// 

	int Draw( VideoDisplay *destinationDisplay,	// Draw a region of a display
		  int xposition, int yposition,		// on a videobuffer at a specific
		  int x_source_start, int y_source_start,// position
		  int x_source_end, int y_source_end,	//
		  int width, int height );		//
		  
	int Draw( VideoBitmap *destinationBitmap,	// Draw a region of another bitmap
		  int xposition, int yposition,		// on a videobuffer at a specific
		  int x_source_start, int y_source_start,// position
		  int x_source_end, int y_source_end,	//
		  int width, int height );		//

protected:
	SDL_Surface* GetSurface( void );		// Get the protected surface

	GLuint Texture;					// OpenGL texture ID
	
	bool ColorKey;					// Indicates if bitmap has a color key (black)

	bool AlphaBlend;				// Indicates if bitmap has alpha
	int AlphaLevel;					// Alpha/transparency 0-255

	bool ColorBlend;				// Indicates if bitmap has color modulation
	int Color[4];					// Color for color blend/modulation (RGBA)

private:
	int CreateTexture( SDL_Surface *surface,
			   bool hasTransparency );	// Create Texture (OpenGL) from an SDL surface

	int DrawPrimary( int primaryWidth, int primaryHeight,	// Draws this bitmap on
		         int xposition, int yposition,		// the primary display
			 int x_source_start, int y_source_start,//
			 int x_source_end, int y_source_end,	//
		         int width, int height );		//
};

typedef VideoBitmap* VideoBitmapPtr;

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
