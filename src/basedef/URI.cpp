#include "URI.h"

#include "private/URI_p.h"

#include "URIParser.h"
#include "URIEncoder.h"
#include "URIException.h"

namespace Magna{
    namespace Core{

        URI::URI()
            :m_data(){

        }

        URI::URI( const String& _uri_string )
            :m_data(){

            if( !_uri_string.empty() ){
                String _encoded_uri_string = URIEncoder::URIEncode( _uri_string );
                URIParser _parser( _encoded_uri_string );
                try{
                    _parser.doParse();

                    // read port
                    uint16 _port = 0;
                    _parser.parsePortOut( _port );

                    URI::QueryParameters _params;
                    _parser.parseQueryParametersOut( _params );

                    m_data = new PrivateData( _uri_string, _encoded_uri_string, _port, _parser.takeParsedParts(), std::move( _params ) );
                } catch(const URIException& exception){
                  // not a valid URI
                }
            }
        }

        URI::URI( const URI& uri )
            :m_data( uri.m_data ){

        }

        URI::~URI(){

        }

        URI& URI::operator = ( const URI& uri ){
            m_data = uri.m_data;
            return *this;
        }

        bool URI::operator == ( const URI& uri ){
            return m_data == uri.m_data && uri.m_data->getOriginalURIString() == m_data->getOriginalURIString();
        }

        bool URI::operator != ( const URI& uri ){
            return !operator == ( uri );
        }

        String URI::getFragment() const{
            String _fragment;
            PRIVATE_DATA_NOT_NULL_BEGIN
                if( m_data->isValid() ){
                    auto _found = m_data->m_URIParts.find( URIParseContext::Fragment );
                    if( m_data->m_URIParts.end() != _found){
                        _fragment = _found->second;
                    }
                }
            PRIVATE_DATA_NOT_NULL_END
            return _fragment;
        }

        String URI::getScheme() const{
            String _scheme;
            PRIVATE_DATA_NOT_NULL_BEGIN
                if( m_data->isValid() ){
                    auto _found = m_data->m_URIParts.find( URIParseContext::Scheme );
                    if( m_data->m_URIParts.end() != _found){
                        _scheme = _found->second;
                    }
                }
            PRIVATE_DATA_NOT_NULL_END
            return _scheme;
        }

        String URI::getQueryParameterValue( const String& key ) const{
            String _param_value;
            PRIVATE_DATA_NOT_NULL_BEGIN
                if( m_data->isValid() ){
                    auto _found = m_data->m_queryParameters.find( key );
                    if( m_data->m_queryParameters.end() != _found ){
                        _param_value = _found->second;
                    }
                }
            PRIVATE_DATA_NOT_NULL_END
            return _param_value;
        }

        URI::QueryParameters URI::getAllQueryParameters() const{
            URI::QueryParameters _parameters;
            PRIVATE_DATA_NOT_NULL_BEGIN
                if( m_data->isValid() ){
                    _parameters = m_data->m_queryParameters;
                }
            PRIVATE_DATA_NOT_NULL_END
            return std::move( _parameters );
        }

        uint16 URI::getPort() const{
            uint16 _port = 0;
            PRIVATE_DATA_NOT_NULL_BEGIN
                if( m_data->isValid() ){
                    _port = static_cast<uint16>( m_data->m_port );
                }
            PRIVATE_DATA_NOT_NULL_END
            return _port;
        }

        String URI::getHostString() const{
            String _host_string;
            PRIVATE_DATA_NOT_NULL_BEGIN
                if( m_data->isValid() ){
                    auto _found = m_data->m_URIParts.find( URIParseContext::Host );
                    if( m_data->m_URIParts.end() != _found){
                        _host_string = _found->second;
                    }
                }
            PRIVATE_DATA_NOT_NULL_END
            return _host_string;
        }

        String URI::getQuery() const{
            String query;
            PRIVATE_DATA_NOT_NULL_BEGIN
                if( m_data->isValid() ){
                    auto _found = m_data->m_URIParts.find( URIParseContext::Query );
                    if( m_data->m_URIParts.end() != _found){
                        query = _found->second;
                    }
                }
            PRIVATE_DATA_NOT_NULL_END
            return query;
        }

        bool URI::isLocal() const{
            bool _is_local_host = false;
            PRIVATE_DATA_NOT_NULL_BEGIN
                if( m_data->isValid() ){
                    _is_local_host = m_data->isFlagOn( PrivateData::LocalHost );
                }
            PRIVATE_DATA_NOT_NULL_END
            return _is_local_host;
        }

        bool URI::isRelative() const{
            bool _is_relative_URI = false;
            PRIVATE_DATA_NOT_NULL_BEGIN
                if( m_data->isValid() ){
                    _is_relative_URI = m_data->isFlagOn( PrivateData::Relative );
                }
            PRIVATE_DATA_NOT_NULL_END
            return _is_relative_URI;
        }

        bool URI::isAbsolute() const{
            bool _is_absolute_URI = false;
            PRIVATE_DATA_NOT_NULL_BEGIN
                if( m_data->isValid() ){
                    _is_absolute_URI = !m_data->isFlagOn( PrivateData::Relative );
                }
            PRIVATE_DATA_NOT_NULL_END
            return _is_absolute_URI;
        }

        URI::PrivateData::PrivateData( const String& _uri_string
                                                        , const String& _encoded_uri_string
                                                        , const uint16 _port
                                                        , URIParseContext::ParsedParts &&_parts
                                                        , URI::QueryParameters &&_params )
            :m_flags()
            ,m_port( _port )
            ,m_originalURIString( _uri_string )
            ,m_encodedURIString( _encoded_uri_string )
            ,m_URIParts( std::move( _parts ) )
            ,m_queryParameters( std::move( _params ) ){

        }

        URI::PrivateData::~PrivateData(){

        }
    }
}