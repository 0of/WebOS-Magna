#ifndef URIPARSER_H
#define URIPARSER_H

#include "URI.h"
// ### context can put to a new header file
#include "URIParser_p.h"

namespace Magna{
    namespace Core{
        
        // ### it's only for internal usage
        // parser
        class URIParser{
            public:
                URIParser( const String& uriString );
                ~URIParser();

            public:
                void doParse();
                inline String getLastError() const { return m_parseContext.getErrorMessage(); }

                void parsePortOut( uint16& _out_port );
                void parseQueryParametersOut( URI::QueryParameters& _out_parameters );

            __Getter public:
                inline URIParseContext::ParsedParts && takeParsedParts() { return std::move( m_parseContext.getParsedParts() ); }

            private:
                static bool parseSchema( URIParseContext& _parse_context );
                static bool parseAuthority( URIParseContext& _parse_context );
                static bool parseUserInfo( URIParseContext& _parse_context );
                static bool parseHost( URIParseContext& _parse_context );
                static bool parsePort( URIParseContext& _parse_context );
                static bool parsePath( URIParseContext& _parse_context );
                static bool parseQuery( URIParseContext& _parse_context );

                typedef bool(*ParseProcess)(URIParseContext&);
                ParseProcess getCurrentProcess() const;

                bool parseFragment( Private::Shift& _out_shift );
               
            private:
                String m_URIString;
                URIParseContext m_parseContext;
        };
    }
}

#endif  /*  URIPARSER_H */