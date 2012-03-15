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
#include <puzl/utility/SdlOglGameShell.h>
#include <puzl/video/SdlOglVideoDisplay.h>

#include <SDL/SDL.h>

#if defined(_WIN64) || defined(_WIN32)
  #include <SDL/SDL_syswm.h>
#endif

#include <string>
#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================
//--------------------------------------------------------------------------------
SdlOglGameShell::SdlOglGameShell( const GameShellSettings& gameShellSettings ): CoreGameShell( gameShellSettings )
{
	
}

//--------------------------------------------------------------------------------
SdlOglGameShell::~SdlOglGameShell( void )
{

}

//--------------------------------------------------------------------------------
void SdlOglGameShell::shellLoop( void )
{
  const unsigned int TICKS_PER_SECOND = 60;
  const unsigned int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
  const unsigned int MAX_FRAMESKIP = 10;
  
  unsigned int nowTime;
  nextTime = SDL_GetTicks();
  unsigned int loops;
  
  // Main loop.
  while( !quit )
  {
    loops = 0;
    nowTime = SDL_GetTicks();
    while( nowTime > nextTime && loops < MAX_FRAMESKIP )
    {
      display->clear();
      draw();
      display->present();
    
      updateSystem();
      loop();
      
      nextTime += SKIP_TICKS;
      loops++;
    }
  }
}

//--------------------------------------------------------------------------------
int SdlOglGameShell::initialize( void )
{
  return 0;
}

//--------------------------------------------------------------------------------
int SdlOglGameShell::shutdown( void )
{
  return 0;
}

//--------------------------------------------------------------------------------
void SdlOglGameShell::loop( void )
{

}

//--------------------------------------------------------------------------------
void SdlOglGameShell::draw( void )
{

}

//--------------------------------------------------------------------------------
int SdlOglGameShell::shellInitialize( void )
{
  cout << "SdlOglGameShell::shellInitialize()" << endl;

	initializeVideo();
	initializeAudio();
	initializeInput();
	
	//SDL_WarpMouse( screenWidth / 2, screenHeight / 2 );
	//SDL_ShowCursor( 1 );
	//SDL_WM_GrabInput( SDL_GRAB_OFF );
	
#ifdef WINDOWS
	SDL_EventState( SDL_SYSWMEVENT, SDL_ENABLE );
#endif
	
	return initialize();
}

//--------------------------------------------------------------------------------
int SdlOglGameShell::initializeVideo( void )
{
  cout << "SdlOglGameShell::initializeVideo()" << endl;
	videoSystem = new SdlOglVideoSystem();
	if( videoSystem->initialize( gameShellSettings.screenWidth, gameShellSettings.screenHeight, DISPLAY_ATTRIBUTE_RESIZABLE ) < 0 )
	{
		cout << "GameShell::initializeVideo(): Failed to initialize video system." << endl;
		delete videoSystem;
		return -1;
	}
	
	display = ( SdlOglVideoDisplay* )( videoSystem->getDisplay() );
	if( display == NULL )
	{
		cout << "GameShell::initializeVideo(): Failed to initialize video display." << endl;
		videoSystem->shutdown();
		delete videoSystem;
		return -1;
	}
	
	return 0;
}

//--------------------------------------------------------------------------------
int SdlOglGameShell::releaseVideo( void )
{
	
}

//--------------------------------------------------------------------------------
int SdlOglGameShell::reloadVideo( void )
{
	
}

//--------------------------------------------------------------------------------
int SdlOglGameShell::initializeInput( void )
{
	inputSystem = new SdlOglInputSystem();
	if( inputSystem->initialize() < 0 )
	{
		cout << "GameShell::initializeInput(): Failed to initialize input system." << endl;
		delete inputSystem;
		return -1;
	}
	
	keyboards = ( SdlOglInputKeyboard** )( inputSystem->getKeyboards() );
	keyboard = keyboards[0]; // TODO: Check if exists.
  
  mice = ( SdlOglInputMouse** )( inputSystem->getMice() );
	joysticks = ( SdlOglInputJoystick** )( inputSystem->getJoysticks() );
	
	return 0;
}

