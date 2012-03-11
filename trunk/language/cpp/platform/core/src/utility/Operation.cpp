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
#include <puzl/utility/Operation.h>

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

//--------------------------------------------------------------------------------
Operation::Operation( void )
{
	attributes	    = OPERATION_ATTRIBUTE_SINGLE_FRAME;
	state		        = OPERATION_STATE_DONE;
	currentFrame	  = 0;
	numberOfFrames	= 0;
	currentSequence	= 0;
	counter		      = 0;
	frameIndex	    = 0;
	countMaximum	  = 1;
}

//--------------------------------------------------------------------------------
Operation::~Operation( void )
{
	int index;
	int numberOfSequences = sequences.size();

	// Clear out all the sequences
	for( index = 0; index < numberOfSequences; index++ )
	{
		sequences[index].clear();
	}

	// Clear out entire operation
	sequences.clear();
}


//--------------------------------------------------------------------------------
int Operation::load( int sequenceIndex, int *sequences )
{
	int index;

	vector<int> tempSequence;		// Temporary sequence to make new sequence entries

	// Check if we are re-initializing an existing 'sequenceIndex'
	if( this->sequences.size() > sequenceIndex )
	{
		return -1;
	}

	// Make as many new sequence entries as 'sequenceIndex' suggests exists
	while( this->sequences.size() < sequenceIndex + 1 )
	{
		this->sequences.push_back( tempSequence );
	}

	// Load in data for sequence
	index = 0;
	while( sequences[index] != -1 )		// -1 = (end of sequence flag)
	{
		this->sequences[sequenceIndex].push_back( sequences[index] );
		index++;
	}
	
	//cout << "operation length = " << index << endl;

	// Add end of sequence flag (-1)
	this->sequences[sequenceIndex].push_back( -1 );

	return 0;
}


//--------------------------------------------------------------------------------
int Operation::load( int sequenceIndex, vector<int> *sequences )
{
	vector<int> tempSequence;		// Temporary sequence to make new sequence entries

	// Check if we are re-initializing an existing 'sequenceIndex'
	if( this->sequences.size() > sequenceIndex )
	{
		return( -1 );
	}

	// Make as many new sequence entries as 'sequenceIndex' suggests exists
	// before this 'sequenceIndex' value
	while( this->sequences.size() < sequenceIndex )
	{
		this->sequences.push_back( tempSequence );
	}

	// Load in data for sequence
	this->sequences.push_back( *sequences );

	// Check and add the terminator (-1) if this sequence does not have one
	if( this->sequences[sequenceIndex][this->sequences[sequenceIndex].size() - 1] != -1 )
	{
		this->sequences[sequenceIndex].push_back( -1 );
	}

	return 0;
}

//--------------------------------------------------------------------------------
int Operation::getAttributes( void )
{
	return attributes;
}

//--------------------------------------------------------------------------------
void Operation::setAttributes( int attributes )
{
	this->attributes = attributes;
}

//--------------------------------------------------------------------------------
int Operation::getState( void )
{
	return state;
}

//--------------------------------------------------------------------------------
void Operation::setState( int state )
{
	this->state = state;
}

//--------------------------------------------------------------------------------
int Operation::getCurrentSequence( void )
{
	return currentSequence;
}

//--------------------------------------------------------------------------------
void Operation::setCurrentSequence( int sequenceIndex )
{
	// Set the animation index
	// ADD SOME SORT OF CHECK FOR AVAILABLE SEQUENCE #'s
	currentSequence = sequenceIndex;

	// Reset animation
	frameIndex = 0;				// DESIGN ISSUE! (resets animation)

	// Set up reference frame for MULTI_SEQUENCE (fixes bad initial frame)
	if( attributes & OPERATION_ATTRIBUTE_MULTI_SEQUENCE )
	{
		currentFrame = sequences[currentSequence][frameIndex];
	}
}

