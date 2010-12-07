//================================================================================
// InputDevice.cpp
// Authors:  Andrew Dieffenbach
// Date:     November 13, 2010
// Description:
//
//================================================================================

// INCLUDES ======================================================================

// Add the SDL header files for appropriate OS build
#include <SDL/SDL.h>

#include "puzl/input/InputDevice.h"	// InputDevice class header file for general input


// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// Name: InputDevice()
// Description:
// Default constructor
//--------------------------------------------------------------------------------
InputDevice::InputDevice()
{
	input = NULL;
	stateChange = NULL;
	stateChangeBufferSize = 0;
	numberOfStateChanges = 0;
	
	lastInputId = -1;
	lastInputType = 0;
}


//--------------------------------------------------------------------------------
// Name: ~InputDevice()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
InputDevice::~InputDevice()
{

}


//--------------------------------------------------------------------------------
// Name: initialize()
// Description:
// 
//--------------------------------------------------------------------------------
int InputDevice::initialize()
{
	return 0;
}


//--------------------------------------------------------------------------------
// Name: shutdown()
// Description:
// 
//--------------------------------------------------------------------------------
int InputDevice::shutdown()
{
	return 0;
}


//--------------------------------------------------------------------------------
// Name: check()
// Description:
// 
//--------------------------------------------------------------------------------
bool InputDevice::check( int inputId )
{
	// NOTE: This implementation is prone to fail if state defines change
	// as it counts both INPUT_STATE_DOWN and INPUT_STATE_PRESSED as sharing
	// a common bit.
	return input[inputId]->state & INPUT_STATE_DOWN ? true : false;
}


//--------------------------------------------------------------------------------
// Name: getState()
// Description:
// 
//--------------------------------------------------------------------------------
int InputDevice::getState( int inputId )
{
	return input[inputId]->state;
}


//--------------------------------------------------------------------------------
// Name: getLastInputId()
// Description:
// 
//--------------------------------------------------------------------------------
int InputDevice::getLastInputId()
{
	return lastInputId;
}


//--------------------------------------------------------------------------------
// Name: update()
// Description:
// 
//--------------------------------------------------------------------------------
void InputDevice::update( SDL_Event *event )
{
	
}

//--------------------------------------------------------------------------------
// Name: age()
// Description:
// 
//--------------------------------------------------------------------------------
void InputDevice::age()
{
	int index;
	for( index = 0; index < numberOfStateChanges; index++ )
	{
		Input* tempStateChange = stateChange[index];
		
		if( tempStateChange->state == INPUT_STATE_RELEASED )
		{
			tempStateChange->state = INPUT_STATE_UP;
		}
		else
		if( tempStateChange->state == INPUT_STATE_PRESSED )
		{
			tempStateChange->state = INPUT_STATE_DOWN;
		}
	}
	
	numberOfStateChanges = 0;
	lastInputId = -1;
}
