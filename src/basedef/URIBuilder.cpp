#include "URIBuilder.h"
#include "StringConvertor.h"

namespace Magna{
    namespace Core{
        struct InvalidPortConstants{ static const uint32 value = -1; };

        URIBuilder::URIBuilder()
            :m_port( InvalidPortConstants::value )    // reserved port
            ,m_scheme() // can be empty for relative URI
            ,m_host()   // can be empty for relative URI
            ,m_path()
            ,m_fragment()
            ,m_userInfo()
            ,m_queries(){

        }

        URIBuilder::~URIBuilder(){

        }

        bool URIBuilder::isValid() const{
            return !( m_host.empty() || m_path.empty() );
        }

        URIBuilder& URIBuilder::setPort( uint16 port ){
            m_port = port;
            return *this;
        }

        URIBuilder& URIBuilder::setScheme( const String& scheme ){
            m_scheme = scheme;
            return *this;
        }

        URIBuilder& URIBuilder::setUserInfo( const String& name, const String& password ){
            m_userInfo = std::make_pair( name, password );
            return *this;
        }

        URIBuilder& URIBuilder::setUsername( const String& name ){
            m_userInfo.first = name;
            return *this;
        }

        URIBuilder& URIBuilder::setPassword( const String& password ){
            m_userInfo.second = password;
            return *this;
        }

        URIBuilder& URIBuilder::setHost( const String& host ){
            m_host = host;
            return *this;
        }

        URIBuilder& URIBuilder::setPath( const String& path ){
            m_path = path;
            return *this;
        }

        URIBuilder& URIBuilder::setFragment( const String& fragment ){
            m_fragment = fragment;
            return *this;
        }

        URIBuilder& URIBuilder::appendQueryParameter( const std::pair<String, String>& param ){
            m_queries.emplace( param );
            return *this;
        }

        URIBuilder& URIBuilder::appendQueryParameters( const std::map<String, String>& params ){
            m_queries.insert( params.begin(), params.end() );
            return *this;
        }

        URI URIBuilder::builds() const{
            URI _built_uri;
            if( isValid() ){
                String _uri_string;

                // append scheme
                if( !m_scheme.empty() ){
                    _uri_string.append( m_scheme );
                    _uri_string.push_back( L':' );

                    if( !m_host.empty() ){
                        _uri_string.append( L"//" );
                    }
                }
                
                { 
                    // append authority
                    bool _has_user_info = false;
                    if( !m_userInfo.first.empty() ){ // user name
                        _uri_string.append( m_userInfo.first );
                        _has_user_info = !false;
                    }
                    if( !m_userInfo.second.empty() ){ // password
                        _uri_string.push_back( L':' );
                        _uri_string.append( m_userInfo.second );
                        _has_user_info = !false;
                    }
                    if( _has_user_info ){
                        _uri_string.push_back( L'@' );
                    }

                    _uri_string.append( m_host );
                    if( InvalidPortConstants::value != m_port ){
                        _uri_string.push_back( L':' );
                        // add port
                        _uri_string.append( StringConvertor::fromValue( m_port ) );
                    }
                }

                // append path
                _uri_string.append( m_path );

                // append queries
                if( !m_queries.empty() ){
                    _uri_string.push_back( L'?' );
                    for( auto _each_query = m_queries.begin(); m_queries.end() != _each_query; ){
                        _uri_string.append( _each_query->first );
                        _uri_string.push_back( L'=' );
                        _uri_string.append( _each_query->second );

                        auto _next_query = ++_each_query;
                        if( m_queries.end() != _next_query ){
                            _uri_string.push_back( L'&' );
                        }
                    }
                }
                
                if( !m_fragment.empty() ){
                    _uri_string.push_back( L'#' );
                    _uri_string.append( m_fragment );
                }

                // build a URI with URI string
                _built_uri = URI( _uri_string );
            }
            return _built_uri;
        }
    }
}