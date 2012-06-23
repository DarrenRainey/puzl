function BlockGraphic( drawObject, cellWidth, cellHeight )
{
  //console.log( cellHeight );
  this.image = drawObject.getCanvas();
  //this.image = image;

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
  //console.log( this.numberOfCells );

  //cellx = ( cellx * ( realWidth  + 1 ) ) + 1;
  //celly = ( celly * ( realHeight + 1 ) ) + 1;

  /*for( var x = 0; x < this.image.width; ++x )
  {
    for( var y = 0; y < this.image.height; ++y )
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

    var canvasContext = this.canvas.getContext( "2d" );
    canvasContext.drawImage( this.image, 0, 0 );
    canvasContext.globalCompositeOperation = "source-atop";
    canvasContext.fillStyle = this.color;
    canvasContext.fillRect( 0, 0, this.image.width, this.image.height );
  }
}

BlockGraphic.prototype.print = function( drawObject, text )
{
  var context = drawObject.getContext();
  if( context == undefined )
  {
    context = drawObject;
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
    if( drawObject.display == null )
    {
      width  = this.width;
      height = this.height;
    }
    else
    {
      xScale = drawObject.display.xScale;
      yScale = drawObject.display.yScale;
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

      if( drawObject.display == null )
      {
        DrawWithNearestScale( this, drawObject,
                              cellX, cellY,
                              this.cellWidth, this.cellHeight,
                              this.xPosition, this.yPosition,
                              width, height );
      }
      else
      {
        DrawWithNearestScale( this, drawObject,
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
  this.xPosition = this.width  * xPosition;
  this.yPosition = this.height * yPosition;
}

BlockGraphic.prototype.getCanvas = function()
{
  return this.canvas;
}
