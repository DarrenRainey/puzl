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
  baseVideoObject.colorKey;

  baseVideoObject.cellList;
  baseVideoObject.cellNameIndexHash;

  baseVideoObject.constructor      = this.constructor;
  baseVideoObject.getAttributes    = this.getAttributes;
  baseVideoObject.setAttributes    = this.setAttributes;
  baseVideoObject.getColor         = this.getColor;
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

  // Populate cells from videoCellImageData.
  this.cellList = new Array();
  this.cellNameIndexHash = new Array();
  var frames = videoCellImageData["frames"];
  var frame;
  for( var frameName in frames )
  {
    //console.log( frameName );
    frame = frames[frameName];
    this.cellNameIndexHash[frameName] = this.loadCell( frame["x"], frame["y"] );
  }

  // Populate layer information.
  var layers = videoCellImageData["layers"];
  var numberOfLayers = layers.length;
  this.color = new Array();
  this.canvas = new Array();
  this.colorKey = new Array();
  
  var layerIndex;
  for( layerIndex = 0; layerIndex < numberOfLayers; layerIndex++ )
  {
    var layer = layers[layerIndex];
    //console.log( layer["name"] );
    var canvas = CreateOffScreenCanvas();
    SetCanvasDimensions( canvas, sourceVideoObjectCanvas.width, sourceVideoObjectCanvas.height );
    this.canvas.push( canvas );

    var colorKey = layer["colorKey"];
    if( colorKey !== undefined )
    {
      colorKey = new Color( colorKey );
      this.colorKey.push( colorKey );
      this.setColor( colorKey, layerIndex );
      //this.attributes &= ~IMAGE_ATTRIBUTE_COLOR;
    }
    else
    {
      this.colorKey.push( colorKey ); // Pushing an undefined instance?
      this.color.push( new Color( 255, 255, 255, 1 ) );
    }
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

VideoCellImage.prototype.getColor = function( layerIndex )
{
  if( layerIndex === undefined )
  {
    //console.log( "Deprecated call to VideoCellImage::getColor" );
    layerIndex = 0;
  }
  
  return this.color[layerIndex];
}

VideoCellImage.prototype.setColor = function( color, layerIndex )
{
  if( layerIndex === undefined )
  {
    //console.log( "Deprecated call to VideoCellImage::setColor" );
    layerIndex = 0;
  }
  
  var thisColor = this.color[layerIndex];
  
  var shouldChangeColor;
  if( thisColor === undefined )
  {
    this.color[layerIndex] = thisColor = new Color( color );
    shouldChangeColor = true;
  }
  else
  if( !thisColor.equals( color ) )
  {
    thisColor.copy( color );
    shouldChangeColor = true;
  }
  else
  {
    shouldChangeColor = false;
  }
  
  if( shouldChangeColor )
  { 
    if( this.queueErase ) // TODO: Fix with polymorphism, as VideoCellImage doesn't have queueErase?
    {
      this.queueErase();
    }
    this.needsRedraw = true;

    //console.log( "Changing layer #" + layerIndex + " to " + thisColor.string );

    var sourceVideoObjectCanvas = this.sourceVideoObject.getCanvas();
    var canvasContext = GetCanvasContext2D( this.canvas[layerIndex] );

    canvasContext.drawImage( sourceVideoObjectCanvas, 0, 0 );

    var colorKey = this.colorKey[layerIndex];
    if( colorKey !== undefined )
    {
      var imageData = canvasContext.getImageData( 0, 0, sourceVideoObjectCanvas.width, sourceVideoObjectCanvas.height );
      var data = imageData.data;

      var red   = thisColor.red;
      var green = thisColor.green;
      var blue  = thisColor.blue;
      var alpha = ( thisColor.alpha * 255 ) | 0;

      var redKey   = colorKey.red;
      var greenKey = colorKey.green;
      var blueKey  = colorKey.blue;
      
      for( var i = 0; i < data.length; i += 4 )
      {
        if( ( data[i] === redKey ) &&
            ( data[i + 1] === greenKey ) &&
            ( data[i + 2] === blueKey ) )
        {
          data[i] = red;
          data[i + 1] = green;
          data[i + 2] = blue;
          data[i + 3] = 255;//alpha;
        }
        else
        {
          data[i] = 0;
          data[i + 1] = 0;
          data[i + 2] = 0;
          data[i + 3] = 0;
        }
      }

      // overwrite original image
      canvasContext.putImageData( imageData, 0, 0 );
    }
    //else
    //if( ( this.attributes & IMAGE_ATTRIBUTE_COLOR ) > 0 )
    /*if( true )
    {
      var imageData = canvasContext.getImageData( 0, 0, sourceVideoObjectCanvas.width, sourceVideoObjectCanvas.height );
      var data = imageData.data;

      var red   = thisColor.red;
      var green = thisColor.green;
      var blue  = thisColor.blue;
      
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
    }*/
    else
    {
      //canvasContext.globalCompositeOperation = "source-atop";
      //canvasContext.fillStyle = thisColor.string;
      canvasContext.drawImage( sourceVideoObjectCanvas, 0, 0, sourceVideoObjectCanvas.width, sourceVideoObjectCanvas.height );
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
  return this.canvas[0];
};
