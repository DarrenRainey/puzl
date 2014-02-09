var OPERATION_STATE_RUNNING              = 1     // Operation is currently running a sequence
var OPERATION_STATE_DONE                 = 2   // Operation sequence is finished
var OPERATION_STATE_RESET                = 4   // Operation sequence reset to run again

var OPERATION_ATTRIBUTE_SINGLE_FRAME     = 1     // Operation has a single frame
var OPERATION_ATTRIBUTE_MULTI_FRAME      = 2   // Operation has multiple frames
var OPERATION_ATTRIBUTE_MULTI_SEQUENCE   = 4       // Operation has multiple sequences
var OPERATION_ATTRIBUTE_ONE_SHOT         = 8 // Operation will perform the sequence once

function Operation()
{
  // Consturctor.
  this.attributes      = OPERATION_ATTRIBUTE_MULTI_SEQUENCE;
  this.state           = OPERATION_STATE_RESET;
  this.currentFrame    = 0;
  this.currentSequence = 0;
  this.nextSequence    = 0;
  this.resetSequenceOnChange = true;
  this.counter         = 0;
  this.frameIndex      = 0;
  this.countMaximum    = 1;
  this.sequences       = new Array();
}

Operation.prototype.destructor = function()
{
  var index;
  var numberOfSequences = sequences.length;

  // Clear out all the sequences
  for( index = 0; index < numberOfSequences; index++ )
  {
    sequences[index] = [];
  }

  // Clear out entire operation
  sequences = [];
};

Operation.prototype.load = function( sequences )
{
  var sequenceIndex = this.sequences.length;

  // Load in data for sequence
  this.sequences.push( sequences );

  // Check and add the terminator (-1) if this sequence does not have one
  if( this.sequences[sequenceIndex][this.sequences[sequenceIndex].length - 1] != -1 )
  {
    this.sequences[sequenceIndex].push( -1 );
  }

  return sequenceIndex;
};

//--------------------------------------------------------------------------------
Operation.prototype.getAttributes = function()
{
  return this.attributes;
};

//--------------------------------------------------------------------------------
Operation.prototype.setAttributes = function( attributes )
{
  this.attributes = attributes;
};

//--------------------------------------------------------------------------------
Operation.prototype.getState = function()
{
  return this.state;
};

//--------------------------------------------------------------------------------
Operation.prototype.setState = function( state )
{
  this.state = state;
};

//--------------------------------------------------------------------------------
Operation.prototype.getCurrentSequence = function()
{
  return this.currentSequence;
};

//--------------------------------------------------------------------------------
Operation.prototype.setCurrentSequence = function( sequenceIndex )
{
  // Set the animation index.

  if( this.currentSequence === sequenceIndex )
  {
    return false;
  }
  
  var previousFrame = -1;
  var sequenceList = this.sequences;
  
  // Check for available sequences (NOTE: not checking for less than 0).
  if( sequenceIndex >= sequenceList.length )
  {
    console.error( "Operation does not have sequence: " + sequenceIndex );
    return false;
  }
  
  previousFrame = sequenceList[this.currentSequence][this.frameIndex];
  
  this.currentSequence = sequenceIndex;
  var sequence = sequenceList[sequenceIndex];

  // Set up reference frame for MULTI_SEQUENCE (fixes bad initial frame)
  if( ( this.attributes & OPERATION_ATTRIBUTE_MULTI_SEQUENCE ) === 0 )
  {
    // Reset animation.
    this.frameIndex = 0;
    this.currentFrame = sequence[0];
  }
  else // ( this.attributes & OPERATION_ATTRIBUTE_MULTI_SEQUENCE )
  {
    var currentFrameIndex = this.frameIndex;
    if( this.resetSequenceOnChange )
    {
      this.frameIndex = currentFrameIndex = 0;
    }
    else
    {
      if( ( currentFrameIndex >= sequence.length ) ||
          ( sequence[currentFrameIndex] === -1 ) )
      {
        this.frameIndex = currentFrameIndex = 0;
      }
    }
    
    this.currentFrame = sequence[currentFrameIndex];
    
    this.nextSequence = sequenceIndex; // NOTE: Setting nextSequence and then setting currentSequence is not compatible.
    this.counter = 0;
  }
  
  if( previousFrame !== this.currentFrame )
  {
    return true;
  }
  
  return false;
};

//--------------------------------------------------------------------------------
Operation.prototype.getCurrentFrame = function()
{
  return this.currentFrame;
};

