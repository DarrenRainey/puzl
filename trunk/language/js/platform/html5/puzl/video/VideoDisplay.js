// var GlobalVideoDisplay;
// function DocumentBodyOnResize()
// {
//   GlobalVideoDisplay.documentBodyOnResize();
// }
// 
// document.body.onload = DocumentBodyOnResize;
// document.body.onresize = DocumentBodyOnResize;
// //window.onresize =  DocumentBodyOnResize;

function VideoDisplay()
{
  //this.canvas;
  //this.context;
  
  //this.realWidth;
  //this.realHeight;
  //this.width;
  //this.height;
  this.fullScreen;
  
  //this.backgroundColor;
  this.foregroundColor;
  
  this.constructor = function()
  { 
//     GlobalVideoDisplay = this;
    
    //this.canvas  = createCanvas( "canvas" );
    //this.context = GetCanvasContext2D( this.canvas );
    
    this.setFullScreen( false );
    
    this.setBackgroundColor( "rgb(0,0,0)" );
  };
  
  this.setFullScreen = function( fullScreen )
  {
    this.fullScreen = fullScreen;
    //this.setDimensions( document.width, document.height );
  };

  this.getHeight = function()
  {
    //return document.height;
    /*console.log( document.body.scrollHeight +":"+ document.documentElement.scrollHeight+":"+
                     document.body.offsetHeight+":"+document.documentElement.offsetHeight+":"+
                     document.body.clientHeight+":"+document.documentElement.clientHeight );*/
    
    return Math.max( /*Math.max( document.body.scrollHeight, document.documentElement.scrollHeight ),*/
                     Math.max( document.body.offsetHeight, document.documentElement.offsetHeight ),
                     Math.max( document.body.clientHeight, document.documentElement.clientHeight ) );
  };
  
  this.getWidth = function()
  {
    //return document.width;
    /*console.log( document.body.scrollWidth +":"+ document.documentElement.scrollWidth+":"+
                     document.body.offsetWidth+":"+document.documentElement.offsetWidth+":"+
                     document.body.clientWidth+":"+document.documentElement.clientWidth );*/
                     
    return Math.max( /*Math.max( document.body.scrollWidth, document.documentElement.scrollWidth ),*/
                     Math.max( document.body.offsetWidth, document.documentElement.offsetWidth ),
                     Math.max( document.body.clientWidth, document.documentElement.clientWidth ) );
  };
  
  this.clear = function()
  {
    //this.context.fillStyle = this.backgroundColor;
    //this.context.fillRect( 0, 0, this.realWidth, this.realHeight );
  };
  
  this.setBackgroundColor = function( color )
  {
    //this.backgroundColor = "rgb(" + color.red + "," + color.green + "," + color.blue + ")";
    document.body.style.backgroundColor = color;
  };
  
  this.setForegroundColor = function( color )
  {
    //this.foregroundColor = "rgb(" + color.red + "," + color.green + "," + color.blue + ")";
    this.foregroundColor = color;
  };
  
  this.drawRectangle = function( xPosition, yPosition, width, height )
  {
    //this.context.fillStyle = this.foregroundColor;
    //this.context.fillRect( xPosition, yPosition, width, height );
  };

  this.drawRectangle = function( canvas, xPosition, yPosition, width, height )
  {
    var canvasContext = GetCanvasContext2D( canvas );
    canvasContext.fillStyle = this.foregroundColor;
    canvasContext.fillRect( xPosition, yPosition, width, height );
  };
  
  /*this.getColorRgb = function( red, green, blue )
  {
    var color = new Color();
    color.setRgb( red, green, blue );
    return color;
  };*/
  
  this.constructor();
  return this;
}
