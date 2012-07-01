
function GameScreen( gameShell, parentScreen )
{
  this.gameShell;
  this.parentScreen;
  
  this.subScreenIndex;
  this.subScreen;
  this.subScreenList;
  
  this.constructor( gameShell, parentScreen );
  return this;
}

GameScreen.prototype.constructor = function( gameShell, parentScreen )
{
  this.gameShell    = gameShell;
  this.parentScreen = parentScreen; // TODO: Check for undefined.
  
  this.subScreenIndex = -1;
  this.subScreen      = null;
  this.subScreenList  = new Array();
};

GameScreen.prototype.setSubScreenIndex = function( subScreenIndex )
{
  //console.log( "GameScreen::setSubScreenIndex(" + subScreenIndex + ")" );
  if( this.subScreenIndex == subScreenIndex )
  {
    return;
  }
  
  this.subScreenIndex = subScreenIndex;
  this.subScreen      = this.subScreenList[this.subScreenIndex];
  //this.initialize     = this.subScreen.initialize; // NOTE: Subscreens shouldn't have their own initialize?
  this.reset          = this.subScreen.reset;
  this.input          = this.subScreen.input;
  this.logic          = this.subScreen.logic;
  this.draw           = this.subScreen.draw;

  // NOTE: Kind of crappily needed for instance runs to recongize
  // this.parentScreen when running subscreen routines.
  this.parentScreen   = this;
};

GameScreen.prototype.initialize = function()
{

};

GameScreen.prototype.reset = function()
{

};

GameScreen.prototype.input = function()
{

};

GameScreen.prototype.logic = function()
{
  
};

GameScreen.prototype.draw = function()
{
  
};
