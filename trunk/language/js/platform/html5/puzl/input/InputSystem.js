function InputSystem()
{
  this.numberOfKeyboards;
  this.numberOfMice;
  this.numberOfJoysticks;
  
  this.keyboards;
  
  this.mice;
  this.hasTouch;
  
  this.joysticks;
  this.supportsGamepads;
  
  // Constructor.
  this.numberOfKeyboards = 1;
  this.numberOfMice      = 0;

  var keyboards = this.keyboards = new Array();
  
  var mice = this.mice = null;
  this.hasTouch = ( 'ontouchstart' in document.documentElement );

  var index;
  
  var numberOfKeyboards = this.numberOfKeyboards;
  for( index = 0; index < numberOfKeyboards; index++ )
  {
    keyboards.push( new InputKeyboard() );
  }

  // Gamepad support (with shim).
  if( navigator.getGamepads === undefined )
  {
    navigator.getGamepads =
    (
      function()
      {
        if( "webkitGetGamepads" in navigator )
        {
          return navigator.webkitGetGamepads;
        }

        if( "mozGetGamepads" in navigator )
        {
          return navigator.mozGetGamepads;
        }

        // Older outdated approach.
        if( "webkitGamepads" in navigator )
        {
          return function(){ return navigator.webkitGamepads; };
        }
        if( "mozGamepads" in navigator )
        {
          return function(){ return navigator.mozGamepads; };
        }

        // Return empty array for for no support.
        return function(){ return InputSystem.prototype.emptyGamepadList; };
      }
    )();
  }
  
  this.supportsGamepads = !!navigator.getGamepads || navigator.webkitGetGamepads || !!navigator.mozGetGamepads;
  if( this.supportsGamepads )
  {
    var numberOfJoysticks = 0;
      
    var gamepadList = navigator.getGamepads();
    if( gamepadList !== null )
    {
      // Determine actual number of valid / defined gamepads.
      var gamepadListLength = gamepadList.length;
      for( index = 0; index < gamepadListLength; index++ )
      {
        gamepad = gamepadList[index];
        if( gamepad !== undefined )
        {
          numberOfJoysticks++;
        }
      }
    }
    
    this.numberOfJoysticks = numberOfJoysticks;
    console.log( "Number of gamepads found:  " + numberOfJoysticks );
    
    var joysticks = this.joysticks = new Array();
    
    if( numberOfJoysticks !== 0 )
    {
      var gamepad = null;
      for( index = 0; index < numberOfJoysticks; index++ )
      {
        joysticks.push( new InputJoystick() );
        
        gamepad = gamepadList[index];
        console.log( index + ":  " + gamepad.id );
      }
    }
  }
}

InputSystem.prototype.emptyGamepadList = new Array();

InputSystem.prototype.attachDisplay = function( display )
{
  if( display === null )
  {
    this.numberOfMice = 0;
    this.mice = null;
    // TODO: Remove approach registered listeners.
    
    return;
  }
  
  var numberOfMice = this.numberOfMice = 1;
  var mice = this.mice = new Array();
  for( var index = 0; index < numberOfMice; index++ )
  {
    mice.push( new InputMouse( display ) );
  }
};

InputSystem.prototype.attachNoDisplay = function()
{
  var numberOfMice = this.numberOfMice = 1;
  var mice = this.mice = new Array();
  for( var index = 0; index < numberOfMice; index++ )
  {
    mice.push( new InputMouse( null ) );
  }
};

InputSystem.prototype.getKeyboard = function( id )
{
  return this.keyboards[id];
};

InputSystem.prototype.getMouse = function( id )
{
  return this.mice[id];
};

InputSystem.prototype.getJoysticks = function()
{
  return this.joysticks;
};

InputSystem.prototype.getJoystick = function( id )
{
  return this.joysticks[id];
};

InputSystem.prototype.update = function()
{
  var numberOfDevices;
  var deviceList;
  var index;
  
  numberOfDevices = this.numberOfKeyboards;
  if( numberOfDevices > 0 )
  {
    deviceList = this.keyboards;
    
    index = numberOfDevices - 1;
    do
    {
      deviceList[index].age();
    }
    while( --index > -1 );
  }

  numberOfDevices = this.numberOfMice;
  if( numberOfDevices > 0 )
  {
    deviceList = this.mice;

    index = numberOfDevices - 1;
    do
    {
      deviceList[index].age();
    }
    while( --index > -1 );
  }

  numberOfDevices = this.numberOfJoysticks;
  if( numberOfDevices > 0 )
  {
    deviceList = this.joysticks;

    /*index = numberOfDevices - 1;
    do
    {
      deviceList[index].age();
    }
    while( --index > -1 );*/
  }

  if( this.supportsGamepads )
  {
    var gamepadList = navigator.getGamepads();
    if( gamepadList !== undefined )
    { 
      deviceList = this.joysticks;
      
      // Get number of legit connected gamepads (must do until connected / disconnected events are abided).
      var numberOfGamepads = 0;
      var gamepad;
      index = gamepadList.length - 1;
      do
      {
        gamepad = gamepadList[index];
        if( gamepad !== undefined )
        {
          numberOfGamepads++;
        }
      }
      while( --index > -1 );
      
      //numberOfDevices = this.numberOfJoysticks; // NOTE: numberOfDevices is already this.numberOfJoysticks!
      if( numberOfDevices < numberOfGamepads )
      {
        // Newly attached / detected gamepad.
        // It needs to be registered into the input engine.
        for( index = numberOfDevices - 1; index < numberOfGamepads; index++ )
        {
          deviceList[index] = new InputJoystick();
        }

        this.numberOfJoysticks = numberOfGamepads;
      }

      // NOTE: This code assumes joystick and corresponding gamepad indexes are the same.
      // This notion needs to be investigated.
      index = numberOfGamepads - 1;
      do
      {
        gamepad = gamepadList[index];
        if( gamepad !== undefined )
        {
          // TODO: Only call this update when timestamp differs from last
          // attempt?
          deviceList[index].updateWithGamepad( gamepad );
        }
      }
      while( --index > -1 );
    }
  }
};
