window.addEventListener( "load", main(), false );

function main()
{
        //alert( "GameShell::main()" );
        var gameShell = new GameShell( 320, 240 );
        gameShell.run();
}

function GameShell( width, height )
{
        var screenWidth = width;
        var screenHeight = height;
        var quit = false;
        
        this.run = function()
        {
                var canvas = document.getElementById( "canvas" );
                if( !canvas || !canvas.getContext )
                {
                        alert( "Failed to get canvas from element id." );
                        return;
                }

                // Get the canvas 2d context.
                var context = canvas.getContext( "2d" );
                if( !context || !context.drawImage )
                {
                        alert( "Failed to load 2D context from canvas." );
                        return;
                }
                
                context.fillStyle = "rgb(127,0,0)";
                context.fillRect( 0, 0, canvas.width, canvas.height );
        }
        
        this.initialize = function()
        {
                
        }
        
        this.shutdown = function()
        {
                
        }

        this.loop = function()
        {
                
        }
        
        this.draw() = function()
        {
                
        }
}