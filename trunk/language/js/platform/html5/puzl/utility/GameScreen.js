function GameScreen( gameShell, parentScreen )
{
  // Constructor.
  this.gameShell    = gameShell;
  this.parentScreen = parentScreen; // TODO: Check for undefined.

  this.subScreen      = null;
  this.nextSubScreen  = null;
  this.resetSubScreen = true;
}

GameScreen.prototype.setNextSubScreen = function( nextSubScreen, reset )
{
  //console.log( "GameScreen::setSubScreenIndex(" + subScreenIndex + ")" );
  if( this.subScreen !== nextSubScreen )
  {
    this.nextSubScreen = nextSubScreen;
  }
  
  if( reset === undefined )
  {
    reset = false;
  }
  
  this.resetSubScreen = reset;
};

GameScreen.prototype.initialize = function()
{
  
};

GameScreen.prototype.postInitialize = function()
{
  
};

GameScreen.prototype.reset = function()
{
  if( this.subScreen !== null )
  {
    this.resetSubScreen = false;
    this.subScreen.reset();
  }
};

GameScreen.prototype.input = function()
{
  if( this.nextSubScreen !== null )
  {
    this.subScreen = this.nextSubScreen;
    this.nextSubScreen = null;
  }
  
  if( this.resetSubScreen ) // NOTE: Should reset run here before logic?
  {
    this.resetSubScreen = false;
    
    if( this.subScreen !== null )
    {
      this.subScreen.reset();
    }
  }
  
  if( this.subScreen !== null )
  {
    this.subScreen.input();
  }
};

GameScreen.prototype.logic = function()
{
  if( this.subScreen !== null )
  {
    this.subScreen.logic();
  }
};
