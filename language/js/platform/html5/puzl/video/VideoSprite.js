var SPRITE_STATE_ANIM_RUNNING      = 1    // Sprite is done animating
var SPRITE_STATE_ANIM_DONE         = 2    // Sprite is currently animating
var SPRITE_STATE_ANIM_RESET        = 4    // Sprite is has reset animation
var SPRITE_STATE_DEAD              = 8    // Sprite is dead
var SPRITE_STATE_ALIVE             = 16   // Sprite is alive
var SPRITE_STATE_DYING             = 32   // Sprite is dying
var SPRITE_STATE_CUSTOM_0          = 64   // Custom state for sprite 0.
var SPRITE_STATE_CUSTOM_1          = 128  // Custom state for sprite 1.
var SPRITE_STATE_CUSTOM_2          = 256  // Custom state for sprite 2.
var SPRITE_STATE_CUSTOM_3          = 512  // Custom state for sprite 3.

var SPRITE_ATTRIBUTE_SINGLE_FRAME  = 1    // Sprite has single frame
var SPRITE_ATTRIBUTE_MULTI_FRAME   = 2    // Sprite has multiple frames
var SPRITE_ATTRIBUTE_MULTI_ANIM    = 4    // Sprite has multiple animations
var SPRITE_ATTRIBUTE_ANIM_ONE_SHOT = 8    // Sprite will perform the animation once
var SPRITE_ATTRIBUTE_VISIBLE       = 16   // Sprite is visible
var SPRITE_ATTRIBUTE_BOUNCE        = 32   // Sprite bounces off edges
var SPRITE_ATTRIBUTE_WRAPAROUND    = 64   // Sprite wraps around edges
var SPRITE_ATTRIBUTE_LOADED        = 128  // Sprite has been loaded
var SPRITE_ATTRIBUTE_CLONE         = 256  // Sprite is a clone

var SPRITE_ATTRIBUTE_ANIMATION_MASK = SPRITE_ATTRIBUTE_SINGLE_FRAME |
                                      SPRITE_ATTRIBUTE_MULTI_FRAME |
                                      SPRITE_ATTRIBUTE_MULTI_ANIM |
                                      SPRITE_ATTRIBUTE_ANIM_ONE_SHOT;

var SPRITE_ATTRIBUTE_TRANSPARENCY  = 1024 // Indicates sprite with transparency
var SPRITE_ATTRIBUTE_ALPHABLEND    = 2048 // Indicates sprite with alpha/semi transparency
var SPRITE_ATTRIBUTE_COLOR         = 4096 // Indicates sprite with color modulation

var SPRITE_COLLISION_RECT          = 0    // Only check if two sprite rectangles intersect
var SPRITE_COLLISION_PIXEL         = 1    // Also check if pixels from two sprite intersect

function VideoSprite( sourceVideoObject, videoSpriteData )
{
  //console.log( "Creating VideoSprite" );
  VideoCellImage.call( this, sourceVideoObject, videoSpriteData );

  this.velocity;

  this.attributes;
  this.state;

  this.animation;
  this.animationNameIndexHash;

  // Constructor.
  if( sourceVideoObject === undefined )
  {
    // TODO: Allow for such in the future?
    console.error( "Attempting to load VideoSprite without source VideoObject." );
    return null;
  }

  if( videoSpriteData === undefined )
  {
    // TODO: Allow for such in the future?
    console.error( "Attempting to load VideoSprite without driving data." );
    return null;
  }
  
  this.velocity = new Vector2d( 0, 0 );
  
  this.state = SPRITE_STATE_ALIVE;

  this.animation = new Operation();
  this.animationNameIndexHash = new Array();

  // Load animations from videoSpriteData.
  var animations = videoSpriteData["animations"];
  if( animations !== undefined )
  {
    var animation;
    for( var animationName in animations )
    {
      //console.log( animationName );
      animation = animations[animationName];

      // TODO: Optimize...
      var indexedAnimation = new Array();
      var animationIndex;
      for( animationIndex in animation )
      {
        var animationFrameName = animation[animationIndex];
        indexedAnimation[animationIndex] = this.cellNameIndexHash[animationFrameName];
        //console.log( animationIndex );
      }
      indexedAnimation[++animationIndex] = -1;

      this.animationNameIndexHash[animationName] = this.loadAnimation( indexedAnimation );
    }
  }
  else
  {
    //console.warn( "Loading VideoSprite without animation information." );
  }

  this.setAttribute( SPRITE_ATTRIBUTE_VISIBLE );
}

extend( VideoSprite, VideoCellImage );

VideoSprite.prototype.drawTo = function( targetVideoObject, rectangle )
{
  if( ( this.attributes & SPRITE_ATTRIBUTE_VISIBLE ) === 0 )
  {
    return;
  }
  
  if( targetVideoObject === null )
  {
    return;
  }

  var context = targetVideoObject.context;
  
  var hasAlpha; // TODO: Optimize. Could allocate this value once for each blockgraphic object.
  if( this.alpha !== 1 )
  {
    hasAlpha = true;
    context.globalAlpha = this.alpha;
  }
  else
  {
    hasAlpha = false;
  }
  
  var cell = this.cellList[this.animation.getCurrentFrame()];
  if( cell === null )
  {
    return;
  }

  var rectangleStartPoint = rectangle.startPoint;
  var rectangleStartX = rectangleStartPoint.x;
  var rectangleStartY = rectangleStartPoint.y;
  var thisStartPoint = this.startPoint;
  var xOffset = rectangleStartX - thisStartPoint.x;
  var yOffset = rectangleStartY - thisStartPoint.y;
  var rectangleEndPoint = rectangle.endPoint;
  var rectangleWidth  = rectangleEndPoint.x - rectangleStartX + 1;
  var rectangleHeight = rectangleEndPoint.y - rectangleStartY + 1;

  // TODO: Needs to factor in scaled dimensions.
  context.drawImage( this.canvas,
                     cell[0] + xOffset, cell[1] + yOffset,

                     rectangleWidth,
                     rectangleHeight,

                     rectangleStartX, rectangleStartY,

                     rectangleWidth,
                     rectangleHeight );
  
  if( hasAlpha )
  {
    context.globalAlpha = 1;
  }
};