//--------------------------------------------------------------------------------
int Operation::getCurrentFrame( void )
{
	return currentFrame;
}

//--------------------------------------------------------------------------------
void Operation::setCurrentFrame( int frameIndex )
{
	if( !( ( frameIndex < 0 ) || ( frameIndex > numberOfFrames - 1 ) ) )
	{
		currentFrame = frameIndex;
	}
}

//--------------------------------------------------------------------------------
int Operation::getFrameIndex( void )
{
	return frameIndex;
}

//--------------------------------------------------------------------------------
void Operation::setFrameIndex( int frameIndex )
{
	// NOTE: This is pretty dangerous since length of animation sequence is not well known.
	if( ( attributes & OPERATION_ATTRIBUTE_MULTI_SEQUENCE ) ||
	    ( attributes & OPERATION_ATTRIBUTE_ONE_SHOT ) )
	{
		this->frameIndex = frameIndex;
		currentFrame = sequences[currentSequence][frameIndex];
	}
}

//--------------------------------------------------------------------------------
int Operation::getNumberOfFrames( void )
{
	return numberOfFrames;
}

//--------------------------------------------------------------------------------
void Operation::setNumberOfFrames( int numberOfFrames )
{
	this->numberOfFrames = numberOfFrames;
}

//--------------------------------------------------------------------------------
void Operation::setSpeed( int speed )
{
	countMaximum = speed;
}

//--------------------------------------------------------------------------------
int Operation::getSpeed( void )
{
	return countMaximum;
}

//--------------------------------------------------------------------------------
int Operation::getCounter( void )
{
	return counter;
}

//--------------------------------------------------------------------------------
int Operation::read( void )
{
	state = OPERATION_STATE_RUNNING;

	// Test the level of sequence
	if( attributes & OPERATION_ATTRIBUTE_SINGLE_FRAME )
	{
		//cout << "OPERATION_ATTRIBUTE_SINGLE_FRAME" << endl;
		
		// Current frame always equals 0
		currentFrame = 0;

		// Set sequence state message to done (always because it never started)
		state = OPERATION_STATE_DONE;
	}
	else
	if( attributes & OPERATION_ATTRIBUTE_MULTI_FRAME )
	{
		//cout << "OPERATION_ATTRIBUTE_MULTI_FRAME" << endl;
		
		// Update the counter and test if its time to increment frame
		if( ++counter >= countMaximum )
		{
			// Reset counter
			counter = 0;

			// Move to next frame
			if( ++currentFrame >= numberOfFrames )
			{
				// Set sequence state message to reset
				state = OPERATION_STATE_RESET;

				currentFrame = 0;
			}
		}
	}
	else
	if( attributes & OPERATION_ATTRIBUTE_MULTI_SEQUENCE )
	{
		// Look for next frame of sequence
		
		//cout << "OPERATION_ATTRIBUTE_MULTI_SEQUENCE" << endl;

		// Test if its time to sequence next frame
		if( ++counter >= countMaximum )
		{
			// Reset counter
			counter = 0;

			// Increment the animation frame index
			frameIndex++;

			// Extract the next frame from sequence list
			currentFrame = sequences[currentSequence][frameIndex];

			// Check for end sequence flag (-1)
			if( currentFrame == -1 )
			{
				// Test if animation is single shot
				if( attributes & OPERATION_ATTRIBUTE_ONE_SHOT )
				{
					// Set sequence state message to done
					state = OPERATION_STATE_DONE;

					// Reset frame back one step
					frameIndex--;

					// Extract sequence frame
					currentFrame = sequences[currentSequence][frameIndex];
				}
				else
				{
					// Set sequence state message to reset
					state = OPERATION_STATE_RESET;

					// Reset sequence index
					frameIndex = 0;

					// Extract first sequence frame
					currentFrame = sequences[currentSequence][frameIndex];
				}
			}
		}
	}

	return state;
}
