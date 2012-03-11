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
// Script.cpp
// Authors:  Andrew Dieffenbach
// Date:     May 13, 2004
// Description:
// 
// 
// 
//================================================================================

// INCLUDES ======================================================================

#include "puzl/utility/Script.h"			// Script header file

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
// Name: Script::Script()
// Description:
// Default Constructor
//--------------------------------------------------------------------------------
Script::Script( void )
{
	attributes	= SCRIPT_ATTRIBUTE_SINGLE_FRAME;
	state		= SCRIPT_STATE_DONE;
	currentFrame	= 0;
	numberOfFrames	= 0;
	currentSequence	= 0;
	counter		= 0;
	frameIndex	= 0;
	countMaximum	= 1;
}


//--------------------------------------------------------------------------------
// Name: Script::~Script()
// Description:
// Default destructor
//--------------------------------------------------------------------------------
Script::~Script( void )
{
	int index;
	int numberOfSequences = sequence.size();

	// Clear out all the sequences
	for( index = 0; index < numberOfSequences; index++ )
	{
		sequence[index].clear();
	}

	// Clear out entire script
	sequence.clear();
}


//--------------------------------------------------------------------------------
// Name: Script::Load()
// Description:
// 
//--------------------------------------------------------------------------------
int Script::load( int sequenceIndex, int *sequence )
{
	int index;

	vector<int> tempSequence;		// Temporary sequence to make new sequence entries

	// Check if we are re-initializing an existing 'sequenceIndex'
	if( this->sequence.size() > sequenceIndex )
	{
		return -1;
	}

	// Make as many new sequence entries as 'sequenceIndex' suggests exists
	while( this->sequence.size() < sequenceIndex + 1 )
	{
		this->sequence.push_back( tempSequence );
	}

	// Load in data for sequence
	index = 0;
	while( sequence[index] != -1 )		// -1 = (end of sequence flag)
	{
		this->sequence[sequenceIndex].push_back( sequence[index] );
		index++;
	}
	
	//cout << "script length = " << index << endl;

	// Add end of sequence flag (-1)
	this->sequence[sequenceIndex].push_back( -1 );

	return 0;
}


//--------------------------------------------------------------------------------
// Name: Script::Load()
// Description:
// 
//--------------------------------------------------------------------------------
int Script::load( int sequenceIndex, vector<int> *sequence )
{
	vector<int> tempSequence;		// Temporary sequence to make new sequence entries

	// Check if we are re-initializing an existing 'sequenceIndex'
	if( this->sequence.size() > sequenceIndex )
	{
		return( -1 );
	}

	// Make as many new sequence entries as 'sequenceIndex' suggests exists
	// before this 'sequenceIndex' value
	while( this->sequence.size() < sequenceIndex )
	{
		this->sequence.push_back( tempSequence );
	}

	// Load in data for sequence
	this->sequence.push_back( *sequence );

	// Check and add the terminator (-1) if this sequence does not have one
	if( this->sequence[sequenceIndex][this->sequence[sequenceIndex].size() - 1] != -1 )
	{
		this->sequence[sequenceIndex].push_back( -1 );
	}

	return 0;
}


//--------------------------------------------------------------------------------
// Name: Script::getAttributes()
// Description:
// 
//--------------------------------------------------------------------------------
int Script::getAttributes()
{
	return attributes;
}


//--------------------------------------------------------------------------------
// Name: Script::setAttributes()
// Description:
// 
//--------------------------------------------------------------------------------
void Script::setAttributes( int attributes )
{
	this->attributes = attributes;
}


//--------------------------------------------------------------------------------
// Name: Script::getState()
// Description:
// 
//--------------------------------------------------------------------------------
int Script::getState()
{
	return state;
}


//--------------------------------------------------------------------------------
// Name: Script::setState()
// Description:
// 
//--------------------------------------------------------------------------------
void Script::setState( int state )
{
	this->state = state;
}


//--------------------------------------------------------------------------------
// Name: Script::getCurrentSequence()
// Description:
// 
//--------------------------------------------------------------------------------
int Script::getCurrentSequence()
{
	return currentSequence;
}


//--------------------------------------------------------------------------------
// Name: Script::setCurrentSequence()
// Description:
// 
//--------------------------------------------------------------------------------
void Script::setCurrentSequence( int sequenceIndex )
{
	// Set the animation index
	// ADD SOME SORT OF CHECK FOR AVAILABLE SEQUENCE #'s
	currentSequence = sequenceIndex;

	// Reset animation
	frameIndex = 0;				// DESIGN ISSUE! (resets animation)

	// Set up reference frame for MULTI_SEQUENCE (fixes bad initial frame)
	if( attributes & SCRIPT_ATTRIBUTE_MULTI_SEQUENCE )
	{
		currentFrame = sequence[currentSequence][frameIndex];
	}
}


