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

// INCLUDES ======================================================================

#include <puzl/video/JsVideoDisplay.h>

//#include <iostream>
//using namespace std;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// EXTERNALS =====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================
v8::Handle<v8::Object> JsVideoDisplay::wrap( void )
{
  // Handle scope for temporary handles, 
  v8::HandleScope handle_scope;
  v8::Persistent<v8::ObjectTemplate> class_template_;

  v8::Handle<v8::ObjectTemplate> raw_template = v8::ObjectTemplate::New();

  //The raw template is the ObjectTemplate (that can be exposed to script too)
    //but is maintained internally.
  raw_template->SetInternalFieldCount(1);

  //Create the actual template object, 
  class_template_ = v8::Persistent<v8::ObjectTemplate>::New(raw_template);

  //Create the new handle to return, and set its template type 
  v8::Handle<v8::Object> result = class_template_->NewInstance();
  v8::Handle<v8::External> class_ptr = v8::External::New(static_cast<VideoDisplay*>( this ) ); 

  //Point the 0 index Field to the c++ pointer for unwrapping later
  result->SetInternalField(0, class_ptr);

  //Return the value, releasing the other handles on its way.
  return handle_scope.Close(result);
}
