#ifndef MAILACCESSREPONSE_H
#define MAILACCESSREPONSE_H

#include <sstream>

namespace Magna{
  namespace Network{
    
    class MailAccessResponse{
      public:
        MailAccessResponse();
        ~MailAccessResponse();

      public:
        const std::ostringstream &getResponseContent();

      private:
        std::ostringstream m_responseContent;
    };

  }//namespace Network
}//namespace Magna

#endif  /*  MAILACCESSREPONSE_H  */