// var GlobalVideoDisplay;

function VideoDisplay( width, height )
{
  var videoObject = new VideoObject();
  
  videoObject.xScale;
  videoObject.yScale;
  videoObject.maintainAspectRatio;

  videoObject.centerDisplay;
  videoObject.xOffset;
  videoObject.yOffset;

  videoObject.left;
  videoObject.top;
  
  videoObject.fullScreen;
  
  videoObject.foregroundColor;

  videoObject.eraseQueue;
  videoObject.numberOfEraseQueueObjects;

  videoObject.constructor             = this.constructor;
  videoObject.setFullScreen           = this.setFullScreen;
  videoObject.getRealHeight           = this.getRealHeight;
  videoObject.getRealWidth            = this.getRealWidth;
  videoObject.setDimensions           = this.setDimensions;
  videoObject.clear                   = this.clear;
  videoObject.setBackgroundColor      = this.setBackgroundColor;
  videoObject.setForegroundColor      = this.setForegroundColor;
  videoObject.drawRectangle           = this.drawRectangle;
  videoObject.addVideoImage           = this.addVideoImage;
  videoObject.removeVideoImage        = this.removeVideoImage;
  videoObject.determineTopLeft        = this.determineTopLeft;
  videoObject.getNextEraseQueueObject = this.getNextEraseQueueObject;
  videoObject.processEraseQueue       = this.processEraseQueue;

  videoObject.updateQuadTree          = this.updateQuadTree;
  
  videoObject.constructor( width, height );
  return videoObject;
}

VideoDisplay.prototype.constructor = function( width, height )
{
  //GlobalVideoDisplay = this;

  this.eraseQueue = new Array();
  this.numberOfEraseQueueObjects = 0;

  this.setFullScreen( false );

  this.centerDisplay = true;
  this.maintainAspectRatio = true;

  this.left = 0;
  this.top  = 0;

  this.quadTree = null;
  
  this.setDimensions( width, height );

  this.setBackgroundColor( "rgb(0,0,0)" );
};

VideoDisplay.prototype.setFullScreen = function( fullScreen )
{
  this.fullScreen = fullScreen;
};

VideoDisplay.prototype.getRealHeight = function()
{
  //return document.height;
  /*console.log( document.body.scrollHeight +":"+ document.documentElement.scrollHeight+":"+
                    document.body.offsetHeight+":"+document.documentElement.offsetHeight+":"+
                    document.body.clientHeight+":"+document.documentElement.clientHeight );*/

  return Math.max( /*Math.max( document.body.scrollHeight, document.documentElement.scrollHeight ),*/
                    Math.max( document.body.offsetHeight, document.documentElement.offsetHeight ),
                    Math.max( document.body.clientHeight, document.documentElement.clientHeight ) );
};

VideoDisplay.prototype.getRealWidth = function()
{
  //return document.width;
  /*console.log( document.body.scrollWidth +":"+ document.documentElement.scrollWidth+":"+
                    document.body.offsetWidth+":"+document.documentElement.offsetWidth+":"+
                    document.body.clientWidth+":"+document.documentElement.clientWidth );*/

  return Math.max( /*Math.max( document.body.scrollWidth, document.documentElement.scrollWidth ),*/
                    Math.max( document.body.offsetWidth, document.documentElement.offsetWidth ),
                    Math.max( document.body.clientWidth, document.documentElement.clientWidth ) );
};

