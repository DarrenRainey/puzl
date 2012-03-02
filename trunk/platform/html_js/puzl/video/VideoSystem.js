RequestAnimFrame = window.requestAnimationFrame       ||
                   window.webkitRequestAnimationFrame ||
                   window.mozRequestAnimationFrame    ||
                   window.msRequestAnimationFrame     ||
                   window.oRequestAnimationFrame;

function VideoSystem( width, height )
{
  this.display = new VideoDisplay( width, height );
                         
  this.getRequestAnimFrame = function( callback )
  {
    return RequestAnimFrame( callback );
  };
  
  this.draw = function()
  {
    this.display.clear();
  };
  
  this.getDisplay = function()
  {
    return this.display;
  };
}
