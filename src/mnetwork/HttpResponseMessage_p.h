#ifndef HTTPRESPONSEMESSAGE_P_H
#define HTTPRESPONSEMESSAGE_P_H

#include "HttpResponseMessage.h"

#include "HttpResponseFactory.h"

namespace Magna{
  namespace Network{
    
    //HTTP response callback

    static size_t /*callback */ responseEntityCallback(void *d, size_t size, size_t nmemb, void *instance){
      size_t _process_num = 0;
      if( instance != nullptr ){
        HttpResponseMessage*_resp_mess = reinterpret_cast<HttpResponseMessage*>( instance ); 

        HttpResponseFactory &_factory = HttpResponseFactory::getHttpResponseFactory();
        _process_num = _factory.processMessageEntity( _resp_mess, d, size, nmemb );
      }
      return _process_num;
    }

    static size_t /*callback */ responseHeaderCallback(void *d, size_t size, size_t nmemb, void *instance){
      size_t _process_num = 0;
      if( instance != nullptr ){
        HttpResponseMessage*_resp_mess = reinterpret_cast<HttpResponseMessage*>( instance ); 

        HttpResponseFactory &_factory = HttpResponseFactory::getHttpResponseFactory();
        _process_num = _factory.processMessageHeader( _resp_mess, d, size, nmemb );
      }
      return _process_num;
    }


  }//namespace Network
}//namespace Magna

#endif  /*  HTTPRESPONSEMESSAGE_P_H  */