var QUAD_TREE_MAX_CAPACITY    = 2;
var QUAD_TREE_MAX_DEPTH_LEVEL = 4;

function QuadTree()
{
  quadTreeNode = new QuadTreeNode( null, -1 );

  quadTreeNode.object2d;

  quadTreeNode.constructor     = this.constructor;
  quadTreeNode.setObject2d     = this.setObject2d;
  quadTreeNode.updateRectangle = this.updateRectangle;

  quadTreeNode.constructor();
  return quadTreeNode;
}

QuadTree.prototype.constructor = function()
{
  this.setObject2d( null );
};

QuadTree.prototype.setObject2d = function( object2d )
{
  this.object2d = object2d;
  this.updateRectangle();
};

QuadTree.prototype.updateRectangle = function()
{
  object2d = this.object2d;
  if( object2d != null )
  {
    this.setRectangle( object2d.getXPosition(), object2d.getYPosition(),
                       object2d.getWidth(),     object2d.getHeight() );
  }
};

//-------------------------------------------------------------------------
function QuadTreeNode( parentNode, nodeID )
{
  this.parentNode;
  this.depthLevel;
  this.nodeID;
  
  this.objectList;
  this.subNodeList;

  this.rectangle;
  this.midPoint;
  
  this.constructor( parentNode, nodeID );
  return this;
}

QuadTreeNode.prototype.constructor = function( parentNode, nodeID )
{
  this.parentNode = parentNode;
  if( parentNode == null )
  {
    this.depthLevel = 0;
  }
  else
  {
    this.depthLevel = parentNode.depthLevel + 1;
  }

  this.nodeID = nodeID;

  this.rectangle = new Rectangle();
  this.midPoint  = new Point();

  this.objectList  = new Array();
  this.subNodeList = new Array( null, null, null, null );
};

QuadTreeNode.prototype.createSubNode = function( subNodeIndex )
{
  var subNode = this.subNodeList[subNodeIndex];
  if( subNode == null )
  {
    subNode = new QuadTreeNode( this, subNodeIndex );
    subNode.updateRectangle();

    this.subNodeList[subNodeList] = subNode;
  }
};

QuadTreeNode.prototype.setRectangle = function( xPosition, yPosition, width, height )
{
  var xPosition1 = xPosition + width  - 1;
  var yPosition1 = yPosition + height - 1;

  var rectanglePointList = this.rectangle.pointList;
  var rectanglePoint0    = rectanglePointList[0];
  var rectanglePoint1    = rectanglePointList[1];
  
  rectanglePoint0.x = xPosition;
  rectanglePoint0.y = yPosition;
  rectanglePoint1.x = xPosition1;
  rectanglePoint1.y = yPosition1;

  //console.log( xPosition+ ":" +yPosition+ ":" +width+ ":" +height );

  // TODO: Only do if there are any subnodes.

  // Midpoint is +1 (start of next rectangle).
  var midXPosition = xPosition1 + ( width  >> 1 );
  var midYPosition = yPosition1 + ( height >> 1 );

  var midPoint = this.midPoint;
  midPoint.x = midXPosition;
  midPoint.y = midYPosition;
  
  var currentNode; // subNodeList order: NW, NE, SW, SE.

  // NW
  currentNode = this.subNodeList[0];
  if( currentNode != null )
  {
    currentNode.setRectangle( xPosition, yPosition, midXPosition, midYPosition );
  }

  // NE
  currentNode = this.subNodeList[1];
  if( currentNode != null )
  {
    currentNode.setRectangle( midXPosition, yPosition, xPosition1, midYPosition );
  }

  // SW
  currentNode = this.subNodeList[2];
  if( currentNode != null )
  {
    currentNode.setRectangle( xPosition, midYPosition, midXPosition, yPosition1 );
  }

  // SE
  currentNode = this.subNodeList[3];
  if( currentNode != null )
  {
    currentNode.setRectangle( midXPosition, midYPosition, xPosition1, yPosition1 );
  }
};

QuadTreeNode.prototype.getNumberOfObjects = function()
{
  return this.objectList.length;
};

QuadTreeNode.prototype.getNumberOfSubObjects = function()
{
  var numberOfSubObjects = 0;
  var currentNode; // subNodeList order: NW, NE, SW, SE.
  for( var index = 0; index < 4; index++ )
  {
    currentNode = this.subNodeList[index];
    if( currentNode == null )
    {
      continue;
    }

    numberOfSubObjects += currentNode.getTotalNumberOfObjects();
  }
  
  return numberOfSubObjects;
};

QuadTreeNode.prototype.getTotalNumberOfObjects = function()
{
  return this.getNumberOfObjects() + this.getNumberOfSubObjects();
};

QuadTreeNode.prototype.insert = function( object2d )
{
  var numberOfObjects = this.getNumberOfObjects();
  //console.log( numberOfObjects );
  if( numberOfObjects > QUAD_TREE_MAX_CAPACITY )
  {
    var point1QuadrantID;
    var point1 = object2d.rectangle.pointList[1];

    if( point1.x < this.midPoint.x )
    {
      // West.
      point1QuadrantID = 0;
    }
    else
    {
      // East.
      point1QuadrantID = 1;
    }

    if( point1.y >= this.midPoint.y )
    {
      // South.
      point1QuadrantID |= 2;
    }
  }
  else
  {
    this.objectList[numberOfObjects] = object2d;
    object2d.setQuadTreeNode( this );
  }
  
}

/*QuadTreeNode.prototype.populateCollisions = function( sourceObject2d )
{
  var index;

  var numberOfObjects = this.getNumberOfObjects();
  var currentObject2d;
  for( index = 0; index < numberOfObjects; index++ )
  {
    currentObject2d = this.objectList[index];
    if( currentObject2d == sourceObject2d )
    {
      continue;
    }

    if( sourceObject2d.checkBBCollision( currentObject2d ) )
    {
      // TODO: Needs to make sure the object isn't inserted twice.
      // Great place for a map?
      sourceObject2d.collisionList[sourceObject2d.numberOfCollisions] = currentObject2d;
    }
  }

  if( this.getNumberOfSubObjects() == 0 )
  {
    return;
  }

  var currentNode; // subNodeList order: NW, NE, SW, SE.
  for( index = 0; index < 4; index++ )
  {
    currentNode = this.subNodeList[index];
    if( currentNode == null )
    {
      continue;
    }

    if( currentNode.getTotalNumberOfObjects() > 0 )
    {
      currentNode.populateCollisions( sourceObject2d );
    }
  }
};
*/
