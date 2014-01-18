// var BUTTON_STATE_UP                   = INPUT_STATE_UP;
// var BUTTON_STATE_RELEASED             = INPUT_STATE_RELEASED;
// var BUTTON_STATE_DOWN                 = INPUT_STATE_DOWN;
// var BUTTON_STATE_PRESSED              = INPUT_STATE_PRESSED;

var INPUT_TYPE_JOYSTICK_BUTTON = 2;
//var NUM_BUTTONS = 3;

GlobalJoystickList = new Array();

function InputJoystick()
{
  InputDevice.call( this );

  this.joystickInput;
  this.xAxis;
  this.yAxis;

  // Constructor.
  var thisJoystickInput = this.joystickInput = new Array();

  var joystickInput;
  var index;
  for( index = 0; index < NUM_BUTTONS; index++ )
  {
    joystickInput       = new Input(); 
    joystickInput.id    = index;
    joystickInput.state = BUTTON_STATE_UP;
    joystickInput.type  = INPUT_TYPE_JOYSTICK_BUTTON;
    
    thisJoystickInput.push( joystickInput );
  }

  this.input = this.joystickInput;

  this.stateChangeBufferSize = 10;
  this.stateChange = new Array( this.stateChangeBufferSize );
  this.numberOfStateChanges = 0;
  
  GlobalJoystickList.push( this );
}

extend( InputJoystick, InputDevice );

InputJoystick.prototype.checkButton = function( buttonID )
{
  if( buttonID < NUM_BUTTONS )
  {
    return this.check( buttonID );
  }
  else
  {
    return false;
  }
};

InputJoystick.prototype.getButtonState = function( buttonID )
{
  if( buttonID < NUM_BUTTONS )
  {
    return this.getState( buttonID );
  }
  else
  {
    return BUTTON_STATE_UP;
  }
};

InputJoystick.prototype.setButtonState = function( buttonID, state )
{
  if( buttonID < NUM_BUTTONS )
  {
    var currentState = this.getState( buttonID );
    if( state === INPUT_STATE_PRESSED )
    {
      if( currentState === INPUT_STATE_PRESSED )
      {
        this.setState( buttonID, INPUT_STATE_DOWN );
      }
      else
      if( ( currentState === INPUT_STATE_UP ) ||
          ( currentState === INPUT_STATE_RELEASED ) )
      {
        this.setState( buttonID, state );
      }
    }
    else // ( state === INPUT_STATE_RELEASED )
    {
      if( currentState === INPUT_STATE_RELEASED )
      {
        this.setState( buttonID, INPUT_STATE_UP );
      }
      else
      if( ( currentState === INPUT_STATE_DOWN ) ||
          ( currentState === INPUT_STATE_PRESSED ) )
      {
        this.setState( buttonID, state );
      }
    }
  }
};

InputJoystick.prototype.getLastButtonPress = function()
{
  return this.getLastInputId();
};

if( !!navigator.webkitGetGamepads )
{
  InputJoystick.prototype.updateWithGamepad = function( gamepad )
  {
    var gamepadAxes = gamepad.axes;
    this.xAxis = gamepadAxes[0];
    this.yAxis = gamepadAxes[1];

    var gamepadButtons = gamepad.buttons;

    for( var index = 0; index < NUM_BUTTONS; index++ )
    {
      this.setButtonState( index, gamepadButtons[index] !== 0 ? BUTTON_STATE_PRESSED : BUTTON_STATE_RELEASED );
    }
  };
}
else
if( !!navigator.getGamepads )
{
  InputJoystick.prototype.updateWithGamepad = function( gamepad )
  {
    var gamepadAxes = gamepad.axes;
    this.xAxis = gamepadAxes[0];
    this.yAxis = gamepadAxes[1];

    var gamepadButtons = gamepad.buttons;

    for( var index = 0; index < NUM_BUTTONS; index++ )
    {
      this.setButtonState( index, gamepadButtons[index].pressed ? BUTTON_STATE_PRESSED : BUTTON_STATE_RELEASED );
    }
  };
}
