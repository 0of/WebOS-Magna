#ifndef HTTPREQUESTCLIENT_H
#define HTTPREQUESTCLIENT_H

#include "HttpRequestMessage.h"
#include "HttpResponseMessage.h"

namespace Magna{
  namespace Network{
    
    class HttpRequestClient{
      public:
        HttpRequestClient();
        ~HttpRequestClient();

      public:
        HttpResponseMessage * performHttpRequest( const HttpRequestMessage& );
        void setAgentCookiePath( const String& );

      __Data_Field private:
        class PrivateData;
        PrivateData *m_data;
    };


  }//namespace Network
}//namespace Magna

#endif  /*  HTTPREQUESTCLIENT_H  */