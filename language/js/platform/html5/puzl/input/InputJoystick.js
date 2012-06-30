// var BUTTON_STATE_UP                   = INPUT_STATE_UP;
// var BUTTON_STATE_RELEASED             = INPUT_STATE_RELEASED;
// var BUTTON_STATE_DOWN                 = INPUT_STATE_DOWN;
// var BUTTON_STATE_PRESSED              = INPUT_STATE_PRESSED;

var INPUT_TYPE_JOYSTICK_BUTTON = 2;
//var NUM_BUTTONS = 3;

function InputJoystick()
{
  inputDevice = new InputDevice();

  inputDevice.joystickInput;
  inputDevice.xAxis;
  inputDevice.yAxis;

  inputDevice.constructor        = this.constructor;
  inputDevice.checkButton        = this.checkButton;
  inputDevice.getButtonState     = this.getButtonState;
  inputDevice.setButtonState     = this.setButtonState;
  inputDevice.getLastButtonPress = this.getLastButtonPress;
  inputDevice.updateWithGamepad  = this.updateWithGamepad;

  inputDevice.constructor();
  return inputDevice;
}

InputJoystick.prototype.constructor = function()
{
  this.joystickInput = new Array();

  var index;
  for( index = 0; index < NUM_BUTTONS; index++ )
  {
    this.joystickInput[index]       = new Input();
    this.joystickInput[index].id    = index;
    this.joystickInput[index].state = BUTTON_STATE_UP;
    this.joystickInput[index].type  = INPUT_TYPE_JOYSTICK_BUTTON;
  }

  this.input = this.joystickInput;

  this.stateChangeBufferSize = 10;
  this.stateChange = new Array( this.stateChangeBufferSize );
  this.numberOfStateChanges = 0;
};

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
    this.setState( buttonID, state );
  }
};

InputJoystick.prototype.getLastButtonPress = function()
{
  return this.getLastInputId();
};

InputJoystick.prototype.updateWithGamepad = function( gamepad )
{
  this.xAxis = gamepad.axes[0];
  this.yAxis = gamepad.axes[1];

  var index;
  for( index = 0; index < NUM_BUTTONS; index++ )
  {
    this.setButtonState( index, gamepad.buttons[index] != 0 ? BUTTON_STATE_DOWN : BUTTON_STATE_UP );
  }
  
};
