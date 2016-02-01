#include "FtpClient.h"

#include <curl/curl.h>

#include "FtpResponseFactory.h"
#include "FtpReponseMessage_p.h"

namespace Magna{
  namespace Network{
    
    class FtpClient::PrivateData{
      public:
        PrivateData();
        ~PrivateData();

      public:
        CURL *m_curlInstance;

        uint16 m_isConnected;
        uint16 m_isHeaderExplicitReceive;
    };

    FtpClient::PrivateData::PrivateData()
      :m_curlInstance( Nullptr ){

      m_curlInstance = curl_easy_init();
    }

    FtpClient::PrivateData::~PrivateData(){
      curl_easy_cleanup(m_curlInstance);
      m_curlInstance = Nullptr;
    }


    FtpClient::FtpClient()
      :m_data( new PrivateData ){

    }

    FtpClient::~FtpClient(){
      if( m_data != Nullptr ){
        delete m_data;
      }
    }

    FtpResponseMessage *FtpClient::performFtpRequest( const FtpRequestMessage& req_mess){
      FtpResponseMessage *_resp_mess = Nullptr;
      if( m_data != Nullptr && m_data->m_curlInstance != Nullptr ){

        const auto& _output_filename = req_mess.getOutputFileName().toString();

        const auto& _URL_string = req_mess.getURLString().toString();

        const auto& _command_string = req_mess.getCommandString().toString();

        //response message
        _resp_mess = new FtpResponseMessage;

        FtpResponseBehaviourParameter _parameter;
        _parameter.m_responseMessage = _resp_mess;

        std::ofstream _file_stream;
        //open the file
        if( !_output_filename.empty() ){
          _file_stream.open( _output_filename, std::ios_base::binary | std::ios_base::out );

          if( _file_stream.is_open() ){
            _parameter.m_fileStream = &_file_stream;
          }
        }
        
      
        if( !_URL_string.empty() ){

          curl_easy_setopt( m_data->m_curlInstance,CURLOPT_URL, _URL_string.c_str() );

          //configurations
          curl_easy_setopt(m_data->m_curlInstance, CURLOPT_NOPROGRESS, 1L);

      
          curl_easy_setopt(m_data->m_curlInstance, CURLOPT_WRITEFUNCTION,  &FtpResponseBehaviour::responseHeaderCallback );
          curl_easy_setopt(m_data->m_curlInstance,  CURLOPT_WRITEDATA, &_parameter);

          if( m_data->m_isHeaderExplicitReceive ){
            //header callback
            curl_easy_setopt( m_data->m_curlInstance,  CURLOPT_HEADERDATA, _resp_mess );
            curl_easy_setopt( m_data->m_curlInstance,  CURLOPT_HEADERFUNCTION, &FtpResponseBehaviour::responseHeaderCallback );
          }        
        }
        
        struct curl_slist *_command = Nullptr; 
        if( !_command_string.empty() ){
          //command    
          _command = curl_slist_append(_command,  _command_string.c_str() ); 

          curl_easy_setopt( m_data->m_curlInstance, CURLOPT_QUOTE, _command );
        }

        CURLcode _perform_code = curl_easy_perform( m_data->m_curlInstance );

        if( _perform_code != CURLE_OK ){

        }

        if( !_command_string.empty() ){
          curl_slist_free_all(_command); 
        }

      }
      return _resp_mess;
    }


  }//namespace Network
}//namespace Magna