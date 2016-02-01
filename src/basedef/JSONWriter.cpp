#include "JSONWriter.h"

#include <fstream>

namespace Magna{
  namespace Core{

    JSONWriter::JSONWriter()
      :m_errorMessage()
      ,m_rootValue(){

    }

    JSONWriter::JSONWriter( const JSONValue& value)
      :m_errorMessage()
      ,m_rootValue( value ){

    }

    JSONWriter::~JSONWriter(){

    }

    bool JSONWriter::writeToOutputStream( std::wostream& out){
      bool _is_ok = false;
      const auto& _writable_root_value = m_rootValue;
      if( out.good() ){
        if( _writable_root_value.isJSONObject() || _writable_root_value.isJSONArray() ){
          out << m_rootValue.toString();
          _is_ok = !false;
        } else{
          m_errorMessage = L"JSON document must be started with JSON object or array.";
        }
      } else{
        m_errorMessage = L"JSON output stream is corrupted.";
      }
      return _is_ok;
    }

    bool JSONWriter::writeToFile( const String& fileName ){
      bool _is_ok = false;

      if( !fileName.empty() ){
        std::wofstream _output_file_stream;
        _output_file_stream.imbue( std::locale( "" ) );
        _output_file_stream.open( fileName, std::ios::out );
        if( _output_file_stream.is_open() ){
          _is_ok = writeToOutputStream( _output_file_stream );
        } else{
          m_errorMessage = L"File path:" + fileName + L" can not be open."; 
        }
        _output_file_stream.close();
      } else{
        m_errorMessage = L"File name is empty.";
      }
      return  _is_ok;
    }

    bool JSONWriter::writeToString( String& out_str ){
      bool _is_ok = false;
      const auto& _writable_root_value = m_rootValue;
      
      if( _writable_root_value.isJSONObject() || _writable_root_value.isJSONArray() ){
        out_str = m_rootValue.toString();
        _is_ok = !false;
      } else{
        m_errorMessage = L"JSON document must be started with JSON object or array.";
      }    
      return _is_ok;
    }
  }
}