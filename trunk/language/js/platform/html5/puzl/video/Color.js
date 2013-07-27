function Color()
{
  this.red;
  this.green;
  this.blue;
  this.alpha;

  this.string;

  var argumentsLength = arguments.length;
  if( argumentsLength === 1 )
  {
    var argument0 = arguments[0];
    if( argument0 instanceof Color )
    {
      this.copy( argument0 );
    }
    else
    {
      this.setRgb( argument0 );
    }
  }
  else
  if( argumentsLength > 2 )
  {
    if( argumentsLength > 3 )
    {
      this.setRgb( arguments[0], arguments[1], arguments[2], arguments[3] );
    }
    else
    {
      this.setRgb( arguments[0], arguments[1], arguments[2] );
    }
  }
  else
  {
    this.setRgb( 0, 0, 0, 1 );
  }
}

Color.prototype.equals = function( color )
{
  // NOTE: Would it be more efficient to compare string values?
  // TODO: Test?
  
  if( this.red !== color.red )
  {
    return false;
  }
  
  if( this.green !== color.green )
  {
    return false;
  }
  
  if( this.blue !== color.blue )
  {
    return false;
  }

  if( this.alpha !== color.alpha )
  {
    return false;
  }

  return true;
}

Color.prototype.copy = function( color )
{
  this.red   = color.red;
  this.green = color.green;
  this.blue  = color.blue;
  this.alpha = color.alpha;

  this.string = color.string;
}

Color.prototype.updateString = function()
{
  if( this.alpha === 1 )
  {
    // Compute a hex string.
    var rString = this.red.toString( 16 );
    if( rString.length === 1 )
    {
      rString = '0' + rString;
    }

    var gString = this.green.toString( 16 );
    if( gString.length === 1 )
    {
      gString = '0' + gString;
    }

    var bString = this.blue.toString( 16 );
    if( bString.length === 1 )
    {
      bString = '0' + bString;
    }

    this.string = '#' + rString + gString + bString;
  }
  else
  {
    // Compute an rgba() string.
    this.string = "rgba(" + this.red + "," + this.green + "," + this.blue + "," + this.alpha + ')';
  }
}

Color.prototype.setRgb = function()
{
  var argumentsLength = arguments.length;
  if( argumentsLength === 1 )
  {
    // Determine string type and extract rgba.
    var string = arguments[0];
    if( string.charAt( 0 ) === '#' )
    {
      // It's a hex string.
      this.red   = parseInt( string.substring( 1, 3 ), 16 );
      this.blue  = parseInt( string.substring( 3, 5 ), 16 );
      this.green = parseInt( string.substring( 5, 7 ), 16 );

      this.alpha = 1.0;
    }
    else
    if( string.substring( 0, 3 ) === "rgb" )
    {
      // TODO: Precompute the regular expression objects.
      // It's an RGB string.
      if( string.substring( 3, 4 ) === "a" )
      {
        // It includes alpha.
        var regExp = new RegExp( "/rgba\\(\\s*(d+)\\s*,\\s*(d+)\\s*,\\s*(d+)\\s*,\\s*(.*)\\s*\\)/" );
        var matchList = regExp.exec( string );
        if( matchList == null || matchList.length !== 4 )
        {
          return;
        }

        this.red   = parseInt( matchList[0] );
        this.green = parseInt( matchList[1] );
        this.blue  = parseInt( matchList[2] );
        this.alpha = parseFloat( matchList[3] );
      }
      else
      {
        // It DOES NOT include alpha.
        var regExp = new RegExp( "/rgb\\(\\s*(d+)\\s*,\\s*(d+)\\s*,\\s*(d+)\\s*,\\s*\\)/" );
        var matchList = regExp.exec( string );
        if( matchList == null || matchList.length !== 3 )
        {
          return;
        }

        this.red   = parseInt( matchList[0] );
        this.green = parseInt( matchList[1] );
        this.blue  = parseInt( matchList[2] );
        this.alpha = 1;
      }
    }
    else
    {
      // String is not supported.
      return;
    }
  }
  else
  if( argumentsLength > 2 )
  {
    this.red   = arguments[0];
    this.green = arguments[1];
    this.blue  = arguments[2];
    
    if( argumentsLength > 3 )
    {
      this.alpha = arguments[3];
    }
    else
    {
      this.alpha = 1;
    }
  }
  else
  {
    return;
  }

  this.updateString();
}

Color.prototype.setRed = function( red )
{
  this.red = red;
  this.updateString();
}

Color.prototype.setGreen = function( green )
{
  this.green = green;
  this.updateString();
}

Color.prototype.setBlue = function( green )
{
  this.blue = blue;
  this.updateString();
}

Color.prototype.setAlpha = function( alpha )
{
  this.alpha = alpha;
  this.updateString();
}
