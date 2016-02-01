#include "JSONArray.h"

#include "JSONValue.h"

namespace Magna{
  namespace Core{

    JSONArray::JSONArray()
      :m_elements(){

    }

    JSONArray::JSONArray( const JSONArray& arr)
      :m_elements( arr.m_elements ){

    }

    JSONArray::JSONArray( JSONArray&& arr)
      :m_elements( arr.m_elements ){
      arr.m_elements = Elements();
    }

    JSONArray::JSONArray( const std::vector<JSONValue>& values)
      :m_elements( new std::vector<JSONValue>() ){

      m_elements->insert( m_elements->end(), values.begin(), values.end() );

    }

    JSONArray::~JSONArray(){

    }

    JSONArray & JSONArray::operator = ( const std::vector<JSONValue>& values){
      if( m_elements.hasReferences() ||  m_elements.isNull() ){
        m_elements = Elements( new std::vector<JSONValue>() );        
      } else{
        m_elements->clear();
      }
      m_elements->insert( m_elements->end(), values.begin(), values.end());
      return *this;
    }

    JSONArray & JSONArray::operator = ( const JSONArray& arr ){
      m_elements = arr.m_elements;
      return *this;
    }

    JSONArray & JSONArray::operator = ( JSONArray&& arr ){
      m_elements = arr.m_elements;
      arr.m_elements = Elements();
      return *this;
    }

    JSONValue JSONArray::operator[] ( const uint32 index){
      return at(index);
    }

    const JSONValue JSONArray::operator[] ( const uint32 index ) const{
      JSONValue _return_value;
      if( !m_elements.isNull() && index < m_elements->size() ){
        _return_value = m_elements->at(index);
      }
      return _return_value;
    }

    JSONValue JSONArray::at( const uint32 index ){
      JSONValue _return_value;
      if( !m_elements.isNull() && index < m_elements->size() ){
        _return_value = m_elements->at(index);
      }
      return _return_value;
    }

    void JSONArray::appendValue( const JSONValue& value){
      if( value.isValid() ){
        if( m_elements.isNull()  ){
          m_elements = Elements( new std::vector<JSONValue>() );          
        }

        m_elements->push_back( value );
      }
    }

  }
}//namespace Magna