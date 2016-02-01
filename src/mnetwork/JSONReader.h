#ifndef JSONREADER_H
#define JSONREADER_H

#include <fstream>

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/String.h"
using namespace Magna::Core;

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
    class JSONReader{
      public:
        //!  Default constructor
        JSONReader();

        //!  Constructor with file path as parameter
        /*
          *    \param filePath
          *      a file path string 
          */
        JSONReader( const String& filePath );

        //!  Constructor with w_char input file stream
        /*
          *    \param stream
          *      must be a already open file stream.
          */
        JSONReader( std::wifstream& stream );

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
        bool readFromFile( const String& filePath );
        bool readFromFileStream( std::wifstream& stream );
        bool readFromString( String::const_iterator start, String::const_iterator end );
        bool readFromString( const unicode_char* data, const uint32 size );

        JSONValue getRootValue() ;
        String getLastErrorMessage() const;

      private:
        JSONValue m_rootValue;
        String m_errorMessage;
    };

  }
}//namespace Magna


#endif  /*  JSONREADER_H  */