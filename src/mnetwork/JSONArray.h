#ifndef JSONARRAY_H
#define JSONARRAY_H

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/String.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

namespace Magna{
  namespace Core{

    class JSONValue;
    class JSONArray{
      __Definitions private:
        typedef SharedPtr<std::vector<JSONValue> > Elements;

      __Constructor_Destructor public:
        JSONArray();
        JSONArray( const JSONArray& );
        JSONArray( JSONArray&& );
        //JSONArray( std::initializer_list<JSONValue> );
        explicit JSONArray( const std::vector<JSONValue>& );
        ~JSONArray();

      __Overloaded_Methods public:
        JSONArray & operator = ( const std::vector<JSONValue>& );
        JSONArray & operator = ( const JSONArray&  );
        JSONArray & operator = ( JSONArray&& );    
        JSONValue operator[] ( const uint32 );
        const JSONValue operator[] ( const uint32 ) const;

      public:
        void appendValue( const JSONValue& );

      __Getter public:
        inline uint32 getLength() const{
          return m_elements.isNull() ? 0 : m_elements->size();
        }
        JSONValue at( const uint32 );

      __Checker public:
        inline bool isEmpty() const{
          return m_elements.isNull() ? 0 : m_elements->empty();
        }

      __Data_Field private:      
        Elements m_elements;
    };

  }
}//namespace Magna

#endif  /*  JSONARRAY_H  */