var QUAD_TREE_MAX_CAPACITY    = 2;
var QUAD_TREE_MAX_DEPTH_LEVEL = 4;

//-------------------------------------------------------------------------
function QuadTreeNode( parentNode, nodeId )
{
  this.parentNode;
  this.depthLevel;
  this.nodeId;
  
  this.objectList;
  this.subNodeList;

  this.rectangle;
  this.midPoint;
  
  // Constructor.
  this.parentNode = parentNode;
  if( parentNode == null )
  {
    this.depthLevel = 0;
  }
  else
  {
    this.depthLevel = parentNode.depthLevel + 1;
  }

  this.nodeId = nodeId;

  this.rectangle = new Rectangle();
  this.midPoint  = new Vector2d();

  this.objectList  = new Array();
  this.subNodeList = new Array( null, null, null, null );
}

QuadTreeNode.prototype.createSubNode = function( subNodeIndex )
{
  var subNode = this.subNodeList[subNodeIndex];
  if( subNode == null )
  {
    subNode = new QuadTreeNode( this, subNodeIndex );
    subNode.updateRectangle();

    this.subNodeList[subNodeIndex] = subNode;
    return subNode;
  }
};

QuadTreeNode.prototype.setRectangle = function( xPosition0, yPosition0, xPosition1, yPosition1 )
{
  this.rectangle.startPoint.x = xPosition0;
  this.rectangle.startPoint.y = yPosition0;
  this.rectangle.endPoint.x = xPosition1;
  this.rectangle.endPoint.y = yPosition1;

  //console.log( xPosition0+ ":" +yPosition0+ ":" +width+ ":" +height );

  // TODO: Only do if there are any subnodes.

  var width  = xPosition1 - xPosition0 + 1;
  var height = yPosition1 - yPosition0 + 1;

  // Midpoint is the first location in the SE quadrant.
  var midXPosition = xPosition0 + ( width  >> 1 ) + 1;
  var midYPosition = yPosition0 + ( height >> 1 ) + 1;

  var midPoint = this.midPoint;
  midPoint.x = midXPosition;
  midPoint.y = midYPosition;
  
  var currentNode;
  for( var index = 0; index < 4; index++ )
  {
    currentNode = this.subNodeList[index];
    if( currentNode != null )
    {
      currentNode.updateRectangle();
    }
  }
};

