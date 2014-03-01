// button functions
/** @constructor */
function Button( xPosition, yPosition, width, height )
{
  this.xPosition = xPosition;
  this.yPosition = yPosition;
  this.width     = width;
  this.height    = height;

  this.xEnd = xPosition + width  - 1;
  this.yEnd = yPosition + height - 1;
}

Button.prototype.checkClicked = function()
{
  //console.log( mouseX + ":" + mouseY );
  if( mouseY < this.yPosition )
  {
    return false;
  }

  if( mouseY > this.yEnd )
  {
    return false;
  }

  if( mouseX < this.xPosition )
  {
    return false;
  }

  if( mouseX > this.xEnd )
  {
    return false;
  }

  return true;
};
