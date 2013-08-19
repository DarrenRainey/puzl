function Object2d()
{
  //console.log( "Creating Object2d" );
  Rectangle.call( this );
  this._width;
  this._height;
  
  this.parentObject;

  this.objectList;

  this.quadTree; // This Object2d's quad tree root.
  this.quadTreeNode; // The quad tree node this object is contained in?
                     // Used for quick reference of currently contained node.

  // Constructor.
  this.objectList = new Array();

  this.quadTreeNode = null;
  this.quadTree = new QuadTree();

  this.parentObject = null;
  this.setDimensions( 1, 1 );

  //this.quadTree.setObject2d( this );
  this.quadTreeNode = null;
};

extend( Object2d, Rectangle );

Object2d.prototype.getXPosition = function()
{
  return this.startPoint.x;
};

Object2d.prototype.getYPosition = function()
{
  return this.startPoint.y;
};

Object2d.prototype.setXPosition = function( xPosition )
{
  this.startPoint.x = xPosition;
  this.endPoint.x   = xPosition + this._width - 1;

  this.updateQuadTree();
};

Object2d.prototype.setYPosition = function( yPosition )
{
  this.startPoint.y = yPosition;
  this.endPoint.y   = yPosition + this._height - 1;

  this.updateQuadTree();
};

Object2d.prototype.setPosition = function( xPosition, yPosition )
{
  this.startPoint.x = xPosition;
  this.endPoint.x   = xPosition + this._width - 1;

  this.startPoint.y = yPosition;
  this.endPoint.y   = yPosition + this._height - 1;

  this.updateQuadTree();
};

Object2d.prototype.getWidth = function()
{
  return this._width;
};

Object2d.prototype.getHeight = function()
{
  return this._height;
};

Object2d.prototype.setDimensions = function( width, height )
{
  this._width  = width;
  this._height = height;

  this.endPoint.x = this.startPoint.x + width  - 1;
  this.endPoint.y = this.startPoint.y + height - 1;

  if( this.quadTree != null )
  {
    console.log( "Object2d::setDimensions, ( this.quadTree != null ), " + width + ":" + height );
    this.quadTree.setRectangle( 0, 0, width - 1, height - 1 );
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

  this.quadTree.insert( object );
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

Object2d.prototype.clearObjects = function()
{
  var length = this.objectList.length;
  var index;
  for( index = 0; index < length; index++ )
  {
    this.objectList[index].parentObject = null;
  }

  this.objectList = []; // NOTE: Bad. Should clear currently allocated Array object.

  // NOTE: Should this update the quad tree?
};

/*Object2d.prototype.setQuadTreeNode = function( quadTreeNode )
{
  this.quadTreeNode = quadTreeNode;
};*/

Object2d.prototype.updateQuadTree = function()
{
  //console.log( "Object2d::updateQuadTree" );
  /*var parentObject = this.parentObject;
  if( ( parentObject != null ) &&
      ( parentObject.quadTree != null ) )
  {
    parentObject.quadTree.insert( this );
  }*/
};
