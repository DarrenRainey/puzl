#include <v8.h>
#include <string>
#include <fstream>
#include <iostream>

#include <puzl/utility/v8utils.h>

using namespace v8;

//=================================================================
int CompileScriptFromFile( const char fileName[], v8::Handle<v8::Script>& script )
{
  std::string scriptText;
  std::ifstream file( fileName );
  std::string line;
  
  while( getline( file, line ) )
  {
     scriptText.append( line );
     scriptText.append( "\n" );
  }
  
  return CompileScript( String::New( scriptText.c_str() ), String::New( fileName ), script );
}

//=================================================================
int CompileScriptFromFile( const std::string& fileName, v8::Handle<v8::Script>& script )
{
  return CompileScriptFromFile( fileName.c_str(), script );
}

//=================================================================
int CompileScript( const char source[], const char name[], v8::Handle<v8::Script>& script )
{
  return CompileScript( String::New( source ), String::New( name ), script );
}

//=================================================================
int CompileScript( const Handle<String>& source, const Handle<Value>& name, v8::Handle<v8::Script>& script )
{
  TryCatch tryCatch;
  script = Script::Compile( source, name );
  if( script.IsEmpty() ) 
  {
    String::AsciiValue error( tryCatch.Exception() );
    printf( "%s\n", *error );
    return -1;
  }
  
  return 0;
}

//=================================================================
Handle<Value> CompileAndExecuteScript( const char source[], const char name[] )
{
  return CompileAndExecuteScript( String::New( source ), String::New( name ) );
}

//=================================================================
Handle<Value> CompileAndExecuteScript( const Handle<String>& source, const Handle<Value>& name )
{
  v8::Handle<v8::Script> script;
  CompileScript( source, name, script );
  return ExecuteScript( script );
}

//=================================================================
Handle<Value> ExecuteScript( const v8::Handle<v8::Script>& script )
{
  HandleScope handleScope;
  TryCatch tryCatch; 
  Handle<Value> result = script->Run();
  if( result.IsEmpty() ) 
  {
    String::AsciiValue error( tryCatch.Exception() );
    std::cout <<  *error << std::endl;
  }
  
  return result;
}

//-----------------------------------------------------------------

//Handle<ObjectTemplate> GlobalTemplate;

//=================================================================
