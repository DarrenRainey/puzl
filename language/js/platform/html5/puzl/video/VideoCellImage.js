var EXTRACT_MODE_CELL              = 0    // Mode to extract a cell from a bitmap for cell image.
var EXTRACT_MODE_ABS               = 1    // Mode to extract the bitmap for a cell image.

var IMAGE_ATTRIBUTE_TRANSPARENCY  = 1024 // Indicates image with transparency.
var IMAGE_ATTRIBUTE_ALPHABLEND    = 2048 // Indicates image with alpha/semi transparency.
var IMAGE_ATTRIBUTE_COLOR         = 4096 // Indicates image with color modulation.

function VideoCellImage( videoObject, videoCellImageData )
{
  var baseVideoObject = new VideoObject();
  
  baseVideoObject.sourceVideoObject;

  baseVideoObject.cellWidth;
  baseVideoObject.cellHeight;

  baseVideoObject.mapWidth;
  baseVideoObject.mapHeight;

  baseVideoObject.canvas;

  baseVideoObject.attributes;

//   baseVideoObject.red;
//   baseVideoObject.green;
//   baseVideoObject.blue;
//   baseVideoObject.alpha;

  baseVideoObject.color;

  baseVideoObject.cellList;
  baseVideoObject.cellNameIndexHash;

  baseVideoObject.constructor      = this.constructor;
  baseVideoObject.getAttributes    = this.getAttributes;
  baseVideoObject.setAttributes    = this.setAttributes;
  baseVideoObject.setColor         = this.setColor;
  baseVideoObject.loadCell         = this.loadCell;
  baseVideoObject.getNumberOfCells = this.getNumberOfCells;
  baseVideoObject.getCanvas        = this.getCanvas;
  
  baseVideoObject.constructor( videoObject, videoCellImageData );
  return baseVideoObject;
};

VideoCellImage.prototype.constructor = function( videoObject, videoCellImageData )
{
  this.sourceVideoObject = videoObject;
  var sourceVideoObjectCanvas = this.sourceVideoObject.getCanvas();

  this.cellWidth  = videoCellImageData["cellWidth"];
  this.cellHeight = videoCellImageData["cellHeight"];

  this.mapWidth  = ( sourceVideoObjectCanvas.width  / ( this.cellWidth  + 1 ) ) | 0;
  this.mapHeight = ( sourceVideoObjectCanvas.height / ( this.cellHeight + 1 ) ) | 0;

  this.setDimensions( this.cellWidth, this.cellHeight );

  this.canvas = CreateOffScreenCanvas();
  SetCanvasDimensions( this.canvas,
                       sourceVideoObjectCanvas.width, sourceVideoObjectCanvas.height );

  this.attributes &= ~IMAGE_ATTRIBUTE_COLOR;
  this.color = new Color( 255, 255, 255, 1 );

  this.cellList = new Array();
  this.cellNameIndexHash = new Array();

  // Populate cells from videoCellImageData.
  var frames = videoCellImageData["frames"];
  var frame;
  for( var frameName in frames )
  {
    //console.log( frameName );
    frame = frames[frameName];
    this.cellNameIndexHash[frameName] = this.loadCell( frame["x"], frame["y"] );
  }
};

VideoCellImage.prototype.getAttributes = function()
{
  return this.attributes;
}

VideoCellImage.prototype.setAttributes = function( attributes )
{
  this.attributes = attributes;
}

VideoCellImage.prototype.setColor = function( color )
{
  if( !this.color.equals( color ) )
  {
    this.queueErase();
    this.needsRedraw = true;
    
    this.color.copy( color );

    var sourceVideoObjectCanvas = this.sourceVideoObject.getCanvas();
    var canvasContext = GetCanvasContext2D( this.canvas );

    canvasContext.drawImage( sourceVideoObjectCanvas, 0, 0 );
    
    //if( ( this.attributes & IMAGE_ATTRIBUTE_COLOR ) > 0 )
    if( true )
    {
      var imageData = canvasContext.getImageData( 0, 0, sourceVideoObjectCanvas.width, sourceVideoObjectCanvas.height );
      var data = imageData.data;

      var red   = this.color.red;
      var green = this.color.green;
      var blue  = this.color.blue;
      
      var tintLevel = .125;
      var tintLevelComplement = 1 - tintLevel;
      for( var i = 0; i < data.length; i += 4 )
      {
        // red
        data[i]     *= tintLevelComplement + ( red   * tintLevel );
        // green
        data[i + 1] *= tintLevelComplement + ( green * tintLevel );
        // blue
        data[i + 2] *= tintLevelComplement + ( blue  * tintLevel );
      }

      // overwrite original image
      canvasContext.putImageData( imageData, 0, 0 );
    }
    else
    {
      canvasContext.globalCompositeOperation = "source-atop";
      canvasContext.fillStyle = this.color.string;
      canvasContext.fillRect( 0, 0, sourceVideoObjectCanvas.width, sourceVideoObjectCanvas.height );
    }
  }
};

VideoCellImage.prototype.loadCell = function( xPosition, yPosition, mode )
{
  if( mode == null )
  {
    mode = EXTRACT_MODE_ABS;
  }
  else
  if( mode === EXTRACT_MODE_CELL )
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
