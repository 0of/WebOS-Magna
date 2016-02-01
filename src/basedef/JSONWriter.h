#ifndef JSONWRITER_H
#define JSONWRITER_H

#include "basedef_lib.h"

#include <ostream>

#include "String.h"
#include "JSONValue.h"

namespace Magna{
  namespace Core{

    class BASEDEF_LIB_EXPORT JSONWriter{
      public:
        JSONWriter();
        JSONWriter( const JSONValue& );
        virtual ~JSONWriter();

      public:
        inline JSONWriter &setWriteRootValue( const JSONValue& value){
          m_rootValue = value;
          return *this;
        }

        bool writeToOutputStream( std::wostream& out);
        bool writeToFile( const String& fileName );
        bool writeToString( String& out_str );

        inline String getLastErrorMessage() const{
          return m_errorMessage;
        }

      private:
        JSONValue m_rootValue;
        String m_errorMessage;
    };

  }
}

#endif  /*  JSONWRITER_H  */