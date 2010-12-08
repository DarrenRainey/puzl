/*
Copyright (C) 2010 Andrew Dieffenbach (www.puzzud.com).

This file is part of puzl.

puzl is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with puzl; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

//================================================================================
// GameShell.cpp
// Authors:  Andrew Dieffenbach
// Date:     August 8, 2010
// Description:
// 
// 
// 
//================================================================================

// INCLUDES ======================================================================

#include "puzl/core/GameShell.h"

#ifdef WINDOWS
	#include <SDL/SDL_syswm.h>
#endif

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

// ===============================================================================
GameShell::GameShell()
{
	videoSystem = NULL;
	audioSystem = NULL;
	inputSystem = NULL;

	display = NULL;

	keyboard = NULL;
	mouse = NULL;
	joystick = NULL;
	
	// TODO: Just get/set these with a VideoDisplay.
	screenWidth = 0;
	screenHeight = 0;
	quit = false;
}


// ===============================================================================
GameShell::GameShell( int width, int height )
{
	// TODO: Just get/set these with a VideoDisplay.
	screenWidth = width;
	screenHeight = height;	
	
	quit = false;;
}


// ===============================================================================
GameShell::~GameShell()
{
	
}


// ===============================================================================
/*
int GameShell::run()
{
	initialize();
	
	const unsigned int TICKS_PER_SECOND = 60;
	const unsigned int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const unsigned int MAX_FRAMESKIP = 10;
	
	nextTime = SDL_GetTicks();
	unsigned int loops;
	
	// Main loop
	while( !quit )
	{
		draw();
		display.present();
		display.clear();
			
		loops = 0;
		while( SDL_GetTicks() > nextTime && loops < MAX_FRAMESKIP )
		{
			// Update engine (maintenance work mostly)
			updateSystem();
			loop();
			
			nextTime += SKIP_TICKS;
			loops++;
			
			
		}
	}
	
	shutdown();

	return( 0 );
}
*/
int GameShell::run()
{
	initialize();
	
	const unsigned int TICKS_PER_SECOND = 60;
	const unsigned int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const unsigned int MAX_FRAMESKIP = 10;
	
	unsigned int nowTime;
	unsigned int checkTime;
	nextTime = SDL_GetTicks();
	unsigned int loops;
	
	// Main loop
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
	
	shutdown();

	return( 0 );
}


// ===============================================================================
int GameShell::initialize()
{
	initializeVideo();
	initializeAudio();
	initializeInput();
	
	SDL_WarpMouse( screenWidth / 2, screenHeight / 2 );
	SDL_ShowCursor( 1 );
	SDL_WM_GrabInput( SDL_GRAB_OFF );
	
#ifdef WIN32
	SDL_EventState( SDL_SYSWMEVENT, SDL_ENABLE );
#endif
	
	return 0;
}


// ===============================================================================
int GameShell::initializeVideo()
{
	videoSystem = new VideoSystem();
	if( videoSystem->initialize( screenWidth, screenHeight, DISPLAY_ATTRIBUTE_RESIZABLE ) < 0 )
	{
		cout << "GameShell::initializeVideo(): Failed to initialize video system." << endl;
		delete videoSystem;
		return -1;
	}
	
	display = videoSystem->getDisplay();
	if( display == NULL )
	{
		cout << "GameShell::initializeVideo(): Failed to initialize video display." << endl;
		videoSystem->shutdown();
		delete videoSystem;
		return -1;
	}
	
	return 0;
}


// ===============================================================================
int GameShell::releaseVideo()
{
	
}


// ===============================================================================
int GameShell::reloadVideo()
{
	
}


// ===============================================================================
int GameShell::initializeInput()
{
	inputSystem = new InputSystem();
	if( inputSystem->initialize() < 0 )
	{
		cout << "GameShell::initializeInput(): Failed to initialize input system." << endl;
		delete inputSystem;
		return -1;
	}
	
	keyboard = inputSystem->getKeyboards();
	mouse = inputSystem->getMice();
	joystick = inputSystem->getJoysticks();
	
	return 0;
}


// ===============================================================================
int GameShell::initializeAudio()
{
	audioSystem = new AudioSystem();
	if( audioSystem->initialize( 44100, 2, 4096 ) < 0 )
	{
		cout << "GameShell::initializeInput(): Failed to initialize input system." << endl;
		delete audioSystem;
		return -1;
	}
	
	return 0;
}


// ===============================================================================
int GameShell::shutdown()
{
	shutdownInput();
	shutdownAudio();
	shutdownVideo();
}

// ===============================================================================
int GameShell::shutdownInput()
{
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


// ===============================================================================
int GameShell::shutdownAudio()
{
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


// ===============================================================================
int GameShell::shutdownVideo()
{
	//cout << "GameShell::shutdownVideo" << endl;
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


// ===============================================================================
int GameShell::updateSystem()
{
	inputSystem->age();			// Process state aging.
	
	SDL_Event event;			// Event variable
	
	// More SDL bullshit I need to eliminate
	// Look for a SDL event
	while( SDL_PollEvent( &event ) )
	{
		
// 		cout << "EVENT("
// 		     << ( int )( event.type )
// 		     << ")";
// 		
// 		if( event.type == 1 )
// 			cout << ":" << (int)event.active.gain << ":" << (int)event.active.state;
// 		
// 		cout << endl;
		
		
		switch( event.type )
		{
			case SDL_QUIT:
			{
				quit = true;
			} break;
			
			// Some of the resizing code TODO (needs more work)
			case SDL_VIDEORESIZE:
			{
				//SDL_Delay( 125 );
				// NOTE: Destroy/shutdown all video memory here?
				//while( display.initialize( event.resize.w, event.resize.h, DISPLAY_ATTRIBUTE_RESIZABLE ) == -1 )
				//{
					// Keep Trying.
				//}
				//SDL_Delay( 125 );
				releaseVideo();
				display->setRealDimensions( event.resize.w, event.resize.h );
				reloadVideo();
				//cout << display.getRealWidth() << "," << display.getRealHeight() << ":";
				//cout << display.getWidth() << "," << display.getHeight() << endl;
				
				//screenWidth  = event.resize.w;
				//screenHeight = event.resize.h;
			} break;
#ifdef WIN32
			// Fixes for resizing in Windows
			case SDL_SYSWMEVENT:
			{
				switch( event.syswm.msg->msg )
				{
					case WM_SIZING:
					{
						SendMessage( event.syswm.msg->hwnd,
							     WM_KILLFOCUS,
							     ( WPARAM )( event.syswm.msg->hwnd ),
							     0 );
					} break;
					
					case WM_SIZE:
					{
						SendMessage( event.syswm.msg->hwnd,
							     WM_KILLFOCUS,
							     ( WPARAM )( event.syswm.msg->hwnd ),
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
				// Put it through the input device handler
				inputSystem->update( &event );
			} break;
		}
	}

	getDeviceInput();
	
	return( 0 );
}


// ===============================================================================
int GameShell::getDeviceInput()
{
	//int index;
	
	//int keyboardInput;			// Tracks most recent keyboard input
	
	// Get device input
	//keyboardInput = keyboard.Read();
	//mouse.Read();
	
	//for( index = 0; index < numberOfJoysticks; index++ )
	//	Joystick[index].Read();

	return 0;
}


// ===============================================================================
void GameShell::setCaption( string caption )
{
	SDL_WM_SetCaption( caption.c_str(), caption.c_str() );
}


// ===============================================================================
void GameShell::setIcon( string filePath )
{
	SDL_WM_SetIcon( IMG_Load( filePath.c_str() ), NULL );
}
