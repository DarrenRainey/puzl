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
  this.mouse;
  
  this.display;
  
  this.logic;

  this.xmlHttpRequestLoadQueue;
  
  // Constructor.
  //console.log( "GameShell::constructor()" );
  GlobalGameShell = this;

  if( gameShellSettings !== undefined )
  {
    this.gameShellSettings = gameShellSettings;
  }
  else
  {
    this.gameShellSettings = new GameShellSettings();
  }
  
  this.quit = false;

  this.xmlHttpRequestLoadQueue = new Array();
}

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
  this.shellPostInitialize();
};

GameShell.prototype.shellPostInitialize = function()
{
  //console.log( "GameShell::shellPostInitialize()" );

  // Make sure all initial resources, queued up previous to this point
  // (during (pre)initialize), have been loaded and processed.
  if( this.videoSystem.videoImageLoadQueue.length > 0 )
  {
    this.videoSystem.processImageLoadQueue();
    return;
  }

  if( this.xmlHttpRequestLoadQueue.length > 0 )
  {
    this.processXmlHttpRequestLoadQueue();
    return;
  }
  
  // Continue with the game initialization and start main loop!
  this.postInitialize();
  this.shellLoop();
};

GameShell.prototype.shellShutdown = function()
{
  //console.log( "GameShell::shtudown()" );
};

/*frame = 0;
lastUpdateTime = Date.now();
acDelta = 0;
msPerFrame = 1000 / 60;*/

GameShell.prototype.shellLoop = function()
{
  //console.log( "GameShell::shellLoop()" );
  if( !this.quit )
  {
    this.input();
    this.logic();
    this.inputSystem.update();

    this.videoSystem.getRequestAnimFrame( VBlank );

    /*var now = Date.now();
    var delta = now - lastUpdateTime;
    if( acDelta > msPerFrame )
    {
      acDelta = 0;
      */
      this.videoSystem.update();
    /*}
    else
    {
      acDelta += delta;
    }

    lastUpdateTime = now;
  */

    this.audioSystem.update();
  }
  else
  {
    this.shutdown();
    this.shellShutdown();
  }
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

GameShell.prototype.queueXmlHttpRequest = function( resourceArray, filename )
{
  xmlHttpRequest = new XMLHttpRequest();
  xmlHttpRequest.filename = filename;
  xmlHttpRequest.resourceArray = resourceArray;
  xmlHttpRequest.onload = ProcessXmlHttpRequestLoad;
  
  this.xmlHttpRequestLoadQueue[this.xmlHttpRequestLoadQueue.length] = xmlHttpRequest;
};

GameShell.prototype.processXmlHttpRequestLoadQueue = function()
{
  var numberOfIDQueuedXmlHttpRequests = this.xmlHttpRequestLoadQueue.length;
  var index;
  var xmlHttpRequest;
  for( index = 0; index < numberOfIDQueuedXmlHttpRequests; index++ )
  {
    xmlHttpRequest = this.xmlHttpRequestLoadQueue[index];
    xmlHttpRequest.open( "GET", xmlHttpRequest.filename, true );
    xmlHttpRequest.send();
  }
};

function ProcessXmlHttpRequestLoad( loadEvent )
{
  console.log( "ProcessXmlHttpRequestLoad" );
  
  var filename = loadEvent.target.filename;

  var numberOfIDQueuedxmlHttpRequests = GlobalGameShell.xmlHttpRequestLoadQueue.length;
  var index;
  var xmlHttpRequest;
  for( index = 0; index < numberOfIDQueuedxmlHttpRequests; index++ )
  {
    // TODO: Replace with a hash?
    xmlHttpRequest = GlobalGameShell.xmlHttpRequestLoadQueue[index];
    if( filename === xmlHttpRequest.filename )
    {
      //console.log( filename );
      //if( ( xmlHttpRequest.xmlHttpResource === undefined ) )
      //{
      //
      //}

      xmlHttpRequest.resourceArray.push( xmlHttpRequest.response );
      GlobalGameShell.xmlHttpRequestLoadQueue.splice( index, 1 );
      break;
    }
  }

  if( GlobalGameShell.xmlHttpRequestLoadQueue.length === 0 )
  {
    // Attempt game post initialize.
    GlobalGameShell.shellPostInitialize();
  }
}
