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
#include <puzl/input/SdlOglInputSystem.h>

#include <SDL/SDL.h>

#include <iostream>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
SdlOglInputSystem::SdlOglInputSystem( void ): CoreInputSystem()
{
  numberOfKeyboards  = 1;
  numberOfMice       = 1;

  if( SDL_InitSubSystem( SDL_INIT_JOYSTICK ) > -1 )
  {
    numberOfJoysticks  = SDL_NumJoysticks();
    if( numberOfJoysticks < 1 )
    {
      SDL_QuitSubSystem( SDL_INIT_JOYSTICK );
    }
  }
  else
  {
    numberOfJoysticks = 0;
  }
}

//--------------------------------------------------------------------------------
SdlOglInputSystem::~SdlOglInputSystem( void )
{

}

//--------------------------------------------------------------------------------
int SdlOglInputSystem::initialize( void )
{
  int index;

  cout << "SdlOglInputSystem::initialize()" << endl;

  keyboards = new CoreInputKeyboard*[numberOfKeyboards];
  for( index = 0; index < numberOfKeyboards; index++ )
  {
    keyboards[index] = new SdlOglInputKeyboard();
    keyboards[index]->initialize();
  }

  mice = new CoreInputMouse*[numberOfMice];
  for( index = 0; index < numberOfMice; index++ )
  {
    mice[index] = new SdlOglInputMouse();
    mice[index]->initialize();
  }

  joysticks = new CoreInputJoystick*[numberOfJoysticks];
  for( index = 0; index < numberOfJoysticks; index++ )
  {
    joysticks[index] = new SdlOglInputJoystick();
    joysticks[index]->initialize();
  }

  return 0;
}

//--------------------------------------------------------------------------------
int SdlOglInputSystem::shutdown( void )
{
  int index;

  for( index = 0; index < numberOfKeyboards; index++ )
  {
    keyboards[index]->shutdown();
    delete keyboards[index];
  }
  delete [] keyboards;

  for( index = 0; index < numberOfMice; index++ )
  {
    mice[index]->shutdown();
    delete mice[index];
  }
  delete [] mice;

  for( index = 0; index < numberOfJoysticks; index++ )
  {
    joysticks[index]->shutdown();
    delete joysticks[index];
  }
  delete [] joysticks;

  return 0;
}

//--------------------------------------------------------------------------------
void SdlOglInputSystem::update( SDL_Event* event )
{
	switch( event->type )
	{
		// Keyboard
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		{
      ( ( SdlOglInputKeyboard* )keyboards[0] )->update( event );  // NOTE Assuming just one keyboard
			//keyboards[0]->update( event );	// NOTE Assuming just one keyboard
			break;
		}

		// Mouse
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		{
		  ( ( SdlOglInputMouse* )mice[0] )->update( event );
			//mice[0]->update( event );	// NOTE Assuming just one mouse.
			break;
		}

		// Joystick
		case SDL_JOYAXISMOTION:
		{
		  ( ( SdlOglInputJoystick* )joysticks[event->jaxis.which] )->update( event );
			//joysticks[event->jaxis.which]->update( event );
			break;
		}

		case SDL_JOYBALLMOTION:
		{
		  ( ( SdlOglInputJoystick* )joysticks[event->jball.which] )->update( event );
			//joysticks[event->jball.which]->update( event );
			break;
		}

		case SDL_JOYHATMOTION:
		{
		  ( ( SdlOglInputJoystick* )joysticks[event->jhat.which] )->update( event );
			//joysticks[event->jhat.which]->update( event );
			break;
		}

		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
		{
		  ( ( SdlOglInputJoystick* )joysticks[event->jbutton.which] )->update( event );
			//joysticks[event->jbutton.which]->update( event );
			break;
		}
	}
}
