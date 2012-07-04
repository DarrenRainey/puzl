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

var SPRITE_ATTRIBUTE_TRANSPARENCY  = 512  // Indicates sprite with transparency
var SPRITE_ATTRIBUTE_ALPHABLEND    = 1024 // Indicates sprite with alpha/semi transparency
var SPRITE_ATTRIBUTE_COLOR         = 2048 // Indicates sprite with color modulation

var SPRITE_COLLISION_RECT          = 0    // Only check if two sprite rectangles intersect
var SPRITE_COLLISION_PIXEL         = 1    // Also check if pixels from two sprite intersect

function VideoSprite( videoImage, cellWidth, cellHeight )
{
  var videoCellImage = new VideoCellImage( videoImage, cellWidth, cellHeight );

  videoCellImage.constructor        = this.constructor;
  videoCellImage.draw               = this.draw;
  videoCellImage.erase              = this.erase;
  videoCellImage.queueErase         = this.queueErase;
  
  videoCellImage.setPosition        = this.setPosition;
  videoCellImage.setXPosition       = this.setXPosition;
  videoCellImage.setYPosition       = this.setYPosition;
  
  videoCellImage.setVelocity        = this.setVelocity;
  videoCellImage.setXVelocity       = this.setXVelocity;
  videoCellImage.setYVelocity       = this.setYVelocity;
  videoCellImage.move               = this.move;
  
  videoCellImage.setAttributes      = this.setAttributes;
  videoCellImage.loadFrame          = this.loadFrame;
  videoCellImage.getNumberOfFrames  = this.getNumberOfFrames;
  videoCellImage.setCurrentSequence = this.setCurrentSequence;
  videoCellImage.setCurrentFrame    = this.setCurrentFrame;
  videoCellImage.setAnimationSpeed  = this.setAnimationSpeed;
  videoCellImage.loadAnimation      = this.loadAnimation;
  videoCellImage.animate            = this.animate;

  this.xVelocity;
  this.yVelocity;

  videoCellImage.constructor();
  return videoCellImage;
}

VideoSprite.prototype.constructor = function()
{
  this.xPosition = 0;
  this.yPosition = 0;
  this.xVelocity = 0;
  this.yVelocity = 0;
  
  this.animation = new Operation();
};

VideoSprite.prototype.draw = function()
{
  //var context = videoObject.getContext();
  if( this.targetVideoObject == null )
  {
    return;
  }
  
  var context = this.targetVideoObject.getContext();
  
  var hasAlpha; // TODO: Optimize. Could allocate this value once for each blockgraphic object.
  if( this.alpha != 1.0 )
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

  if( this.targetVideoObject.display == null )
  {
    DrawWithNearestScale( this, this.targetVideoObject,
                          cell[0], cell[1],
                          this.cellWidth, this.cellHeight,
                          this.xPosition, this.yPosition,
                          this.width, this.height );
  }
  else
  {
    var videoObjectDisplay = this.targetVideoObject.display;
    var xScale = videoObjectDisplay.xScale;
    var yScale = videoObjectDisplay.yScale;
    
    DrawWithNearestScale( this, this.targetVideoObject,
                          cell[0], cell[1],
                          this.cellWidth, this.cellHeight,
                          ( this.xPosition - this.targetVideoObject.xPosition ) * xScale,
                          ( this.yPosition - this.targetVideoObject.yPosition ) * yScale,
                          this.width * xScale, this.height * yScale );
  }
  
  if( hasAlpha )
  {
    context.globalAlpha = 1.0;
  }
};

VideoSprite.prototype.erase = function()
{
  var context = this.targetVideoObject.getContext();
  
  if( this.targetVideoObject.display == null )
  {
    context.clearRect( this.xPosition, this.yPosition,
                       this.width, this.height );
  }
  else
  {
    var videoObjectDisplay = this.targetVideoObject.display;
    var xScale = videoObjectDisplay.xScale;
    var yScale = videoObjectDisplay.yScale;

    context.clearRect( ( this.xPosition - this.targetVideoObject.xPosition ) * xScale,
                       ( this.yPosition - this.targetVideoObject.yPosition ) * yScale,
                       this.width * xScale, this.height * yScale );
  }
};

VideoSprite.prototype.queueErase = function()
{
  var videoObjectDisplay = this.targetVideoObject.display;

  var eraseQueueObject = videoObjectDisplay.getNextEraseQueueObject();
  eraseQueueObject.targetVideoObject = this.targetVideoObject;
  
  var xScale = videoObjectDisplay.xScale;
  var yScale = videoObjectDisplay.yScale;

  eraseQueueObject.xPosition = ( this.xPosition - this.targetVideoObject.xPosition ) * xScale;
  eraseQueueObject.yPosition = ( this.yPosition - this.targetVideoObject.yPosition ) * yScale;
  eraseQueueObject.width     = this.width  * xScale;
  eraseQueueObject.height    = this.height * yScale;
};

VideoSprite.prototype.setPosition = function( xPosition, yPosition )
{
  this.setXPosition( xPosition );
  this.setYPosition( yPosition );
};

VideoSprite.prototype.setXPosition = function( xPosition )
{
  this.xPosition = xPosition;
};

VideoSprite.prototype.setYPosition = function( yPosition )
{
  this.yPosition = yPosition;
};

VideoSprite.prototype.setXVelocity = function( xVelocity )
{
  this.xVelocity = xVelocity;
};

VideoSprite.prototype.setYVelocity = function( yVelocity )
{
  this.yVelocity = yVelocity;
};

VideoSprite.prototype.setVelocity = function( xVelocity, yVelocity )
{
  this.setXVelocity( xVelocity );
  this.setYVelocity( yVelocity );
};

VideoSprite.prototype.move = function()
{
  if( ( this.xVelocity != 0 ) || ( this.yVelocity != 0 ) )
  {
    this.queueErase();
    
    if( this.xVelocity != 0 )
    {
      this.xPosition += this.xVelocity;
    }

    if( this.yVelocity != 0 )
    {
      this.yPosition += this.yVelocity;
    }
    
    return true;
  }

  return false;
};

VideoSprite.prototype.setAttributes = function( attributes )
{
  return this.animation.setAttributes( attributes );
};

VideoSprite.prototype.loadFrame = function( xPosition, yPosition, mode )
{
  var frameIndex = this.loadCell( xPosition, yPosition, mode );
  this.animation.setNumberOfFrames( this.getNumberOfFrames() );
  return frameIndex;
};

VideoSprite.prototype.getNumberOfFrames = function()
{
  return this.getNumberOfCells();
};

VideoSprite.prototype.setCurrentSequence = function( currentSequence )
{
  return this.animation.setCurrentSequence( currentSequence );
};

VideoSprite.prototype.setCurrentFrame = function( currentFrame )
{
  return this.animation.setCurrentFrame( currentFrame );
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
    this.queueErase();
  }

  return frameChanged;
};
