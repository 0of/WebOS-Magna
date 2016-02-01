#ifndef JSONVALUE_H
#define JSONVALUE_H

#include "basedef_lib.h"

#include "BaseTypes.h"
#include "SystemDef.h"
#include "String.h"
#include "SharedPtr.h"

namespace Magna{
  namespace Core{
    class JSONObject;
    class JSONArray;

    //!    A value stores variable type data.
    class BASEDEF_LIB_EXPORT JSONValue{
    public:
      //!    JSON value type. 
      enum ValueType{
        ValueType_Invalid,  /*!< default value */  
        ValueType_Null,  /*!< a constant 'null' */  
        ValueType_True,  /*!< a constant 'true' */  
        ValueType_False,  /*!< a constant 'false' */  
        ValueType_Int,  /*!< 32-bit integer type */  
        ValueType_UInt,  /*!< 32-bit unsigned integer type */  
        ValueType_Double,  /*!< double type */  
        ValueType_String,    /*!< wide char string */  
        ValueType_Object,  /*!< JSON object */  
        ValueType_Array  /*!< JSON array */  
      };

      public:
        //!    Default constructor
        JSONValue();

        //!    Constructor with 32-bit integer value
        JSONValue( const sint32 );

        //!    Constructor with unsigned 32-bit integer value
        JSONValue( const uint32 );

        //!    Constructor with double value
        JSONValue( const double& );

        //!    Constructor with String value
        JSONValue( const String& );

        //!    Constructor with bool value
        /*!  
         *    the given value determinates the ValueType::ValueType_True or ValueType::ValueType_False
         */
        JSONValue( const bool );

        //!    Constructor with Null type
        /*!  
         *    the given value determinates the ValueType::ValueType_Null
         */
        JSONValue( const void *);

        //!    Copy constructor
        JSONValue( const JSONValue& );

        //!    Constructor with JSONObject
        JSONValue( const JSONObject& );

        //!    Constructor with JSONArray
        JSONValue( const JSONArray& );

        //!    Assign constructor
        JSONValue& operator= ( const JSONValue& );

      public:
        //!    Check the JSONValue is valid
        inline bool isValid() const{
          return m_type != JSONValue::ValueType_Invalid;
        }

        //!    Check the JSONValue is a integer
        inline bool isInt() const{
          return m_type == JSONValue::ValueType_Int;
        }

        //!    Check the JSONValue is a unsigned integer
        inline bool isUInt() const{
          return m_type == JSONValue::ValueType_UInt;
        }

        //!    Check the JSONValue is a double
        inline bool isDouble() const{
          return m_type == JSONValue::ValueType_Double;
        }

        //!    Check the JSONValue is a 'null' constant
        inline bool isNull() const{
          return m_data.isNull() || m_type == JSONValue::ValueType_Null;
        }

        //!    Check the JSONValue is a JSONObject
        inline bool isJSONObject() const{
          return m_type == JSONValue::ValueType_Object;
        }

        //!    Check the JSONValue is a JSONArray
        inline bool isJSONArray() const{
          return m_type == JSONValue::ValueType_Array;
        }

        //!    Check the JSONValue is true
        inline bool isTrue() const{
          return m_type == JSONValue::ValueType_True;
        }

        //!    Check the JSONValue is false
        inline bool isFalse() const{
          return m_type == JSONValue::ValueType_False;
        }

        //!    Check the JSONValue is a String
        inline bool isString() const{
          return m_type == JSONValue::ValueType_String;
        }

      public:
        //!    Cast the value to sint32
        /*!  
         *    \return true means OK to cast.    
         */
        bool asInt( sint32& );

        //!    Cast the value to uint32
        /*!  
         *    \return true means OK to cast.    
         */
        bool asUInt( uint32& );

        //!    Cast the value to double
        /*!  
         *    \return true means OK to cast.    
         */
        bool asDouble( double& );

        //!    Cast the value to String
        /*!  
         *    \return true means OK to cast.    
         */
        bool asString( String& );

        //!    Cast the value to JSONObject
        /*!  
         *    \return true means OK to cast.    
         */
        bool asJSONObject( JSONObject& ) const;

        //!    Cast the value to JSONArray
        /*!  
         *    \return true means OK to cast.    
         */
        bool asJSONArray( JSONArray& ) const;

        //!  Serialize all its value to string
        String toString() const;

      public:
        //!    Get the type
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