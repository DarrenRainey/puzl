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
    //this.postInitialize();
    
    //if( this.videoSystem.videoImageLoadQueue.length == 0 )
    //{
      this.shellInitialize();
      //this.postInitialize();
      //this.shellLoop();
    //}
  };
  
  this.shellInitialize = function()
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

    this.videoSystem.processImageLoadQueue();
  };

  this.shellPostInitialize = function()
  {
    this.postInitialize();
    this.shellLoop();
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

  this.documentBodyOnResize = function()
  {
    /*if( this.fullScreen )
    {
      this.setDimensions( document.width, document.height );
    }*/
    //console.log( "body resize" );
    this.resize();
  };

  this.resize = function(){};
  this.postInitialize = function(){};
  
  this.constructor( gameShellSettings );
  return this;
}

function VBlank()
{
  GlobalGameShell.shellLoop();
}
