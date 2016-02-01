#include "HttpRequestClient.h"

#include "curl/curl.h"

#include "HttpResponseMessage_p.h"

namespace Magna{
  namespace Network{
    
    class HttpRequestClient::PrivateData{
      public:
        CURL *m_curlInstance;
        String m_cookiePath;

        PrivateData();
        ~PrivateData();

    };

    HttpRequestClient::PrivateData::PrivateData()
      :m_curlInstance( Nullptr ){

      //init
      m_curlInstance = curl_easy_init();

    }

    HttpRequestClient::PrivateData::~PrivateData(){
      //clear up
      curl_easy_cleanup(m_curlInstance);
      m_curlInstance = Nullptr;
    }

    HttpRequestClient::HttpRequestClient()
      :m_data( new PrivateData ){

    }

    HttpRequestClient::~HttpRequestClient(){
      if( m_data != Nullptr ){
        delete m_data;
      }
    }

    HttpResponseMessage * HttpRequestClient::performHttpRequest( const HttpRequestMessage& _req_mess){
      HttpResponseMessage *_ret_mess = Nullptr;
      if( _req_mess.isValid() 
        && m_data != Nullptr 
        && m_data->m_curlInstance != Nullptr ){

        switch( _req_mess.getMethod() ){
          case HttpRequestMessage::Method_GET:
            {
              //setup GET options
              //URL utf-8 string
              auto &_URL_string = _req_mess.getURLString().toString();
              curl_easy_setopt( m_data->m_curlInstance,CURLOPT_URL, _URL_string.c_str() );
              
              //configurations
              curl_easy_setopt(m_data->m_curlInstance, CURLOPT_NOPROGRESS, 1L);

              auto &_factory = HttpResponseFactory::getHttpResponseFactory();
              _ret_mess = _factory.produces();


              //entity callback 
              curl_easy_setopt(m_data->m_curlInstance, CURLOPT_WRITEFUNCTION,  responseEntityCallback );
              curl_easy_setopt(m_data->m_curlInstance,  CURLOPT_WRITEDATA, _ret_mess);

              //header callback
              curl_easy_setopt( m_data->m_curlInstance,  CURLOPT_HEADERDATA, _ret_mess );
              curl_easy_setopt( m_data->m_curlInstance,  CURLOPT_HEADERFUNCTION, responseHeaderCallback );  

              //perform
              curl_easy_perform( m_data->m_curlInstance );
            }
            break;

          case HttpRequestMessage::Method_POST:
            {
              //init parameter field
              struct curl_httppost *_p_start = Nullptr ;
              struct curl_httppost *_p_end = Nullptr;

              const auto &_para_field = _req_mess.getParameterField();

              for( auto _each = _para_field.begin(); _each != _para_field.end(); ++_each ){
                curl_formadd( &_p_start, &_p_end,
                  CURLFORM_COPYNAME, _each->first.toString().c_str(),
                  CURLFORM_COPYCONTENTS, _each->second.toString().c_str(),
                  CURLFORM_END);
              }
              
              auto &_URL_string = _req_mess.getURLString().toString();
              curl_easy_setopt( m_data->m_curlInstance,CURLOPT_URL, _URL_string.c_str() );

              //configurations
              curl_easy_setopt(m_data->m_curlInstance, CURLOPT_NOPROGRESS, 1L);

              auto &_factory = HttpResponseFactory::getHttpResponseFactory();
              _ret_mess = _factory.produces();


              //entity callback 
              curl_easy_setopt(m_data->m_curlInstance, CURLOPT_WRITEFUNCTION,  responseEntityCallback );
              curl_easy_setopt(m_data->m_curlInstance,  CURLOPT_WRITEDATA, _ret_mess);

              //header callback
              curl_easy_setopt( m_data->m_curlInstance,  CURLOPT_HEADERDATA, _ret_mess );
              curl_easy_setopt( m_data->m_curlInstance,  CURLOPT_HEADERFUNCTION, responseHeaderCallback );  

              //post
              curl_easy_setopt(m_data->m_curlInstance, CURLOPT_HTTPPOST, _p_start);

              //perform
              CURLcode _perform_code = curl_easy_perform( m_data->m_curlInstance );

              if( _perform_code != CURLE_OK ){

              }

              //clear form data
              curl_formfree(_p_start);
            }
            break;

          default:
            break;
        }
      }
      
      return _ret_mess;
    }


  }//namespace Network
}//namespace Magna