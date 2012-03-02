function InputSystem()
{
  this.numberOfKeyboards;
  this.numberOfMice;
  this.numberOfJoystick;
  
  this.keyboards;
  this.mice;
  this.joysticks;
  
  this.constructor = function()
  {
    this.numberOfKeyboards = 1;
    this.numberOfMice      = 1;
    this.numberOfJoysticks = 0;
    
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
  
  this.getKeyboard = function( id )
  {
    return this.keyboards[id];
  };
  
  this.update = function()
  {
    var index;
    for( index = 0; index < this.numberOfKeyboards; index++ )
    {
      this.keyboards[index].age();
    }
  };
  
  this.constructor();
  return this;
}
