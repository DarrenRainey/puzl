function VideoImage()
{
  //console.log( "Creating VideoImage" );
  VideoObject.call( this );
  
  this.canvas;
  this.display;

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
  this.filename = "";
}

extend( VideoImage, VideoObject );

VideoImage.prototype.setRealDimensions = function( width, height )
{
  if( this.canvas !== undefined )
  {
    SetCanvasDimensions( this.canvas, width, height );
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
  var context = GetCanvasContext2D( canvas );
  context.fillStyle = color.string;
  context.fillRect( 0, 0, canvas.width, canvas.height );
};

VideoImage.prototype.clear = function()
{
  var canvas = this.canvas;
  var context = GetCanvasContext2D( canvas );
  context.clearRect( 0, 0, canvas.width, canvas.height );
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
