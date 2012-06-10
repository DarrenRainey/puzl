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
    this.shellInitialize();
    this.shellLoop();
  };
  
  this.shellInitialize = function()
  {
    //console.log( "GameShell::initialize()" );
    this.inputSystem = new InputSystem();
    this.keyboard    = this.inputSystem.getKeyboard( 0 );
    
    this.videoSystem = new VideoSystem( this.gameShellSettings.width, this.gameShellSettings.height );
    this.display     = this.videoSystem.getDisplay();
    
    this.audioSystem = new AudioSystem();
    
    this.initialize();
  };

  this.shellShutdown = function()
  {
    //console.log( "GameShell::shtudown()" );
  };
  
  this.shellLoop = function()
  {
    if( !this.quit )
    {
      this.loop();
      this.inputSystem.update();
      
      this.videoSystem.getRequestAnimFrame( VBlank );
      this.shellDraw();
    }
    else
    {
      this.shutdown();
      this.shellShutdown();
    }
  };
  
  this.shellDraw = function()
  {
    this.videoSystem.draw();
    this.draw();
  };
  
  this.constructor( gameShellSettings );
  return this;
}

function VBlank()
{
  GlobalGameShell.shellLoop();
}
