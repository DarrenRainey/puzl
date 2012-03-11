/*
Copyright (C) 2010 Andrew Dieffenbach (www.puzzud.com).

This file is part of puzl.

puzl is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with puzl; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

// Watch for multiple inclusions
#ifndef JS_VIDEO_DISPLAY
#define JS_VIDEO_DISPLAY

// INCLUDES ======================================================================

#include <puzl/video/VideoDisplay.h>
#include <puzl/utility/v8utils.h>

#include <v8.h>
#include <string>
#include <iostream>

using namespace v8;

// DEFINES =======================================================================

// TYPES =========================================================================

class JsVideoDisplay : public VideoDisplay
{
public:
  JsVideoDisplay();
  ~JsVideoDisplay();

  v8::Handle<v8::Object> wrap( void );

protected:
  
private:
  
};

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

#endif
