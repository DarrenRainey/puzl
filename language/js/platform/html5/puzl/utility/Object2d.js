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
  Object2d.prototype.setDimensions.call( this, 1, 1 );

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

  this.insertIntoParentQuadTree();
};

Object2d.prototype.setYPosition = function( yPosition )
{
  this.startPoint.y = yPosition;
  this.endPoint.y   = yPosition + this._height - 1;

  this.insertIntoParentQuadTree();
};

Object2d.prototype.setPosition = function( xPosition, yPosition )
{
  var thisStartPoint = this.startPoint;
  var thisEndPoint = this.endPoint;
  
  thisStartPoint.x = xPosition;
  thisEndPoint.x   = xPosition + this._width - 1;

  thisStartPoint.y = yPosition;
  thisEndPoint.y   = yPosition + this._height - 1;

  this.insertIntoParentQuadTree();
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

  var thisStartPoint = this.startPoint;
  var thisEndPoint = this.endPoint;
  thisEndPoint.x = thisStartPoint.x + width  - 1;
  thisEndPoint.y = thisStartPoint.y + height - 1;

  if( this.quadTree !== null )
  {
    //console.log( "Object2d::setDimensions, ( this.quadTree != null ), " + width + ":" + height );
    this.quadTree.setRectangle( 0, 0, width - 1, height - 1 );
  }

  this.insertIntoParentQuadTree();
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
  if( objectParentObject !== null )
  {
    objectParentObject.removeObject( object );
  }
  
  object.parentObject = this;
  this.objectList.push( object );

  this.quadTree.insert( object );
};

Object2d.prototype.removeObject = function( object )
{
  var thisObjectList = this.objectList;
  
  var length = thisObjectList.length;
  var index;
  for( index = 0; index < length; index++ )
  {
    if( object == thisObjectList[index] )
    {
      object.parentObject = null;
      thisObjectList.splice( index, 1 );
      return;
    }
  }

  // NOTE: Should this update the quad tree?
};

Object2d.prototype.clearObjects = function()
{
  var thisObjectList = this.objectList;
  
  var length = thisObjectList.length;
  var index;
  for( index = 0; index < length; index++ )
  {
    thisObjectList[index].parentObject = null;
  }

  thisObjectList.length = 0;

  // NOTE: Should this update the quad tree?
};

Object2d.prototype.insertIntoParentQuadTree = function()
{
  //console.log( "Object2d::insertIntoParentQuadTree" );
  var parentObject = this.parentObject;
  if( ( parentObject !== null ) &&
      ( parentObject.quadTree !== null ) )
  {
    var previousNode = this.quadTreeNode;
    if( previousNode !== null )
    {
      var previousNodeObjectList = previousNode.objectList;
      var index = previousNodeObjectList.indexOf( this );
      if( index > -1 )
      {
        previousNodeObjectList.splice( index, 1 );
      }
    }
    
    parentObject.quadTree.insert( this );
  }
};
