function VideoImage()
{
  //console.log( "Creating VideoImage" );
  VideoObject.call( this );
  
  this.canvas;
  this.context;

  this.filename;

  // Constructor.
  /*if( arguments.length > 0 )
  {
    if( arguments.length > 2 )
    {
      //var argument0 = arguments[0];
      //if( typeof arguments[0] )
    }
  }
  else
  {

  }*/

  this.canvas = CreateOffScreenCanvas();
  this.context = GetCanvasContext2D( this.canvas );
  
  this.filename = "";
}

extend( VideoImage, VideoObject );

VideoImage.prototype.setRealDimensions = function( width, height )
{
  if( this.canvas )
  {
    SetCanvasDimensions( this.canvas, width, height );
    this.context = GetCanvasContext2D( this.canvas );
  }
};

VideoImage.prototype.getRealWidth = function()
{
  if( this.canvas === undefined )
  {
    return -1;
  }
  
  return this.canvas.width;
};

VideoImage.prototype.getRealHeight = function()
{
  if( this.canvas === undefined )
  {
    return -1;
  }

  return this.canvas.height;
};

VideoImage.prototype.fill = function( color )
{
  var canvas = this.canvas;
  //var context = GetCanvasContext2D( canvas );
  var context = this.context;
  context.fillStyle = color.string;
  context.fillRect( 0, 0, canvas.width, canvas.height );
  
  var thisTargetVideoObject = this.targetVideoObject;
  if( thisTargetVideoObject )
  {
    thisTargetVideoObject.addDirtyRectangle( this );
  }
};

VideoImage.prototype.clear = function( rectangle )
{
  var canvas = this.canvas;
  //var context = GetCanvasContext2D( canvas );
  
  if( rectangle )
  {
    var rectangleStartPoint  = rectangle.startPoint;
    var rectangleStartPointX = rectangleStartPoint.x;
    var rectangleStartPointY = rectangleStartPoint.y;
    var rectangleEndPoint    = rectangle.endPoint;
    this.context.clearRect( rectangleStartPointX, rectangleStartPointY,
                            rectangleEndPoint.x - rectangleStartPointX + 1, rectangleEndPoint.y - rectangleStartPointY + 1 );
  }
  else
  {
    this.context.clearRect( 0, 0, canvas.width, canvas.height );
  }
  
  var thisTargetVideoObject = this.targetVideoObject;
  if( thisTargetVideoObject )
  {
    if( rectangle )
    {
      thisTargetVideoObject.addDirtyRectangle( rectangle );
    }
    else
    {
      thisTargetVideoObject.addDirtyRectangle( this );
    }
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
  return this.context;
};
