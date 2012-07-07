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

  // Pre-calculate all cell rectangles.
  var cellX;
  var cellY;
  var numberOfCells = this.mapWidth * this.mapHeight;
  for( var index = 0; index < numberOfCells; index++ )
  {
    cellX = index % this.mapWidth;
    cellY = Math.floor( index / this.mapWidth );

    this.loadCell( cellX, cellY, EXTRACT_MODE_CELL );
  }
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
    var cell;

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
      cell = this.cellList[charCode];
      
      if( videoObject.display == null )
      {
        DrawWithNearestScale( this, videoObject,
                              cell[0], cell[1],
                              this.cellWidth, this.cellHeight,
                              this.xPosition, this.yPosition,
                              width, height );
      }
      else
      {
        DrawWithNearestScale( this, videoObject,
                              cell[0], cell[1],
                              this.cellWidth, this.cellHeight,
                              ( this.xPosition - videoObject.xPosition ) * xScale,
                              ( this.yPosition - videoObject.yPosition ) * yScale,
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
