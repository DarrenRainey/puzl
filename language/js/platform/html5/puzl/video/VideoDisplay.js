function VideoDisplay( width, height )
{
  //console.log( "Creating VideoDisplay" );
  VideoObject.call( this );

  this.canvas;

  this.backgroundColor;
  this.foregroundColor;
  
  // Constructor.
  this.canvas = CreateOnScreenCanvas();
  var context = this.context = GetCanvasContext2D( this.canvas );
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

    var context = this.context;
    context.restore();
    context.scale( xScale, yScale );
    context.save();
  }
};

VideoDisplay.prototype.clear = function()
{
  var context = this.context;
  if( this.backgroundColor !== undefined )
  {
    context.fillStyle = this.backgroundColor.string;
  }
  else
  {
    context.fillStyle = "#000000";
  }

  context.fillRect( 0, 0, this._width, this._height );
};

VideoDisplay.prototype.setBackgroundColor = function( color )
{
  this.backgroundColor.copy( color );
};

VideoDisplay.prototype.setBorderColor = function( color )
{
  if( color )
  {
    document.body.style.backgroundColor = color.string;
  }
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
  
  var context = targetVideoObject.context;
  context.fillStyle = this.foregroundColor.string;
  
  if( yPosition !== undefined )
  {
    context.fillRect( xPosition, yPosition, width, height );
    
    var tempDirtyRectangle = this.tempDirtyRectangle;
    var tempDirtyRectangleStartPoint = tempDirtyRectangle.startPoint;
    tempDirtyRectangleStartPoint.x = xPosition;
    tempDirtyRectangleStartPoint.y = yPosition;
    var tempDirtyRectangleEndPoint = tempDirtyRectangle.endPoint;
    tempDirtyRectangleEndPoint.x = xPosition + width - 1;
    tempDirtyRectangleEndPoint.y = yPosition + height - 1;
    
    targetVideoObject.targetVideoObject.addDirtyRectangle( tempDirtyRectangle );
  }
  else
  {
    var rectangle = xPosition;
    var rectangleStartPoint = rectangle.startPoint;
    var rectangleStartPointX = rectangleStartPoint.x;
    var rectangleStartPointY = rectangleStartPoint.y;
    var rectangleEndPoint = rectangle.endPoint;
    context.fillRect( rectangleStartPointX, rectangleStartPointY,
                      rectangleEndPoint.x - rectangleStartPointX + 1, rectangleEndPoint.y - rectangleStartPointY + 1 );
                      
    targetVideoObject.targetVideoObject.addDirtyRectangle( rectangle );
  }
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
  var context = this.context;

  // TODO: Needs to factor in scaled dimensions.
  context.fillStyle = this.backgroundColor.string;

  var rectangleStartPoint = rectangle.startPoint;
  var rectangleStartPointX = rectangleStartPoint.x;
  var rectangleStartPointY = rectangleStartPoint.y;
  var rectangleEndPoint = rectangle.endPoint;
  var rectangleEndPointX = rectangleEndPoint.x;
  var rectangleEndPointY = rectangleEndPoint.y;
  
  context.fillRect( rectangleStartPointX, rectangleStartPointY,
                    rectangleEndPointX - rectangleStartPointX + 1,
                    rectangleEndPointY - rectangleStartPointY + 1 );
};