//--------------------------------------------------------------------------------
// Name: Script::getCurrentFrame()
// Description:
// 
//--------------------------------------------------------------------------------
int Script::getCurrentFrame()
{
	return currentFrame;
}


//--------------------------------------------------------------------------------
// Name: Script::setCurrentFrame()
// Description:
// 
//--------------------------------------------------------------------------------
void Script::setCurrentFrame( int frameIndex )
{
	if( !( ( frameIndex < 0 ) || ( frameIndex > numberOfFrames - 1 ) ) )
	{
		currentFrame = frameIndex;
	}
}


//--------------------------------------------------------------------------------
// Name: Script::getFrameIndex()
// Description:
// 
//--------------------------------------------------------------------------------
int Script::getFrameIndex()
{
	/*
	if( !( ( frameIndex < 0 ) || ( frameIndex > numberOfFrames - 1 ) ) )
	{
		currentFrame = frameIndex;
	}
	*/
	return frameIndex;
}


//--------------------------------------------------------------------------------
// Name: Script::setFrameIndex()
// Description:
// 
//--------------------------------------------------------------------------------
void Script::setFrameIndex( int frameIndex )
{
	// NOTE: This is pretty dangerous since length of animation sequence is not well known.
	if( ( attributes & SCRIPT_ATTRIBUTE_MULTI_SEQUENCE ) || ( attributes & SCRIPT_ATTRIBUTE_ONE_SHOT ) )
	{
		this->frameIndex = frameIndex;
		currentFrame = sequence[currentSequence][frameIndex];
	}
}


//--------------------------------------------------------------------------------
// Name: Script::getNumberOfFrames()
// Description:
// 
//--------------------------------------------------------------------------------
int Script::getNumberOfFrames()
{
	return numberOfFrames;
}


//--------------------------------------------------------------------------------
// Name: Script::setNumberOfFrames()
// Description:
// 
//--------------------------------------------------------------------------------
void Script::setNumberOfFrames( int numberOfFrames )
{
	this->numberOfFrames = numberOfFrames;
}


//--------------------------------------------------------------------------------
// Name: Script::setSpeed()
// Description:
// 
//--------------------------------------------------------------------------------
void Script::setSpeed( int speed )
{
	// Set speed
	countMaximum = speed;
}


//--------------------------------------------------------------------------------
// Name: Script::getSpeed()
// Description:
// 
//--------------------------------------------------------------------------------
int Script::getSpeed()
{
	return countMaximum;
}


//--------------------------------------------------------------------------------
// Name: Script::getCounter()
// Description:
// 
//--------------------------------------------------------------------------------
int Script::getCounter()
{
	return counter;
}

//--------------------------------------------------------------------------------
// Name: Script::read()
// Description:
// 
//--------------------------------------------------------------------------------
int Script::read()
{
	state = SCRIPT_STATE_RUNNING;

	// Test the level of sequence
	if( attributes & SCRIPT_ATTRIBUTE_SINGLE_FRAME )
	{
		//cout << "SCRIPT_ATTRIBUTE_SINGLE_FRAME" << endl;
		
		// Current frame always equals 0
		currentFrame = 0;

		// Set sequence state message to done (always because it never started)
		state = SCRIPT_STATE_DONE;
	}
	else
	if( attributes & SCRIPT_ATTRIBUTE_MULTI_FRAME )
	{
		//cout << "SCRIPT_ATTRIBUTE_MULTI_FRAME" << endl;
		
		// Update the counter and test if its time to increment frame
		if( ++counter >= countMaximum )
		{
			// Reset counter
			counter = 0;

			// Move to next frame
			if( ++currentFrame >= numberOfFrames )
			{
				// Set sequence state message to reset
				state = SCRIPT_STATE_RESET;

				currentFrame = 0;
			}
		}
	}
	else
	if( attributes & SCRIPT_ATTRIBUTE_MULTI_SEQUENCE )
	{
		// Look for next frame of sequence
		
		//cout << "SCRIPT_ATTRIBUTE_MULTI_SEQUENCE" << endl;

		// Test if its time to sequence next frame
		if( ++counter >= countMaximum )
		{
			// Reset counter
			counter = 0;

			// Increment the animation frame index
			frameIndex++;

			// Extract the next frame from sequence list
			currentFrame = sequence[currentSequence][frameIndex];

			// Check for end sequence flag (-1)
			if( currentFrame == -1 )
			{
				// Test if animation is single shot
				if( attributes & SCRIPT_ATTRIBUTE_ONE_SHOT )
				{
					// Set sequence state message to done
					state = SCRIPT_STATE_DONE;

					// Reset frame back one step
					frameIndex--;

					// Extract sequence frame
					currentFrame = sequence[currentSequence][frameIndex];
				}
				else
				{
					// Set sequence state message to reset
					state = SCRIPT_STATE_RESET;

					// Reset sequence index
					frameIndex = 0;

					// Extract first sequence frame
					currentFrame = sequence[currentSequence][frameIndex];
				}
			}
		}
	}

	return state;
}

