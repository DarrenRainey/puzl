var BUTTON_STATE_UP                   = INPUT_STATE_UP;
var BUTTON_STATE_RELEASED             = INPUT_STATE_RELEASED;
var BUTTON_STATE_DOWN                 = INPUT_STATE_DOWN;
var BUTTON_STATE_PRESSED              = INPUT_STATE_PRESSED;

var INPUT_TYPE_MOUSE_BUTTON = 1;
var NUM_BUTTONS = 3;

var GlobalMouse;

function ProcessMouseDown( mouseEvent )
{
  GlobalMouse.setButtonState( mouseEvent.which - 1, BUTTON_STATE_PRESSED );
  
  mouseEvent.stopPropagation();
  mouseEvent.preventDefault();
}

function ProcessMouseUp( mouseEvent )
{
  GlobalMouse.setButtonState( mouseEvent.which - 1, BUTTON_STATE_RELEASED );
  
  mouseEvent.stopPropagation();
  mouseEvent.preventDefault();
}

function ProcessMouseMove( mouseEvent )
{
  GlobalMouse.xPosition = ( ( mouseEvent.pageX - GlobalMouse.xOffset ) / GlobalMouse.xScale ) | 0;
  GlobalMouse.yPosition = ( ( mouseEvent.pageY - GlobalMouse.yOffset ) / GlobalMouse.yScale ) | 0;
  
  mouseEvent.stopPropagation();
  mouseEvent.preventDefault();
}

// TODO: Move touch to own class.
function IsTouchDevice()
{
  return ( 'ontouchstart' in document.documentElement );
}

function ProcessTouchStart( touchEvent )
{
  var targetTouch;
  if( touchEvent.targetTouches.length > 0 )
  {
    targetTouch = touchEvent.targetTouches[0];
  }
  else
  {
    targetTouch = touchEvent.targetTouches;
  }

  GlobalMouse.xPosition = ( ( targetTouch.pageX - GlobalMouse.xOffset ) / GlobalMouse.xScale ) | 0;
  GlobalMouse.yPosition = ( ( targetTouch.pageY - GlobalMouse.yOffset ) / GlobalMouse.yScale ) | 0;

  GlobalMouse.setButtonState( 0, BUTTON_STATE_PRESSED );

  touchEvent.stopPropagation();
  touchEvent.preventDefault();
}

function ProcessTouchEnd( touchEvent )
{
  var touchEventTargetTouches = touchEvent.targetTouches;
  var targetTouch;
  if( touchEventTargetTouches.length > 0 )
  {
    targetTouch = touchEventTargetTouches[0];
  }
  else
  {
    targetTouch = touchEventTargetTouches;
  }

  GlobalMouse.xPosition = ( ( targetTouch.pageX - GlobalMouse.xOffset ) / GlobalMouse.xScale ) | 0;
  GlobalMouse.yPosition = ( ( targetTouch.pageY - GlobalMouse.yOffset ) / GlobalMouse.yScale ) | 0;

  GlobalMouse.setButtonState( 0, BUTTON_STATE_RELEASED );

  touchEvent.stopPropagation();
  touchEvent.preventDefault();
}

function ProcessTouchMove( touchEvent )
{
  var touchEventTargetTouches = touchEvent.targetTouches;
  var targetTouch;
  if( touchEventTargetTouches.length > 0 )
  {
    targetTouch = touchEventTargetTouches[0];
  }
  else
  {
    targetTouch = touchEventTargetTouches;
  }
  
  GlobalMouse.xPosition = ( ( targetTouch.pageX - GlobalMouse.xOffset ) / GlobalMouse.xScale ) | 0;
  GlobalMouse.yPosition = ( ( targetTouch.pageY - GlobalMouse.yOffset ) / GlobalMouse.yScale ) | 0;

  touchEvent.stopPropagation();
  touchEvent.preventDefault();
}

function InputMouse()
{
  InputDevice.call( this );

  this.mouseInput;
  this.xPosition;
  this.yPosition;
  
  this.xScale;
  this.yScale;
  this.xOffset;
  this.yOffset;

  // Constructor.
  var thisMouseInput = this.mouseInput = new Array();

  var mouseInput;
  var index;
  for( index = 0; index < NUM_BUTTONS; index++ )
  {
    mouseInput       = new Input();
    mouseInput.id    = index;
    mouseInput.state = BUTTON_STATE_UP;
    mouseInput.type  = INPUT_TYPE_MOUSE_BUTTON;
    
    thisMouseInput.push( mouseInput );
  }

  this.input = this.mouseInput;
  GlobalMouse = this;
  
  document.addEventListener( "mousedown", ProcessMouseDown, false );
  document.addEventListener( "mouseup",   ProcessMouseUp,   false );
  document.addEventListener( "mousemove", ProcessMouseMove, false );
  
  if( IsTouchDevice() )
  {
    document.addEventListener( "touchstart", ProcessTouchStart, false );
    document.addEventListener( "touchend",   ProcessTouchEnd,   false );
    document.addEventListener( "touchmove",  ProcessTouchMove,  false );
  }

  this.xPosition = 0;
  this.yPosition = 0;

  this.stateChangeBufferSize = 10;
  this.stateChange = new Array( this.stateChangeBufferSize );
  this.numberOfStateChanges = 0;

  this.xScale = 1;
  this.yScale = 1;
  this.xOffset = 0;
  this.yOffset = 0;
}

extend( InputMouse, InputDevice );

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
  return this.xPosition;
};

InputMouse.prototype.getYPosition = function()
{
  return this.yPosition;
};
