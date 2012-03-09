#ifndef V8_UTILS_H
#define V8_UTILS_H

#include <string>
#include <v8.h>

using namespace v8;


static int x = 0;

static Handle<Value> XGetter( Local<String> name, const AccessorInfo& info )
{
  return Number::New( x );
}

static void XSetter( Local<String> name, Local<Value> value, const AccessorInfo& info )
{
  x = value->Int32Value();
}

//-----------------------------------------------------------------
int CompileScriptFromFile( const char fileName[], v8::Handle<v8::Script>& script );
int CompileScriptFromFile( const std::string& fileName, v8::Handle<v8::Script>& script );

int CompileScript( const char source[], const char name[], v8::Handle<v8::Script>& script );
int CompileScript( const Handle<String>& source, const Handle<Value>& name, v8::Handle<v8::Script>& script );

Handle<Value> CompileAndExecuteScript( const char source[], const char name[] );
Handle<Value> CompileAndExecuteScript( const Handle<String>& source, const Handle<Value>& name );

Handle<Value> ExecuteScript( const v8::Handle<v8::Script>& script );

#endif
