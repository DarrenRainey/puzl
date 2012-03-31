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
#include <puzl/input/AndroidInputSystem.h>

#include <iostream>

using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
AndroidInputSystem::AndroidInputSystem( void ): CoreInputSystem()
{
  numberOfKeyboards  = 1;
  numberOfMice       = 1;
  numberOfJoysticks  = 0;
}

//--------------------------------------------------------------------------------
AndroidInputSystem::~AndroidInputSystem( void )
{

}

//--------------------------------------------------------------------------------
int AndroidInputSystem::initialize( void )
{
  int index;

  cout << "AndroidInputSystem::initialize()" << endl;

  keyboards = new CoreInputKeyboard*[numberOfKeyboards];
  for( index = 0; index < numberOfKeyboards; index++ )
  {
    keyboards[index] = new AndroidInputKeyboard();
    keyboards[index]->initialize();
  }

  mice = new CoreInputMouse*[numberOfMice];
  for( index = 0; index < numberOfMice; index++ )
  {
    mice[index] = new AndroidInputMouse();
    mice[index]->initialize();
  }

  joysticks = new CoreInputJoystick*[numberOfJoysticks];
  for( index = 0; index < numberOfJoysticks; index++ )
  {
    joysticks[index] = new AndroidInputJoystick();
    joysticks[index]->initialize();
  }

  return 0;
}

//--------------------------------------------------------------------------------
int AndroidInputSystem::shutdown( void )
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
void AndroidInputSystem::update( void )
{
  int index;

  // TODO: Add/implement buffered input for keyboards/joysticks.

  for( index = 0; index < numberOfMice; index++ )
  {
    ( ( AndroidInputMouse* )mice[index] )->update();
  }
}