//--------------------------------------------------------------------------------
Operation.prototype.setNextSequence = function( nextSequenceIndex )
{
  this.nextSequence = nextSequenceIndex;
}

//--------------------------------------------------------------------------------
Operation.prototype.setCurrentFrame = function( frameIndex )
{
  if( frameIndex > -1 )
  {
    this.currentFrame = frameIndex;
  }
};

//--------------------------------------------------------------------------------
Operation.prototype.getFrameIndex = function()
{
  return this.frameIndex;
};

//--------------------------------------------------------------------------------
Operation.prototype.setFrameIndex = function( frameIndex )
{
  // NOTE: This is pretty dangerous since length of animation sequence is not well known.
  if( ( this.attributes & OPERATION_ATTRIBUTE_MULTI_SEQUENCE ) ||
      ( this.attributes & OPERATION_ATTRIBUTE_ONE_SHOT ) )
  {
    this.frameIndex = frameIndex;
    // TODO: Error check this.
    this.currentFrame = this.sequences[this.currentSequence][this.frameIndex];
  }
};

//--------------------------------------------------------------------------------
Operation.prototype.setSpeed = function( speed )
{
  this.countMaximum = speed;
};

//--------------------------------------------------------------------------------
Operation.prototype.getSpeed = function()
{
  return this.countMaximum;
}

//--------------------------------------------------------------------------------
Operation.prototype.getCounter = function()
{
  return this.counter;
};

//--------------------------------------------------------------------------------
Operation.prototype.read = function()
{
  // Test the level of sequence
  if( this.attributes & OPERATION_ATTRIBUTE_SINGLE_FRAME )
  {
    //cout << "OPERATION_ATTRIBUTE_SINGLE_FRAME" << endl;

    // Current frame always equals 0
    this.currentFrame = 0;

    // Set sequence state message to done (always because it never started)
    //this.state = OPERATION_STATE_DONE;
    this.state = OPERATION_STATE_RUNNING;
    return false;
  }
  else
  /*if( this.attributes & OPERATION_ATTRIBUTE_MULTI_FRAME )
  {
    //cout << "OPERATION_ATTRIBUTE_MULTI_FRAME" << endl;

    // Update the counter and test if its time to increment frame
    if( ++this.counter >= this.countMaximum )
    {
      // Reset counter
      this.counter = 0;

      // Move to next frame
      if( ++this.currentFrame >= this.numberOfFrames )
      {
        // Set sequence state message to reset
        this.state = OPERATION_STATE_RESET;

        this.currentFrame = 0;
      }
      else
      {
        this.state = OPERATION_STATE_RUNNING;
      }

      return true;
    }

    return false;
  }
  else*/
  if( this.attributes & OPERATION_ATTRIBUTE_MULTI_SEQUENCE )
  {
    // See if there is a pending animation sequence change.
    if( this.currentSequence !== this.nextSequence )
    {
      //this.currentSequence = this.nextSequence;
      return this.setCurrentSequence( this.nextSequence );
    }
    
    // Look for next frame of sequence

    //cout << "OPERATION_ATTRIBUTE_MULTI_SEQUENCE" << endl;

    // Test if its time to sequence next frame
    if( ++this.counter >= this.countMaximum )
    {
      // Reset counter
      this.counter = 0;

      // Increment the animation frame index
      this.frameIndex++;

      // Extract the next frame from sequence list.
      var lastFrame = this.currentFrame;
      this.currentFrame = this.sequences[this.currentSequence][this.frameIndex];

      // Check for end sequence flag (-1)
      if( this.currentFrame === -1 )
      {
        // Test if animation is single shot
        if( this.attributes & OPERATION_ATTRIBUTE_ONE_SHOT )
        {
          // Set sequence state message to done
          this.state = OPERATION_STATE_DONE;

          // Reset frame back one step
          this.frameIndex--;

          // Extract sequence frame
          this.currentFrame = this.sequences[this.currentSequence][this.frameIndex];
        }
        else
        {
          // Set sequence state message to reset
          this.state = OPERATION_STATE_RESET;

          // Reset sequence index
          this.frameIndex = 0;

          // Extract first sequence frame
          this.currentFrame = this.sequences[this.currentSequence][this.frameIndex];
        }
      }

      if( this.currentFrame !== lastFrame )
      {
        return true;
      }
    }

    return false;
  }
};
