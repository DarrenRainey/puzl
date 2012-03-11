function GameShellSettings()
{
  this.width   = 0;
  this.height  = 0;
}

var GlobalGameShell;

function GameShell( gameShellSettings )
{
  this.inputSystem;
  this.videoSystem;
  this.soundSystem;
  
  this.gameShellSettings;
  
  this.quit;
  
  this.keyboard;
  this.display;
  
  this.loop;
  
  this.constructor = function()
  {
    GlobalGameShell = this;
    this.gameShellSettings = gameShellSettings;
    this.quit = false;
  };
  
  this.run = function()
  {
    this.initialize();
    this.mainLoop();
  };
  
  this.initialize = function()
  {
    //console.log( "GameShell::initialize()" );
    this.inputSystem = new InputSystem();
    this.keyboard    = this.inputSystem.getKeyboard( 0 );
    
    this.videoSystem = new VideoSystem( this.gameShellSettings.width, this.gameShellSettings.height );
    this.display     = this.videoSystem.getDisplay();
    
    this.audioSystem = new AudioSystem();
  };

  this.shutdown = function()
  {
    //console.log( "GameShell::shtudown()" );
  };
  
  this.mainLoop = function()
  {
    if( !this.quit )
    {
      this.loop();
      this.inputSystem.update();
      
      this.videoSystem.getRequestAnimFrame( VBlank );
      this.draw();
    }
    else
    {
      this.shutdown();
    }
  };
  
  this.draw = function()
  {
    this.videoSystem.draw();
  };
  
  this.constructor( gameShellSettings );
  return this;
}

function VBlank()
{
  GlobalGameShell.mainLoop();
}
