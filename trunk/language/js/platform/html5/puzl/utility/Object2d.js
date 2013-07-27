function Object2d()
{
  this.rectangle;
  this.position;
  this.width;
  this.height;
  
  this.parentObject;

  this.objectList;

  this.quadTree;
  this.quadTreeNode;

  this.constructor();
  return this;
};

Object2d.prototype.constructor = function()
{
  this.rectangle  = new Rectangle();
  this.objectList = new Array();
  this.quadTree   = new QuadTree();
  
  this.position  = this.rectangle.pointList[0];
  
  //this.setPosition( 0, 0 );
  this.setDimensions( 1, 1 );

  this.parentObject = null;
  this.needsRedraw  = false;
  
  this.quadTree.setObject2d( this );
  
  this.quadTreeNode = null;
};

Object2d.prototype.getXPosition = function()
{
  return this.position.x;
};

Object2d.prototype.getYPosition = function()
{
  return this.position.y;
};

Object2d.prototype.setXPosition = function( xPosition )
{
  var point = this.position;
  point.x   = xPosition;

  point     = this.rectangle.pointList[1];
  point.x   = xPosition + this.width  - 1;

  this.updateQuadTree();
};

Object2d.prototype.setYPosition = function( yPosition )
{
  var point = this.position;
  point.y   = yPosition;

  point     = this.rectangle.pointList[1];
  point.y   = yPosition + this.height - 1;

  this.updateQuadTree();
};

Object2d.prototype.setPosition = function( xPosition, yPosition )
{
  var point = this.position;
  point.x   = xPosition;
  point.y   = yPosition;

  point     = this.rectangle.pointList[1];
  point.x   = xPosition + this.width  - 1;
  point.y   = yPosition + this.height - 1;

  this.updateQuadTree();
};

Object2d.prototype.getWidth = function()
{
  return this.width;
};

Object2d.prototype.getHeight = function()
{
  return this.height;
};

Object2d.prototype.setDimensions = function( width, height )
{
  this.width  = width;
  this.height = height;

  var point = this.rectangle.pointList[1];
  //var position = this.position;
  //point.x      = position.x + this.width  - 1;
  //point.y      = position.y + this.height - 1;
  point.x  += this.width  - width;
  point.y  += this.height - height;

  if( this.quadTree != null )
  {
    this.quadTree.updateRectangle();
  }

  this.updateQuadTree();
};

Object2d.prototype.addObject = function( object )
{
  //console.log( object.name );
  // TODO: Make sure object2d is not already in the list.
  if( this == object )
  {
    return;
  }

  if( object == null )
  {
    return;
  }

  var objectParentObject = object.parentObject;
  if( objectParentObject != null )
  {
    objectParentObject.removeObject( object );
  }
  
  object.parentObject = this;
  this.objectList[this.objectList.length] = object;

  // NOTE: Should this update the quad tree?
  //this.quadTree.insert( object );
};

Object2d.prototype.removeObject = function( object )
{
  var length = this.objectList.length;
  var index;
  for( index = 0; index < length; index++ )
  {
    if( object == this.objectList[index] )
    {
      object.parentObject = null;
      this.objectList.splice( index, 1 );
      return;
    }
  }

  // NOTE: Should this update the quad tree?
};

Object2d.prototype.setQuadTreeNode = function( quadTreeNode )
{
  this.quadTreeNode = quadTreeNode;
};

Object2d.prototype.updateQuadTree = function()
{
  var parentObject = this.parentObject;
  if( ( parentObject != null ) &&
      ( parentObject.quadTree != null ) )
  {
    parentObject.quadTree.insert( this );
  }
};

Object2d.prototype.isInsideRectangle = function( rectangle )
{
  return this.rectangle.isInsideRectangle( rectangle );
};

Object2d.prototype.isBoxColliding = function( otherObject )
{
  return this.rectangle.isRectangleColliding( otherObject.rectangle );
};
