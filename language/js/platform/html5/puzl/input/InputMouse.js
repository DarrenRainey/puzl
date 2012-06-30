var BUTTON_STATE_UP                   = INPUT_STATE_UP;
var BUTTON_STATE_RELEASED             = INPUT_STATE_RELEASED;
var BUTTON_STATE_DOWN                 = INPUT_STATE_DOWN;
var BUTTON_STATE_PRESSED              = INPUT_STATE_PRESSED;

var INPUT_TYPE_MOUSE_BUTTON = 1;
var NUM_BUTTONS = 3;

var GlobalMouse;

function ProcessMouseDown( mouseEvent )
{
  GlobalMouse.setButtonState( mouseEvent.which, BUTTON_STATE_PRESSED );
  //mouseEvent.preventDefault();
}

function ProcessMouseUp( mouseEvent )
{
  GlobalMouse.setButtonState( mouseEvent.which, BUTTON_STATE_RELEASED );
  //mouseEvent.preventDefault();
}

function ProcessMouseMove( mouseEvent )
{
  GlobalMouse.xPosition = mouseEvent.pageX;
  GlobalMouse.yPosition = mouseEvent.pageY;
}

document.addEventListener( "mousedown", ProcessMouseDown, false );
document.addEventListener( "mouseup",   ProcessMouseUp,   false );
document.addEventListener( "mousemove", ProcessMouseMove, false );

function InputMouse()
{
  inputDevice = new InputDevice();

  inputDevice.mouseInput;
  inputDevice.xPosition;
  inputDevice.yPosition;
  inputDevice.display;

  inputDevice.constructor        = this.constructor;
  inputDevice.checkButton        = this.checkButton;
  inputDevice.getButtonState     = this.getButtonState;
  inputDevice.setButtonState     = this.setButtonState;
  inputDevice.getLastButtonPress = this.getLastButtonPress;
  inputDevice.getXPosition       = this.getXPosition;
  inputDevice.getYPosition       = this.getYPosition;
  
  inputDevice.setDisplay         = this.setDisplay;

  inputDevice.constructor();
  return inputDevice;
}

InputMouse.prototype.constructor = function()
{
  this.mouseInput = new Array();

  var index;
  for( index = 0; index < NUM_BUTTONS; index++ )
  {
    this.mouseInput[index]       = new Input();
    this.mouseInput[index].id    = index;
    this.mouseInput[index].state = BUTTON_STATE_UP;
    this.mouseInput[index].type  = INPUT_TYPE_MOUSE_BUTTON;
  }

  this.input = this.mouseInput;
  GlobalMouse = this;

  this.xPosition = 0;
  this.yPosition = 0;

  this.stateChangeBufferSize = 10;
  this.stateChange = new Array( this.stateChangeBufferSize );
  this.numberOfStateChanges = 0;

  this.setDisplay( null );
};

InputMouse.prototype.checkButton = function( buttonID )
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

InputMouse.prototype.getButtonState = function( buttonID )
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

InputMouse.prototype.setButtonState = function( buttonID, state )
{
  if( buttonID < NUM_BUTTONS )
  {
    this.setState( buttonID, state );
  }
};

InputMouse.prototype.getLastButtonPress = function()
{
  return this.getLastInputId();
};

InputMouse.prototype.getXPosition = function()
{
  if( this.display != null )
  {
    return ( ( this.xPosition - this.display.xOffset ) / this.display.xScale ) | 0;
  }

  return this.xPosition;
};

InputMouse.prototype.getYPosition = function()
{
  if( this.display != null )
  {
    return ( ( this.yPosition - this.display.yOffset ) / this.display.yScale ) | 0;
  }

  return this.yPosition;
};

InputMouse.prototype.setDisplay = function( display )
{
  this.display = display;
};
