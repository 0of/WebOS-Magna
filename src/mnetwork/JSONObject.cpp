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

  }
}
