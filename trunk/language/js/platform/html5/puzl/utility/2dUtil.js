// --------------------------------------------------------
function Vector2d()
{
  this.x;
  this.y;

  // Constructor.
  if( arguments.length === 1 )
  {
    var vector2d = arguments[0];
    this.x = vector2d.x;
    this.y = vector2d.y;
  }
  else
  if( arguments.length === 2 )
  {
    this.x = arguments[0];
    this.y = arguments[1];
  }
  else
  {
    this.x = 0;
    this.y = 0;
  }

  return this;
}

// --------------------------------------------------------
Vector2d.prototype.copy = function( vector2d )
{
  this.x = vector2d.x;
  this.y = vector2d.y;
};

// --------------------------------------------------------
Vector2d.prototype.isInside = function( rectangle )
{
  var thisX = this.x;
  var rectangleStartPoint = rectangle.startPoint;
  var rectangleStartPointX = rectangleStartPoint.x;
  if( thisX < rectangleStartPointX )
  {
    return false;
  }

  var thisY = this.y;
  var rectangleStartPointY = rectangleStartPoint.y;
  if( thisY < rectangleStartPointY )
  {
    return false;
  }
  
  var rectangleEndPoint = rectangle.endPoint;
  var rectangleEndPointX = rectangleEndPoint.x;
  if( thisX > rectangleEndPointX )
  {
    return false;
  }

  rectangleEndPointY = rectangleEndPoint.y;
  if( thisY > rectangleEndPointY )
  {
    return false;
  }
  
  return true;
};

// --------------------------------------------------------
function Rectangle()
{
  this.startPoint;
  this.endPoint;

  // Constructor.
  if( arguments.length === 1 )
  {
    // Rectangle.
    var rectangle = arguments[0];
    this.startPoint = new Vector2d( rectangle.startPoint );
    this.endPoint = new Vector2d( rectangle.endPoint );
  }
  else
  if( arguments.length === 2 )
  {
    // Two points.
    var startPoint = arguments[0];
    var endPoint   = arguments[1];
    this.startPoint = new Vector2d( startPoint.x, startPoint.y );
    this.endPoint   = new Vector2d( endPoint.x, endPoint.y );
  }
  else
  if( arguments.length === 4 )
  {
    // Two sets of point XYs.
    this.startPoint = new Vector2d( arguments[0], arguments[1] );
    this.endPoint   = new Vector2d( arguments[2], arguments[3] );
  }
  else
  {
    this.startPoint = new Vector2d();
    this.endPoint   = new Vector2d();
  }
}

// --------------------------------------------------------
Rectangle.prototype.copy = function( rectangle )
{
  this.startPoint.copy( rectangle.startPoint );
  this.endPoint.copy( rectangle.endPoint );
};

Rectangle.prototype.isInside = function( rectangle )
{
  var thisStartPoint = this.startPoint;
  var thisStartPointX = thisStartPoint.x;
  var rectangleStartPoint = rectangle.startPoint;
  var rectangleStartPointX = rectangleStartPoint.x;
  if( thisStartPointX < rectangleStartPointX )
  {
    return false;
  }

  var thisStartPointY = thisStartPoint.y;
  var rectanglePointY = rectangleStartPoint.y;
  if( thisStartPointY < rectanglePointY )
  {
    return false;
  }

  var thisEndPoint = this.endPoint;
  var thisEndPointX = thisEndPoint.x;
  var rectanglePoint = rectangle.endPoint;
  var rectangleEndPointX = rectanglePoint.x;
  if( thisEndPointX > rectangleEndPointX )
  {
    return false;
  }

  thisEndPointY = thisEndPoint.y;
  rectangleEndPointY = rectanglePoint.y;
  if( thisEndPointY > rectangleEndPointY )
  {
    return false;
  }

  return true;
};

Rectangle.prototype.isIntersecting = function( rectangle )
{
  // TODO: Optimize to favor collision vertically, as most displays
  // will be wider than they are tall.

  var thisStartPoint = this.startPoint;
  var thisStartPointX = thisStartPoint.x;
  var thisStartPointY = thisStartPoint.y;
  var thisEndPoint = this.endPoint;
  var thisEndPointX = thisEndPoint.x;
  var thisEndPointY = thisEndPoint.y;

  var rectangleStartPoint = rectangle.startPoint;
  var rectangleStartPointX = rectangleStartPoint.x;
  var rectangleStartPointY = rectangleStartPoint.y;
  var rectangleEndPoint = rectangle.endPoint;
  var rectangleEndPointX = rectangleEndPoint.x;
  var rectangleEndPointY = rectangleEndPoint.y;
  
  return !( rectangleStartPointX > thisEndPointX ||
            rectangleEndPointX < thisStartPointX ||
            rectangleStartPointY > thisEndPointY ||
            rectangleEndPointY < thisStartPointY );
};

Rectangle.prototype.getIntersection = function( rectangle, intersectionRectangle )
{
  var thisStartPoint = this.startPoint;
  var thisStartPointX = thisStartPoint.x;
  var thisStartPointY = thisStartPoint.y;
  var thisEndPoint = this.endPoint;
  var thisEndPointX = thisEndPoint.x;
  var thisEndPointY = thisEndPoint.y;

  var rectangleStartPoint = rectangle.startPoint;
  var rectangleStartPointX = rectangleStartPoint.x;
  var rectangleStartPointY = rectangleStartPoint.y;
  var rectangleEndPoint = rectangle.endPoint;
  var rectangleEndPointX = rectangleEndPoint.x;
  var rectangleEndPointY = rectangleEndPoint.y;
  
  intersectionRectangle.startPoint.x =
    ( thisStartPointX > rectangleStartPointX ) ? thisStartPointX : rectangleStartPointX;

  intersectionRectangle.startPoint.y =
    ( thisStartPointY > rectangleStartPointY ) ? thisStartPointY : rectangleStartPointY;

  intersectionRectangle.endPoint.x =
    ( thisEndPointX < rectangleEndPointX ) ? thisEndPointX : rectangleEndPointX;

  intersectionRectangle.endPoint.y =
    ( thisEndPointY < rectangleEndPointY ) ? thisEndPointY : rectangleEndPointY;
};
