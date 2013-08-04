function VideoObject()
{
  var object2d = new Object2d();
  
  object2d.needsRedraw;

  object2d.eraseQueue;
  object2d.numberOfEraseQueueObjects;

  object2d.constructor = this.constructor;
  
  object2d.baseObject2dSetDimensions = object2d.setDimensions;
  object2d.setDimensions             = this.setDimensions;
  object2d.baseObject2dSetPosition   = object2d.setPosition;
  object2d.setPosition               = this.setPosition;
  
  object2d.getNextEraseQueueObject = this.getNextEraseQueueObject;
  object2d.processEraseQueue       = this.processEraseQueue;
  
  object2d.getCanvas = this.getCanvas;

  //object2d.getDisplay = this.getDisplay;

  object2d.setNeedsRedraw = this.setNeedsRedraw;
  
  object2d.drawUpdate = this.drawUpdate;

  object2d.constructor();
  return object2d;
};

VideoObject.prototype.constructor = function()
{
  this.needsRedraw = false;

  this.eraseQueue = new Array();
  this.numberOfEraseQueueObjects = 0;
};

VideoObject.prototype.setDimensions = function( width, height )
{
  this.baseObject2dSetDimensions( width, height );
  this.setNeedsRedraw( true, true );
};

VideoObject.prototype.setPosition = function( xPosition, yPosition )
{
  this.baseObject2dSetPosition( xPosition, yPosition );
  this.setNeedsRedraw( true, false );
};

VideoObject.prototype.getCanvas = function()
{
  return null;
};

/*VideoObject.prototype.getDisplay = function()
{
  if( GlobalDisplay === undefined )
  {
    return null;
  }
  
  return GlobalDisplay; // TODO: Do this better?
};

VideoObject.prototype.setDisplay = function( display )
{
  return; // TODO: Do nothing for now?
};*/

VideoObject.prototype.setNeedsRedraw = function( needsRedraw, propagate )
{
  this.needsRedraw = needsRedraw;

  // Always back propagate, if necessary.
  var parentObject = this.getParentObject();
  if( parentObject !== null )
  {
    if( !parentObject.needsRedraw )
    {
      parentObject.setNeedsRedraw( true, false );
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
    this.setNeedsRedraw( false, false );
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
  var eraseQueueObject;
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
