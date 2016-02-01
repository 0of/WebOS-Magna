#include "JSONObject.h"

#include "JSONValue.h"

namespace Magna{
  namespace Core{

    JSONObject::JSONObject()
      :m_members(){

    }

    JSONObject::~JSONObject(){

    }

    JSONObject::JSONObject( const JSONObject& _object)
      :m_members( _object.m_members ){

    }

    JSONObject& JSONObject::operator = ( const JSONObject& _object ){
      m_members = _object.m_members;
      return *this;
    }

    void JSONObject::emplace( const String& key, const JSONValue& value ){
      if( !key.empty() && value.isValid() ){
        if( m_members.isNull() ){
          m_members = new std::map<String, JSONValue>();
        }
        m_members->insert( m_members->end(), std::make_pair( key, value ) );
      }
    }

    JSONValue JSONObject::operator [] ( const String& key ){
      return getBy( key );
    }

    const JSONValue JSONObject::operator [] ( const String& key ) const{
      return getBy( key );
    }

    JSONValue JSONObject::getBy( const String& key ){
      JSONValue _value;
      if( !m_members.isNull() ){
        auto _found = m_members->find( key );
        if( m_members->end() != _found ){
          _value = _found->second;
        }
      }
      return _value;
    }

    const JSONValue JSONObject::getBy( const String& key ) const{
      JSONValue _value;
      if( !m_members.isNull() ){
        auto _found = m_members->find( key );
        if( m_members->end() != _found ){
          _value =  _found->second;
        }
      }
      return _value;
    }

    String JSONObject::toString() const{
      String _json_obj_string;
      if( !m_members.isNull() ){
        _json_obj_string.push_back( L'{' );  //start symbol

        uint32 _element_counter = 0;

        for( auto _each_pair = m_members->begin(); m_members->end() != _each_pair ; ++_each_pair ){
          _json_obj_string.push_back( L'\"' );
          _json_obj_string.append( _each_pair->first );
          _json_obj_string.push_back( L'\"' );
          _json_obj_string.push_back( L':' );
          _json_obj_string.append( _each_pair->second.toString() );
      
          if( m_members->size() != ++_element_counter ){
            _json_obj_string.push_back( L',' );
          }
        }
        _json_obj_string.push_back( L'}' );
      }
      return _json_obj_string;
    }

  }
}
