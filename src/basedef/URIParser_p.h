#ifndef URIPARSER_P_H
#define URIPARSER_P_H

#include <map>

#include "BaseTypes.h"
#include "SystemDef.h"
#include "String.h"

namespace Magna{
    namespace Core{

        namespace Private{
            typedef String::size_type Shift;
            typedef std::pair<Shift, Shift> Range;
        }

        class URIParseContext{
            __Definitions public:
                enum ParseHierPart{
                    Scheme = 0
                    ,Authority = 1
                    ,UserInfo = 2
                    ,Host = 3
                    ,Path = 4
                    ,Port = 5
                    ,Query = 6
                    ,Fragment = 7
                    ,End = 8
                };
                typedef std::map<ParseHierPart, String > ParsedParts;

            __Constructor_Destructor public:
                URIParseContext( const String& _uri_string );
                ~URIParseContext();

            public:
                inline void switchParseHierPart( ParseHierPart _part ){
                    if( End != m_parsingPart && m_parsingPart != _part ){
                        m_parsingPart = _part;
                    }
                }

                // called after switching part successfully
                // record parsing part which turns to parsed state
                inline void recordParsedHierPart( const Private::Shift _start, const Private::Shift _part_end ){
                    m_parsedParts[ m_parsingPart ] = String( _uriString + _start, _part_end - _start );
                }

                inline void updateReadAt( const Private::Shift _read_at ){ m_readAt = _read_at; }

                inline void putTrackAt( const Private::Shift _track_at ){ m_trackAt = _track_at; }
                inline void putErrorMessage( const String _error_message ){ m_errorMessage = _error_message; }

            __Getter public:
                inline ParseHierPart getParseHierPart() const{ return m_parsingPart; }
                inline Private::Shift getReadAt() const { return m_readAt; }
                inline Private::Shift getTrackAt() const { return m_trackAt; }
                inline const String& getErrorMessage() const { return m_errorMessage; }
                inline ParsedParts & getParsedParts() { return m_parsedParts; }

            __Data_Field public:
                const unicode_char* _uriString;
                const Private::Shift _uriStringLength;

            __Data_Field private:
                ParseHierPart m_parsingPart;
                Private::Shift m_readAt;
                ParsedParts m_parsedParts;

                // exception 
                String m_errorMessage;
                Private::Shift m_trackAt;
        };

        
        class CharacterChecker{
        public:
            inline static bool isUnencodedChar( unicode_char _char ){
                return isUnreserved( _char ) || isSubDelims( _char ) || isGenDelims( _char );
            }

            inline static bool isAlphabetic( unicode_char _char ){
                return ( _char < L'Z' && _char > L'A' )
                    || ( _char < L'z' && _char > L'a' );
            }

            inline static bool isDigit( unicode_char _char ){
                return _char < L'9' && _char > L'0';
            }

            // "!" / "$" / "&" / "'" / "(" / ")"
            // / "*" / "+" / "," / ";" / "="
            inline static bool isSubDelims( unicode_char _char ){
                return _char == L'!' || _char == L'$' || _char == L'&'
                    || _char == L'\'' || _char == L'(' || _char == L')' || _char == L'*'
                    || _char == L'+' || _char == L',' || _char == L';' || _char == L'=';
            }

            // ALPHA / DIGIT / "-" / "." / "_" / "~"
            inline static bool isUnreserved( unicode_char _char ){
                return ( _char < L'Z' && _char > L'A' )
                    || ( _char < L'z' && _char > L'a' )
                    || ( _char < L'9' && _char > L'0' )
                    || _char == L'-'
                    || _char == L'.'
                    || _char == L'_'
                    || _char == L'~';
            }

            // gen-delims    = ":" / "/" / "?" / "#" / "[" / "]" / "@"
            inline static bool isGenDelims( unicode_char _char ){
                return _char == L':'
                    || _char == L'/'
                    || _char == L'?'
                    || _char == L'#'
                    || _char == L'['
                    || _char == L']'
                    || _char == L'@';
            }

            inline static bool isPathCharacter( unicode_char _char ){
                return isUnencodedChar( _char ) || _char == L'%' || _char == L'@' || _char == L':';
            }
        };
    }
}

#endif  /*  URIPARSER_P_H   */