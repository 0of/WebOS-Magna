#include "JSONValue.h"

#include "JSONObject.h"
#include "JSONArray.h"

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
        PrivateData( String * const _init_value );
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

    JSONValue::PrivateData::PrivateData( String * const _init_value )
      :m_data()
      ,m_type( JSONValue::ValueType_String ){
      ::memset( &m_data, 0, sizeof ( decltype( m_data ) ) );
      m_data.m_stringData = _init_value;
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
      ,m_type( JSONValue::ValueType_Array ){
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
          if( Nullptr != m_data.m_arrayData ){
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
      :m_data()
      ,m_type( JSONValue::ValueType_Invalid ){

    }

    JSONValue::JSONValue( const sint32 init_value)
      :m_data( new PrivateData( init_value ) )
      ,m_type( JSONValue::ValueType_Int ){

    }

    JSONValue::JSONValue( const uint32 init_value )
      :m_data( new PrivateData( init_value ) )
      ,m_type( JSONValue::ValueType_UInt ){

    }

    JSONValue::JSONValue( const double& init_value)
      :m_data( new PrivateData( init_value ) )
      ,m_type( JSONValue::ValueType_Double ){

    }

    JSONValue::JSONValue( const bool init_value )
      :m_data()
      ,m_type( init_value != false ? ValueType_True : ValueType_False ){

    }

    JSONValue::JSONValue( const String& str)
      :m_data( new PrivateData( new String(str) ) )
      ,m_type( JSONValue::ValueType_String ){

    }

    JSONValue::JSONValue( const void *)
      :m_data()
      ,m_type( JSONValue::ValueType_Null ){

    }

    JSONValue::JSONValue( const JSONObject& object)
      :m_data( new PrivateData( new JSONObject( object ) ) )
      ,m_type( JSONValue::ValueType_Object ){

    }

    JSONValue::JSONValue( const JSONArray& arr)
      :m_data( new PrivateData( new JSONArray( arr ) ) )
      ,m_type( JSONValue::ValueType_Array ){

    }


    JSONValue::JSONValue( const JSONValue& value )
      :m_data( value.m_data )
      ,m_type( value.m_type ){

    }

    JSONValue& JSONValue::operator= ( const JSONValue& value){
      m_data = value.m_data;
      m_type = value.m_type;
      return *this;
    }

    bool JSONValue::asInt( sint32& _out_value ){
      bool _is_int = (!m_data.isNull() && m_data->m_type == JSONValue::ValueType_Int);
      if( _is_int ){
        _out_value = m_data->m_data.m_intData;
      }
      return _is_int;
    }

    bool JSONValue::asUInt( uint32& _out_value ){
      bool _is_uint =  (!m_data.isNull() && m_data->m_type == JSONValue::ValueType_UInt);
      if( _is_uint ){
        _out_value = m_data->m_data.m_uintData;
      }
      return _is_uint ;
    }

    bool JSONValue::asDouble( double& _out_value ){
      bool _is_double = (!m_data.isNull() && m_data->m_type == JSONValue::ValueType_Double);
      if( _is_double ){
        _out_value = m_data->m_data.m_doubleData;
      }
      return _is_double ;
    }

    bool JSONValue::asString( String& _out_value ){
      bool _is_string = (!m_data.isNull() && m_data->m_type == JSONValue::ValueType_String);
      if( _is_string ){
        auto *_string_data = m_data->m_data.m_stringData;
        if( Nullptr != _string_data ){
          _out_value = *_string_data;
        }
      }
      return _is_string ;
    }

    bool JSONValue::asJSONObject( JSONObject& _out_obj) const{
      bool _is_json_obj = (!m_data.isNull() && m_data->m_type == JSONValue::ValueType_Object);
      if( _is_json_obj ){
        auto *_obj_data = m_data->m_data.m_objectData;
        if( Nullptr != _obj_data ){
          _out_obj = *_obj_data;
        }
      }
      return _is_json_obj ;
    }

    bool JSONValue::asJSONArray( JSONArray& _out_array ) const{
      bool _is_json_array = (!m_data.isNull() && m_data->m_type == JSONValue::ValueType_Array);
      if( _is_json_array ){
        auto *_array_data = m_data->m_data.m_arrayData;
        if( Nullptr != _array_data ){
          _out_array = *_array_data;
        }
      }
      return _is_json_array ;
    }

    String JSONValue::toString() const{
      String _value_string;
      if( !m_data.isNull() ){
        OutStringStream _convertor;
        switch( m_data->m_type ){
        case JSONValue::ValueType_Object:
          if( Nullptr != m_data->m_data.m_objectData ){
            _value_string = m_data->m_data.m_objectData->toString();
          } break;

        case JSONValue::ValueType_Array:
          if( Nullptr != m_data->m_data.m_objectData ){
            _value_string = m_data->m_data.m_arrayData->toString();
          } break;

        case JSONValue::ValueType_String:
          if( Nullptr != m_data->m_data.m_stringData ){
            _value_string.push_back('\"');
            _value_string.append( *m_data->m_data.m_stringData );
            _value_string.push_back('\"');
          } break;

          case JSONValue::ValueType_Int:
            _convertor << m_data->m_data.m_intData;
            _value_string.append( _convertor.str() );
            break;

          case JSONValue::ValueType_UInt:
            _convertor << m_data->m_data.m_uintData;
            _value_string.append( _convertor.str() );
            break;

          case JSONValue::ValueType_Double:
            _convertor << m_data->m_data.m_doubleData;
            _value_string.append( _convertor.str() );
            break;

          default:
            break;
        }
      }

      if( isValid() ){
        switch( m_type ){
          case ValueType_True:
            _value_string = L"true";
            break;

          case ValueType_Null:
            _value_string = L"null";
            break;

          case ValueType_False:
            _value_string = L"false";
            break;

          default:
            break;
        }
      }
      return _value_string;
    }

  }
}//namespace Magna