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

  this.setDimensions( width, height );

  this.backgroundColor = new Color( 0, 0, 0 );
  this.foregroundColor = new Color( 255, 255, 255 );
}

extend( VideoDisplay, VideoObject );

VideoDisplay.prototype.setRealDimensions = function( width, height )
{
  if( this.canvas !== undefined )
  {
    if( ( this.canvas.width !== width ) || ( this.canvas.height !== height ) )
    {
      SetCanvasDimensions( this.canvas, width, height );
      this.setDimensions( this._width, this._height );
    }
  }
};

VideoDisplay.prototype.setDimensions = function( width, height )
{
  VideoObject.prototype.setDimensions.call( this, width, height );

  // Determine scale.
  if( this.canvas !== undefined )
  {
    var xScale = ( this.canvas.width  / width );
    var yScale = ( this.canvas.height / height );

    var context = GetCanvasContext2D( this.canvas );
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
  canvasContext.fillRect( rectangle.startPoint.x, rectangle.startPoint.y,
                          rectangle.endPoint.x - rectangle.startPoint.x + 1,
                          rectangle.endPoint.y - rectangle.startPoint.y + 1 );
};
