#ifndef MAILCLIENT_H
#define MAILCLIENT_H

#include "basedef/String.h"
using namespace Magna::Core;

#include "MailAccessReponse.h"

namespace Magna{
  namespace Network{
    
    class MailClient{
      public:
        MailClient();
        ~MailClient();

      public:
        void setLoginInfo( const String& uname, const String& psw );
        void setMailServerHost( const String& host, const String& servertype);
        
        void performMailAccessRequest( const String& command, MailAccessResponse &resp );

      private:
        class PrivateData;
        PrivateData *m_data;
    };

  }//namespace Network
}//namespace Magna

#endif  /*  MAILCLIENT_H  */