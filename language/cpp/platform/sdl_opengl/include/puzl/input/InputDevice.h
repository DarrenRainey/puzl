//================================================================================
// InputDevice.h
// Authors:  Andrew Dieffenbach
// Date:     November 13, 2010
// Description:
//
//================================================================================

// Watch for multiple inclusions
#ifndef INPUT_DEVICE
#define INPUT_DEVICE

// INCLUDES ======================================================================

// Add the SDL header files for appropriate OS build
#include <SDL/SDL.h>

#include <iostream>
using namespace std;

// DEFINES =======================================================================

// Define return values
#ifndef SUCCESS
	#define SUCCESS		0
	#define FAILURE	       -1
#endif

// Input state defines
#define INPUT_STATE_UP			0		// 00b
#define INPUT_STATE_RELEASED		2		// 10b
#define INPUT_STATE_DOWN		1		// 01b
#define INPUT_STATE_PRESSED		3		// 11b

// TYPES =========================================================================

struct Input
{
	int state;
	int type;
	int id;
};

// InputDevice class
class InputDevice
{
public:
	InputDevice();
	~InputDevice();

	virtual int initialize();
	virtual int shutdown();
	
 	bool check( int inputId );			// Check if input is on or off.
	int getState( int inputId );			// Get current state of an input.
	virtual int getLastInputId();
		
protected:
	virtual void update( SDL_Event *event );	// Update the state of keyboard
	void age();					// Age the state changes.
	Input** input;
	
	Input** stateChange;
	int stateChangeBufferSize;
	int numberOfStateChanges;
	int lastInputId;
	int lastInputType;

	friend class InputSystem;			// InputSys is omniscent of InputKeyboard's data
};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
