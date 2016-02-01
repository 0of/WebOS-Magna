#ifndef JSONREADER_H
#define JSONREADER_H

#include "basedef_lib.h"

#include <fstream>

#include "BaseTypes.h"
#include "SystemDef.h"
#include "String.h"

#include "JSONValue.h"

namespace Magna{
  namespace Core{

        //!  a applicable interface for JSON parsing.
        /*
        *  The class represents a JSON document reader for parsing
        *  a string stream or a file stream. When all parsing done, 
        *  it'll return a JSONValue. If all works perfectly, no error message 
        *  would be pop up and the return value -- a JSONValue, as a root value,
        *  shall be a valid value.
        */
        class BASEDEF_LIB_EXPORT JSONReader{
      public:
        //!  Default constructor
        JSONReader();

        //!  Constructor with file path as parameter
        /*
          *    \param filePath
          *      a file path string 
          */
        JSONReader( const String& filePath );

        //!  Constructor with input stream
        /*
          *    \param stream
          *      a input stream.
          */
        JSONReader( std::wistream& stream );

        //!  Constructor with string iterator start and end
        /*
          *    \param start
          *      string iterator start.
          *    \param end
          *      string iterator end.
          */
        JSONReader( String::const_iterator start, String::const_iterator end );

        //!  Constructor with string plain data and its size.
        /*
          *    \param data
          *      a const pointer to data
          *    \param size
          *      data size.
          */
        JSONReader( const unicode_char* data, const uint32 size);
        virtual ~JSONReader();

      public:
        //!  Read JSON from file
        /*
          *    \param filePath
          *      a file path string 
          *    \return 
          *      true means parsing ok, otherwise false
          */
        bool readFromFile( const String& filePath );

        //!  Read JSON from input stream
        /*
          *    \param stream
          *      a input stream.
          *    \return 
          *      true means parsing ok, otherwise false
          */
        bool readFromStream( std::wistream& stream );

        //!  Read JSON with string iterator start and end
        /*
          *    \param start
          *      string iterator start.
          *    \param end
          *      string iterator end.
          *    \return 
          *      true means parsing ok, otherwise false
          */
        bool readFromString( String::const_iterator start, String::const_iterator end );

        //!  Constructor with string plain data and its size.
        /*
          *    \param data
          *      a const pointer to data
          *    \param size
          *      data size.
          *    \return 
          *      true means parsing ok, otherwise false
          */
        bool readFromString( const unicode_char* data, const uint32 size );

        //!    get the root value
        inline JSONValue getRootValue() {
          return m_rootValue;
        }
        //!    get the last error message
        inline String getLastErrorMessage() const{
          return m_errorMessage;
        }

      private:
        JSONValue m_rootValue;
        String m_errorMessage;
    };

  }
}//namespace Magna


#endif  /*  JSONREADER_H  */