/*function Vector2d(){};
function Rectangle(){};
function QuadTreeNode(){};
function QuadTree(){};
function Object2d(){};

function Operation(){};
function Button(){};

function Color(){};
function VideoObject(){};
function VideoImage(){};
function VideoCellImage(){};
function VideoSprite(){};
function BlockGraphic(){};
function VideoDisplay(){};
function VideoSystem(){};
function ProcessVideoImageLoad(){};

function Input(){};
function InputDevice(){};
function InputKeyboard(){};
function InputMouse(){};
function InputJoystick(){};
function InputSystem(){};

function AudioSystem(){};

function GameScreen(){};
function GameShell(){};*/

// Externs for W3C Gamepad API (until Google adds it to Closure).
/**
 * @typedef {{id: string, index: number, timestamp: number, axes: Array.<number>, buttons: Array.<number>}}
 */
var Gamepad;

/**
 * @return {Array.<Gamepad>}
 */
navigator.getGamepads = function() {};

/**
 * @return {Array.<Gamepad>}
 */
navigator.webkitGetGamepads = function() {};
// End Externs for W3C Gamepad API.

// OUYA externs.
navigator.isCocoonJS = function(){};

/**
 * @typedef {{}}
 */
var ext;
ext.IDTK_APP = function(){};
ext.IDTK_APP.makeCall = function(){};
// End Ouya externs.
