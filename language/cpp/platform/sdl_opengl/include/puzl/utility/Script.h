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
// Script.h
// Authors:  Andrew Dieffenbach
// Date:     May 13, 2004
// Description:
// 
//================================================================================

// Watch for multiple inclusions
#ifndef SCRIPT_H
#define SCRIPT_H

// INCLUDES ======================================================================

#include <iostream>
#include <vector>

// DEFINES =======================================================================

using namespace std;

#define SCRIPT_STATE_RUNNING		1	// Script is currently running a sequence
#define SCRIPT_STATE_DONE		2	// Script sequence is finished
#define SCRIPT_STATE_RESET		4	// Script sequence reset to run again

#define SCRIPT_ATTRIBUTE_SINGLE_FRAME	1	// Script has a single frame
#define SCRIPT_ATTRIBUTE_MULTI_FRAME	2	// Script has multiple frames
#define SCRIPT_ATTRIBUTE_MULTI_SEQUENCE	4	// Script has multiple sequences
#define SCRIPT_ATTRIBUTE_ONE_SHOT	8	// Script will perform the sequence once


// TYPES =========================================================================

// Script class
class Script
{
public:
	Script();
	~Script();
	
	int  load( int animationIndex,		// Load an animation script
		   int *sequence );		//
	int  load( int sequenceIndex,		// 
		   vector<int> *sequence );	// 

	int  getAttributes();			// Get the attributes of this script
	void setAttributes( int attributes );	// Set the attributes of this script

	int  getState();			// Get the state of this script
	void setState( int state );		// Set the state of this script

	int  getCurrentSequence();		// Get the current sequence of this script
	void setCurrentSequence( int sequenceIndex );// Set the sequence of this script
	
	int  getCurrentFrame();			// 
	void setCurrentFrame( int frameIndex );	// 
	
	int  getFrameIndex();			// 
	void setFrameIndex( int frameIndex );	// 

	int  getNumberOfFrames();		// Get the number of frames available to script
	void setNumberOfFrames( int numberOfFrames ); // Set number of frames available to script

	void setSpeed( int speed );		// Set the sequence speed (cycles per frame)
	int  getSpeed();			// Get the sequence speed (cycles per frame)

	int  getCounter();			// Get the time elapsed between sequence frames
						// NOT SURE IF THIS IS GOOD/NEEDED (use GetState)

	int  read();				// Process the script based on current settings

protected:
	int attributes;				// Attributes of sequence execution
	int state;				// State of the sequence
	int currentFrame;			// Current frame of the current sequence
	int numberOfFrames;			// Number of frames to use for this script
	int currentSequence;			// Current sequence of script
	int counter;				// Used to time sequence transition
	int frameIndex;				// Sequence frame index (for multi-sequence)
	int countMaximum;			// Number of cycles before frame change
	vector< vector<int> > sequence;		// Script sequences
};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
