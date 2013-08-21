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
Vector2d.prototype.isInside = function( rectangle )
{
  var rectanglePoint = rectangle.startPoint;
  if( this.x < rectanglePoint.x )
  {
    return false;
  }

  if( this.y < rectanglePoint.y )
  {
    return false;
  }
  
  rectanglePoint = rectangle.endPoint;
  if( this.x > rectanglePoint.x )
  {
    return false;
  }

  if( this.y > rectanglePoint.y )
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

Rectangle.prototype.isInside = function( rectangle )
{
  if( this.startPoint.isInside( rectangle ) &&
      this.endPoint.isInside( rectangle ) )
  {
    return true;
  }

  return false;
};

Rectangle.prototype.isIntersecting = function( rectangle )
{
  // TODO: Optimize to favor collision vertically, as most displays
  // will be wider than they are tall.
  return !( rectangle.startPoint.x > this.endPoint.x ||
            rectangle.endPoint.x < this.startPoint.x ||
            rectangle.startPoint.y > this.endPoint.y ||
            rectangle.endPoint.y < this.startPoint.y );
};

Rectangle.prototype.getIntersection = function( rectangle, intersectionRectangle )
{
  intersectionRectangle.startPoint.x =
    ( this.startPoint.x > rectangle.startPoint.x ) ? this.startPoint.x : rectangle.startPoint.x;

  intersectionRectangle.startPoint.y =
    ( this.startPoint.y > rectangle.startPoint.y ) ? this.startPoint.y : rectangle.startPoint.y;

  intersectionRectangle.endPoint.x =
    ( this.endPoint.x < rectangle.endPoint.x ) ? this.endPoint.x : rectangle.endPoint.x;

  intersectionRectangle.endPoint.y =
    ( this.endPoint.y < rectangle.endPoint.y ) ? this.endPoint.y : rectangle.endPoint.y;
};
