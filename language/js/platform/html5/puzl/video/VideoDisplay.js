function VideoDisplay( width, height )
{
  //console.log( "Creating VideoDisplay" );
  VideoObject.call( this );

  this.canvas;

  this.backgroundColor;
  this.foregroundColor;
  
  // Constructor.
  this.canvas = CreateOnScreenCanvas();
  var context = GetCanvasContext2D( this.canvas );
  context.save();

  this.targetVideoObject = this; // Special case where a display's target is itself.

  Object2d.prototype.setDimensions.call( this, width, height );

  this.backgroundColor = new Color( 0, 0, 0 );
  this.foregroundColor = new Color( 255, 255, 255 );
}

extend( VideoDisplay, VideoObject );

VideoDisplay.prototype.setRealDimensions = function( width, height )
{
  var thisCanvas = this.canvas;
  if( thisCanvas !== undefined )
  {
    if( ( thisCanvas.width !== width ) || ( thisCanvas.height !== height ) )
    {
      SetCanvasDimensions( thisCanvas, width, height );
      this.setDimensions( this._width, this._height );
    }
  }
};

VideoDisplay.prototype.setDimensions = function( width, height )
{
  VideoObject.prototype.setDimensions.call( this, width, height );

  // Determine scale.
  var thisCanvas = this.canvas;
  if( thisCanvas !== undefined )
  {
    var xScale = ( thisCanvas.width  / width );
    var yScale = ( thisCanvas.height / height );

    var context = GetCanvasContext2D( thisCanvas );
    context.restore();
    context.scale( xScale, yScale );
    context.save();
  }
};

VideoDisplay.prototype.clear = function()
{
  var canvasContext = GetCanvasContext2D( this.canvas );
  if( this.backgroundColor !== undefined )
  {
    canvasContext.fillStyle = this.backgroundColor.string;
  }
  else
  {
    canvasContext.fillStyle = "#000000";
  }

  canvasContext.fillRect( 0, 0, this._width, this._height );
};

VideoDisplay.prototype.setBackgroundColor = function( color )
{
  this.backgroundColor.copy( color );
  //document.body.style.backgroundColor = color.string;
};

VideoDisplay.prototype.setForegroundColor = function( color )
{
  this.foregroundColor.copy( color );
};

VideoDisplay.prototype.drawRectangleTo = function( targetVideoObject, xPosition, yPosition, width, height )
{
  if( targetVideoObject === null )
  {
    targetVideoObject = this;
  }
  
  var canvas = targetVideoObject.getCanvas();
  if( canvas === null )
  {
    return;
  }
  
  var canvasContext = GetCanvasContext2D( canvas );
  canvasContext.fillStyle = this.foregroundColor.string;
  canvasContext.fillRect( xPosition, yPosition, width, height );
};

VideoDisplay.prototype.drawRectangle = function( xPosition, yPosition, width, height )
{
  this.drawRectangleTo( null, xPosition, yPosition, width, height );
};

VideoDisplay.prototype.getCanvas = function()
{
  return this.canvas;
};

VideoDisplay.prototype.draw = function( rectangle )
{
  var canvasContext = GetCanvasContext2D( this.canvas );

  // TODO: Needs to factor in scaled dimensions.
  canvasContext.fillStyle = this.backgroundColor.string;

  var rectangleStartPoint = rectangle.startPoint;
  var rectangleStartPointX = rectangleStartPoint.x;
  var rectangleStartPointY = rectangleStartPoint.y;
  var rectangleEndPoint = rectangle.endPoint;
  var rectangleEndPointX = rectangleEndPoint.x;
  var rectangleEndPointY = rectangleEndPoint.y;
  
  canvasContext.fillRect( rectangleStartPointX, rectangleStartPointY,
                          rectangleEndPointX - rectangleStartPointX + 1,
                          rectangleEndPointY - rectangleStartPointY + 1 );
};
