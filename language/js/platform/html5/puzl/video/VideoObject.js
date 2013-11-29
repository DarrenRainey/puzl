function VideoObject()
{
  //console.log( "Creating VideoObject" );
  Object2d.call( this );

  this.targetVideoObject;

  this.orderId;

  this.dirtyRectangleList;

  // Constructor.
  this.targetVideoObject = null;
  this.orderId = -1;
  
  this.dirtyRectangleList = new Array();

  this.tempDirtyRectangle = new Rectangle();
  
  this.rectanglePool = new Array();
}

extend( VideoObject, Object2d );

VideoObject.prototype.setDimensions = function( width, height )
{
  var thisTargetVideoObject = this.targetVideoObject;
  if( thisTargetVideoObject )
  {
    thisTargetVideoObject.addDirtyRectangle( this );
  }
  
  Object2d.prototype.setDimensions.call( this, width, height );

  if( this.context !== undefined )
  {
    this.context = GetCanvasContext2D( this.canvas );
  }
  
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
  
  if( thisTargetVideoObject )
  {
    thisTargetVideoObject.addDirtyRectangle( this );
  }
};

VideoObject.prototype.setXPosition = function( xPosition )
{
  var thisTargetVideoObject = this.targetVideoObject;
  if( thisTargetVideoObject )
  {
    thisTargetVideoObject.addDirtyRectangle( this );
  }
  
  Object2d.prototype.setXPosition.call( this, xPosition );
  
  if( thisTargetVideoObject )
  {
    thisTargetVideoObject.addDirtyRectangle( this );
  }
};

VideoObject.prototype.setYPosition = function( yPosition )
{
  var thisTargetVideoObject = this.targetVideoObject;
  if( thisTargetVideoObject )
  {
    thisTargetVideoObject.addDirtyRectangle( this );
  }
  
  Object2d.prototype.setYPosition.call( this, yPosition );
  
  if( thisTargetVideoObject )
  {
    thisTargetVideoObject.addDirtyRectangle( this );
  }
};

VideoObject.prototype.addObject = function( videoObject )
{
  Object2d.prototype.addObject.call( this, videoObject );

  videoObject.orderId = this.objectList.length - 1;

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
    targetVideoObject.context.drawImage( this.canvas,
                                         rectangleStartPointX, rectangleStartPointY,
                                         rectangleWidth, rectangleHeight,
                                         rectangleStartPointX, rectangleStartPointY,
                                         rectangleWidth, rectangleHeight );
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

    var objectList;
    var videoObjectListLength;

    var thisQuadTree = this.quadTree;

    var thisRectanglePool = this.rectanglePool;

    dirtyRectangleListIndex = dirtyRectangleListLength - 1;
    do
    {
      dirtyRectangle = thisDirtyRectangleList[dirtyRectangleListIndex];
      if( this.isIntersecting( dirtyRectangle ) )
      {
        this.getIntersection( dirtyRectangle, tempDirtyRectangle );
        this.draw( tempDirtyRectangle );
      }

      //var sortString;

      // Use quad tree query instead of traversing over all video objects.
      objectList = thisQuadTree.query( dirtyRectangle );
      //objectList = this.objectList;

      //console.log( objectList );

      //sortString = "";
    
      videoObjectListLength = objectList.length;
      if( videoObjectListLength > 0 )
      {
        objectList.sort( this.sortByOrderId );

        for( videoObjectListIndex = 0; videoObjectListIndex < videoObjectListLength; videoObjectListIndex++ )
        {
          videoObject = objectList[videoObjectListIndex];

          //sortString += videoObject.orderId;
          //sortString += " ";

          videoObject.getIntersection( dirtyRectangle, tempDirtyRectangle );
          videoObject.draw( tempDirtyRectangle );
        }
      }

      //console.log( sortString );

      thisRectanglePool.push( dirtyRectangle );
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
      // Check if any existing dirty rectangles already include the same space
      // as the newly submitted one.
      var dirtyRectangleListIndex = thisDirtyRectangleListLength - 1;
      do
      {
        // TODO: Possible to optimize this loop if calls to isInside and isIntersecting
        // are not made, but instead all logic presides here (less recalculating of same values).
        dirtyRectangle = thisDirtyRectangleList[dirtyRectangleListIndex];
        if( rectangle.isInside( dirtyRectangle ) )
        {
          // Exit without actually adding this rectangle.
          return;
        }
        else
        if( rectangle.isIntersecting( dirtyRectangle ) )
        {
          rectangle.getConvexHull( dirtyRectangle, dirtyRectangle );
          return;
        }
        
        // TODO: Also see if rectangles are colinear vertically or horizontally.
      }
      while( --dirtyRectangleListIndex > -1 );

      // TODO: Perhaps it would be good to call this block of code,
      // if the rectangles are within a certain threshold, such as distance from each other or
      // difference in area between convex hull and sum of individual rectangles.
      /*// Convert existing dirty rectangle(s) to be convex hull
      // between it and the newly submitted one.
      var dirtyRectangleListIndex = thisDirtyRectangleListLength - 1;
      do
      {
        dirtyRectangle = thisDirtyRectangleList[dirtyRectangleListIndex];
        rectangle.getConvexHull( dirtyRectangle, dirtyRectangle );
      }
      while( --dirtyRectangleListIndex > -1 );

      return;*/
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
    
    thisDirtyRectangleList.push( dirtyRectangle );
  }
};

VideoObject.prototype.sortByOrderId = function( videoObject1, videoObject2 )
{
  return videoObject1.orderId - videoObject2.orderId;
};
