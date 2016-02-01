#ifndef URI_H
#define URI_H

#include <map>

#include "String.h"
#include "SharedPtr.h"

namespace Magna{
    namespace Core{


        //!     see more details http://tools.ietf.org/html/rfc3986
        //
        class URI{
            __Definitions public:
                typedef std::map<String, String> QueryParameters;

        public:
            URI();
            URI( const String& uriString );
            URI( const URI& uri );
            ~URI();

        public:
            URI& operator = ( const URI& uri );
            bool operator == ( const URI& uri );
            bool operator != ( const URI& uri );

        public:
            String getFragment() const;
            String getScheme() const;
            String getQuery() const;
            String getQueryParameterValue( const String& key ) const;
            QueryParameters getAllQueryParameters() const;
            uint16 getPort() const;
            String getHostString() const;

            bool isLocal() const;
            bool isRelative() const;
            bool isAbsolute() const;

        private:
            class PrivateData;
            SharedPtr<PrivateData> m_data;
        };
    }
}

#endif  /*  URI_H   */