function VideoObject()
{
  //console.log( "Creating VideoObject" );
  Object2d.call( this );

  this.targetVideoObject;

  this.eraseQueue;
  this.numberOfEraseQueueObjects;
  this.needsRedraw;

  // Constructor.
  this.targetVideoObject = null;
  
  this.eraseQueue = new Array();
  this.numberOfEraseQueueObjects = this.eraseQueue.length;
  this.needsRedraw = false;
};

extend( VideoObject, Object2d );

VideoObject.prototype.setDimensions = function( width, height )
{
  Object2d.prototype.setDimensions.call( this, width, height );
  this.setNeedsRedraw( true, true );
};

VideoObject.prototype.setPosition = function( xPosition, yPosition )
{
  Object2d.prototype.setPosition.call( this, xPosition, yPosition );
  this.setNeedsRedraw( true, false );
};

VideoObject.prototype.addObject = function( videoObject )
{
  Object2d.prototype.addObject.call( this, videoObject );

  if( videoObject.targetVideoObject === null )
  {
    videoObject.targetVideoObject = this;
  }
};

VideoObject.prototype.getCanvas = function()
{
  return null;
};

VideoObject.prototype.setNeedsRedraw = function( needsRedraw, propagate )
{
  this.needsRedraw = needsRedraw;

  // Always back propagate, if necessary.
  var targetVideoObject = this.targetVideoObject;
  if( targetVideoObject !== undefined && targetVideoObject !== null ) // TODO: See if there is a way to simplify this check.
  {
    if( !targetVideoObject.needsRedraw )
    {
      targetVideoObject.setNeedsRedraw( true, false );
    }
  }
  
  // Forward propagate, if wanted.
  if( propagate )
  {
    var videoObjectListLength = this.objectList.length;
    if( videoObjectListLength > 0 )
    {
      var videoObject;
      for( var index = 0; index < videoObjectListLength; index++ )
      {
        this.objectList[index].setNeedsRedraw( needsRedraw, propagate );
      }
    }
  }
};

VideoObject.prototype.drawUpdate = function()
{
  if( this.numberOfEraseQueueObjects > 0 )
  {
    this.processEraseQueue();
  }

  if( this.draw !== undefined )
  {
    this.draw();
    //this.setNeedsRedraw( false, false );
  }
  
  var videoObjectListLength = this.objectList.length;
  if( videoObjectListLength > 0 )
  {
    var videoObject;
    for( var index = 0; index < videoObjectListLength; index++ )
    {
      videoObject = this.objectList[index];
      if( videoObject.needsRedraw )
      {
        videoObject.drawUpdate();
      }
    }
  }
};

VideoObject.prototype.getNextEraseQueueObject = function()
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

VideoObject.prototype.processEraseQueue = function()
{
  /*var eraseQueueObject;
  var lastCanvas    = null;
  var currentCanvas = null;
  var context;
  var targetVideoObject;
  var numberOfEraseQueueObjects = this.numberOfEraseQueueObjects;
  for( var index = 0; index < numberOfEraseQueueObjects; index++ )
  {
    eraseQueueObject = this.eraseQueue[index];
    targetVideoObject = eraseQueueObject.targetVideoObject;
    currentCanvas = targetVideoObject.getCanvas();
    if( currentCanvas != lastCanvas )
    {
      context = GetCanvasContext2D( currentCanvas );
      lastCanvas = currentCanvas;
    }
    
    context.fillStyle = targetVideoObject.backgroundColor;
    context.fillRect( eraseQueueObject.xPosition,
                       eraseQueueObject.yPosition,
                       eraseQueueObject.width,
                       eraseQueueObject.height );
  }
  */
  this.numberOfEraseQueueObjects = 0;
};

// NOTE: This function is likely going away with dirty rectangles, as nothing will simply
// erase.
VideoObject.prototype.erase = function()
{
  var targetVideoObject = this.targetVideoObject;
  if( targetVideoObject === null )
  {
    return;
  }

  var canvas = targetVideoObject.getCanvas();
  var context = GetCanvasContext2D( canvas );

  context.clearRect( this.position.x, this.position.y,
                     this.width, this.height );
};

VideoObject.prototype.queueErase = function()
{
  var targetVideoObject = this.targetVideoObject;
  if( targetVideoObject === null )
  {
    return;
  }

  var eraseQueueObject = targetVideoObject.getNextEraseQueueObject();
  if( eraseQueueObject === undefined )
  {
    return;
  }

  eraseQueueObject.targetVideoObject = targetVideoObject;

  eraseQueueObject.xPosition = this.position.x;
  eraseQueueObject.yPosition = this.position.y;
  eraseQueueObject.width     = this.width;
  eraseQueueObject.height    = this.height;
};

function EraseQueueObject()
{
  this.targetVideoObject;
  this.xPosition;
  this.yPosition;
  this.width;
  this.height;
};
