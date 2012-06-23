function InputMouse()
{
  
}

// event functions
function mouseClicked( mouseEvent )
{
  mouseX = mouseEvent.pageX - TitleCanvas.offsetLeft;
  mouseY = mouseEvent.pageY - TitleCanvas.offsetTop;
}

/*
function CheckKeyDown( e )
{
    var keyID = e.keyCode || e.which;
    if( keyID === 38 || keyID === 87 )
    { //up arrow or W key
        e.preventDefault();
    }

    if( keyID === 39 || keyID === 68 )
    { //right arrow or D key
        e.preventDefault();
    }

    if( keyID === 40 || keyID === 83 )
    { //down arrow or S key
        e.preventDefault();
    }

    if( keyID === 37 || keyID === 65 )
    { //left arrow or A key
        e.preventDefault();
    }

    if( keyID === 32 )
    { //spacebar
        e.preventDefault();
    }
}

function CheckKeyUp( e )
{
    var keyID = e.keyCode || e.which;
    if( keyID === 38 || keyID === 87 )
    { //up arrow or W key
        e.preventDefault();
    }

    if( keyID === 39 || keyID === 68 )
    { //right arrow or D key
        e.preventDefault();
    }

    if( keyID === 40 || keyID === 83 )
    { //down arrow or S key
        e.preventDefault();
    }

    if( keyID === 37 || keyID === 65 )
    { //left arrow or A key
        e.preventDefault();
    }

    if( keyID === 32 )
    { //spacebar
        e.preventDefault();
    }
}
*/
