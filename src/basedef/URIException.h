#ifndef URIEXCEPTION_H
#define URIEXCEPTION_H

#include <stdexcept>

#include "String.h"

namespace Magna{
    namespace Core{
        class URIException : public std::exception{
            public:
                URIException( const String& uri_string, const String& message );
                virtual ~URIException();

            protected:
                String m_URIString;
        };

        class URISyntaxException : public URIException{
            public:
                URISyntaxException( const String& uri_string, const String& message );
                virtual ~URISyntaxException();
        };
    }
}

#endif  /*  URIEXCEPTION_H  */