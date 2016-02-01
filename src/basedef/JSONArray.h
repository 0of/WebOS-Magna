#ifndef JSONARRAY_H
#define JSONARRAY_H

#include "basedef_lib.h"

#include "BaseTypes.h"
#include "SystemDef.h"
#include "String.h"
#include "SharedPtr.h"

namespace Magna{
  namespace Core{

    class JSONValue;

    //!    JSON array
    class BASEDEF_LIB_EXPORT JSONArray{
      __Definitions private:
        typedef SharedPtr<std::vector<JSONValue> > Elements;

      __Constructor_Destructor public:
        //!    Default constructor
        JSONArray();
        //!    Copy constructor
        JSONArray( const JSONArray& );

        //!    RV-reference constructor
        JSONArray( JSONArray&& );

        //!    Constructor with a vector of JSONValue s
        explicit JSONArray( const std::vector<JSONValue>& );

        //!    Destructor
        ~JSONArray();

      __Overloaded_Methods public:
        //!    Assign operator with a vector of JSONValue s
        JSONArray & operator = ( const std::vector<JSONValue>& );

        //!    Assign operator
        JSONArray & operator = ( const JSONArray&  );

        //!    RV-reference Assign operator
        JSONArray & operator = ( JSONArray&& );    

        //!    Index operator
        JSONValue operator[] ( const uint32 );

        //!    Index operator
        const JSONValue operator[] ( const uint32 ) const;

      public:
        //!    Append JSONValue 
        void appendValue( const JSONValue& );

        //!    Serialize all its children to strings
        String toString() const;

      __Getter public:
        //!    Get the length of the JSONArray
        inline uint32 getLength() const{
          return m_elements.isNull() ? 0 : m_elements->size();
        }

        //!    Get the JSONValue by id
        /*!  
         *    \param index
         *      if index > getLength() , it'll returns a invalid JSONValue  
         */
        JSONValue at( const uint32 index);

      __Checker public:
        //!    Check the array is empty
        inline bool isEmpty() const{
          return m_elements.isNull() ? 0 : m_elements->empty();
        }

      __Data_Field private:      
        Elements m_elements;
    };

  }
}//namespace Magna

#endif  /*  JSONARRAY_H  */