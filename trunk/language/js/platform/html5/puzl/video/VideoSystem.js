RequestAnimFrame = window.requestAnimationFrame       ||
                   window.webkitRequestAnimationFrame ||
                   window.mozRequestAnimationFrame    ||
                   window.oRequestAnimationFrame      ||
                   window.msRequestAnimationFrame     ||
                   function( callback )
                   {
                     window.setTimeout( callback, 1000 / 60 );
                   };

var GlobalVideoSystem;

function VideoSystem( width, height )
{
  GlobalVideoSystem = this;

  this.videoImageIDList    = new Array();
  this.videoImageLoadQueue = new Array();

  this.display = new VideoDisplay( width, height );
  
  this.getRequestAnimFrame = function( callback )
  {
    return RequestAnimFrame( callback );
  };
  
  this.draw = function()
  {
    this.display.clear();
  };
  
  this.getDisplay = function()
  {
    return this.display;
  };

  this.getAvailableImageID = function()
  {
    var numberOfIDSlots = this.videoImageIDList.length;
    var index;
    for( index = 0; index < numberOfIDSlots; index++ )
    {
      if( this.videoImageIDList[index] == null )
      {
        return index;
      }
    }

    return index;
  };

  this.queueVideoImage = function( videoImage, filename )
  {
    var availableImageID = this.getAvailableImageID();

    videoImage.videoSystem = this;
    videoImage.id = availableImageID;

    this.videoImageLoadQueue[this.videoImageLoadQueue.length] = videoImage;
    videoImage.image = new Image();

    videoImage.image.videoImageID = videoImage.id;
    videoImage.image.addEventListener( "load", ProcessVideoImageLoad, false );

    videoImage.filename = filename;
  };

  this.processImageLoadQueue = function()
  {
    var numberOfIDQueuedVideoImages = GlobalVideoSystem.videoImageLoadQueue.length;
    var index;
    var videoImage;
    for( index = 0; index < numberOfIDQueuedVideoImages; index++ )
    {
      videoImage = GlobalVideoSystem.videoImageLoadQueue[index];
      videoImage.image.src = videoImage.filename;
    }
  };
}

function ProcessVideoImageLoad( loadEvent )
{
  var id = loadEvent.target.videoImageID;

  var numberOfIDQueuedVideoImages = GlobalVideoSystem.videoImageLoadQueue.length;
  var index;
  var videoImage;
  for( index = 0; index < numberOfIDQueuedVideoImages; index++ )
  {
    videoImage = GlobalVideoSystem.videoImageLoadQueue[index];
    if( id == videoImage.id )
    {
      SetCanvasDimensions( videoImage.getCanvas(), videoImage.image.width, videoImage.image.height );
      videoImage.getContext().drawImage( videoImage.image, 0, 0 );
      
      GlobalVideoSystem.videoImageLoadQueue.splice( index, 1 );
      videoImage.image.src = null;
      break;
    }
  }

  if( GlobalVideoSystem.videoImageLoadQueue.length == 0 )
  {
    GlobalGameShell.shellPostInitialize();
  }
}

function SetCanvasXPosition( canvas, xPosition )
{
  canvas.style.left = xPosition + "px";
}

function SetCanvasYPosition( canvas, yPosition )
{
  canvas.style.top  = yPosition + "px";
}

function SetCanvasPosition( canvas, xPosition, yPosition )
{
  SetCanvasXPosition( canvas, xPosition );
  SetCanvasYPosition( canvas, yPosition );
}

function SetCanvasDimensions( canvas, width, height )
{
  canvas.width  = width;
  canvas.height = height;
}

function DrawWithNearestScale( image, context, xPosition, yPosition, width, height )
{
  // Create an offscreen canvas, draw an image to it, and fetch the pixels
  var offtx = document.createElement( "canvas" ).getContext( "2d" );
  offtx.drawImage( image, 0, 0 );

  var imgData;
  try
  {
    imgData = offtx.getImageData( 0, 0, image.width, image.height ).data;
  }
  catch( error )
  {
    // Just draw image the regular way.
    context.drawImage( image, xPosition, yPosition, width, height );
    return;
  }

  var zoomXLevel = width  / image.width;
  var zoomYLevel = height / image.height;

//   var zoomX
//
//   var i;
//   var r;
//   var g;
//   var b;
//   var a;


  // Draw the zoomed-up pixels to a different canvas context
  for( var x = 0; x < image.width; ++x )
  {
    for( var y = 0; y < image.height; ++y )
    {
      // Find the starting index in the one-dimensional image data
      var i = ( y * image.width + x ) * 4;
      var r = imgData[i    ];
      var g = imgData[i + 1];
      var b = imgData[i + 2];
      var a = imgData[i + 3];

      context.fillStyle = "rgba(" + r + "," + g + "," + b + "," + ( a / 255 ) + ")";
      context.fillRect( xPosition + ( x * zoomXLevel ), // TODO: Optimize.
                        yPosition + ( y * zoomYLevel ),
                        zoomXLevel, zoomYLevel );
    }
  }

  //document.destroyElement( "OffscreenCanvas" );
}

var offscreenCanvas        = document.createElement( "canvas" );
var offscreenCanvasContext = offscreenCanvas.getContext( "2d" );

