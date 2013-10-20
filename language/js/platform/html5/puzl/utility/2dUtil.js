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
Vector2d.prototype.equals = function( vector2d )
{
  return this.x === vector2d.x &&
         this.y === vector2d.y;
};

// --------------------------------------------------------
Vector2d.prototype.copy = function( vector2d )
{
  this.x = vector2d.x;
  this.y = vector2d.y;
};

// --------------------------------------------------------
Vector2d.prototype.add = function( vector2d )
{
  this.x += vector2d.x;
  this.y += vector2d.y;
};

// --------------------------------------------------------
Vector2d.prototype.subtract = function( vector2d )
{
  this.x -= vector2d.x;
  this.y -= vector2d.y;
};

// --------------------------------------------------------
Vector2d.prototype.multiply = function( vector2d )
{
  this.x *= vector2d.x;
  this.y *= vector2d.y;
};

// --------------------------------------------------------
Vector2d.prototype.divide = function( vector2d )
{
  var vector2dX = vector2d.x;
  var vector2dY = vector2d.y;
  if( ( vector2dX === 0 ) || ( vector2dY === 0 ) )
  {
    console.error( "Divide by 0." );
    return;
  }
  
  this.x /= vector2dX;
  this.y /= vector2dY;
};

// --------------------------------------------------------
Vector2d.prototype.toString = function()
{
  var string = "(";
  string += this.x;
  string += ",";
  string += this.y;
  string += ")";

  return string;
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

  var rectangleEndPointY = rectangleEndPoint.y;
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
Rectangle.prototype.equals = function( rectangle )
{
  return this.startPoint.equals( rectangle.startPoint ) &&
         this.endPoint.equals( rectangle.endPoint );
};

// --------------------------------------------------------
Rectangle.prototype.copy = function( rectangle )
{
  this.startPoint.copy( rectangle.startPoint );
  this.endPoint.copy( rectangle.endPoint );
};

// --------------------------------------------------------
Rectangle.prototype.toString = function()
{
  var string = "[";
  string += this.startPoint.toString();
  string += ",";
  string += this.endPoint.toString();
  string += "]";

  return string;
};

Rectangle.prototype.setPosition = function( xPosition, yPosition )
{
  var thisStartPoint = this.startPoint;
  var thisEndPoint = this.endPoint;

  var widthMinusOne = thisEndPoint.x - thisStartPoint.x;
  var heightMinusOne = thisEndPoint.y - thisStartPoint.y;

  thisStartPoint.x = xPosition;
  thisStartPoint.y = yPosition;

  thisEndPoint.x = xPosition + widthMinusOne;
  thisEndPoint.y = yPosition + heightMinusOne;
};

Rectangle.prototype.getXPosition = function()
{
  return this.startPoint.x;
};

Rectangle.prototype.getYPosition = function()
{
  return this.startPoint.y;
};

Rectangle.prototype.setDimensions = function( width, height )
{
  var thisStartPoint = this.startPoint;
  var thisEndPoint = this.endPoint;
  thisEndPoint.x = thisStartPoint.x + width - 1;
  thisEndPoint.y = thisStartPoint.y + height - 1;
};

Rectangle.prototype.getWidth = function()
{
  return this.endPoint.x - this.startPoint.x + 1;
};

Rectangle.prototype.getHeight = function()
{
  return this.endPoint.y - this.startPoint.y + 1;
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

  var thisEndPointY = thisEndPoint.y;
  var rectangleEndPointY = rectanglePoint.y;
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

Rectangle.prototype.getIntersection = function( rectangle, resultRectangle )
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
  
  resultRectangle.startPoint.x =
    ( thisStartPointX > rectangleStartPointX ) ? thisStartPointX : rectangleStartPointX;

  resultRectangle.startPoint.y =
    ( thisStartPointY > rectangleStartPointY ) ? thisStartPointY : rectangleStartPointY;

  resultRectangle.endPoint.x =
    ( thisEndPointX < rectangleEndPointX ) ? thisEndPointX : rectangleEndPointX;

  resultRectangle.endPoint.y =
    ( thisEndPointY < rectangleEndPointY ) ? thisEndPointY : rectangleEndPointY;
};

Rectangle.prototype.getConvexHull = function( rectangle, resultRectangle )
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

  resultRectangle.startPoint.x =
    ( thisStartPointX < rectangleStartPointX ) ? thisStartPointX : rectangleStartPointX;

  resultRectangle.startPoint.y =
    ( thisStartPointY < rectangleStartPointY ) ? thisStartPointY : rectangleStartPointY;

  resultRectangle.endPoint.x =
    ( thisEndPointX > rectangleEndPointX ) ? thisEndPointX : rectangleEndPointX;

  resultRectangle.endPoint.y =
    ( thisEndPointY > rectangleEndPointY ) ? thisEndPointY : rectangleEndPointY;
};
