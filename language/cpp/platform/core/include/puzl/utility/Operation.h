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

#ifndef OPERATION_H
#define OPERATION_H

// INCLUDES ======================================================================
#include <iostream>
#include <vector>

using namespace std;

// DEFINES =======================================================================
#define OPERATION_STATE_RUNNING		          1	// Operation is currently running a sequence
#define OPERATION_STATE_DONE		            2	// Operation sequence is finished
#define OPERATION_STATE_RESET		            4	// Operation sequence reset to run again

#define OPERATION_ATTRIBUTE_SINGLE_FRAME	  1	// Operation has a single frame
#define OPERATION_ATTRIBUTE_MULTI_FRAME	    2	// Operation has multiple frames
#define OPERATION_ATTRIBUTE_MULTI_SEQUENCE	4	// Operation has multiple sequences
#define OPERATION_ATTRIBUTE_ONE_SHOT	      8	// Operation will perform the sequence once

// TYPES =========================================================================
class Operation
{
public:
  Operation( void );
	~Operation( void );
	
	int load( int animationIndex, int* sequences );        //
	int load( int sequenceIndex, vector<int>* sequences ); //

	int getAttributes( void );                    // Get the attributes of this operation
	void setAttributes( int attributes );	        // Set the attributes of this operation

	int getState( void );			                    // Get the state of this operation
	void setState( int state );		                // Set the state of this operation

	int getCurrentSequence( void );	              // Get the current sequence of this operation
	void setCurrentSequence( int sequenceIndex ); // Set the sequence of this operation
	
	int getCurrentFrame( void );			            //
	void setCurrentFrame( int frameIndex );	      //
	
	int getFrameIndex( void );			              //
	void setFrameIndex( int frameIndex );	        //

	int getNumberOfFrames( void );		            // Get the number of frames available to operation
	void setNumberOfFrames( int numberOfFrames ); // Set number of frames available to operation

	int getSpeed( void );                         // Get the sequence speed (cycles per frame)
	void setSpeed( int speed );		                // Set the sequence speed (cycles per frame)

	int getCounter( void );			                  // Get the time elapsed between sequence frames.
	int read( void );				                      // Process the operation based on current settings

protected:
	int attributes;				          // Attributes of sequence execution
	int state;				              // State of the sequence
	int currentFrame;			          // Current frame of the current sequence
	int numberOfFrames;			        // Number of frames to use for this operation
	int currentSequence;			      // Current sequence of operation
	int counter;				            // Used to time sequence transition
	int frameIndex;				          // Sequence frame index (for multi-sequence)
	int countMaximum;			          // Number of cycles before frame change
	vector< vector<int> > sequences;// Operation sequences
};

#endif
