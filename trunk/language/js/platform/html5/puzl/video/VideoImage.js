var CanvasIdCounter = -1;

function VideoImage()
{
  this.canvasID;
  this.canvas;
  this.display;

  this.filename;

  this.width;
  this.height;

  this.xPosition;
  this.yPosition;

  this.constructor();
  return this;
}

VideoImage.prototype.constructor = function()
{
  if( arguments.length > 0 )
  {
    if( arguments.length > 2 )
    {
      //var argument0 = arguments[0];
      //if( typeof arguments[0] )
    }
  }
  else
  {

  }

  this.canvasID = ++CanvasIdCounter + "canvas";
  this.canvas   = CreateOffScreenCanvas( this.canvasID );
  this.display  = null;

  this.filename = "";

  this.setRealDimensions( 1, 1 );
  //this.width  = 1;
  //this.height = 1;

  this.xPosition = 0;
  this.yPosition = 0;
};

VideoImage.prototype.setRealDimensions = function( width, height )
{
  SetCanvasDimensions( this.canvas, width, height );

  if( this.display == null )
  {
    this.width  = width;
    this.height = height;
  }
};

VideoImage.prototype.getRealWidth = function()
{
  return this.canvas.width;
};

VideoImage.prototype.getRealHeight = function()
{
  return this.canvas.height;
};

VideoImage.prototype.setDimensions = function( width, height )
{
  if( this.display == null )
  {
    this.setRealDimensions( width, height );
  }
  else
  {
    this.width  = width;
    this.height = height;

    this.setRealDimensions( width  * this.display.xScale,
                            height * this.display.yScale );
  }
};

VideoImage.prototype.getWidth = function()
{
  return this.width;
};

VideoImage.prototype.getHeight = function()
{
  return this.height;
};

VideoImage.prototype.getXPosition = function()
{
  return this.xPosition;
};

VideoImage.prototype.getYPosition = function()
{
  return this.yPosition;
};

VideoImage.prototype.setPosition = function( xPosition, yPosition )
{
  // NOTE: Should this only happen with a display.
  if( this.display != null )
  {
    //console.log( this.display.xOffset );
    this.xPosition = xPosition;
    this.yPosition = yPosition;
    
    SetCanvasPosition( this.canvas,
                       ( xPosition * this.display.xScale ) + this.display.xOffset,
                       ( yPosition * this.display.yScale ) + this.display.yOffset );
  }
};

VideoImage.prototype.fill = function( colorRgb )
{
  var canvas = this.canvas;
  var context = GetCanvasContext2D( canvas );
  context.fillStyle = colorRgb;
  context.fillRect( 0, 0, canvas.width, canvas.height );
};

VideoImage.prototype.clear = function()
{
  var canvas = this.canvas;
  var context = GetCanvasContext2D( canvas );
  context.clearRect( 0, 0, canvas.width, canvas.height );
};

VideoImage.prototype.setDisplay = function( display )
{
  //console.log( "VideoImage::setDisplay()" );
  if( display == this.display )
  {
    return;
  }

  if( display == null && this.display != null )
  {
    // Turn this page anchored canvas to an offscreen canvas.
    this.display = null;
  }
  else
  {
    // Turn this offscreen canvas to a page anchored canvas.
    if( this.display != null )
    {
      // NOTE: Multiple displays are not really supported right now;
      // so, just act like nothing happened.
      //this.setDisplay( null );
      return;
    }

    this.canvas = OffScreenToOnScreenCanvas( this.canvas );
    this.display = display;
  }
};

VideoImage.prototype.load = function( filename )
{
  //console.log( "VideoImage::load()" );
  this.filename = filename;
  GlobalVideoSystem.queueVideoImage( this, this.filename );
};

// Temporary?
VideoImage.prototype.getCanvas = function()
{
  return this.canvas;
};

VideoImage.prototype.getContext = function()
{
  return GetCanvasContext2D( this.canvas );
};
