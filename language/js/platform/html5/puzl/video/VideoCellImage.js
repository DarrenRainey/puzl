var EXTRACT_MODE_CELL              = 0    // Mode to extract a cell from a bitmap for cell image.
var EXTRACT_MODE_ABS               = 1    // Mode to extract the bitmap for a cell image.

var IMAGE_ATTRIBUTE_TRANSPARENCY  = 1024 // Indicates image with transparency.
var IMAGE_ATTRIBUTE_ALPHABLEND    = 2048 // Indicates image with alpha/semi transparency.
var IMAGE_ATTRIBUTE_COLOR         = 4096 // Indicates image with color modulation.

function VideoCellImage( sourceVideoObject, videoCellImageData )
{
  //console.log( "Creating VideoCellImage" );
  VideoObject.call( this );

  /*this.sourceVideoObject;

  this.cellWidth;
  this.cellHeight;

  this.mapWidth;
  this.mapHeight;

  this.canvas;
  this.layerCanvas;

  this.attributes;
  this.alpha;

  this.color;
  this.colorKey;

  this.cellList;
  this.cellNameIndexHash;*/
  
  // Constructor.
  if( sourceVideoObject === undefined )
  {
    // TODO: Allow for such in the future?
    console.error( "Attempting to load VideoCellImage without source VideoObject." );
    return null;
  }

  if( videoCellImageData === undefined )
  {
    // TODO: Allow for such in the future?
    console.error( "Attempting to load VideoCellImage without driving data." );
    return null;
  }
  
  this.sourceVideoObject = sourceVideoObject;
  var sourceVideoObjectCanvas = sourceVideoObject.getCanvas();

  this.cellWidth  = videoCellImageData["cellWidth"];
  this.cellHeight = videoCellImageData["cellHeight"];

  var overallWidth  = sourceVideoObjectCanvas.width;
  var overallHeight = sourceVideoObjectCanvas.height;

  this.mapWidth  = ( overallWidth  / ( this.cellWidth  + 1 ) ) | 0;
  this.mapHeight = ( overallHeight / ( this.cellHeight + 1 ) ) | 0;

  Object2d.prototype.setDimensions.call( this, this.cellWidth, this.cellHeight );

  // Populate cells from videoCellImageData.
  this.cellList = new Array();
  this.cellNameIndexHash = new Array();
  
  var frames = videoCellImageData["frames"];
  if( frames !== undefined )
  {
    var frame;
    for( var frameId in frames )
    {
      //console.log( frameId );
      frame = frames[frameId];
      this.cellNameIndexHash[frameId] = this.loadCell( frame["x"], frame["y"] );
    }
  }
  else
  {
    console.warn( "VideoCellImage driving data does not contain frame information." );
  }

  this.canvas = CreateOffScreenCanvas();
  SetCanvasDimensions( this.canvas, overallWidth, overallHeight );

  // Populate layer information.
  this.color = new Array();
  this.layerCanvas = new Array();
  this.colorKey = new Array();

  var numberOfLayers;
  var layerIndex;
  
  var layers = videoCellImageData["layers"];
  if( layers !== undefined )
  {
    numberOfLayers = layers.length;
    layerIndex;
    for( layerIndex = 0; layerIndex < numberOfLayers; layerIndex++ )
    {
      var layer = layers[layerIndex];
      //console.log( layer["name"] );
      var canvas = CreateOffScreenCanvas();
      SetCanvasDimensions( canvas, overallWidth, overallHeight );
      this.layerCanvas.push( canvas );

      var canvasContext = GetCanvasContext2D( canvas );
      canvasContext.drawImage( sourceVideoObjectCanvas, 0, 0 );

      var colorKey = layer["colorKey"];
      if( colorKey !== undefined )
      {
        colorKey = new Color( colorKey );
        this.colorKey.push( colorKey );

        var imageData = canvasContext.getImageData( 0, 0, overallWidth, overallHeight );
        var data = imageData.data;

        var redKey   = colorKey.red;
        var greenKey = colorKey.green;
        var blueKey  = colorKey.blue;

        var dataLength = data.length;
        for( var i = 0; i < dataLength; i += 4 )
        {
          if( ( data[i] !== redKey ) ||
              ( data[i + 1] !== greenKey ) ||
              ( data[i + 2] !== blueKey ) )
          {
            data[i] = 0;
            data[i + 1] = 0;
            data[i + 2] = 0;
            data[i + 3] = 0;
          }
        }

        // overwrite original image
        canvasContext.putImageData( imageData, 0, 0 );
        
        this.color.push( colorKey );
        //this.attributes &= ~IMAGE_ATTRIBUTE_COLOR;
      }
      else
      {
        this.colorKey.push( colorKey ); // Pushing an undefined instance?
        this.color.push( new Color( 255, 255, 255, 1 ) );
      }
    }
  }
  else
  {
    console.warn( "VideoCellImage driving data does not contain layer information. Defaulting single layer." );

    var canvas = CreateOffScreenCanvas();
    SetCanvasDimensions( canvas, overallWidth, overallHeight );
    this.layerCanvas.push( canvas );
    this.colorKey.push( undefined );
    this.color.push( new Color( 255, 255, 255, 1 ) );
  }

  this.alpha = 1;

  this._redrawPrimaryCanvas();

  this.context = GetCanvasContext2D( this.canvas );
}

