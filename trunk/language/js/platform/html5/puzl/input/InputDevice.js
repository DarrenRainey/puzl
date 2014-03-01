var INPUT_STATE_UP       = 0; // 00b
var INPUT_STATE_RELEASED = 2; // 10b
var INPUT_STATE_DOWN     = 1; // 01b
var INPUT_STATE_PRESSED  = 3; // 11b

/** @constructor */
function Input()
{
  this.state = 0;
  this.type  = 0;
  this.id    = 0;
  
  return this;
}

/** @constructor */
function InputDevice()
{
  /*this.input;
  this.stateChange;
  
  this.stateChangeBufferSize;
  this.numberOfStateChanges;
  
  this.lastInputId;
  this.lastInputType;*/

  // Constructor.
  this.stateChangeBufferSize = 0;
  this.numberOfStateChanges  = 0;

  this.lastInputId   = -1;
  this.lastInputType = 0;
}

InputDevice.prototype.initialize = function()
{
  return 0;
};

InputDevice.prototype.shutdown = function()
{
  return 0;
};

InputDevice.prototype.check = function( inputId )
{
  return ( this.input[inputId].state & INPUT_STATE_DOWN ) === 0 ? false : true;
};

InputDevice.prototype.getState = function( inputId )
{
  return this.input[inputId].state;
};

InputDevice.prototype.setState = function( inputId, state )
{
  var thisInput = this.input[inputId];
  if( state === INPUT_STATE_PRESSED )
  {
    var currentState = thisInput.state;
    if( ( currentState & INPUT_STATE_DOWN ) > 0 )
    {
      return;
    }

    this.lastInputId = inputId;
  }
  
  thisInput.state = state;

  var stateChangeIndex = this.numberOfStateChanges++;
  
  var thisStateChange = this.stateChange;
  if( thisStateChange.length < stateChangeIndex + 1 )
  {
    thisStateChange.push( thisInput );
  }
  else
  {
    thisStateChange[stateChangeIndex] = thisInput;
  }
};

InputDevice.prototype.getLastInputId = function()
{
  return this.lastInputId;
};

InputDevice.prototype.age = function()
{
  var numberOfStateChanges = this.numberOfStateChanges;
  if( numberOfStateChanges > 0 )
  {
    var thisStateChange = this.stateChange;
    
    var tempState;
    var tempStateChange;
    var index;
    for( index = 0; index < numberOfStateChanges; index++ )
    {
      tempStateChange = thisStateChange[index];
      tempState = tempStateChange.state;
      if( tempState === INPUT_STATE_RELEASED )
      {
        tempStateChange.state = INPUT_STATE_UP;
      }
      else
      if( tempState === INPUT_STATE_PRESSED )
      {
        tempStateChange.state = INPUT_STATE_DOWN;
      }
    }

    this.numberOfStateChanges = 0;
    this.lastInputId          = -1;
  }
};
