#include "JSONValue.h"

#include "JSONArray.h"
#include "JSONObject.h"


namespace Magna{
  namespace Core{

    namespace Private{
      typedef union _JSONValueData{    
        uint32 m_uintData;
        sint32 m_intData;
        double m_doubleData;
        String *m_stringData;
        JSONObject *m_objectData;
        JSONArray *m_arrayData;
      } JSONValueData;
    }

    class JSONValue::PrivateData{
      public:
        JSONValue::ValueType m_type;
        Private::JSONValueData m_data;

      public:
        PrivateData();
        PrivateData( const sint32 _init_value );
        PrivateData( const uint32 _init_value );
        PrivateData( const double& _init_value );
        PrivateData( const bool _init_value );
        PrivateData( JSONObject * const _init_value );
        PrivateData( JSONArray * const _init_value );
        ~PrivateData();
    };
  
    //Private Data {
    JSONValue::PrivateData::PrivateData()
      :m_data()
      ,m_type( JSONValue::ValueType_Null ){
      ::memset( &m_data, 0, sizeof ( decltype( m_data ) ) );
    }

    JSONValue::PrivateData::PrivateData( const sint32 _init_value )
      :m_data()
      ,m_type( JSONValue::ValueType_Int ){
      ::memset( &m_data, 0, sizeof ( decltype( m_data ) ) );
      m_data.m_intData = _init_value;
    }

    JSONValue::PrivateData::PrivateData( const uint32 _init_value )
      :m_data()
      ,m_type( JSONValue::ValueType_UInt ){
      ::memset( &m_data, 0, sizeof ( decltype( m_data ) ) );
      m_data.m_uintData = _init_value;
    }

    JSONValue::PrivateData::PrivateData( const double& _init_value )
      :m_data()
      ,m_type( JSONValue::ValueType_Double ){
      ::memset( &m_data, 0, sizeof ( decltype( m_data ) ) );
      m_data.m_doubleData = _init_value;
    }

    JSONValue::PrivateData::PrivateData( const bool _init_value )
      :m_data()
      ,m_type( _init_value != false ? ValueType_True : ValueType_False ){
      ::memset( &m_data, 0, sizeof ( decltype( m_data ) ) );
    }

    JSONValue::PrivateData::PrivateData( JSONObject * const _init_value )
      :m_data()
      ,m_type( JSONValue::ValueType_Object ){
      ::memset( &m_data, 0, sizeof ( decltype( m_data ) ) );
      m_data.m_objectData = _init_value;
    }

    JSONValue::PrivateData::PrivateData( JSONArray * const _init_value )
      :m_data()
      ,m_type( JSONValue::ValueType_Object ){
      ::memset( &m_data, 0, sizeof ( decltype( m_data ) ) );
      m_data.m_arrayData = _init_value;
    }

    JSONValue::PrivateData::~PrivateData(){
      switch( m_type ){
        case JSONValue::ValueType_Object:{
          if( Nullptr != m_data.m_objectData ){
            delete m_data.m_objectData;
            m_data.m_objectData = Nullptr;
          }
        } break;

        case JSONValue::ValueType_Array:{
          if( Nullptr != m_data.m_objectData ){
            delete m_data.m_arrayData;
            m_data.m_arrayData = Nullptr;
          }
        } break;

        case JSONValue::ValueType_String:{
          if( Nullptr != m_data.m_stringData ){
            delete m_data.m_stringData;
            m_data.m_stringData = Nullptr;
          }
        } break;
        
        default:
          break;
      }
    }

    //  } Private Data 

    JSONValue::JSONValue()
      :m_data(){

    }

    JSONValue::JSONValue( const sint32 init_value)
      :m_data( new PrivateData( init_value ) ){

    }

    JSONValue::JSONValue( const uint32 init_value )
      :m_data( new PrivateData( init_value ) ){

    }

    JSONValue::JSONValue( const double& init_value)
      :m_data( new PrivateData( init_value ) ){

    }

    JSONValue::JSONValue( const bool init_value )
      :m_data( new PrivateData( init_value ) ){

    }



    JSONValue::JSONValue( const JSONValue& value )
      :m_data( value.m_data ){

    }

    JSONValue& JSONValue::operator= ( const JSONValue& value){
      m_data = value.m_data;
      return *this;
    }

    bool JSONValue::isInt() const{
      return !m_data.isNull() && m_data->m_type == JSONValue::ValueType_Int;
    } 

    bool JSONValue::isUInt() const{
      return !m_data.isNull() && m_data->m_type == JSONValue::ValueType_UInt;
    }

    bool JSONValue::isDouble() const{
      return !m_data.isNull() && m_data->m_type == JSONValue::ValueType_Double;
    }

    bool JSONValue::isNull() const{
      return m_data.isNull() || m_data->m_type == JSONValue::ValueType_Null;
    }

    bool JSONValue::isJSONObject() const{
      return !m_data.isNull() && m_data->m_type == JSONValue::ValueType_Object;
    }

    bool JSONValue::isJSONArray() const{
      return false;
    }

    bool JSONValue::isTrue() const{
      return !m_data.isNull() && m_data->m_type == JSONValue::ValueType_True;
    }

    bool JSONValue::isFalse() const{
      return !m_data.isNull() && m_data->m_type == JSONValue::ValueType_False;
    }

    bool JSONValue::isString() const{
      return !m_data.isNull() && m_data->m_type == JSONValue::ValueType_String;
    }

    bool JSONValue::asInt( sint32& _out_value ){
      bool _is_int = isInt();
      if( _is_int ){
        _out_value = m_data->m_data.m_intData;
      }
      return _is_int;
    }

    bool JSONValue::asUInt( uint32& _out_value ){
      bool _is_uint = isUInt();
      if( _is_uint ){
        _out_value = m_data->m_data.m_uintData;
      }
      return _is_uint ;
    }

    bool JSONValue::asDouble( double& _out_value ){
      bool _is_double = isDouble();
      if( _is_double ){
        _out_value = m_data->m_data.m_doubleData;
      }
      return _is_double ;
    }

    bool JSONValue::asString( String& _out_value ){
      bool _is_string = isString();
      if( _is_string ){
        auto *_string_data = m_data->m_data.m_stringData;
        if( Nullptr != _string_data ){
          _out_value = *_string_data;
        }
      }
      return _is_string ;
    }

    bool JSONValue::asJSONObject( JSONObject& _out_obj) const{
      bool _is_json_object = isJSONObject();
      if( _is_json_object ){
        auto *_object_data = m_data->m_data.m_objectData;
        if( Nullptr != _object_data ){
          _out_obj = *_object_data;
        }
      }
      return _is_json_object;
    }

    bool JSONValue::asJSONArray( JSONArray& _out_array) const{
      bool _is_json_array = isJSONArray();
      if( _is_json_array ){
        auto *_array_data = m_data->m_data.m_arrayData;
        if( Nullptr != _array_data ){
          _out_array = *_array_data;
        }
      }
      return _is_json_array;
    }

  }
}//namespace Magna