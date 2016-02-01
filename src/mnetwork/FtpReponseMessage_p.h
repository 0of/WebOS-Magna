#ifndef FTPRESPONSEMESSAGE_P_H
#define FTPRESPONSEMESSAGE_P_H

#include <fstream>

#include "FtpResponseMessage.h"
#include "FtpResponseFactory.h"

namespace Magna{
  namespace Network{
    
    //use for passing parameter
    class FtpResponseBehaviourParameter{
      public:
        FtpResponseMessage *m_responseMessage;
        std::ofstream *m_fileStream;

      public:
        FtpResponseBehaviourParameter()
          :m_responseMessage( Nullptr )
          ,m_fileStream( Nullptr ){}

        ~FtpResponseBehaviourParameter(){

        }
    };

    class FtpResponseBehaviour{
      public:

        static  size_t /*callback */ responseContentCallback(void *d, size_t size, size_t nmemb, void *instance){
          size_t _process_num = 0 ;
          if( instance != Nullptr ){

            FtpResponseBehaviourParameter *_para = reinterpret_cast<FtpResponseBehaviourParameter *>( instance );
            if( _para ->m_fileStream != Nullptr ){
              auto &_file_stream = *(_para ->m_fileStream);

              if( _file_stream.is_open() ){
                _process_num = size * nmemb;
                _file_stream.write( reinterpret_cast<assic_char *>(d), size * nmemb );
              }
            }
            else{
              if( _para->m_responseMessage != Nullptr ){
                auto &_factory = FtpResponseFactory::getFtpResponseFactory();

                _process_num = _factory.processMessageContent(  _para->m_responseMessage, d, size, nmemb );
              }
            }
          }
          return _process_num;
        }

        static  size_t /*callback */ responseHeaderCallback(void *d, size_t size, size_t nmemb, void *instance){

          size_t _process_num = 0 ;
          if( instance != Nullptr ){
            FtpResponseBehaviourParameter *_para = reinterpret_cast<FtpResponseBehaviourParameter *>( instance );
            if( _para->m_responseMessage != Nullptr ){
              auto &_factory = FtpResponseFactory::getFtpResponseFactory();

              _process_num = _factory.processMessageHeader(  _para->m_responseMessage, d, size, nmemb );
            }
          }
          return _process_num;
        }

    };

  }//namespace Network
}//namespace Magna

#endif  /*  FTPRESPONSEMESSAGE_P_H  */