VideoSprite.prototype.getXVelocity = function()
{
  return this.velocity.x;
};

VideoSprite.prototype.getYVelocity = function()
{
  return this.velocity.y;
};

VideoSprite.prototype.setXVelocity = function( xVelocity )
{
  this.velocity.x = xVelocity;
};

VideoSprite.prototype.setYVelocity = function( yVelocity )
{
  this.velocity.y = yVelocity;
};

VideoSprite.prototype.setVelocity = function( xVelocity, yVelocity )
{
  var velocity = this.velocity;
  velocity.x = xVelocity;
  velocity.y = yVelocity;
};

VideoSprite.prototype.move = function()
{
  var velocity = this.velocity;
  var velocityX = velocity.x;
  var velocityY = velocity.y;
  if( ( velocityX !== 0 ) || ( velocityY !== 0 ) )
  {
    var position = this.startPoint;
    this.setPosition( position.x + velocityX,
                      position.y + velocityY );
    
    return true;
  }

  return false;
};

VideoSprite.prototype.getState = function()
{
  return this.state;
};

VideoSprite.prototype.setState = function( state )
{
  this.state = state;
};

VideoSprite.prototype.setAttribute = function( attribute )
{
  var attributes = this.attributes | attribute;
  if( this.attributes === attributes )
  {
    return;
  }

  this.attributes = attributes;
  
  if( attribute < SPRITE_ATTRIBUTE_VISIBLE )
  {
    this.animation.setAttributes( attributes & SPRITE_ATTRIBUTE_ANIMATION_MASK );
  }

  if( attribute & SPRITE_ATTRIBUTE_VISIBLE )
  {
    // Time to show sprite.
    if( this.targetVideoObject !== null )
    {
      this.targetVideoObject.addDirtyRectangle( this );
    }
  }
};

VideoSprite.prototype.clearAttribute = function( attribute )
{
  var attributes = this.attributes & ~attribute;
  if( this.attributes === attributes )
  {
    return;
  }

  this.attributes = attributes;
  
  if( attribute < SPRITE_ATTRIBUTE_VISIBLE )
  {
    this.animation.setAttributes( attributes & SPRITE_ATTRIBUTE_ANIMATION_MASK );
  }
  
  if( attribute & SPRITE_ATTRIBUTE_VISIBLE )
  {
    // Time to hide sprite.
    if( this.targetVideoObject !== null )
    {
      this.targetVideoObject.addDirtyRectangle( this );
    }
  }
};

VideoSprite.prototype.setAttributes = function( attributes )
{
  this.attributes = attributes;
  this.animation.setAttributes( attributes & ~SPRITE_ATTRIBUTE_ANIMATION_MASK );
};

VideoSprite.prototype.loadFrame = function( xPosition, yPosition, mode )
{
  var frameIndex = this.loadCell( xPosition, yPosition, mode );
  return frameIndex;
};

VideoSprite.prototype.getNumberOfFrames = function()
{
  return this.getNumberOfCells();
};

VideoSprite.prototype.getCurrentSequence = function()
{
  return this.animation.currentSequence;
};

VideoSprite.prototype.setCurrentSequence = function( currentSequence )
{
  //console.log( currentSequence );
  var thisAnimation = this.animation;
  var previousFrame = thisAnimation.getCurrentFrame();
  
  thisAnimation.setCurrentSequence( currentSequence );
  if( previousFrame !== thisAnimation.getCurrentFrame() )
  {
    this.targetVideoObject.addDirtyRectangle( this );
  }
};

VideoSprite.prototype.getFrameIndex = function()
{
  return this.animation.getFrameIndex();
};

VideoSprite.prototype.setFrameIndex = function( frameIndex )
{
  var thisAnimation = this.animation;

  if( frameIndex !== thisAnimation.getFrameIndex() )
  {
    this.targetVideoObject.addDirtyRectangle( this );
  }

  thisAnimation.setFrameIndex( frameIndex );
};

VideoSprite.prototype.getCurrentFrame = function()
{
  return this.animation.getCurrentFrame();
};

VideoSprite.prototype.setCurrentFrame = function( currentFrame )
{
  var thisAnimation = this.animation;
  
  if( currentFrame !== thisAnimation.getCurrentFrame() )
  {
    if( this.targetVideoObject )
    {
      this.targetVideoObject.addDirtyRectangle( this );
    }
  }
  
  thisAnimation.setCurrentFrame( currentFrame );
};

VideoSprite.prototype.setCurrentFrameByName = function( frameName )
{
  //console.log( "Frame index: " + this.cellNameIndexHash[frameName] );
  this.setCurrentFrame( this.cellNameIndexHash[frameName] );
};

VideoSprite.prototype.setAnimationSpeed = function( animationSpeed )
{
  return this.animation.setSpeed( animationSpeed );
};

VideoSprite.prototype.loadAnimation = function( animation )
{
  return this.animation.load( animation );
};

VideoSprite.prototype.animate = function()
{
  var frameChanged = this.animation.read();
  if( frameChanged )
  {
    this.targetVideoObject.addDirtyRectangle( this );
  }

  return frameChanged;
};
