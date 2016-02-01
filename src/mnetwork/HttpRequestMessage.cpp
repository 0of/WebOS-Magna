#include "HttpRequestMessage.h"

#include <regex>

namespace Magna{
  namespace Network{
    
    HttpRequestMessage::HttpRequestMessage()
      :m_headerString()
      ,m_parameterField()
      ,m_URLString()
      ,m_method( HttpRequestMessage::Method_GET ){

    }

    HttpRequestMessage::HttpRequestMessage( const String& url, Method method)
      :m_headerString()
      ,m_parameterField()
      ,m_URLString( url )
      ,m_method( method ){


    }

    HttpRequestMessage::HttpRequestMessage( const HttpRequestMessage& mess)
      :m_headerString( mess.m_headerString )
      ,m_method( mess.m_method )
      ,m_parameterField( mess.m_parameterField )
      ,m_URLString( mess.m_URLString ){

    }

    HttpRequestMessage::~HttpRequestMessage(){

    }

    HttpRequestMessage& HttpRequestMessage::operator =( const HttpRequestMessage& mess){

      m_headerString = mess.m_headerString ;
      m_method = mess.m_method;
      m_parameterField = mess.m_parameterField;
      m_URLString = mess.m_URLString ;

      return *this;
    }

    String HttpRequestMessage::getHost() const{
      String _ret_host_str;
      auto _found_start = m_URLString.find( L"://" );

      if( _found_start != std::string ::npos ){
        _found_start += 3;
        if( _found_start < m_URLString.size() ){
          auto _found_end = m_URLString.find( L"/" , _found_start );
          _ret_host_str = m_URLString.substr( _found_start , _found_end - _found_start );
        }  
      }  

      return _ret_host_str;
    }

    bool HttpRequestMessage::isValid() const{
      //regex
      String _http_url_pattern (L"^(http|https)\\://[a-zA-Z0-9\\-\\.]+\\.[a-zA-Z]{2,3}(:[a-zA-Z0-9]*)?/?([a-zA-Z0-9\\-\\._\\?\\,\\'/\\\\+&amp;%\\$#\\=~])*[^\\.\\,\\)\\(\\s]$");
      std::wregex _reg( _http_url_pattern );

      std::wsregex_iterator _reg_iter ( m_URLString.begin(), m_URLString.end(), _reg );
      return _reg_iter != std::wsregex_iterator();
    }

    void HttpRequestMessage::setHost( const String& host_str){
      m_URLString = host_str;
    }

    void HttpRequestMessage::setHeader( const String& header){
      m_headerString =header;
    }

    void HttpRequestMessage::setParameterField(const ParameterField& p){
      m_parameterField = p;
    }

    void HttpRequestMessage::setMethod( const HttpRequestMessage::Method& m){
      m_method = m;
    }
  }//namespace Network
}//namespace Magna