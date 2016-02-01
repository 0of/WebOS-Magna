#ifndef FTPCLIENT_H
#define FTPCLIENT_H

#include "FtpRequestMessage.h"
#include "FtpResponseMessage.h"

namespace Magna{
  namespace Network{
    
    class FtpClient{
      public:
        FtpClient();
        virtual ~FtpClient();

      public:
        FtpResponseMessage *performFtpRequest( const FtpRequestMessage& );

      private:
        class PrivateData;
        PrivateData *m_data;
    };
    
  }//namespace Network
}//namespace Magna

#endif  /*  FTPCLIENT_H  */