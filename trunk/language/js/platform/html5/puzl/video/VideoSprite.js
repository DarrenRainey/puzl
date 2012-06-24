function VideoSprite( videoImage, cellWidth, cellHeight )
{
  var videoCellImage = new VideoCellImage( videoImage, cellWidth, cellHeight );

  videoCellImage.constructor   = this.constructor;
  videoCellImage.draw          = this.draw;
  videoCellImage.setPosition   = this.setPosition;
  videoCellImage.loadAnimation = this.loadAnimation;
  videoCellImage.animate       = this.animate;

  videoCellImage.constructor();
  return videoCellImage;
};

VideoSprite.prototype.constructor = function()
{
  this.xPosition = 0;
  this.yPosition = 0;
  
  this.animation = new Operation();
};

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
  this.xPosition = xPosition;
  this.yPosition = yPosition;
};

VideoSprite.prototype.loadAnimation = function( animation )
{
  return this.animation.load( animation );
};

VideoSprite.prototype.animate = function()
{
  this.animation.read();
};
