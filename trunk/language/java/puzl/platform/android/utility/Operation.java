/*
Copyright (C) 2010 Andrew Dieffenbach (www.puzzud.com).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

package puzl.platform.android.utility;

import java.util.Vector;

// Script
public class Operation
{
	int attributes;				// Attributes of sequence execution
	int state;				// State of the sequence
	int currentFrame;			// Current frame of the current sequence
	int numberOfFrames;			// Number of frames to use for this script
	int currentSequence;			// Current sequence of script
	int counter;				// Used to time sequence transition
	int frameIndex;				// Sequence frame index (for multi-sequence)
	int countMaximum;			// Number of cycles before frame change
	Vector<int[]> sequence;		// Script sequences
	
	public static final int SCRIPT_STATE_RUNNING			= 0;
	public static final int SCRIPT_STATE_DONE			= 1;
	public static final int SCRIPT_STATE_RESET			= 2;
	
	public static final int SCRIPT_ATTR_SINGLE_FRAME		= 1;
	public static final int SCRIPT_ATTR_MULTI_FRAME			= 2;
	public static final int SCRIPT_ATTR_MULTI_SEQUENCE		= 4;
	public static final int SCRIPT_ATTR_ONE_SHOT			= 8;
	
	public Operation()
	{
		attributes	= SCRIPT_ATTR_SINGLE_FRAME;
		state		= SCRIPT_STATE_DONE;
		currentFrame	= 0;
		numberOfFrames	= 0;
		currentSequence	= 0;
		counter		= 0;
		frameIndex	= 0;
		countMaximum	= 1;
		
		sequence = new Vector<int[]>();
	}
	

	public int load( int[] newSequence )
	{
		// Check if we are re-initializing an existing 'sequenceIndex'
		//if( sequence.size() > sequenceIndex )
		//	return( -1 );
		
		//Vector<int> tempSequence = new Vector<int>();
	
		int index;
		for( index = 0; index < newSequence.length; index++ )
		{
			//tempSequence.add( newSequence[index] );
			//System.out.println( newSequence[index] );
		}
		
		sequence.add( newSequence );
		
		//return( sequence.size() - 1 );
		return( 0 );
		
		/*
		// Make as many new sequence entries as 'sequenceIndex' suggests exists
		while( sequence.size() < sequenceIndex + 1 )
			sequence.add( tempSequence );
	
		// Load in data for sequence
		index = 0;
		while( sequence.elementAt( index ) != -1 )		// -1 = (end of sequence flag)
		{
			sequence[sequenceIndex].add( newSequence[index] );
	
			index++;
		}
	
		// Add end of sequence flag (-1)
		sequence[sequenceIndex].add( -1 );
		*/
	}

/*
	public int load( int sequenceIndex, vector<int> *sequence )
{
	vector<int> tempSequence;		// Temporary sequence to make new sequence entries

	// Check if we are re-initializing an existing 'sequenceIndex'
	if( Sequence.size() > sequenceIndex )
		return( -1 );

	// Make as many new sequence entries as 'sequenceIndex' suggests exists
	// before this 'sequenceIndex' value
	while( Sequence.size() < sequenceIndex )
		Sequence.add( tempSequence );

	// Load in data for sequence
	Sequence.add( *sequence );

	// Check and add the terminator (-1) if this sequence does not have one
	if( Sequence[sequenceIndex][Sequence[sequenceIndex].size() - 1] != -1 )
		Sequence[sequenceIndex].add( -1 );

	return( 0 );
}
*/

	public int getAttributes()
	{
		return( attributes );
	}


	public void setAttributes( int attributes )
	{
		this.attributes = attributes;
	}
	
	
	public int getState()
	{
		return( state );
	}
	
	
	public void setState( int state )
	{
		this.state = state;
	}
	
	
	public int getCurrentSequence()
	{
		return( currentSequence );
	}
	
	
	public void setCurrentSequence( int sequenceIndex )
	{
		// Set the animation index
		// ADD SOME SORT OF CHECK FOR AVAILABLE SEQUENCE #'s
		currentSequence = sequenceIndex;
	
		// Reset animation
		frameIndex = 0;				// DESIGN ISSUE! (resets animation)
	
		// Set up reference frame for MULTI_SEQUENCE (fixes bad initial frame)
		if( ( attributes & SCRIPT_ATTR_MULTI_SEQUENCE ) > 0 )
		{
			currentFrame = sequence.elementAt( currentSequence )[frameIndex];
			//currentFrame = sequence.elementAt( currentSequence ).elementAt( frameIndex );
		}
	}
	
	
	public int getCurrentFrame()
	{
		return( currentFrame );
	}
	
	
	public void setCurrentFrame( int frameIndex )
	{
		// Error checking on input
		if( !( ( frameIndex < 0 ) || ( frameIndex > numberOfFrames - 1 ) ) )
		{
			currentFrame = frameIndex;
		}
	}
	
	
	public int getNumberOfFrames()
	{
		return( numberOfFrames );
	}
	
	
	public void setNumberOfFrames( int numberOfFrames )
	{
		this.numberOfFrames = numberOfFrames;
	}
	
	
	public void setSpeed( int speed )
	{
		// Set speed
		countMaximum = speed;
	}
	
	
	public int getSpeed()
	{
		return( countMaximum );
	}
	
	
	public int getCounter()
	{
		return( counter );
	}
	
	
	public int read()
	{
		state = SCRIPT_STATE_RUNNING;
	
		// Test the level of sequence
		if( ( attributes & SCRIPT_ATTR_SINGLE_FRAME ) > 0 )
		{
			// Current frame always equals 0
			currentFrame = 0;
	
			// Set sequence state message to done (always because it never started)
			state = SCRIPT_STATE_DONE;
		}
		else
		if( ( attributes & SCRIPT_ATTR_MULTI_FRAME ) > 0 )
		{
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
		if( ( attributes & SCRIPT_ATTR_MULTI_SEQUENCE ) > 0 )
		{
			// Look for next frame of sequence
	
			// Test if its time to sequence next frame
			if( ++counter >= countMaximum )
			{
				// Reset counter
				counter = 0;
	
				// Increment the animation frame index
				frameIndex++;
	
				// Extract the next frame from sequence list
				// NOTE Move this below next if block?
				currentFrame = sequence.elementAt( currentSequence )[frameIndex];
	
				// Check for end sequence flag (-1)
				if( currentFrame == -1 )
				{
					// Test if animation is single shot
					if( ( attributes & SCRIPT_ATTR_ONE_SHOT ) > 0 )
					{
						// Set sequence state message to done
						state = SCRIPT_STATE_DONE;
	
						// Reset frame back one step
						frameIndex--;
	
						// Extract sequence frame
						// NOTE Is this redundant?
						currentFrame = sequence.elementAt( currentSequence )[frameIndex];
					}
					else
					{
						// Set sequence state message to reset
						state = SCRIPT_STATE_RESET;
	
						// Reset sequence index
						frameIndex = 0;
	
						// Extract first sequence frame
						// NOTE Is this redundant?
						currentFrame = sequence.elementAt( currentSequence )[frameIndex];
					}
				}
			}
		}
	
		return( state );
	}

}