//--------------------------------------------------------------------------------
int SdlOglGameShell::initializeAudio( void )
{
	audioSystem = new SdlOglAudioSystem();
	if( audioSystem->initialize( 44100, 2, 4096 ) < 0 )
	{
		cout << "GameShell::initializeAudio(): Failed to initialize audio system." << endl;
		delete audioSystem;
		return -1;
	}
	
	return 0;
}

//--------------------------------------------------------------------------------
int SdlOglGameShell::shellShutdown( void )
{
  cout << "shellShutdown" << endl;
  shutdown();
  
	shutdownInput();
	shutdownAudio();
	shutdownVideo();

  return 0;
}

//--------------------------------------------------------------------------------
int SdlOglGameShell::shutdownInput( void )
{
  cout << "shutdownInput" << endl;
	if( inputSystem->shutdown() < 0 )
	{
		cout << "GameShell::shutdownInput(): Failed to shut down input system." << endl;
		delete inputSystem;
		return -1;
	}
	else
	{
		delete inputSystem;
		return 0;
	}
}

//--------------------------------------------------------------------------------
int SdlOglGameShell::shutdownAudio( void )
{
  cout << "shutdownAudio" << endl;
	if( audioSystem->shutdown() < 0 )
	{
		cout << "GameShell::shutdownInput(): Failed to shut down audio system." << endl;
		delete audioSystem;
		return -1;
	}
	else
	{
		delete audioSystem;
		return 0;
	}
}

//--------------------------------------------------------------------------------
int SdlOglGameShell::shutdownVideo( void )
{
	cout << "SdlOglGameShell::shutdownVideo()" << endl;
	if( videoSystem->shutdown() < 0 )
	{
		cout << "GameShell::shutdownInput(): Failed to shut down video system." << endl;
		delete videoSystem;
		return -1;
	}
	else
	{
		delete videoSystem;
		return 0;
	}
}

//--------------------------------------------------------------------------------
int SdlOglGameShell::updateSystem( void )
{
	inputSystem->age();			// Process state aging.
	
	SDL_Event event;			// Event variable.
	
	// Look for a SDL event
	while( SDL_PollEvent( &event ) )
	{
#ifdef DEBUG
		cout << "EVENT(" << ( int )event.type << ")";
		
		if( event.type == 1 )
		{
			cout << ":" << ( int )event.active.gain << ":" << ( int )event.active.state;
		}
		cout << endl;
#endif
		
		switch( event.type )
		{
			case SDL_QUIT:
			{
			  cout << "quit" << endl;
				quit = true;
				break;
			}
			
			// Some of the resizing code TODO (needs more work).
			case SDL_VIDEORESIZE:
			{
				releaseVideo();
				display->setRealDimensions( event.resize.w, event.resize.h );
				reloadVideo();
				break;
			}

#ifdef WINDOWS
			// Fixes for resizing in Windows.
			case SDL_SYSWMEVENT:
			{
				switch( event.syswm.msg->msg )
				{
					case WM_SIZING:
					{
						SendMessage( event.syswm.msg->hwnd,
						             WM_KILLFOCUS,
						             ( WPARAM )event.syswm.msg->hwnd,
						             0 );
					} break;
					
					case WM_SIZE:
					{
						SendMessage( event.syswm.msg->hwnd,
						             WM_KILLFOCUS,
						             ( WPARAM )event.syswm.msg->hwnd,
						             0 );
					} break;
				}
			} break;
#endif
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_JOYAXISMOTION:
			case SDL_JOYBALLMOTION:
			case SDL_JOYHATMOTION:
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
			{
				// Put it through the input device handler.
				inputSystem->update( &event );
			} break;
		}
	}
	
	return 0;
}

//--------------------------------------------------------------------------------
void SdlOglGameShell::setCaption( string caption )
{
  CoreGameShell::setCaption( caption );
	SDL_WM_SetCaption( caption.c_str(), caption.c_str() );
}

//--------------------------------------------------------------------------------
void SdlOglGameShell::setIcon( string filePath )
{
  CoreGameShell::setIcon( filePath );
	SDL_WM_SetIcon( IMG_Load( filePath.c_str() ), NULL );
}
