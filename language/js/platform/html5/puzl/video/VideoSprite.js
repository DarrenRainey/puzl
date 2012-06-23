function VideoSprite( videoImage, cellWidth, cellHeight )
{
  //console.log( cellHeight );
  this.image = videoImage.getCanvas();

  this.cellWidth  = cellWidth;
  this.cellHeight = cellHeight;

  this.mapWidth  = Math.floor( this.image.width  / ( this.cellWidth  + 1 ) );
  this.mapHeight = Math.floor( this.image.height / ( this.cellHeight + 1 ) );

  this.setDimensions( this.cellWidth, this.cellHeight );

  this.canvas = document.createElement( "canvas" );
  this.canvas.width  = this.image.width;
  this.canvas.height = this.image.height;

  this.xPosition = 0;
  this.yPosition = 0;
  this.absolutePosition = false;

  this.red   = -1;
  this.green = -1;
  this.blue  = -1;
  //this.alpha = 1.0;
  this.setColor( 255, 255, 255, 1.0 );

  // TODO: Pre-calculate cell rectangles.
  this.numberOfCells = this.mapWidth * this.mapHeight;

  this.animation = new Operation();
}

VideoSprite.prototype.setDimensions = function( width, height )
{
  this.width  = width;
  this.height = height;
}

VideoSprite.prototype.setColor = function( red, green, blue, alpha )
{
  this.alpha = alpha;

  var colorChangeDetected = false;
  if( this.red != red )
  {
    colorChangeDetected = true;
  }
  else
  if( this.green != green )
  {
    colorChangeDetected = true;
  }
  else
  if( this.blue != blue )
  {
    colorChangeDetected = true;
  }

  if( colorChangeDetected )
  {
    this.red   = red;
    this.green = green;
    this.blue  = blue;

    this.color = BuildRgb( this.red, this.green, this.blue );

    var canvasContext = this.canvas.getContext( "2d" );
    canvasContext.drawImage( this.image, 0, 0 );
    canvasContext.globalCompositeOperation = "source-atop";
    canvasContext.fillStyle = this.color;
    canvasContext.fillRect( 0, 0, this.image.width, this.image.height );
  }
}

VideoSprite.prototype.draw = function( drawObject )
{
  var context = drawObject.getContext();
  if( context == undefined )
  {
    context = drawObject;
  }
  
  var frameIndex = this.animation.getCurrentFrame();

  var hasAlpha; // TODO: Optimize. Could allocate this value once for each blockgraphic object.
  if( this.alpha != 1.0 )
  {
    hasAlpha = true;
    context.globalAlpha = this.alpha;
  }
  else
  {
    hasAlpha = false;
  }
  
  // TODO: Optimize. Use prebuilt rectangles.
  cellX = frameIndex % this.mapWidth;
  cellY = Math.floor( frameIndex / this.mapWidth );

  cellX = ( cellX * ( this.cellWidth  + 1 ) ) + 1;
  cellY = ( cellY * ( this.cellHeight + 1 ) ) + 1;

  if( drawObject.display == null )
  {
    DrawWithNearestScale( this, drawObject,
                          cellX, cellY,
                          this.cellWidth, this.cellHeight,
                          this.xPosition, this.yPosition,
                          this.width, this.height );
  }
  else
  {
    var xScale = drawObject.display.xScale;
    var yScale = drawObject.display.yScale;
    
    DrawWithNearestScale( this, drawObject,
                          cellX, cellY,
                          this.cellWidth, this.cellHeight,
                          this.xPosition * xScale, this.yPosition * yScale,
                          this.width * xScale, this.height * yScale );
  }
  
  if( hasAlpha )
  {
    context.globalAlpha = 1.0;
  }
};

VideoSprite.prototype.setPosition = function( xPosition, yPosition )
{
  this.xPosition = this.width  * xPosition;
  this.yPosition = this.height * yPosition;
}

VideoSprite.prototype.loadAnimation = function( animation )
{
  return this.animation.load( animation );
}

VideoSprite.prototype.animate = function()
{
  this.animation.read();
}

VideoSprite.prototype.getCanvas = function()
{
  return this.canvas;
}