function DrawWithNearestScale( sourceDrawObject, targetDrawObject, sourceXPosition, sourceYPosition, sourceWidth, sourceHeight, xPosition, yPosition, width, height )
{
  var image = sourceDrawObject.getCanvas();
  if( image == undefined )
  {
    image = sourceDrawObject;
  }
  var context = targetDrawObject.getContext();
  
  context.mozImageSmoothingEnabled    = false;
  context.webkitImageSmoothingEnabled = false;
  context.drawImage( image, sourceXPosition, sourceYPosition, sourceWidth, sourceHeight, xPosition, yPosition, width, height );
  return;

  if( ( sourceHeight == height ) && ( sourceWidth == width ) )
  {
    // Just draw image the regular way.
    context.drawImage( image, sourceXPosition, sourceYPosition, sourceWidth, sourceHeight, xPosition, yPosition, width, height );
  }

  // Create an offscreen canvas, draw an image to it, and fetch the pixels
  //var offscreenCanvasContext = document.createElement( "canvas" ).getContext( "2d" );
  offscreenCanvasContext.width  = sourceWidth;
  offscreenCanvasContext.height = sourceHeight;
  //offscreenCanvasContext.globalCompositeOperation = "source-over";
  //offscreenCanvasContext.fillStyle = "rgba(0,0,0,0.0)";
  //offscreenCanvasContext.fillRect( 0, 0, sourceWidth, sourceHeight );
  offscreenCanvasContext.clearRect( 0, 0, sourceWidth, sourceHeight );

  offscreenCanvasContext.drawImage( image, sourceXPosition, sourceYPosition, sourceWidth, sourceHeight, 0, 0, sourceWidth, sourceHeight );

  //offscreenCanvasContext.globalCompositeOperation = "source-atop";
  //offscreenCanvasContext.fillStyle = BuildRgb( 32, 144, 223 );
  //offscreenCanvasContext.fillRect( 0, 0, sourceWidth, sourceHeight );

  var imgData;
  try
  {
    imgData = offscreenCanvasContext.getImageData( 0, 0, sourceWidth, sourceHeight ).data;
  }
  catch( error )
  {
    // Just draw image the regular way.
    context.drawImage( image, sourceXPosition, sourceYPosition, sourceWidth, sourceHeight, xPosition, yPosition, width, height );
    return;
  }

  var zoomXLevel = width  / sourceWidth;
  var zoomYLevel = height / sourceHeight;

  var zoomXIncrement = 0;
  var zoomYIncrement = 0;

  var i;
  var r;
  var g;
  var b;
  var a;

  // Draw the zoomed-up pixels to a different canvas context
  for( var x = 0; x < sourceWidth; ++x )
  {
    zoomXIncrement = x * zoomXLevel;

    for( var y = 0; y < sourceHeight; ++y )
    {
      zoomYIncrement = y * zoomYLevel;

      // Find the starting index in the one-dimensional image data
      i = ( y * sourceWidth + x ) << 2;
      r = imgData[i    ];
      g = imgData[i + 1];
      b = imgData[i + 2];
      a = imgData[i + 3];

      context.fillStyle = "rgba(" + r + "," + g + "," + b + "," + ( a / 255 ) + ")";
      context.fillRect( xPosition + ( zoomXIncrement ), // TODO: Optimize.
                        yPosition + ( zoomYIncrement ),
                        zoomXLevel, zoomYLevel );
    }
  }

  //document.destroyElement( "OffscreenCanvas" );
}

function BuildRgb( red, green, blue )
{
  return "rgb(" + red + "," + green + "," + blue + ")";
}

/*function BuildRgb( color )
{
  return "rgb(" + color[0] + "," + color[1] + "," + color[2] + ")";
}*/

function BuildRgba( red, green, blue, alpha )
{
  return "rgba(" + red + "," + green + "," + blue + "," + ( alpha / 255 ) + ")";
}

function CreateOnScreenCanvas( id )
{
  document.write( "<canvas id=\"" + id + "\" style=\"position: absolute; left: 0; top: 0; z-index: 1;\">Canvas not supported.</canvas>" );
  return GetCanvas( id );
}

function CreateOffScreenCanvas( id )
{
  var canvas = document.createElement( "canvas" );

  if( id != null || id != "" )
  {
    canvas.id = id;
  }

  return canvas;
}

function OffScreenToOnScreenCanvas( oldCanvas )
{
  //document.write( oldCanvas.outerHTML );
  //return GetCanvas( oldCanvas.id );

  var newCanvas = CreateOnScreenCanvas( oldCanvas.id );
  var context   = GetCanvasContext2D( newCanvas );
  context.drawImage( oldCanvas, 0, 0 );
  // NOTE: First draw sets the dimensions?

  return newCanvas;
}

function OnScreenToOffScreenCanvas( oldCanvas )
{
  // TODO: Needs more testing.
  oldCanvas = GetCanvas( oldCanvas.id );
  oldCanvas.parentNode.removeChild( oldCanvas );
  return oldCanvas;
}

function GetCanvas( id )
{
  var canvas = document.getElementById( id );
  if( !canvas || !canvas.getContext )
  {
    console.error( "Failed to get canvas element by id." );
    return;
  }

  return canvas;
}

function GetCanvasContext2D( canvas )
{
  return canvas.getContext( "2d" );
  /*var context = canvas.getContext( "2d" );
  if( !context || !context.drawImage )
  {
    console.error( "Failed to load 2D context from canvas." );
    return;
  }

  return context;*/
}