QuadTreeNode.prototype.updateRectangle = function()
{
  var parentNode = this.parentNode;
  if( parentNode == null )
  {
    return;
  }

  var rectangle = parentNode.rectangle;

  // Order: NW, NE, SW, SE.
  switch( this.nodeId )
  {
    case 0:
    {
      //console.log( "midpoint: " + parentNode.midPoint.x + "," + parentNode.midPoint.y );
      var point = rectangle.startPoint;
      this.setRectangle( point.x, point.y,
                         parentNode.midPoint.x - 1, parentNode.midPoint.y - 1 );
      break;
    }

    case 1:
    {
      var yPosition  = rectangle.startPoint.y;
      var xPosition1 = rectangle.endPoint.x;
      this.setRectangle( parentNode.midPoint.x, yPosition,
                         xPosition1, parentNode.midPoint.y - 1 );
      break;
    }

    case 2:
    {
      var xPosition  = rectangle.startPoint.x;
      var yPosition1 = rectangle.endPoint.y;
      this.setRectangle( xPosition, parentNode.midPoint.y,
                         parentNode.midPoint.x - 1, yPosition1 );
      break;
    }

    case 3:
    {
      var endPoint = rectangle.endPoint;
      this.setRectangle( parentNode.midPoint.x, parentNode.midPoint.y,
                         endPoint.x, endPoint.y );
      break;
    }
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

QuadTreeNode.prototype.getQuadrantId = function( rectangle )
{
  var midPoint = this.midPoint;

  var point1QuadrantId;
  var point = rectangle.endPoint;
  if( point.x < midPoint.x )
  {
    // West.
    point1QuadrantId = 0;
  }
  else
  {
    // East.
    point1QuadrantId = 1;
  }

  if( point.y >= midPoint.y )
  {
    // South.
    point1QuadrantId |= 2;
  }

  if( point1QuadrantId === 0 )
  {
    // Checking if point1 (end point) is in the NW (0)
    // quadrant is an optimization.
    return point1QuadrantId;
  }
  else
  {
    var point0QuadrantId;
    point = rectangle.startPoint;

    if( point.x >= midPoint.x )
    {
      // East.
      point0QuadrantId = 1;
    }
    else
    {
      // West.
      point0QuadrantId = 0;
    }

    if( point.y >= midPoint.y )
    {
      // South.
      point0QuadrantId |= 2;
    }

    if( point0QuadrantId === 3 )
    {
      // Checking if point0 (start point) is in the SE (3)
      // quadrant is an optimization.
      return point0QuadrantId;
    }
    else
    {
      if( point0QuadrantId === point1QuadrantId )
      {
        return point0QuadrantId;
      }
      else
      {
        return -1;
      }
    }
  }

  return -1;
}

QuadTreeNode.prototype.insert = function( object2d )
{
  var targetSubNodeIndex;
  
  var numberOfObjects = this.getNumberOfObjects();
  if( ( numberOfObjects > QUAD_TREE_MAX_CAPACITY ) &&
      ( this.depthLevel <= QUAD_TREE_MAX_DEPTH_LEVEL ) )
  {
    targetSubNodeIndex = this.getQuadrantId( object2d );
    if( targetSubNodeIndex !== -1 )
    {
      //console.log( "new: " + targetSubNodeIndex );
      var subNode = this.subNodeList[targetSubNodeIndex];
      if( subNode == null )
      {
        //console.log( "new: " + targetSubNodeIndex );
        subNode = this.createSubNode( targetSubNodeIndex );
      }

      subNode.insert( object2d );
    }
  }
  else
  {
    targetSubNodeIndex = -1;
  }

  //console.log( targetSubNodeIndex );

  if( targetSubNodeIndex === -1 )
  {
    // Put it in this node.
    var oldNode = object2d.quadTreeNode;
    if( oldNode != this )
    {
      if( oldNode != null )
      {
        var oldNodeObjectList  = oldNode.objectList;
        var oldnumberOfObjects = oldNode.getNumberOfObjects();
        for( var index = 0; index < oldnumberOfObjects; index++ )
        {
          if( object2d == oldNodeObjectList[index] )
          {
            oldNodeObjectList.splice( index, 1 );
            return;
          }
        }
      }

      //console.log( object2d );
      object2d.quadTreeNode = this;
      this.objectList[numberOfObjects] = object2d;
    }
  }
};

QuadTreeNode.prototype.query = function( rectangle, resultList )
{
  var numberOfObjects = this.getNumberOfObjects();
  if( numberOfObjects > 0 )
  {
    var currentObject2d;
    for( var index = 0; index < numberOfObjects; index++ )
    {
      currentObject2d = this.objectList[index];
      if( currentObject2d.isIntersecting( rectangle ) )
      {
        resultList[resultList.length] = currentObject2d;
      }
    }
  }

  targetSubNodeIndex = this.getQuadrantId( rectangle );
  if( targetSubNodeIndex !== -1 )
  {
    var subNodeList = this.subNodeList;
    var currentNode; // subNodeList order: NW, NE, SW, SE.
    for( var index = 0; index < 4; index++ )
    {
      currentNode = subNodeList[index];
      if( currentNode != null )
      {
        currentNode.query( rectangle, resultList );
      }
    }
  }
  else
  {
    var currentNode = this.subNodeList[targetSubNodeIndex];
    if( currentNode != null )
    {
      currentNode.query( rectangle, resultList );
    }
  }
};

//-------------------------------------------------------------------------
function QuadTree()
{
  QuadTreeNode.call( this, null, -1 );
  //quadTreeNode = new QuadTreeNode( null, -1 );

  //this.object2d;

  // Constructor.
  //this.setObject2d( null );
}

extend( QuadTree, QuadTreeNode );

/*QuadTree.prototype.setObject2d = function( object2d )
{
  this.object2d = object2d;
  if( object2d != null )
  {
    this.setRectangle( 0, 0,
                       object2d.getWidth() - 1, object2d.getHeight() - 1 );
  }
};

QuadTree.prototype.updateRectangle = function()
{
  object2d = this.object2d;
  if( object2d != null )
  {
    var newX = object2d.getWidth()  - 1;
    var newY = object2d.getHeight() - 1;

    if( ( this.rectangle.endPoint.x !== newX ) || ( this.rectangle.endPoint.y !== newY ) )
    {
      this.setRectangle( 0, 0, newX, newY );
    }
  }
};*/

