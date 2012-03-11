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
#ifndef JS_GAME_SHELL_H
#define JS_GAME_SHELL_H

// INCLUDES ======================================================================

#include <puzl/core/GameShell.h>
#include <puzl/utility/v8utils.h>

#include <v8.h>
#include <string>
#include <iostream>

using namespace v8;

//#include "puzl/video/VideoSystem.h"   // VideoSystem header file
//#include "puzl/audio/AudioSystem.h"   // AudioSystem header file
//#include "puzl/input/InputSystem.h"   // InputSystem header file

// DEFINES =======================================================================

// PROTOTYPES ====================================================================
//Handle<Value> GetGameShellAge( Local<String> property, const AccessorInfo& info );
//void SetGameShellAge( Local<String> property, Local<Value> value, const AccessorInfo& info );

Handle<Value> GameShellMethodInitialize( const Arguments& args );
Handle<Value> GameShellMethodShutdown( const Arguments& args );

// TYPES =========================================================================
class JsGameShell : public GameShell
{
public:
  JsGameShell( const GameShellSettings& gameShellSettings, Persistent<Context> context, std::string id );
  ~JsGameShell();
  
  int initialize( void );
  int shutdown( void );
  
  void loop( void );
  void draw( void );
  
protected:
  std::string id;
  
  v8::Handle<v8::Script> initializeScript;
  v8::Handle<v8::Script> shutdownScript;
  v8::Handle<v8::Script> loopScript;
  v8::Handle<v8::Script> drawScript;
};

// GLOBALS =======================================================================

#endif
