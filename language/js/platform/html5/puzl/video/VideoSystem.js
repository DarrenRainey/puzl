RequestAnimFrame = window.requestAnimationFrame       ||
                   window.webkitRequestAnimationFrame ||
                   window.mozRequestAnimationFrame    ||
                   window.oRequestAnimationFrame      ||
                   window.msRequestAnimationFrame     ||
                   function( callback )
                   {
                     window.setTimeout( callback, 1000 / 60 );
                   };

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
