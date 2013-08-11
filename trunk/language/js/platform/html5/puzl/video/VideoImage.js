function VideoImage()
{
  //console.log( "Creating VideoImage" );
  VideoObject.call( this );
  
  this.canvas;
  this.display;

  this.filename;

  // Constructor.
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

  this.canvas = CreateOffScreenCanvas();
  //this.display  = null;

  this.filename = "";

  this.setRealDimensions( 1, 1 );
}

extend( VideoImage, VideoObject );

VideoImage.prototype.setRealDimensions = function( width, height )
{
  if( this.canvas !== undefined )
  {
    SetCanvasDimensions( this.canvas, width, height );
  }
  
  this.width  = width;
  this.height = height;
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
  VideoObject.prototype.setDimensions.call( this, width, height );
   
  //if( this.display == null )
  {
    this.setRealDimensions( width, height );
  }
  /*else
  {
    this.width  = width;
    this.height = height;

    this.setRealDimensions( width  * this.display.xScale,
                            height * this.display.yScale );
  }*/
};

VideoImage.prototype.setPosition = function( xPosition, yPosition )
{
  VideoObject.prototype.setPosition.call( this, xPosition, yPosition );
  
  // NOTE: Should this only happen with a display.
  //if( this.display != null )
  {
    //console.log( this.display.xOffset );
    //this.xPosition = xPosition;
    //this.yPosition = yPosition;
    
    //SetCanvasPosition( this.canvas,
    //                   ( xPosition * this.display.xScale ) + this.display.xOffset,
    //                   ( yPosition * this.display.yScale ) + this.display.yOffset );
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
  /*if( display == this.display )
  {
    return;
  }

  // TODO: Maybe set target to display in the future.
  //this.setParent( display );

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
  }*/
};

VideoImage.prototype.load = function( filename )
{
  //console.log( "VideoImage::load()" );
  this.filename = filename;
  GlobalVideoSystem.queueVideoImage( this, this.filename );
};

VideoImage.prototype.draw = function()
{
  var parentObject = this.getParentObject();
  if( parentObject !== null )
  {
    var canvas = parentObject.getCanvas();
    DrawWithNearestScale( this, parentObject,
                          0, 0,
                          this.width, this.height,
                          this.position.x, this.position.y,
                          this.width, this.height );
  }
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
