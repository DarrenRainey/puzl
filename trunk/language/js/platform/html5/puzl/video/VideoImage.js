var CanvasIdCounter = -1;

function VideoImage()
{
  this.canvasID;
  this.canvas;
  this.display;

  this.filename;

  this.width;
  this.height;
    
  this.constructor = function()
  {
    if( arguments.length > 0 )
    {
      if( arguments.length > 2 )
      {
        //var argument0 = arguments[0];
        //if( typeof arguments[0] )
      }
    }
    else
    {

    }

    this.canvasID = ++CanvasIdCounter + "canvas";
    this.canvas   = CreateOffScreenCanvas( this.canvasID );
    this.display  = null;

    this.filename = "";

    this.width  = 1;
    this.height = 1;
  };

  this.setRealDimensions = function( width, height )
  {
    SetCanvasDimensions( this.canvas, width, height );
    
    if( this.display == null )
    {
      this.width  = width;
      this.height = height;
    }
  };

  this.getRealWidth = function( width )
  {
    return this.canvas.width;
  };

  this.getRealHeight = function( height )
  {
    return this.canvas.height;
  };
  
  this.setDimensions = function( width, height )
  {
    if( this.display == null )
    {
      this.setRealDimensions( width, height );
    }
    else
    {
      this.width  = width;
      this.height = height;

      this.setRealDimensions( width  * this.display.xScale,
                              height * this.display.yScale );
    }
  };

  this.getWidth = function( width )
  {
    return this.width;
  };

  this.getHeight = function( height )
  {
    return this.height;
  };

  this.setPosition = function( xPosition, yPosition )
  {
    // NOTE: Should this only happen with a display.
    if( this.display != null )
    {
      //console.log( this.display.xOffset );
      SetCanvasPosition( this.canvas,
                         ( xPosition * this.display.xScale ) + this.display.xOffset,
                         ( yPosition * this.display.yScale ) + this.display.yOffset );
    }
  };

  this.fill = function( colorRgb )
  {
    var context = GetCanvasContext2D( this.canvas );
    context.fillStyle = colorRgb;
    context.fillRect( 0, 0, this.canvas.width, this.canvas.height );
  };

  this.setDisplay = function( display )
  {
    //console.log( "VideoImage::setDisplay()" );
    if( display == this.display )
    {
      return;
    }
    
    if( display == null && this.display != null )
    {
      // Turn this page anchored canvas to an offscreen canvas.
      this.canvas = OnScreenToOffScreenCanvas( this.canvas );
      this.display = null;
    }
    else
    {
      // Turn this offscreen canvas to a page anchored canvas.
      if( this.display != null )
      {
        // NOTE: Multiple displays are not really supported right now;
        // so, just act like nothing happened.
        //this.setDisplay( null );
        return;
      }

      this.canvas = OffScreenToOnScreenCanvas( this.canvas );
      this.display = display;
    }
  };

  this.load = function( filename )
  {
    //console.log( "VideoImage::load()" );
    this.filename = filename;
    GlobalVideoSystem.queueVideoImage( this, this.filename );
  };

  // Temporary?
  this.getCanvas = function()
  {
    return this.canvas;
  };

  this.getContext = function()
  {
    return GetCanvasContext2D( this.canvas );
  };

  this.constructor();
  return this;
}
