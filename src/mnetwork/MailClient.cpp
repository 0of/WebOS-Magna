#include "MailClient.h"

#include <curl/curl.h>

namespace Magna{
  namespace Network{
    
    class MailClient::PrivateData{
      public:
        CURL *m_curlInstance;
        String m_hostString;
        String m_serverType;

        String m_loginInfo;
    };

    void MailClient::performMailAccessRequest( const String& command, MailAccessResponse &resp ){
      if( !command.empty() && Nullptr != m_data && Nullptr != m_data->m_curlInstance ){

        curl_easy_setopt( m_data->m_curlInstance,  CURLOPT_USERPWD, m_data->m_loginInfo.toString().c_str() );

        String _URL_string = m_data->m_serverType + L"://" + m_data->m_hostString;
        curl_easy_setopt(  m_data->m_curlInstance, CURLOPT_URL, _URL_string.toString().c_str() );



      }
    }


    void MailClient::setMailServerHost( const String& host, const String& servertype){
      if( Nullptr != m_data ){

        if( L"pop3" == servertype 
          || L"imap" == servertype ){
          m_data->m_hostString = host;
          m_data->m_serverType = servertype;
          
        }
        
      }
    }

  }//namespace Network
}//namespace Magna