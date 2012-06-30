function InputSystem()
{
  this.numberOfKeyboards;
  this.numberOfMice;
  this.numberOfJoystick;
  
  this.keyboards;
  this.mice;
  
  this.joysticks;
  this.gamepadList;
  
  this.constructor();
  return this;
}

InputSystem.prototype.constructor = function()
{
  this.numberOfKeyboards = 1;
  this.numberOfMice      = 1;

  var gamepadList = navigator.webkitGamepads;
  if( gamepadList != null )
  {
    //console.log( gamepadList );
    // TODO: Determine actual number of valid/defined gamepads.
    this.numberOfJoysticks = gamepadList.length;
  }
  else
  {
    this.numberOfJoysticks = 0;
  }
  
  this.keyboards = new Array( this.numberOfKeyboards );
  this.mice      = new Array( this.numberOfMice );
  this.joysticks = new Array( this.numberOfJoysticks );

  var index;
  for( index = 0; index < this.numberOfKeyboards; index++ )
  {
    this.keyboards[index] = new InputKeyboard();
  }

  for( index = 0; index < this.numberOfMice; index++ )
  {
    this.mice[index] = new InputMouse();
  }

  for( index = 0; index < this.numberOfJoysticks; index++ )
  {
    this.joysticks[index] = new InputJoystick();
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
  var index;
  if( this.numberOfKeyboards > 0 )
  {
    for( index = 0; index < this.numberOfKeyboards; index++ )
    {
      this.keyboards[index].age();
    }
  }

  if( this.numberOfMice > 0 )
  {
    for( index = 0; index < this.numberOfMice; index++ )
    {
      this.mice[index].age();
    }
  }

  if( this.numberOfJoysticks > 0 )
  {
    for( index = 0; index < this.numberOfJoysticks; index++ )
    {
      this.joysticks[index].age();
    }

    var gamepadList = navigator.webkitGamepads;
    if( gamepadList != null )
    {
      var gamepad;
      //console.log( gamepadList );
      for( index = 0; index < gamepadList.length; index++ )
      {
        gamepad = gamepadList[index];
        if( gamepad != null )
        {
          this.joysticks[index].updateWithGamepad( gamepad );
        }
      }
    }
  }
};
