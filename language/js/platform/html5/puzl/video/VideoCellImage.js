var EXTRACT_MODE_CELL              = 0    // Mode to extract a cell from a bitmap for sprite
var EXTRACT_MODE_ABS               = 1    // Mode to extract the bitmap for a sprite

function VideoCellImage( videoObject, cellWidth, cellHeight )
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

  this.red   = -1;
  this.green = -1;
  this.blue  = -1;
  this.alpha;
  this.setColor( 255, 255, 255, 0.0 );

  this.cellList = new Array();
};

VideoCellImage.prototype.setDimensions = function( width, height )
{
  this.width  = width;
  this.height = height;
};

VideoCellImage.prototype.setColor = function( red, green, blue, alpha )
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
};

VideoCellImage.prototype.loadCell = function( xPosition, yPosition, mode )
{
  if( mode == EXTRACT_MODE_CELL )
  {
    xPosition = ( xPosition * ( this.cellWidth  + 1 ) ) + 1;
    yPosition = ( yPosition * ( this.cellHeight + 1 ) ) + 1;
  }

  var cellIndex = this.cellList.length;
  this.cellList[cellIndex] = new Array( xPosition, yPosition );
  return cellIndex;
};

VideoCellImage.prototype.getNumberOfCells = function()
{
  return this.cellList.length;
};

VideoCellImage.prototype.getCanvas = function()
{
  return this.canvas;
};
