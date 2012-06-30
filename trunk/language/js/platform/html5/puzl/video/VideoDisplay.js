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

  this.videoImageList;
  
  this.fullScreen;
  
  this.foregroundColor;
  
  this.constructor();
  return this;
}

VideoDisplay.prototype.constructor = function()
{
  //GlobalVideoDisplay = this;

  this.setFullScreen( false );

  this.centerDisplay = true;
  this.maintainAspectRatio = true;
  this.setRealDimensions( this.getHeight(), this.getWidth() );

  this.setBackgroundColor( "rgb(0,0,0)" );

  this.videoImageList = new Array();
};

VideoDisplay.prototype.setFullScreen = function( fullScreen )
{
  this.fullScreen = fullScreen;
};

VideoDisplay.prototype.getHeight = function()
{
  //return document.height;
  /*console.log( document.body.scrollHeight +":"+ document.documentElement.scrollHeight+":"+
                    document.body.offsetHeight+":"+document.documentElement.offsetHeight+":"+
                    document.body.clientHeight+":"+document.documentElement.clientHeight );*/

  return Math.max( /*Math.max( document.body.scrollHeight, document.documentElement.scrollHeight ),*/
                    Math.max( document.body.offsetHeight, document.documentElement.offsetHeight ),
                    Math.max( document.body.clientHeight, document.documentElement.clientHeight ) );
};

VideoDisplay.prototype.getWidth = function()
{
  //return document.width;
  /*console.log( document.body.scrollWidth +":"+ document.documentElement.scrollWidth+":"+
                    document.body.offsetWidth+":"+document.documentElement.offsetWidth+":"+
                    document.body.clientWidth+":"+document.documentElement.clientWidth );*/

  return Math.max( /*Math.max( document.body.scrollWidth, document.documentElement.scrollWidth ),*/
                    Math.max( document.body.offsetWidth, document.documentElement.offsetWidth ),
                    Math.max( document.body.clientWidth, document.documentElement.clientWidth ) );
};

VideoDisplay.prototype.setRealDimensions = function( width, height )
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

VideoDisplay.prototype.clear = function()
{
  // Clear list of registered VideoObjects and null their links to
  // this display.
  var length = this.videoImageList.length;
  var index;
  for( index = 0; index < length; index++ )
  {
    this.videoImageList[index].setDisplay( null );
  }

  this.videoImageList = [];
};

VideoDisplay.prototype.setBackgroundColor = function( color )
{
  //this.backgroundColor = "rgb(" + color.red + "," + color.green + "," + color.blue + ")";
  document.body.style.backgroundColor = color;
};

VideoDisplay.prototype.setForegroundColor = function( color )
{
  //this.foregroundColor = "rgb(" + color.red + "," + color.green + "," + color.blue + ")";
  this.foregroundColor = color;
};

VideoDisplay.prototype.drawRectangle = function( xPosition, yPosition, width, height )
{
  //this.context.fillStyle = this.foregroundColor;
  //this.context.fillRect( xPosition, yPosition, width, height );
};

VideoDisplay.prototype.drawRectangle = function( canvas, xPosition, yPosition, width, height )
{
  var canvasContext = GetCanvasContext2D( canvas );
  canvasContext.fillStyle = this.foregroundColor;
  canvasContext.fillRect( xPosition, yPosition, width, height );
};

/*VideoDisplay.prototype.getColorRgb = function( red, green, blue )
{
  var color = new Color();
  color.setRgb( red, green, blue );
  return color;
};*/

VideoDisplay.prototype.addVideoImage = function( videoImage )
{
  // TODO: Make sure videoImage is not already in the list.
  videoImage.setDisplay( this );
  this.videoImageList[this.videoImageList.length] = videoImage;
};

VideoDisplay.prototype.addVideoImage = function( videoImage )
{
  // TODO: Make sure videoImage is not already in the list.
  videoImage.setDisplay( this );
  this.videoImageList[this.videoImageList.length] = videoImage;
};

VideoDisplay.prototype.removeVideoImage = function( videoImage )
{
  var length = this.videoImageList.length;
  var index;
  for( index = 0; index < length; index++ )
  {
    if( videoImage == this.videoImageList[index] )
    {
      videoImage.setDisplay( null );
      this.videoImageList.splice( index, 1 );
      return;
    }
  }
};

VideoDisplay.prototype.determineTopLeft = function()
{
  var videoImage;
  var length = this.videoImageList.length;
  if( length < 1 )
  {
    this.top  = 0;
    this.left = 0;
    return;
  }
  
  this.top  = this.videoImageList[index].getYPosition();
  this.left = this.videoImageList[index].getXPosition();

  var currentTop;
  var currentLeft;
  for( var index = 0; index < length; index++ )
  {
    videoImage  = this.videoImageList[index];
    
    currentTop  = videoImage.getYPosition();
    if( currentTop < this.top )
    {
      this.top = currentTop;
    }

    currentLeft = videoImage.getXPosition();
    if( currentLeft < this.left )
    {
      this.left = currentLeft;
    }
  }
};
