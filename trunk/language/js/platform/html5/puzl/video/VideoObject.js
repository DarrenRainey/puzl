function VideoObject()
{
  var object2d = new Object2d();
  
  object2d.needsRedraw;

  object2d.constructor = this.constructor;
  object2d.getCanvas   = this.getCanvas;

  object2d.constructor();
  return object2d;
};

VideoObject.prototype.constructor = function()
{
  this.needsRedraw = false;
};

VideoObject.prototype.getCanvas = function()
{
  return null;
};
