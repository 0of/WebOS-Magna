#ifndef JSONVALUE_H
#define JSONVALUE_H

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/String.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

namespace Magna{
  namespace Core{
    class JSONObject;
    class JSONArray;
    class JSONValue{
    public:
      enum ValueType{
        ValueType_Invalid,
        ValueType_Null,
        ValueType_True,
        ValueType_False,
        ValueType_Int,
        ValueType_UInt,
        ValueType_Double,
        ValueType_String,
        ValueType_Object,
        ValueType_Array
      };

      public:
        JSONValue();
        JSONValue( const sint32 );
        JSONValue( const uint32 );
        JSONValue( const double& );
        JSONValue( const String& );
        JSONValue( const bool );
        // null type
        JSONValue( const void *);
        JSONValue( const JSONValue& );
        JSONValue( const JSONObject& );
        JSONValue( const JSONArray& );
        JSONValue& operator= ( const JSONValue& );

      public:
        bool isValid() const;
        bool isInt() const;
        bool isUInt() const;
        bool isDouble() const;
        bool isNull() const;
        bool isJSONObject() const;
        bool isJSONArray() const;
        bool isTrue() const;
        bool isFalse() const;
        bool isString() const;

      public:
        bool asInt( sint32& );
        bool asUInt( uint32& );
        bool asDouble( double& );
        bool asString( String& );
        bool asJSONObject( JSONObject& ) const;
        bool asJSONArray( JSONArray& ) const;

      public:
        inline ValueType getType() const{
          return m_type;
        }

      private:
        class PrivateData;
        SharedPtr< PrivateData > m_data;
        ValueType m_type;
    };
  } 
}//namespace Magna

#endif  /*  JSONVALUE_H  */