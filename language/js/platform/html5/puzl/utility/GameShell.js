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
  /*this.inputSystem;
  this.videoSystem;
  this.soundSystem;
  
  this.gameShellSettings;
  
  this.quit;
  
  this.keyboard;
  this.mouse;
  
  this.display;
  
  this.logic;

  this.xmlHttpRequestLoadQueue;*/
  
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
  
  this.initialized = false;
  
  this.quit = false;

  this.xmlHttpRequestLoadQueue = new Array();
  
  this.loadingResources = false;
}

GameShell.prototype.run = function()
{
  //console.log( "GameShell::run()" );
  this.shellInitialize();
};

GameShell.prototype.shellInitialize = function()
{
  //console.log( "GameShell::initialize()" );
  this.videoSystem = new VideoSystem( this.gameShellSettings.width, this.gameShellSettings.height );
  this.display     = this.videoSystem.getDisplay();
  GlobalVideoDisplay = this.display;
  
  this.inputSystem = new InputSystem();
  this.keyboard    = this.inputSystem.getKeyboard( 0 );
  this.joysticks   = this.inputSystem.getJoysticks();
  
  if( navigator.isCocoonJS !== undefined )
  {
    this.inputSystem.attachDisplay( this.display );
  }
  else
  {
    this.inputSystem.attachNoDisplay();
  }
  
  this.mouse = this.inputSystem.getMouse( 0 );
  
  this.clientScale();
  
  this.pageParameters = GeneralUtil.getPageParameters();

  this.audioSystem = new AudioSystem();

  this.initialize();
  
  this.loadingResources = true; // Set to attempt to load resources.
  this.shellPostInitialize();
};

GameShell.prototype.shellPostInitialize = function()
{
  //console.log( "GameShell::shellPostInitialize()" );

  // Make sure all initial resources, queued up previous to this point
  // (during (pre)initialize), have been loaded and processed.
  if( this.loadingResources && this.loadResources() )
  {
    return;
  }
  
  // Continue with the game initialization and start main loop!
  if( !this.initialized )
  {
    this.postInitialize();
    this.initialized = true;
  }
    
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
    if( this.loadingResources )
    {
      this.loadResources();
      return;
    }
    
    this.input();
    this.logic();
    this.inputSystem.update();

    //this.videoSystem.getRequestAnimFrame( VBlank );
    RequestAnimationFrame( VBlank );

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
  this.clientScale();

  this.resize();
};

GameShell.prototype.clientScale = function()
{
  var clientWidth  = window.innerWidth;
  var clientHeight = window.innerHeight;

  //var documentBody = document.body;
  //var documentElement = document.documentElement;
  //var clientWidth = Math.max( Math.max( documentBody.offsetWidth, documentElement.offsetWidth ),
  //                            Math.max( documentBody.clientWidth, documentElement.clientWidth ) );
  //
  //var clientHeight = Math.max( Math.max( documentBody.offsetHeight, documentElement.offsetHeight ),
  //                             Math.max( documentBody.clientHeight, documentElement.clientHeight ) );
  
  
  var fullscreen = true;
  var maintainAspectRatio = true;
  var stretch = false;
  
  var thisDisplay = this.display;
  var thisDisplayWidth  = thisDisplay.getWidth();
  var thisDisplayHeight = thisDisplay.getHeight();
  
  var xScale = ( clientWidth  / thisDisplayWidth );
  var yScale = ( clientHeight / thisDisplayHeight );

  if( fullscreen )
  {
    var xScaleTruncated = xScale | 0;
    var yScaleTruncated = yScale | 0;
    /*var yScaleRemainder = xScale - xScaleTruncated;
    var xScaleRemainder = yScale - yScaleTruncated;
    
    if( xScaleRemainder > 0.25 )
    {
      stretch = true;
    }*/
    
    if( !stretch )
    {
      xScale = xScaleTruncated;
      yScale = yScaleTruncated;
  
      if( xScale <= 0 )
      {
        xScale = 1;
      }
  
      if( yScale <= 0 )
      {
        yScale = 1;
      }
    }

    if( maintainAspectRatio )
    {
      xScale = yScale = Math.min( xScale, yScale );
    }
  }
  else
  {
    xScale = 1;
    yScale = 1;
  }

  var width  = ( thisDisplayWidth  * xScale ) | 0;
  var height = ( thisDisplayHeight * yScale ) | 0;
  thisDisplay.setRealDimensions( width, height );

  // Center display (determine position offset).
  var canvas = thisDisplay.getCanvas();
  var xOffset = ( ( clientWidth  - width  ) / 2 ) | 0;
  var yOffset = ( ( clientHeight - height ) / 2 ) | 0;
  SetCanvasPosition( canvas, xOffset, yOffset );

  // Adjust mouse metrics to fit display on browser.
  var thisMouse = this.mouse;
  thisMouse.xScale = xScale;
  thisMouse.yScale = yScale;
  
  if( navigator.isCocoonJS === undefined )
  {
    thisMouse.xOffset = xOffset;
    thisMouse.yOffset = yOffset;
  }
  else
  {
    thisMouse.xOffset = 0;
    thisMouse.yOffset = 0;
  }
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

GameShell.prototype.loadResources = function()
{
  if( this.videoSystem.videoImageLoadQueue.length > 0 )
  {
    this.videoSystem.processImageLoadQueue();
    
    if( this.videoSystem.videoImageLoadQueue.length > 0 )
    {
      this.loadingResources = true;
    }
  }
  else
  if( this.xmlHttpRequestLoadQueue.length > 0 )
  {
    this.processXmlHttpRequestLoadQueue();
    
    if( this.xmlHttpRequestLoadQueue.length > 0 )
    {
      this.loadingResources = true;
    }
  }
  else
  {
    this.loadingResources = false;
  }
  
  return this.loadingResources;
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
  //console.log( "ProcessXmlHttpRequestLoad" );
  
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
