function puzLInclude( path )
{
  if( navigator.isCocoonJS !== undefined )
  {
    var script = document.createElement( "script" );
    script.type = "text/javascript";
    script.src  = path;
    
    document.body.appendChild( script );
  }
  else
  {
    document.write( "<script type=\"text/javascript\" src=\"" + path + "\"></script>" );
  }
}

puzLInclude( "puzl/input/InputDevice.js" );
puzLInclude( "puzl/input/InputKeyboard.js" );
puzLInclude( "puzl/input/InputMouse.js" );
puzLInclude( "puzl/input/InputJoystick.js" );
puzLInclude( "puzl/input/InputSystem.js" );

puzLInclude( "puzl/video/VideoObject.js" );
puzLInclude( "puzl/video/BlockGraphic.js" );
puzLInclude( "puzl/video/VideoCellImage.js" ) ;
puzLInclude( "puzl/video/VideoSprite.js" );
puzLInclude( "puzl/video/VideoImage.js" );
puzLInclude( "puzl/video/VideoDisplay.js" );
puzLInclude( "puzl/video/VideoSystem.js" );

puzLInclude( "puzl/audio/AudioSystem.js" );

puzLInclude( "puzl/utility/2dUtil.js" );
puzLInclude( "puzl/utility/Object2d.js" );
puzLInclude( "puzl/utility/QuadTree.js" );
puzLInclude( "puzl/utility/Operation.js" );
puzLInclude( "puzl/utility/Button.js" );
puzLInclude( "puzl/utility/GameScreen.js" );

puzLInclude( "puzl/utility/GameShell.js" );
