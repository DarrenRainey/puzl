var CanvasIdCounter = -1;

function VideoImage()
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

  this.setDimensions = function( width, height )
  {
    SetCanvasDimensions( this.canvas, width, height );
  };

  this.getWidth = function( width )
  {
    return this.canvas.width;
  };

  this.getHeight = function( height )
  {
    return this.canvas.height;
  };

  this.setPosition = function( xPosition, yPosition )
  {
    SetCanvasPosition( this.canvas, xPosition, yPosition );
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
}
