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
};

extend( VideoObject, Object2d );

VideoObject.prototype.setDimensions = function( width, height )
{
  this.addDirtyRectangle();
  
  Object2d.prototype.setDimensions.call( this, width, height );
  
  //this.setNeedsRedraw( true, true );
  this.addDirtyRectangle();
};

VideoObject.prototype.setPosition = function( xPosition, yPosition )
{
  this.addDirtyRectangle();
  
  Object2d.prototype.setPosition.call( this, xPosition, yPosition );
  
  //this.setNeedsRedraw( true, false );
  this.addDirtyRectangle();
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
    // TODO: Needs to factor in scaled dimensions.
    DrawWithNearestScale( this, targetVideoObject,
                          rectangle.startPoint.x, rectangle.startPoint.y,
                          rectangle.endPoint.x - rectangle.startPoint.x + 1,
                          rectangle.endPoint.y - rectangle.startPoint.y + 1,
                          rectangle.startPoint.x, rectangle.startPoint.y,
                          rectangle.endPoint.x - rectangle.startPoint.x + 1,
                          rectangle.endPoint.y - rectangle.startPoint.y + 1 );

    //this.needsRedraw = false;
  }
};

VideoObject.prototype.draw = function( rectangle )
{
  this.drawTo( this.targetVideoObject, rectangle );
};

VideoObject.prototype.drawUpdate = function()
{
  var dirtyRectangleListLength = this.dirtyRectangleList.length;
  if( dirtyRectangleListLength > 0 )
  {
    var videoObject;
    var videoObjectListIndex;
    var dirtyRectangle;
    var dirtyRectangleListIndex;
    
    var tempDirtyRectangle = new Rectangle();

    for( dirtyRectangleListIndex = 0; dirtyRectangleListIndex < dirtyRectangleListLength; dirtyRectangleListIndex++ )
    {
      dirtyRectangle = this.dirtyRectangleList[dirtyRectangleListIndex];
      if( this.isIntersecting( dirtyRectangle ) )
      {
        this.getIntersection( dirtyRectangle, tempDirtyRectangle );
        this.draw( tempDirtyRectangle );
      }
    }

    var videoObjectListLength = this.objectList.length;
    for( videoObjectListIndex = 0; videoObjectListIndex < videoObjectListLength; videoObjectListIndex++ )
    {
      videoObject = this.objectList[videoObjectListIndex];
      for( dirtyRectangleListIndex = 0; dirtyRectangleListIndex < dirtyRectangleListLength; dirtyRectangleListIndex++ )
      {
        dirtyRectangle = this.dirtyRectangleList[dirtyRectangleListIndex];
        if( videoObject.isIntersecting( dirtyRectangle ) )
        {
          videoObject.getIntersection( dirtyRectangle, tempDirtyRectangle );
          videoObject.draw( tempDirtyRectangle );
        }
      }
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

    this.dirtyRectangleList.length = 0;
  }
};

VideoObject.prototype.addDirtyRectangle = function( rectangle )
{
  if( rectangle === undefined )
  {
    if( this.targetVideoObject != null )
    {
      this.targetVideoObject.addDirtyRectangle( this );
    }
    else
    {
      this.addDirtyRectangle( this );
    }
  }
  else
  {
    if( this.dirtyRectangleList )
    {
      this.dirtyRectangleList.push( new Rectangle( rectangle ) );
    }
  }
};
