#include "URIParser.h"

#include "StringConvertor.h"
#include "URIException.h"

namespace Magna{
    namespace Core{
        
        URIParseContext::URIParseContext( const String& _uri_string )
            :_uriString( _uri_string.c_str() )
            ,_uriStringLength( _uri_string.size() )
            ,m_readAt( 0 )
            ,m_errorMessage()
            ,m_trackAt( String::npos ){

        }

        URIParseContext::~URIParseContext(){

        }

        void URIParser::parsePortOut( uint16& _out_port ){
            auto &_parsed_part = m_parseContext.getParsedParts();
            auto _found_port = _parsed_part.find( URIParseContext::Port );
            if( _parsed_part.end() != _found_port ){
                try{
                    StringConvertor::toValue( _found_port->second, _out_port );
                }
                catch( const std::overflow_error& overflow_exception ){
                    throw URISyntaxException( m_URIString, L"Invalid port number " + _found_port->second );
                }
                catch( const NumberFormatException& format_exception ){
                    throw URIException( m_URIString, L"Unknown parse exception " + _found_port->second );
                }
            } else{
                // find the schema mapping port

            }
        }

        void URIParser::parseQueryParametersOut( URI::QueryParameters& _out_parameters ){
            const unicode_char _sub_delimit = L'=';
            const String _delimit = L"&";

            auto & _parsed_part = m_parseContext.getParsedParts();
            auto _found_query = _parsed_part.find( URIParseContext::Query );
            if( _parsed_part.end() != _found_query ){
                auto &&_query_param_pairs = _found_query->second.split( _delimit );
                for( auto _each_pair = _query_param_pairs.begin(); _query_param_pairs.end() != _each_pair; ++_each_pair ){
                    auto _sub_delimit_index = _each_pair->find( _sub_delimit );
                    if( String::npos != _sub_delimit_index ){
                        _out_parameters.insert( std::make_pair( _each_pair->substr( 0, _sub_delimit_index )
                            , _each_pair->substr( _sub_delimit_index ) ) );
                    } else{
                        // if not a key-value pair, the value of the parameter is assigned to empty
                        _out_parameters.insert( std::make_pair( *_each_pair, String::EmptyString ) );
                    }
                }
            }
        }

        URIParser::URIParser( const String& uriString )
            :m_URIString( uriString )
            ,m_parseContext( uriString ){

        }

        URIParser::~URIParser(){

        }

        void URIParser::doParse() {
            bool _parse_ok = !false;
            bool _reached_parsed_end = false;

            while( _parse_ok && !_reached_parsed_end ){
                if( m_parseContext.getParseHierPart() != URIParseContext::End ){
                    auto _each_process = getCurrentProcess();

                    if( Nullptr != _each_process ){
                        _parse_ok = ( *_each_process )( m_parseContext );
                    } else{
                        _reached_parsed_end = !false;
                    }
                } else{
                    _reached_parsed_end = !false;
                }
            }

            if( !_parse_ok ){
                String _execption_message = m_parseContext.getErrorMessage() + L"\n\t Tracking at : " + L" character in the parsing URI";
                throw URISyntaxException(m_URIString, _execption_message );
            }
        }

        URIParser::ParseProcess URIParser::getCurrentProcess() const{
            static URIParser::ParseProcess _process_series[] ={ parseSchema, parseAuthority
                , parseUserInfo, parseHost, parsePort, parsePath, parseQuery };

            auto _parsing_part = m_parseContext.getParseHierPart();
            return _parsing_part < URIParseContext::End ? _process_series[ _parsing_part ] : Nullptr;
        }

