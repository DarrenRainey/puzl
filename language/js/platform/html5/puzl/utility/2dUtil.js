// --------------------------------------------------------
/** @constructor */
function Vector2d()
{
  //this.x;
  //this.y;

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
/** @constructor */
function Rectangle()
{
  //this.startPoint;
  //this.endPoint;

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

// --------------------------------------------------------
areSameSigns = function( a, b )
{
  if( a > 0 && b < 0 )
  {
    return false;
  }

  if( a < 0 && b > 0 )
  {
    return false;
  }

  return true;
};

// --------------------------------------------------------
// Lifted from author Mukesh Prasad (xlines.c). Some custom modifications apply.
var DONT_INTERSECT = 0;
var DO_INTERSECT   = 1;
var COLLINEAR      = 2;
GetSegmentToSegmentIntersection = function( segment0Start, segment0End,
                                            segment1Start, segment1End,
                                            intersectionPoint )
{
  var x1 = segment0Start.x;
  var y1 = segment0Start.y;
  var x2 = segment0End.x;
  var y2 = segment0End.y;

  var x3 = segment1Start.x;
  var y3 = segment1Start.y;
  var x4 = segment1End.x;
  var y4 = segment1End.y;

  //a1, a2, b1, b2, c1, c2; // Coefficients of line equations.
  //r1, r2, r3, r4;         // 'Sign' values.

  // Compute a1, b1, c1, where line joining points 1 and 2
  // is "a1 x  +  b1 y  +  c1  =  0".
  var a1 = y2 - y1;
  var b1 = x1 - x2;
  var c1 = x2 * y1 - x1 * y2;

  // Compute r3 and r4.
  var r3 = a1 * x3 + b1 * y3 + c1;
  var r4 = a1 * x4 + b1 * y4 + c1;

  // Check signs of r3 and r4. If both point 3 and point 4 lie on
  // same side of line 1, the line segments do not intersect.
  if( r3 !== 0 &&
      r4 !== 0 &&
      areSameSigns( r3, r4 ) )
  {
    return DONT_INTERSECT;
  }
  
  // Compute a2, b2, c2.
  var a2 = y4 - y3;
  var b2 = x3 - x4;
  var c2 = x4 * y3 - x3 * y4;

  // Compute r1 and r2.
  var r1 = a2 * x1 + b2 * y1 + c2;
  var r2 = a2 * x2 + b2 * y2 + c2;

  // Check signs of r1 and r2.  If both point 1 and point 2 lie
  // on same side of second line segment, the line segments do
  // not intersect.
  if( r1 !== 0 &&
      r2 !== 0 &&
      areSameSigns( r1, r2 ) )
  {
    return DONT_INTERSECT;
  }

  // Line segments intersect: compute intersection point.
  denom = a1 * b2 - a2 * b1;
  if( denom === 0 )
  {
    return ( COLLINEAR );
  }
  
  offset = ( denom < 0 ) ? -denom / 2 : denom / 2;

  // The denom/2 is to get rounding instead of truncating.  It
  // is added or subtracted to the numerator, depending upon the
  // sign of the numerator.
  num = b1 * c2 - b2 * c1;
  intersectionPoint.x = ( num < 0 ? num - offset : num + offset ) / denom;

  num = a2 * c1 - a1 * c2;
  intersectionPoint.y = ( num < 0 ? num - offset : num + offset ) / denom;

  return DO_INTERSECT;
}
