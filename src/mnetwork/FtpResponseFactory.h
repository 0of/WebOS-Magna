#ifndef FTPRESPONSEFACTORY_H
#define FTPRESPONSEFACTORY_H

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"

#include "FtpResponseMessage.h"

namespace Magna{
  namespace Network{
    
    class FtpResponseFactory{
      public:
        static FtpResponseFactory &getFtpResponseFactory();

      private:
        FtpResponseFactory();
        ~FtpResponseFactory();

      public:
        FtpResponseMessage* produces();
        uint32 processMessageHeader( FtpResponseMessage*, void *,  uint32, uint32 );
        uint32 processMessageContent( FtpResponseMessage*, void *,  uint32, uint32 );
    };


  }//namespace Network
}//namespace Magna

#endif  /*  FTPRESPONSEFACTORY_H  */