        // scheme = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
        // always at the beginning of the URI string
        bool URIParser::parseSchema( URIParseContext& _parse_context ){
            bool _error_occurred = false;
            bool _reached_schema_end = false;

            const Private::Shift _schema_start_at = _parse_context.getReadAt();

            Private::Shift _schema_read_at = _parse_context.getReadAt();
            URIParseContext::ParseHierPart _schema_next_part = _parse_context.getParseHierPart();

            while( !_error_occurred && !_reached_schema_end ){

                if( _schema_read_at < _parse_context._uriStringLength ){
                    unicode_char _each_char = *( _parse_context._uriString + _schema_read_at );

                    if( CharacterChecker::isAlphabetic( _each_char )
                        || CharacterChecker::isDigit( _each_char )
                        || _each_char == L'+'
                        || _each_char == L'-'
                        || _each_char == L'.' ){
                        ++_schema_read_at;
                    } else if( _each_char == L':' ){
                        // schema end
                        _schema_next_part = URIParseContext::Authority;
                        _reached_schema_end = !false;
                    } else if( _each_char == L'/' ){
                        if( _schema_start_at == _schema_read_at ){
                            // means no schema
                            // relative URI
                            _schema_next_part = URIParseContext::Path;
                            _reached_schema_end = !false;
                        } else{
                            // error
                            // invalid character for schema
                            _parse_context.putErrorMessage( L"Invalid character for schema");
                            _error_occurred = !false;
                        }
                    } else{
                        // error
                        // invalid character for schema
                        _parse_context.putErrorMessage( L"Invalid character for schema");
                        _error_occurred = !false;
                    }
                } else{ // reached the end of the URI
                    _parse_context.putErrorMessage( L"Invalid URI structure");
                    _error_occurred = !false;
                }
            }

            if( !_error_occurred ){
                _parse_context.recordParsedHierPart( _schema_start_at, _schema_read_at );

                _parse_context.updateReadAt( _schema_read_at );
                _parse_context.switchParseHierPart( _schema_next_part );
            } else{
                _parse_context.putTrackAt( _schema_read_at );
            }

            return !_error_occurred;
        }

        // authority   = [ userinfo "@" ] host [ ":" port ]
        bool URIParser::parseAuthority( URIParseContext& _parse_context ){
            bool _error_occurred = false;
            bool _is_hierarchical_URI = !false; // default true

            Private::Shift _authority_start_at = _parse_context.getReadAt();
            URIParseContext::ParseHierPart _authority_next_part = _parse_context.getParseHierPart();

            // pre-parse the first 3 characters for determining the UIR is hierarchical 
            // at least 3 characters
            if( ( _authority_start_at + 3 ) < _parse_context._uriStringLength ){
                if( L':' == *( _parse_context._uriString + _authority_start_at ) ){
                    // compare the sec & third char
                    auto _sec_char = *( _parse_context._uriString + _authority_start_at + 1 );
                    auto _third_char = *( _parse_context._uriString + _authority_start_at + 2 );

                    _authority_start_at += ( L'/' == _sec_char && L'/' == _third_char ) ? 3 : 1;
                    _parse_context.updateReadAt( _authority_start_at );
                    // not the correct read at index
                    // the value would be updated when finished parsed authority
                    _parse_context.switchParseHierPart( URIParseContext::UserInfo );
                    if( parseUserInfo( _parse_context ) && parseHost( _parse_context ) ){
                        _authority_next_part = _parse_context.getParseHierPart();
                        if ( _authority_next_part == URIParseContext::Port ){
                            _error_occurred = !parsePort( _parse_context );
                        } 
                    }

                } else{
                    // invalid character for URI
                    _parse_context.putErrorMessage( L"Invalid URI structure" );
                    _error_occurred = !false;
                }
            }

            if( !_error_occurred ){
                // switches to auth part first
                _parse_context.switchParseHierPart( URIParseContext::Authority );
                _parse_context.recordParsedHierPart( _authority_start_at, _parse_context.getReadAt() );

                // switches back to next part
                _parse_context.switchParseHierPart( _authority_next_part );
            } else{
                 _parse_context.putTrackAt( _authority_next_part );
            }

            return !_error_occurred;
        }

