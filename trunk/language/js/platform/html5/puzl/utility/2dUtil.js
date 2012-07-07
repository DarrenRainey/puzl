function Point( argument0, argument1 )
{
  if( arguments.length == 1 )
  {
    var point = argument0;
    this.x = point.x;
    this.y = point.y;
  }
  else
  if( arguments.length == 2 )
  {
    this.x = argument0;
    this.y = argument1;
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

function Rectangle( argument0, argument1, argument2, argument3 )
{
  this.pointList = new Array();

  if( arguments.length == 1 )
  {
    this.pointList[0] = new Point( argument0.pointList[0] );
    this.pointList[1] = new Point( argument0.pointList[1] );
  }
  else
  if( arguments.length == 2 )
  {
    this.pointList[0] = new Point( argument0.x, argument0.y );
    this.pointList[1] = new Point( argument1.x, argument1.y );
  }
  else
  {
    this.pointList[0] = new Point();
    this.pointList[1] = new Point();
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
