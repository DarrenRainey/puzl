function VideoObject()
{
  //console.log( "Creating VideoObject" );
  Object2d.call( this );

  this.targetVideoObject;

  this.dirtyRectangleList;
  this.needsRedraw;

  // Constructor.
  this.targetVideoObject = null;
  
  this.needsRedraw = false;
  this.dirtyRectangleList = new Array();

  this.tempDirtyRectangle = new Rectangle();
  this.rectanglePool = new Array();
};

extend( VideoObject, Object2d );

VideoObject.prototype.setDimensions = function( width, height )
{
  var thisTargetVideoObject = this.targetVideoObject;
  if( thisTargetVideoObject )
  {
    thisTargetVideoObject.addDirtyRectangle( this );
  }
  
  Object2d.prototype.setDimensions.call( this, width, height );
  
  //this.setNeedsRedraw( true, true );
  if( thisTargetVideoObject )
  {
    thisTargetVideoObject.addDirtyRectangle( this );
  }
};

VideoObject.prototype.setPosition = function( xPosition, yPosition )
{
  var thisTargetVideoObject = this.targetVideoObject;
  if( thisTargetVideoObject )
  {
    thisTargetVideoObject.addDirtyRectangle( this );
  }
  
  Object2d.prototype.setPosition.call( this, xPosition, yPosition );
  
  //this.setNeedsRedraw( true, false );
  if( thisTargetVideoObject )
  {
    thisTargetVideoObject.addDirtyRectangle( this );
  }
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

VideoObject.prototype.drawTo = function( targetVideoObject, rectangle )
{
  if( targetVideoObject !== null )
  {
    var rectangleStartPoint = rectangle.startPoint;
    var rectangleStartPointX = rectangleStartPoint.x;
    var rectangleStartPointY = rectangleStartPoint.y;
    var rectangleEndPoint = rectangle.endPoint;
    var rectangleEndPointX = rectangleEndPoint.x;
    var rectangleEndPointY = rectangleEndPoint.y;

    var rectangleWidth  = rectangleEndPointX - rectangleStartPointX + 1;
    var rectangleHeight = rectangleEndPointY - rectangleStartPointY + 1;
  
    // TODO: Needs to factor in scaled dimensions.
    DrawWithNearestScale( this, targetVideoObject,
                          rectangleStartPointX, rectangleStartPointY,
                          rectangleWidth, rectangleHeight,
                          rectangleStartPointX, rectangleStartPointY,
                          rectangleWidth, rectangleHeight );

    //this.needsRedraw = false;
  }
};

VideoObject.prototype.draw = function( rectangle )
{
  this.drawTo( this.targetVideoObject, rectangle );
};

VideoObject.prototype.drawUpdate = function()
{
  var thisDirtyRectangleList = this.dirtyRectangleList;
  var dirtyRectangleListLength = thisDirtyRectangleList.length;
  if( dirtyRectangleListLength > 0 )
  {
    var videoObject;
    var videoObjectListIndex;
    var dirtyRectangle;
    var dirtyRectangleListIndex;
    
    var tempDirtyRectangle = this.tempDirtyRectangle;

    dirtyRectangleListIndex = dirtyRectangleListLength - 1;
    do
    {
      dirtyRectangle = thisDirtyRectangleList[dirtyRectangleListIndex];
      if( this.isIntersecting( dirtyRectangle ) )
      {
        this.getIntersection( dirtyRectangle, tempDirtyRectangle );
        this.draw( tempDirtyRectangle );
      }
    }
    while( --dirtyRectangleListIndex > -1 );

    var thisObjectList = this.objectList;
    var videoObjectListLength = thisObjectList.length;
    for( videoObjectListIndex = 0; videoObjectListIndex < videoObjectListLength; videoObjectListIndex++ )
    {
      videoObject = thisObjectList[videoObjectListIndex];
      
      dirtyRectangleListIndex = dirtyRectangleListLength - 1;
      do
      {
        dirtyRectangle = thisDirtyRectangleList[dirtyRectangleListIndex];
        if( videoObject.isIntersecting( dirtyRectangle ) )
        {
          videoObject.getIntersection( dirtyRectangle, tempDirtyRectangle );
          videoObject.draw( tempDirtyRectangle );
        }
      }
      while( --dirtyRectangleListIndex > -1 );
    }

    // NOTE: Shambles of an attempt to use quad tree query over multiple linear traversals
    // of object list and intersection tests.
    /*var collisionList = new Array();
    this.quadTree.query( dirtyRectangle, collisionList );
    var videoObjectListLength = collisionList.length;
    if( videoObjectListLength > 0 )
    {
      for( videoObjectListIndex = 0; videoObjectListIndex < videoObjectListLength; videoObjectListIndex++ )
      {
        videoObject = collisionList[videoObjectListIndex];
        videoObject.needsRedraw = true;
      }

      videoObjectListLength = this.objectList.length;
      for( videoObjectListIndex = 0; videoObjectListIndex < videoObjectListLength; videoObjectListIndex++ )
      {
        videoObject = this.objectList[videoObjectListIndex];
        if( videoObject.needsRedraw )
        {
          videoObject.getIntersection( dirtyRectangle, tempDirtyRectangle );
          videoObject.draw( tempDirtyRectangle );
        }
      }
    }*/

    var thisRectanglePool = this.rectanglePool;
    dirtyRectangleListIndex = dirtyRectangleListLength - 1;
    do
    {
      thisRectanglePool.push( thisDirtyRectangleList[dirtyRectangleListIndex] );
    }
    while( --dirtyRectangleListIndex > -1 );
    
    thisDirtyRectangleList.length = 0;
  }
};

VideoObject.prototype.addDirtyRectangle = function( rectangle )
{
  var thisDirtyRectangleList = this.dirtyRectangleList;
  if( thisDirtyRectangleList )
  {
    var dirtyRectangle;
    
    var thisDirtyRectangleListLength = thisDirtyRectangleList.length;
    if( thisDirtyRectangleListLength > 0 )
    {
      var dirtyRectangleListIndex = thisDirtyRectangleListLength - 1;
      do
      {
        dirtyRectangle = thisDirtyRectangleList[dirtyRectangleListIndex];
        if( rectangle.isInside( dirtyRectangle ) )
        {
          // Exit without actually adding this rectangle.
          return;
        }
      }
      while( --dirtyRectangleListIndex > -1 );
    }

    var thisRectanglePool = this.rectanglePool;
    if( thisRectanglePool.length === 0 )
    {
      dirtyRectangle = new Rectangle( rectangle );
    }
    else
    {
      dirtyRectangle = thisRectanglePool.pop();
      dirtyRectangle.copy( rectangle );
    }
    
    this.dirtyRectangleList.push( dirtyRectangle );
  }
};
