// var GlobalVideoDisplay;

function VideoDisplay()
{
  this.realWidth;
  this.realHeight;
  this.xScale;
  this.yScale;
  this.maintainAspectRatio;

  this.centerDisplay;
  this.xOffset;
  this.yOffset;
  
  this.fullScreen;
  
  this.foregroundColor;
  
  this.constructor = function()
  {
    //GlobalVideoDisplay = this;
    
    this.setFullScreen( false );

    this.centerDisplay = true;
    this.maintainAspectRatio = true;
    this.setRealDimensions( this.getHeight(), this.getWidth() );
    
    this.setBackgroundColor( "rgb(0,0,0)" );
  };
  
  this.setFullScreen = function( fullScreen )
  {
    this.fullScreen = fullScreen;
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

  this.setRealDimensions = function( width, height )
  {
    this.realWidth  = width;
    this.realHeight = height;

    // Determine scale.
    this.xScale = Math.floor( this.getWidth()  / this.realWidth );
    if( this.xScale <= 0 )
    {
      this.xScale = 1;
    }
    
    this.yScale = Math.floor( this.getHeight() / this.realHeight );
    if( this.yScale <= 0 )
    {
      this.yScale = 1;
    }

    if( this.maintainAspectRatio )
    {
      this.xScale = this.yScale = Math.min( this.xScale, this.yScale );
    }

    // Determine position offset.
    if( this.centerDisplay )
    {
      this.xOffset = Math.floor( ( this.getWidth()  - ( this.realWidth  * this.xScale ) ) / 2 );
      this.yOffset = Math.floor( ( this.getHeight() - ( this.realHeight * this.yScale ) ) / 2 );
    }
    else
    {
      this.xOffset = 0;
      this.yOffset = 0;
    }
  };
  
  this.clear = function()
  {
    // TODO: Determine what this function should do.
    // Perhaps clear list of registered VideoObjects and null their links to
    // this display.
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
