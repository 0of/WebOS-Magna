#ifndef URIENCODER_H
#define URIENCODER_H

#include "String.h"

namespace Magna{
    namespace Core{
        class URIEncoder{
            public:
                static String URIEncode( const String& input_uri_string );
                static String dataEncode( const String& input_uri_string );
        };
    }
}

#endif  /*  URIENCODER_H    */