VideoDisplay.prototype.setDimensions = function( width, height )
{
  this.width  = width;
  this.height = height;

  var realWidth  = this.getRealWidth();
  var realHeight = this.getRealHeight();

  // Determine scale.
  this.xScale = ( realWidth  / this.width ) | 0;
  if( this.xScale <= 0 )
  {
    this.xScale = 1;
  }

  this.yScale = ( realHeight / this.height ) | 0;
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
    this.xOffset = ( ( realWidth  - ( this.width  * this.xScale ) ) / 2 ) | 0;
    this.yOffset = ( ( realHeight - ( this.height * this.yScale ) ) / 2 ) | 0;
  }
  else
  {
    this.xOffset = 0;
    this.yOffset = 0;
  }

  // Scale and position all linked video images.
  var videoObjectListLength = this.objectList.length;
  if( videoObjectListLength > 0 )
  {
    var videoImage;
    for( index = 0; index < videoObjectListLength; index++ )
    {
      videoImage = this.objectList[index];
      videoImage.setDimensions( videoImage.getWidth(), videoImage.getHeight() );
      videoImage.setPosition( videoImage.getXPosition(), videoImage.getYPosition() );
    }
  }

  this.determineTopLeft();
};

VideoDisplay.prototype.clear = function()
{
  // Clear list of registered VideoObjects and null their links to
  // this display.
  var length = this.objectList.length;
  var index;
  for( index = 0; index < length; index++ )
  {
    this.objectList[index].setDisplay( null );
  }

  this.objectList = [];
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

/*VideoDisplay.prototype.drawRectangle = function( xPosition, yPosition, width, height )
{
  //this.context.fillStyle = this.foregroundColor;
  //this.context.fillRect( xPosition, yPosition, width, height );
};*/

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
  videoImage.setDisplay( this );
  this.addObject( videoImage );
};

VideoDisplay.prototype.removeVideoImage = function( videoImage )
{
  videoImage.setDisplay( null );
  this.removeObject( videoImage );
};

VideoDisplay.prototype.updateQuadTree = function()
{
  // Do nothing, visible canvas are already managed.
};

VideoDisplay.prototype.determineTopLeft = function()
{
  // TODO: Allow top left to be defined by a particular video image in the
  // videoObjectList.
  var videoImage;
  var length = this.objectList.length;
  if( length < 1 )
  {
    this.top  = 0;
    this.left = 0;
    return;
  }

  var index = 0;
  videoImage = this.objectList[index];
  this.top  = videoImage.getYPosition();
  this.left = videoImage.getXPosition();

  if( ++index >= length )
  {
    return;
  }

  var currentTop;
  var currentLeft;
  for( ; index < length; index++ )
  {
    videoImage  = this.objectList[index];
    
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

VideoDisplay.prototype.getNextEraseQueueObject = function()
{
  var numberOfEraseQueueObjects = ++this.numberOfEraseQueueObjects;

  var eraseQueueObject;
  var eraseQueueLength = this.eraseQueue.length;
  if( numberOfEraseQueueObjects < eraseQueueLength )
  {
    eraseQueueObject = this.eraseQueue[numberOfEraseQueueObjects - 1];
  }
  else
  {
    eraseQueueObject = new EraseQueueObject();
    this.eraseQueue[numberOfEraseQueueObjects - 1] = eraseQueueObject;
  }

  return eraseQueueObject;
};

VideoDisplay.prototype.processEraseQueue = function()
{
  var eraseQueueObject;
  var lastCanvas    = null;
  var currentCanvas = null;
  var context;
  var numberOfEraseQueueObjects = this.numberOfEraseQueueObjects;
  for( var index = 0; index < numberOfEraseQueueObjects; index++ )
  {
    eraseQueueObject = this.eraseQueue[index];
    currentCanvas = eraseQueueObject.targetVideoObject.getCanvas();
    if( currentCanvas != lastCanvas )
    {
      context = GetCanvasContext2D( currentCanvas );
      lastCanvas = currentCanvas;
    }

    context.clearRect( eraseQueueObject.xPosition,
                       eraseQueueObject.yPosition,
                       eraseQueueObject.width,
                       eraseQueueObject.height );
  }
  
  this.numberOfEraseQueueObjects = 0;
};

function EraseQueueObject()
{
  this.targetVideoObject;
  this.xPosition;
  this.yPosition;
  this.width;
  this.height;
};
