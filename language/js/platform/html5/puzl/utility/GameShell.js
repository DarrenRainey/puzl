function GameShellSettings()
{
  this.width   = 0;
  this.height  = 0;
}

var GlobalGameShell;

var GlobalVideoDisplay;
function DocumentBodyOnResize()
{
  GlobalGameShell.documentBodyOnResize();
}

document.body.onload   = DocumentBodyOnResize;
document.body.onresize = DocumentBodyOnResize;
//window.onresize        = DocumentBodyOnResize;

function VBlank()
{
  GlobalGameShell.shellLoop();
}

function GameShell( gameShellSettings )
{
  this.inputSystem;
  this.videoSystem;
  this.soundSystem;
  
  this.gameShellSettings;
  
  this.quit;
  
  this.keyboard;
  this.display;
  
  this.logic;
  
  this.constructor( gameShellSettings );
  return this;
}

GameShell.prototype.constructor = function()
{
  //console.log( "GameShell::constructor()" );
  GlobalGameShell = this;
  this.gameShellSettings = gameShellSettings;
  this.quit = false;
};

GameShell.prototype.run = function()
{
  //console.log( "GameShell::run()" );
  this.shellInitialize();
};

GameShell.prototype.shellInitialize = function()
{
  //console.log( "GameShell::initialize()" );
  this.inputSystem = new InputSystem();
  this.keyboard    = this.inputSystem.getKeyboard( 0 );
  this.mouse       = this.inputSystem.getMouse( 0 );
  this.joysticks   = this.inputSystem.getJoysticks();

  this.videoSystem = new VideoSystem( this.gameShellSettings.width, this.gameShellSettings.height );
  this.display     = this.videoSystem.getDisplay();
  GlobalVideoDisplay = this.display;

  this.mouse.setDisplay( this.display );

  this.audioSystem = new AudioSystem();

  this.initialize();

  if( this.videoSystem.videoImageLoadQueue.length > 0 )
  {
    this.videoSystem.processImageLoadQueue();
  }
  else
  {
    this.shellPostInitialize();
  }
};

GameShell.prototype.shellPostInitialize = function()
{
  //console.log( "GameShell::shellPostInitialize()" );
  this.postInitialize();
  this.shellLoop();
};

GameShell.prototype.shellShutdown = function()
{
  //console.log( "GameShell::shtudown()" );
};

GameShell.prototype.shellLoop = function()
{
  //console.log( "GameShell::shellLoop()" );
  if( !this.quit )
  {
    this.input();
    this.logic();
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

GameShell.prototype.shellDraw = function()
{
  //console.log( "GameShell::shellDraw()" );
  this.videoSystem.draw();
  this.draw();
};

GameShell.prototype.documentBodyOnResize = function()
{
  this.shellResize();
};

GameShell.prototype.shellResize = function()
{
  this.display.setDimensions( this.display.width,
                              this.display.height );

  this.resize();
};

GameShell.prototype.input  = function(){};
GameShell.prototype.resize = function(){};
GameShell.prototype.postInitialize = function(){};