        bool URIParser::parseUserInfo( URIParseContext& _parse_context ){
            bool _error_occurred = false;

            bool _reached_string_end = false;
            bool _reached_user_info_end = false;
            bool _has_user_info_separator = false;

            const Private::Shift _userinfo_start_at = _parse_context.getReadAt();

            Private::Shift _userinfo_read_at = _userinfo_start_at;
            URIParseContext::ParseHierPart _userinfo_next_part = _parse_context.getParseHierPart();

            while( !_error_occurred && !_reached_user_info_end ){

                if( _userinfo_read_at < _parse_context._uriStringLength ){
                    unicode_char _each_char = *( _parse_context._uriString + _userinfo_read_at );
                    if( L'@' == _each_char ){
                        // end
                        _userinfo_next_part = URIParseContext::Host;
                        _reached_user_info_end = !false;
                    } else if( L':' == _each_char ){
                        ++_userinfo_read_at;
                        _has_user_info_separator = !false;
                    } else if( CharacterChecker::isUnreserved( _each_char )
                        || CharacterChecker::isSubDelims( _each_char )
                        || L'%' == _each_char ){
                        ++_userinfo_read_at;
                    } else{
                        _parse_context.putErrorMessage( L"Invalid Character for URI" );
                        _error_occurred = !false;
                    }
                } else{
                    // may end like this if there's no user info part 
                    _userinfo_next_part = URIParseContext::Host;
                    _reached_string_end = !false;
                }
            }

            if( _reached_user_info_end ){
                _parse_context.recordParsedHierPart( _userinfo_start_at, _userinfo_read_at );
                _parse_context.updateReadAt( _userinfo_read_at );
            }

            if( !_error_occurred ){
                _parse_context.switchParseHierPart( _userinfo_next_part );
            }

            return !_error_occurred;
        }

        // host = IP-literal / IPv4address / reg-name
        // IP-literal = "[" ( IPv6address / IPvFuture  ) "]"
        // IPv4address = dec-octet "." dec-octet "." dec-octet "." dec-octet
        // reg-name    = *( unreserved / pct-encoded / sub-delims )
        // 
        // any DNS-unresolved host name would be valid for URI resolving
        //
        bool URIParser::parseHost( URIParseContext& _parse_context ){
            bool _error_occurred = false;
            bool _reached_host_end = false;

            const Private::Shift _host_start_at = _parse_context.getReadAt();

            Private::Shift _host_read_at = _host_start_at;
            URIParseContext::ParseHierPart _host_next_part = _parse_context.getParseHierPart();

            while( !_error_occurred && !_reached_host_end ){

                if( _host_read_at < _parse_context._uriStringLength ){
                    unicode_char _each_char = *( _parse_context._uriString + _host_read_at );
                    if( CharacterChecker::isSubDelims( _each_char ) 
                        || CharacterChecker::isAlphabetic( _each_char )
                        || CharacterChecker::isDigit( _each_char )
                        || _each_char == L'%' ){
                        ++_host_read_at;
                    } else if( _each_char == L'/' ){
                        // next part is path part
                        _host_next_part = URIParseContext::Path;
                        _reached_host_end = !false;
                    } else if( _each_char == L':' ){
                        // next part is port part
                        _host_next_part = URIParseContext::Port;
                        _reached_host_end = !false;
                    } else{
                        // invalid host character
                        _parse_context.putErrorMessage( L"Invalid character for Host part" );
                        _error_occurred = !false;
                    }
                } else{
                    // end string
                    _host_next_part = URIParseContext::End;
                    _reached_host_end = !false;
                }
            }

            if( !_error_occurred ){
                _parse_context.recordParsedHierPart( _host_start_at, _host_read_at );
                _parse_context.updateReadAt( _host_read_at );

                _parse_context.switchParseHierPart( _host_next_part );
            } else{
                _parse_context.putTrackAt( _host_read_at );
            }

            return !_error_occurred;
        }

        // port = *DIGIT
        bool URIParser::parsePort( URIParseContext& _parse_context ){
            bool _error_occurred = false;
            bool _reached_port_end = false;

            const Private::Shift _port_start_at = _parse_context.getReadAt();

            Private::Shift _port_read_at = _port_start_at;
            URIParseContext::ParseHierPart _port_next_part = _parse_context.getParseHierPart();

            while( !_error_occurred && !_reached_port_end ){

                if( _port_read_at < _parse_context._uriStringLength ){
                    unicode_char _each_char = *( _parse_context._uriString + _port_read_at );
                    if( CharacterChecker::isDigit( _each_char ) ){
                        ++_port_read_at;
                    } else if( _each_char == L'/' ){ // end slash
                        if( _port_read_at != _port_start_at ){
                            _port_next_part = URIParseContext::Path;
                            _reached_port_end = !false;
                        } else{
                            // invalid port number
                            _parse_context.putErrorMessage( L"Port part length is 0" );
                            _error_occurred = !false;
                        }
                    } else{ // invalid character for port
                        _parse_context.putErrorMessage( L"Invalid character for Port part" );
                        _error_occurred = !false;
                    }
                } else{ // end URI
                    if( _port_read_at > _port_start_at ){
                        _port_next_part = URIParseContext::End;
                        _reached_port_end = !false;
                    } else{
                        // invalid port number
                        _parse_context.putErrorMessage( L"Port part length is 0" );
                        _error_occurred = !false;
                    }
                }
            }
            // check number ?

            if( !_error_occurred ){
                _parse_context.recordParsedHierPart( _port_start_at, _port_read_at );

                _parse_context.updateReadAt( _port_read_at );
                _parse_context.switchParseHierPart( _port_next_part );
            } else{
                _parse_context.putTrackAt( _port_read_at );
            }

            return !_error_occurred;
        }

