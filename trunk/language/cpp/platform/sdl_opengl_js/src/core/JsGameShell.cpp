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

#include <puzl/core/JsGameShell.h>

using namespace v8;

// DEFINES =======================================================================

// TYPES =========================================================================

// PROTOTYPES ====================================================================

// GLOBALS =======================================================================

// FUNCTIONS =====================================================================

// ===============================================================================
JsGameShell::JsGameShell( const GameShellSettings& gameShellSettings, Persistent<Context> context, std::string id ) : GameShell( gameShellSettings )
{
  this->id = id;
  
  Handle<FunctionTemplate> GameShellFunctionTemplate = FunctionTemplate::New();
  GameShellFunctionTemplate->SetClassName( String::New( "GameShell" ) );
  
  Handle<ObjectTemplate> GameShellTemplate = GameShellFunctionTemplate->PrototypeTemplate();
  GameShellTemplate->Set( "initialize", FunctionTemplate::New( GameShellMethodInitialize ) );
  GameShellTemplate->Set( "shutdown",   FunctionTemplate::New( GameShellMethodShutdown ) );
 
  std::string initializeCall = id;
  initializeCall.append( "." );
  initializeCall.append( "initialize" );
  initializeCall.append( "();" );
  CompileScript( initializeCall.c_str(), initializeCall.c_str(), initializeScript );
  
  std::string shutdownCall = id;
  shutdownCall.append( "." );
  shutdownCall.append( "shutdown" );
  shutdownCall.append( "();" );
  CompileScript( shutdownCall.c_str(), shutdownCall.c_str(), shutdownScript );
  
  std::string loopCall = id;
  loopCall.append( "." );
  loopCall.append( "loop" );
  loopCall.append( "();" );
  CompileScript( loopCall.c_str(), loopCall.c_str(), loopScript );
  
  std::string drawCall = id;
  drawCall.append( "." );
  drawCall.append( "draw" );
  drawCall.append( "();" );
  CompileScript( drawCall.c_str(), drawCall.c_str(), drawScript );
  
  Handle<ObjectTemplate> GameShellInstance = GameShellFunctionTemplate->InstanceTemplate();
  GameShellInstance->SetInternalFieldCount( 1 );
  
  Handle<Function> point_ctor = GameShellFunctionTemplate->GetFunction();
  
  Local<Object> object = point_ctor->NewInstance();
  object->SetInternalField( 0, External::New( this ) );
  
  context->Global()->Set( String::New( id.c_str() ), object );
}

JsGameShell::~JsGameShell()
{
}

int JsGameShell::initialize( void )
{
  //std::cout << "JsGameShell::initialize" << std::endl;
  ExecuteScript( initializeScript );
}

int JsGameShell::shutdown( void )
{
  //std::cout << "JsGameShell::shutdown" << std::endl;
  ExecuteScript( shutdownScript );
}

void JsGameShell::loop( void )
{
  //std::cout << "JsGameShell::loop" << std::endl;
  ExecuteScript( loopScript );
}

void JsGameShell::draw( void )
{
  //std::cout << "JsGameShell::draw" << std::endl;
  ExecuteScript( drawScript );
}

//=================================================================

//-----------------------------------------------------------------
Handle<Value> GameShellMethodInitialize( const Arguments& args )
{
  Local<Object> self = args.Holder();
  Local<External> wrap = Local<External>::Cast( self->GetInternalField( 0 ) );
  
  void* ptr = wrap->Value();
  static_cast<GameShell*>( ptr )->shellInitialize();
  return Undefined();
}

//-----------------------------------------------------------------
Handle<Value> GameShellMethodShutdown( const Arguments& args )
{
  Local<Object> self = args.Holder();
  Local<External> wrap = Local<External>::Cast( self->GetInternalField( 0 ) );
  
  void* ptr = wrap->Value();
  static_cast<GameShell*>( ptr )->shellShutdown();
  return Undefined();
}
