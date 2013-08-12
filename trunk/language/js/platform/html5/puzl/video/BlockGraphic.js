function BlockGraphic( sourceVideoObject, blockgraphicData )
{
  // console.log( "Creating BlockGraphic" );
  VideoCellImage.call( this, sourceVideoObject, blockgraphicData );

  this.absolute;

  this.codeToCellTable;
  
  // Constructor.
  if( sourceVideoObject === undefined )
  {
    // TODO: Allow for such in the future?
    console.error( "Attempting to load BlockGraphic without source VideoObject." );
    return null;
  }

  if( blockgraphicData === undefined )
  {
    // TODO: Allow for such in the future?
    console.error( "Attempting to load BlockGraphic without driving data." );
    return null;
  }

  this.absolute = false;
  this.setPosition( 0, 0 );

  // Populate character code to cell lookup table.
  this.codeToCellTable = new Array();
  var codeToFramePartitions = blockgraphicData["codeToFramePartitions"];
  if( codeToFramePartitions !== undefined )
  {
    //this.cellNameIndexHash
    var numberOfPartitions = codeToFramePartitions.length;
    var partitionIndex;
    for( partitionIndex = 0; partitionIndex < numberOfPartitions; partitionIndex++ )
    {
      var partition = codeToFramePartitions[partitionIndex];
      var codeBase = partition["codeBase"];

      var frames = partition["frames"];
      var numberOfFrames = frames.length;
      var frameIndex;
      for( frameIndex = 0; frameIndex < numberOfFrames; frameIndex++ )
      {
        var frameId = frames[frameIndex];
        this.codeToCellTable[codeBase + frameIndex] = this.cellList[this.cellNameIndexHash[frameId]];

        // NOTE: It's important to know that undefined elements are padded
        // into the codeToCellTable array, if 'codeBase + frameIndex' is not equal
        // to the current length of the array.
      }
    }
  }
  else
  {
    console.error( "Attempting to load BlockGraphic without code to frame data." );
    return null;
  }
};

extend( BlockGraphic, VideoCellImage );

/*BlockGraphic.prototype.setPositionGridCellDimensions = function( positionGridCellWidth, positionGridCellHeight )
{
  this.positionGridCellWidth  = positionGridCellWidth;
  this.positionGridCellHeight = positionGridCellHeight;
};*/

BlockGraphic.prototype.print = function( text )
{
  var length = text.length;
  if( length < 1 )
  {
    return;
  }
  
  var canvas = this.targetVideoObject.getCanvas();
  var context = GetCanvasContext2D( canvas );

  var hasAlpha; // TODO: Optimize. Could allocate this value once for each blockgraphic object.
  if( this.alpha !== 1.0 )
  {
    hasAlpha = true;
    context.globalAlpha = this.alpha;
  }
  else
  {
    hasAlpha = false;
  }

  var xPosition = VideoCellImage.prototype.getXPosition.call( this );
  var yPosition = VideoCellImage.prototype.getYPosition.call( this );

  var character;
  var characterCode;
  var cell;
  for( var index = 0; index < length; index++ )
  {
    character = text.charAt( index );
    /*if( character === '\n' )
    {
      xPosition = 0;
      yPosition += this.height;
      continue;
    }*/

    characterCode = character.charCodeAt( 0 );
    
    cell = this.codeToCellTable[characterCode];
    if( cell !== undefined )
    {
      DrawWithNearestScale( this, this.targetVideoObject,
                            cell[0], cell[1],
                            this.cellWidth, this.cellHeight,
                            xPosition, yPosition,
                            this.width, this.height );
    }

    xPosition += this.width;
  }

  VideoCellImage.prototype.setPosition.call( this, xPosition, yPosition );

  if( hasAlpha )
  {
    context.globalAlpha = 1.0;
  }
};

BlockGraphic.prototype.setPosition = function( xPosition, yPosition )
{
  if( this.absolute !== true )
  {
    xPosition = xPosition * this.cellWidth;
    yPosition = yPosition * this.cellHeight;
  }
  
  VideoCellImage.prototype.setPosition.call( this, xPosition, yPosition );
};

BlockGraphic.prototype.getXPosition = function()
{
  var xPosition = VideoCellImage.prototype.getXPosition.call( this );
  
  if( this.absolute === true )
  {
    return xPosition;
  }

  return ( xPosition / this.cellWidth ) | 0;
};

BlockGraphic.prototype.getYPosition = function()
{
  var yPosition = VideoCellImage.prototype.getYPosition.call( this );

  if( this.absolute === true )
  {
    return yPosition;
  }

  return ( yPosition / this.cellHeight ) | 0;
};

