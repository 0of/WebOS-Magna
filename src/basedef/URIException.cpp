#include "URIException.h"

namespace Magna{
    namespace Core{

        URIException::URIException( const String& uri_string, const String& message )
            :std::exception( message.toString().c_str() )
            ,m_URIString( uri_string ){

        }

        URIException::~URIException(){

        }

        URISyntaxException::URISyntaxException( const String& uri_string, const String& message )
            :URIException( uri_string, message ){

        }

        URISyntaxException::~URISyntaxException(){

        }
    }
}