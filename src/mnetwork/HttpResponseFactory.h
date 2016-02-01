#ifndef HTTPRESPONSEFACTORY_H
#define HTTPRESPONSEFACTORY_H

#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include "HttpResponseMessage.h"

namespace Magna{
  namespace Network{
    
    class HttpResponseFactory{
      public:
        static HttpResponseFactory &getHttpResponseFactory();

      private:
        HttpResponseFactory();
        ~HttpResponseFactory();

      public:
        HttpResponseMessage* produces();
        uint32 processMessageHeader( HttpResponseMessage*, void *,  uint32, uint32 );
        uint32 processMessageEntity( HttpResponseMessage*, void *,  uint32, uint32 );
    };

  }//namespace Network
}//namespace Magna

#endif  /*  HTTPRESPONSEFACTORY_H  */