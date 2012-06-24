function BlockGraphic( videoObject, cellWidth, cellHeight )
{
  this.sourceVideoObject = videoObject;
  var sourceVideoObjectCanvas = this.sourceVideoObject.getCanvas();

  this.cellWidth  = cellWidth;
  this.cellHeight = cellHeight;

  this.mapWidth  = Math.floor( sourceVideoObjectCanvas.width  / ( this.cellWidth  + 1 ) );
  this.mapHeight = Math.floor( sourceVideoObjectCanvas.height / ( this.cellHeight + 1 ) );

  this.setDimensions( this.cellWidth, this.cellHeight );

  this.canvas = CreateOffScreenCanvas( null );
  SetCanvasDimensions( this.canvas,
                       sourceVideoObjectCanvas.width, sourceVideoObjectCanvas.height );

  this.xPosition = 0;
  this.yPosition = 0;
  this.absolutePosition = false;
  this.positionGridCellWidth;
  this.positionGridCellHeight;
  this.setPositionGridCellDimensions( this.cellWidth, this.cellHeight );

  this.red   = -1;
  this.green = -1;
  this.blue  = -1;
  this.alpha;
  this.setColor( 255, 255, 255, 0.0 );

  // TODO: Pre-calculate cell rectangles.
  this.numberOfCells = this.mapWidth * this.mapHeight;
  //console.log( this.numberOfCells );

  //cellx = ( cellx * ( realWidth  + 1 ) ) + 1;
  //celly = ( celly * ( realHeight + 1 ) ) + 1;

  /*for( var x = 0; x < sourceVideoObjectCanvas.width; ++x )
  {
    for( var y = 0; y < sourceVideoObjectCanvas.height; ++y )
    {

    }
  }*/
}

BlockGraphic.prototype.setDimensions = function( width, height )
{
  this.width  = width;
  this.height = height;
}

BlockGraphic.prototype.setColor = function( red, green, blue, alpha )
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

    var sourceVideoObjectCanvas = this.sourceVideoObject.getCanvas();
    var canvasContext = GetCanvasContext2D( this.canvas );
    canvasContext.drawImage( sourceVideoObjectCanvas, 0, 0 );
    canvasContext.globalCompositeOperation = "source-atop";
    canvasContext.fillStyle = this.color;
    canvasContext.fillRect( 0, 0, sourceVideoObjectCanvas.width, sourceVideoObjectCanvas.height );
  }
}

BlockGraphic.prototype.setPositionGridCellDimensions = function( positionGridCellWidth, positionGridCellHeight )
{
  this.positionGridCellWidth = positionGridCellWidth;
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
}

BlockGraphic.prototype.getCanvas = function()
{
  return this.canvas;
}