extend( VideoCellImage, VideoObject );

// NOTE: Temporary routine until video cell image layers are handled by sub video objects.
VideoCellImage.prototype._redrawPrimaryCanvas = function()
{
  var thisCanvas = this.canvas;
  var overallWidth  = thisCanvas.width;
  var overallHeight = thisCanvas.height;
  var context = GetCanvasContext2D( thisCanvas );
  context.clearRect( 0, 0, overallWidth, overallHeight );

  var thisLayerCanvas = this.layerCanvas;
  var numberOfLayers = thisLayerCanvas.length;
  var layerIndex;
  for( layerIndex = 0; layerIndex < numberOfLayers; layerIndex++ )
  {
    context.drawImage( thisLayerCanvas[layerIndex], 0, 0, overallWidth, overallHeight );
  }
};

VideoCellImage.prototype.getAttributes = function()
{
  return this.attributes;
};

VideoCellImage.prototype.setAttributes = function( attributes )
{
  this.attributes = attributes;
};

VideoCellImage.prototype.getColor = function( layerIndex )
{
  if( layerIndex === undefined )
  {
    //console.log( "Deprecated call to VideoCellImage::getColor" );
    layerIndex = 0;
  }
  
  return this.color[layerIndex];
};

VideoCellImage.prototype.setColor = function( color, layerIndex )
{
  if( layerIndex === undefined )
  {
    //console.log( "Deprecated call to VideoCellImage::setColor" );
    layerIndex = 0;
  }
  
  var thisColor = this.color[layerIndex];
  if( thisColor.equals( color ) )
  {
    return;
  }

  thisColor.copy( color );
  
  //console.log( "Changing layer #" + layerIndex + " to " + thisColor.string );

  var canvas = this.layerCanvas[layerIndex];
  var canvasContext = GetCanvasContext2D( canvas );

  var colorKey = this.colorKey[layerIndex];
  if( colorKey !== undefined )
  {
    canvasContext.globalCompositeOperation = "source-atop"; // NOTE: CocoonJS doesn't seem to do "source-in".
    canvasContext.fillStyle = thisColor.string;
    canvasContext.fillRect( 0, 0, canvas.width, canvas.height );
  }
  //else
  //if( ( this.attributes & IMAGE_ATTRIBUTE_COLOR ) > 0 )
  /*if( true )
  {
    canvasContext.drawImage( sourceVideoObjectCanvas, 0, 0 );
    
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
    var sourceVideoObjectCanvas = this.sourceVideoObject.getCanvas();
    canvasContext.drawImage( sourceVideoObjectCanvas, 0, 0, sourceVideoObjectCanvas.width, sourceVideoObjectCanvas.height );
  }

  this._redrawPrimaryCanvas();

  var thisTargetVideoObject = this.targetVideoObject;
  if( thisTargetVideoObject )
  {
    thisTargetVideoObject.addDirtyRectangle( this );
  }
};

VideoCellImage.prototype.loadCell = function( xPosition, yPosition, mode )
{
  if( mode === null )
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
  this.cellList.push( new Array( xPosition, yPosition ) );
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