        //    path = path-abempty    ; begins with "/" or is empty
        //      / path-absolute   ; begins with "/" but not "//"
        //      / path-noscheme   ; begins with a non-colon segment
        //      / path-rootless   ; begins with a segment
        //      / path-empty      ; zero characters
        bool URIParser::parsePath( URIParseContext& _parse_context ){
            bool _error_occurred = false;
            bool _reached_path_end = false;

            const Private::Shift _path_start_at = _parse_context.getReadAt();

            Private::Shift _path_read_at = _path_start_at;
            URIParseContext::ParseHierPart _path_next_part = _parse_context.getParseHierPart();

            while( !_error_occurred && !_reached_path_end ){
                if( _path_read_at < _parse_context._uriStringLength ){
                    unicode_char _each_char = *( _parse_context._uriString + _path_read_at );

                    if( CharacterChecker::isPathCharacter( _each_char ) ){
                        ++_path_read_at;
                    } else if( _each_char == L'?' ){
                        _path_next_part = URIParseContext::Query;
                        _reached_path_end = !false;
                    } else if( _each_char == L'#' ){
                        _path_next_part = URIParseContext::Fragment;
                        _reached_path_end = !false;
                    } else{
                        // invalid path character
                        _parse_context.putErrorMessage( L"Invalid character for Path part");
                        _error_occurred = !false;
                    }
                } else{
                    // it can reached the end of the URI
                    _path_next_part = URIParseContext::End;
                    _reached_path_end = !false;
                }
            }

            if( !_error_occurred ){
                _parse_context.recordParsedHierPart( _path_start_at, _path_read_at );

                _parse_context.updateReadAt( _path_read_at );
                _parse_context.switchParseHierPart( _path_next_part );
            } else{
                _parse_context.putTrackAt( _path_read_at );
            }

            return !_error_occurred;
        }

        bool URIParser::parseQuery( URIParseContext& _parse_context ){
            bool _error_occurred = false;
            bool _reached_query_end = false;

            const Private::Shift _query_start_at = _parse_context.getReadAt();

            Private::Shift _query_read_at = _query_start_at;
            URIParseContext::ParseHierPart _query_next_part = _parse_context.getParseHierPart();

            while( !_error_occurred && !_reached_query_end ){
                if( _query_read_at < _parse_context._uriStringLength ){
                    unicode_char _each_char = *( _parse_context._uriString + _query_read_at );
                    if( CharacterChecker::isUnreserved( _each_char )
                        || CharacterChecker::isSubDelims( _each_char )
                        || _each_char == L'%'
                        || _each_char == L':'
                        || _each_char == L'@' ){
                        ++_query_read_at;
                    } else if( _each_char == L'#' ){
                        // fragment
                        _query_next_part = URIParseContext::Fragment;
                        _reached_query_end = !false;
                    } else{
                        // invalid character
                        _parse_context.putErrorMessage( L"Invalid character for Query part");
                        _error_occurred = !false;
                    }
                } else{
                    // URI end
                    _query_next_part = URIParseContext::End;
                    _reached_query_end = !false;
                }
            }

            if( !_error_occurred ){
                _parse_context.recordParsedHierPart( _query_start_at, _query_read_at );

                _parse_context.updateReadAt( _query_read_at );
                _parse_context.switchParseHierPart( _query_next_part );
            } else{
                _parse_context.putTrackAt( _query_read_at );
            }

            return !_error_occurred;
        }

        bool URIParser::parseFragment( Private::Shift& _out_shift ){
            return false;
        }

    }
}