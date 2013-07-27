function Point()
{
  if( arguments.length === 1 )
  {
    var point = arguments[0];
    this.x = point.x;
    this.y = point.y;
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

Point.prototype.isInsideRectangle = function( rectangle )
{
  var pointList = this.rectangle.pointList;
  
  var rectanglePoint = pointList[0];
  if( this.x < rectanglePoint.x )
  {
    return false;
  }

  if( this.y < rectanglePoint.y )
  {
    return false;
  }
  
  rectanglePoint = pointList[1];
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

function Rectangle()
{
  this.pointList = new Array();

  if( arguments.length === 1 )
  {
    // Rectangle.
    var rectangle = arguments[0];
    this.pointList.push( new Point( rectangle.pointList[0] ) );
    this.pointList.push( new Point( rectangle.pointList[1] ) );
  }
  else
  if( arguments.length === 2 )
  {
    // Two points.
    var point0 = arguments[0];
    var point1 = arguments[1];
    this.pointList.push( new Point( point0.x, point0.y ) );
    this.pointList.push( new Point( point1.x, point1.y ) );
  }
  else
  if( arguments.length === 4 )
  {
    this.pointList.push( new Point( arguments[0], arguments[1] ) );
    this.pointList.push( new Point( arguments[2], arguments[3] ) );
  }
  else
  {
    this.pointList.push( new Point() );
    this.pointList.push( new Point() );
  }

  return this;
}

Rectangle.prototype.isInsideRectangle = function( rectangle )
{
  if( this.pointList[0].isInsideRectangle( rectangle ) &&
      this.pointList[1].isInsideRectangle( rectangle ) )
  {
    return true;
  }

  return false;
};

Rectangle.prototype.isRectangleColliding = function( rectangle )
{
  var thisRectangle = this.rectangle;
  var r1PointList   = thisRectangle.pointList;
  var r1EndPoint    = r1PointList[1];

  var r2PointList   = rectangle.pointList;
  var r2StartPoint  = r2PointList[0];
  
  if( !( r2StartPoint.x > r1EndPoint.x ||
         r2StartPoint.y > r1EndPoint.y ) )
  {
    return true;
  }
  
  var r1StartPoint  = r1PointList[0];
  var r2EndPoint    = r2PointList[1];

  return !( r2EndPoint.x < r1StartPoint.x ||
            r2EndPoint.y < r1StartPoint.y );
};
