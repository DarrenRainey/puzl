function VideoDisplay( width, height )
{
  //console.log( "Creating VideoDisplay" );
  VideoObject.call( this );

  this.canvas;
  
  this.xScale;
  this.yScale;
  this.maintainAspectRatio;

  this.centerDisplay;
  this.xOffset;
  this.yOffset;

  this.left;
  this.top;
  
  this.fullScreen;

  this.backgroundColor;
  this.foregroundColor;
  
  // Constructor.
  this.setFullScreen( false );

  this.centerDisplay = true;
  this.maintainAspectRatio = true;

  this.left = 0;
  this.top  = 0;
  
  this.canvas = CreateOnScreenCanvas();
  var context = GetCanvasContext2D( this.canvas );
  context.save();

  this.quadTree = null;
  
  this.setDimensions( width, height );

  this.backgroundColor = new Color( 0, 0, 0 );
  this.foregroundColor = new Color( 255, 255, 255 );
}

extend( VideoDisplay, VideoObject );

VideoDisplay.prototype.setFullScreen = function( fullScreen )
{
  this.fullScreen = fullScreen;
};

VideoDisplay.prototype.getRealHeight = function()
{
  return Math.max( Math.max( document.body.offsetHeight, document.documentElement.offsetHeight ),
                   Math.max( document.body.clientHeight, document.documentElement.clientHeight ) );

  return this.height;
};

VideoDisplay.prototype.getRealWidth = function()
{
  return Math.max( Math.max( document.body.offsetWidth, document.documentElement.offsetWidth ),
                   Math.max( document.body.clientWidth, document.documentElement.clientWidth ) );

  return this.width;
};

VideoDisplay.prototype.setDimensions = function( width, height )
{
  this.width  = width;
  this.height = height;

  var realWidth  = this.getRealWidth();
  var realHeight = this.getRealHeight();

  // Determine scale.
  this.xScale = ( realWidth  / this.width ) | 0;
  if( this.xScale <= 0 )
  {
    this.xScale = 1;
  }

  this.yScale = ( realHeight / this.height ) | 0;
  if( this.yScale <= 0 )
  {
    this.yScale = 1;
  }

  if( this.maintainAspectRatio )
  {
    this.xScale = this.yScale = Math.min( this.xScale, this.yScale );
  }

  // Determine position offset.
  if( this.centerDisplay )
  {
    this.xOffset = ( ( realWidth  - ( this.width  * this.xScale ) ) / 2 ) | 0;
    this.yOffset = ( ( realHeight - ( this.height * this.yScale ) ) / 2 ) | 0;
  }
  else
  {
    this.xOffset = 0;
    this.yOffset = 0;
  }

  if( this.canvas !== undefined )
  {
    SetCanvasDimensions( this.canvas, this.width * this.xScale, this.height * this.yScale );

    var context = GetCanvasContext2D( this.canvas );
    context.restore();
    context.scale( this.xScale, this.yScale );
    context.save();

    // TODO: Engine should not be concerned with positioning?
    SetCanvasPosition( this.canvas, this.xOffset, this.yOffset );

    // TODO: Temporary first time draw.
    this.clear();
  }
  
  var length = this.objectList.length;
  var index;
  for( index = 0; index < length; index++ )
  {
    this.objectList[index].setNeedsRedraw( true );
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

  canvasContext.fillRect( 0, 0, this.width, this.height );
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

VideoDisplay.prototype.drawRectangle = function( xPosition, yPosition, width, height )
{
  var canvas = this.getCanvas();
  if( canvas === null )
  {
    return;
  }
  
  var canvasContext = GetCanvasContext2D( canvas );
  canvasContext.fillStyle = this.foregroundColor.string;
  canvasContext.fillRect( xPosition, yPosition, width, height );
};

VideoDisplay.prototype.updateQuadTree = function()
{
  // Do nothing, visible canvas are already managed.
};

VideoDisplay.prototype.getCanvas = function()
{
  return this.canvas;
};

VideoDisplay.prototype.draw = function()
{
  var canvasContext = GetCanvasContext2D( this.canvas );
  canvasContext.fillStyle = this.backgroundColor.string;
  canvasContext.fillRect( 0, 0, this.width, this.height );
};
