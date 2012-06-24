function BlockGraphic( videoObject, cellWidth, cellHeight )
{
  var videoCellImage = new VideoCellImage( videoObject, cellWidth, cellHeight );

  videoCellImage.constructor                   = this.constructor;
  videoCellImage.setPositionGridCellDimensions = this.setPositionGridCellDimensions;
  videoCellImage.print                         = this.print;
  videoCellImage.setPosition                   = this.setPosition;

  videoCellImage.constructor();
  return videoCellImage;
};

BlockGraphic.prototype.constructor = function()
{
  this.xPosition = 0;
  this.yPosition = 0;
  this.absolutePosition = false;
  this.positionGridCellWidth;
  this.positionGridCellHeight;
  this.setPositionGridCellDimensions( this.cellWidth, this.cellHeight );

  // TODO: Pre-calculate all cell rectangles.
};

BlockGraphic.prototype.setPositionGridCellDimensions = function( positionGridCellWidth, positionGridCellHeight )
{
  this.positionGridCellWidth  = positionGridCellWidth;
  this.positionGridCellHeight = positionGridCellHeight;
};

BlockGraphic.prototype.print = function( videoObject, text )
{
  var context = videoObject.getContext();
  if( context == undefined )
  {
    context = videoObject;
  }

  var length = text.length;
  if( length > 0 )
  {
    var charCode;
    var cellX;
    var cellY;

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

    var width;
    var height;
    var xScale;
    var yScale;
    if( videoObject.display == null )
    {
      width  = this.width;
      height = this.height;
    }
    else
    {
      xScale = videoObject.display.xScale;
      yScale = videoObject.display.yScale;
      width  = this.width  * xScale;
      height = this.height * yScale;
    }

    for( var index = 0; index < length; index++ )
    {
      charCode = text.charCodeAt( index ) - 32; // TODO: The offset value should be eliminated with prebuilt rectangle array.

      // TODO: Optimize. Use prebuilt rectangles.
      cellX = charCode % this.mapWidth;
      cellY = Math.floor( charCode / this.mapWidth );

      cellX = ( cellX * ( this.cellWidth  + 1 ) ) + 1;
      cellY = ( cellY * ( this.cellHeight + 1 ) ) + 1;

      if( videoObject.display == null )
      {
        DrawWithNearestScale( this, videoObject,
                              cellX, cellY,
                              this.cellWidth, this.cellHeight,
                              this.xPosition, this.yPosition,
                              width, height );
      }
      else
      {
        DrawWithNearestScale( this, videoObject,
                              cellX, cellY,
                              this.cellWidth, this.cellHeight,
                              this.xPosition * xScale, this.yPosition * yScale,
                              width, height );
      }

      this.xPosition += this.width;
    }

    if( hasAlpha )
    {
      context.globalAlpha = 1.0;
    }
  }
};

BlockGraphic.prototype.setPosition = function( xPosition, yPosition )
{
  this.xPosition = this.positionGridCellWidth  * xPosition;
  this.yPosition = this.positionGridCellHeight * yPosition;
};
