var KEY_BACKSPACE                  = 8;
var KEY_TAB                        = 9;
var KEY_ENTER                      = 13;
var KEY_ESCAPE                     = 27;
var KEY_SPACE                      = 32;
var KEY_QUOTE                      = 222;
var KEY_MINUS                      = 109;
var KEY_EQUAL                      = 187;
var KEY_COMMA                      = 188;
var KEY_PERIOD                     = 190;
var KEY_FORWARDSLASH               = 191;

var KEY_0                          = 48;
var KEY_1                          = 49;
var KEY_2                          = 50;
var KEY_3                          = 51;
var KEY_4                          = 52;
var KEY_5                          = 53;
var KEY_6                          = 54;
var KEY_7                          = 55;
var KEY_8                          = 56;
var KEY_9                          = 57;

var KEY_SEMICOLON                  = 186;
var KEY_LEFTBRACKET                = 219;
var KEY_BACKSLASH                  = 220;
var KEY_RIGHTBRACKET               = 221;
var KEY_BACKQUOTE                  = 192;

var KEY_A                          = 65;
var KEY_B                          = 66;
var KEY_C                          = 67;
var KEY_D                          = 68;
var KEY_E                          = 69;
var KEY_F                          = 70;
var KEY_G                          = 71;
var KEY_H                          = 72;
var KEY_I                          = 73;
var KEY_J                          = 74;
var KEY_K                          = 75;
var KEY_L                          = 76;
var KEY_M                          = 77;
var KEY_N                          = 78;
var KEY_O                          = 79;
var KEY_P                          = 80;
var KEY_Q                          = 81;
var KEY_R                          = 82;
var KEY_S                          = 83;
var KEY_T                          = 84;
var KEY_U                          = 85;
var KEY_V                          = 86;
var KEY_W                          = 87;
var KEY_X                          = 88;
var KEY_Y                          = 89;
var KEY_Z                          = 90;

var KEY_KP_0                       = 96;
var KEY_KP_1                       = 97;
var KEY_KP_2                       = 98;
var KEY_KP_3                       = 99;
var KEY_KP_4                       = 100;
var KEY_KP_5                       = 101;
var KEY_KP_6                       = 102;
var KEY_KP_7                       = 103;
var KEY_KP_8                       = 104;
var KEY_KP_9                       = 105;
var KEY_KP_PERIOD                  = 110;
var KEY_KP_DIVIDE                  = 111;
var KEY_KP_MULTIPLY                = 106;
var KEY_KP_MINUS                   = 109;
var KEY_KP_PLUS                    = 107;
//var KEY_KP_ENTER                   = _ENTER;
//var KEY_KP_EQUALS                  = _EQUALS;

var KEY_LEFT                       = 37;
var KEY_RIGHT                      = 39;
var KEY_UP                         = 38;
var KEY_DOWN                       = 40;

var KEY_INSERT                     = 45;
var KEY_DELETE                     = 46;
var KEY_HOME                       = 36;
var KEY_END                        = 35;
var KEY_PAGEUP                     = 33;
var KEY_PAGEDOWN                   = 34;

var KEY_F1                         = 112;
var KEY_F2                         = 113;
var KEY_F3                         = 114;
var KEY_F4                         = 115;
var KEY_F5                         = 116;
var KEY_F6                         = 117;
var KEY_F7                         = 118;
var KEY_F8                         = 119;
var KEY_F9                         = 120;
var KEY_F10                        = 121;
var KEY_F11                        = 122;
var KEY_F12                        = 123;
//var KEY_F13                        = 124;
//var KEY_F14                        = 125;
//var KEY_F15                        = 126;

var KEY_NUMLOCK                    = 144;
var KEY_CAPSLOCK                   = 20;
var KEY_SCROLLOCK                  = 145;
var KEY_RIGHTSHIFT                 = 16;
var KEY_LEFTSHIFT                  = 16;
var KEY_RIGHTCTRL                  = 17;
var KEY_LEFTCTRL                   = 17;
var KEY_RIGHTALT                   = 18;
var KEY_LEFTALT                    = 18;
var KEY_LEFTWINDOWS                = 91;
var KEY_RIGHTWINDOWS               = 92;

//var KEY_SYSREQ                     = Q;
var KEY_BREAK                      = 19;

var KEY_STATE_UP                   = INPUT_STATE_UP;
var KEY_STATE_RELEASED             = INPUT_STATE_RELEASED;
var KEY_STATE_DOWN                 = INPUT_STATE_DOWN;
var KEY_STATE_PRESSED              = INPUT_STATE_PRESSED;

var INPUT_TYPE_KEYBOARD_KEY        = 0;

var NUM_KEY_CODES                  = 222;             // Number of possible key codes (SDL)

var GlobalKeyboard;

function ProcessKeyDown( keyEvent )
{
  GlobalKeyboard.setKeyState( keyEvent.keyCode || keyEvent.which, KEY_STATE_PRESSED );
  keyEvent.stopPropagation();
  keyEvent.preventDefault();
}

function ProcessKeyUp( keyEvent )
{
  GlobalKeyboard.setKeyState( keyEvent.keyCode || keyEvent.which, KEY_STATE_RELEASED );
  keyEvent.stopPropagation();
  keyEvent.preventDefault();
}

function InputKeyboard()
{
  InputDevice.call( this );
  
  this.keyInput;
  
  // Constructor.
  this.keyInput = new Array();
  
  var index;
  for( index = 0; index < NUM_KEY_CODES; index++ )
  {
    this.keyInput[index]       = new Input();
    this.keyInput[index].id    = index;
    this.keyInput[index].state = KEY_STATE_UP;
    this.keyInput[index].type  = INPUT_TYPE_KEYBOARD_KEY;
  }

  this.input = this.keyInput;
  GlobalKeyboard = this;
  
  document.addEventListener( "keydown", ProcessKeyDown, false );
  document.addEventListener( "keyup",   ProcessKeyUp,   false );

  this.stateChangeBufferSize = 10;
  this.stateChange = new Array( this.stateChangeBufferSize );
  this.numberOfStateChanges = 0;
}

extend( InputKeyboard, InputDevice );

InputKeyboard.prototype.checkKey = function( keyCode )
{
  return this.check( keyCode );
};

InputKeyboard.prototype.getKeyState = function( keyCode )
{
  return this.getState( keyCode );
};

InputKeyboard.prototype.setKeyState = function( keyCode, state )
{
  this.setState( keyCode, state );
};

InputKeyboard.prototype.getLastKeyPress = function()
{
  return this.getLastInputId();
};

//   this.getCurrentKeyEvents = function()
//   {
//
//   };
//
//   this.getNumberOfCurrentKeyEvents = function()
//   {
//
//   };

//   this.update = function( keyEvent )
//   {
//
//   };

