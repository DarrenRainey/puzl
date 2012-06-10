function createCanvas( id )
{
  document.write( "<canvas id=\"" + id + "\" style=\"position: absolute; left: 0; top: 0; z-index: 1;\">Canvas not supported.</canvas>" );
  return getCanvas( id );
}

function getCanvas( id )
{
  var canvas = document.getElementById( id );
  if( !canvas || !canvas.getContext )
  {
    console.error( "Failed to get canvas element by id." );
    return;
  }
  
  return canvas;
}

function getContext2D( canvas )
{
  var context = canvas.getContext( "2d" );
  if( !context || !context.drawImage )
  {
    console.error( "Failed to load 2D context from canvas." );
    return;
  }
  
  return context;
}

var GlobalVideoDisplay;
function DocumentBodyOnResize()
{
  GlobalVideoDisplay.documentBodyOnResize();
}

document.body.onload = DocumentBodyOnResize;
document.body.onresize = DocumentBodyOnResize;
//window.onresize =  DocumentBodyOnResize;

function VideoDisplay( width, height )
{
  this.canvas;
  this.context;
  
  this.realWidth;
  this.realHeight;
  this.width;
  this.height;
  this.fullScreen;
  
  this.backgroundColor;
  this.foregroundColor;
  
  this.constructor = function( width, height )
  { 
    GlobalVideoDisplay = this;
    
    this.canvas  = createCanvas( "canvas" );
    this.context = getContext2D( this.canvas );
  
    this.setDimensions( width, height );
    this.setRealDimensions( width, height );
    this.setFullScreen( false );
    
    this.backgroundColor = "rgb(0,0,0)";
  };
  
  this.setDimensions = function( width, height )
  {
    this.width  = width;
    this.height = height;
    //this.canvas.width  = this.realWidth  = width;
    //this.canvas.height = this.realHeight = height;
  };
  
  this.setRealDimensions = function( width, height )
  {
    this.canvas.width  = this.realWidth  = width;
    this.canvas.height = this.realHeight = height;
  };
  
  this.setFullScreen = function( fullScreen )
  {
    this.fullScreen = fullScreen;
    if( fullScreen )
    {
      this.setRealDimensions( document.width, document.height );
    }
    else
    {
      this.setRealDimensions( this.width, this.height );
    }
  };
  
  this.documentBodyOnResize = function()
  {
    if( this.fullScreen )
    {
      this.setRealDimensions( document.width, document.height );
    }
  };
  
  this.clear = function()
  {
    this.context.fillStyle = this.backgroundColor;
    this.context.fillRect( 0, 0, this.realWidth, this.realHeight );
  };
  
  this.setBackgroundColor = function( color )
  {
    //this.backgroundColor = "rgb(" + color.red + "," + color.green + "," + color.blue + ")";
    this.backgroundColor = color;
  };
  
  this.setForegroundColor = function( color )
  {
    //this.foregroundColor = "rgb(" + color.red + "," + color.green + "," + color.blue + ")";
    this.foregroundColor = color;
  };
  
  this.drawRectangle = function( xPosition, yPosition, width, height )
  {
    this.context.fillStyle = this.foregroundColor;
    this.context.fillRect( xPosition, yPosition, width, height );
  };
  
  /*this.getColorRgb = function( red, green, blue )
  {
    var color = new Color();
    color.setRgb( red, green, blue );
    return color;
  };*/
  
  this.constructor( width, height );
  return this;
}
