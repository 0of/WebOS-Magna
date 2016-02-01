#ifndef FTPREQUESTMESSAGE_H
#define FTPREQUESTMESSAGE_H

#include "basedef/String.h"
using namespace Magna::Core;

namespace Magna{
  namespace Network{
      
    class FtpRequestMessage{
      __Constructor_Destructor public:
        FtpRequestMessage();
        FtpRequestMessage( const String& url, const String& outputfile = String() );
        FtpRequestMessage( const FtpRequestMessage& );
        ~FtpRequestMessage();

        FtpRequestMessage& operator = ( const FtpRequestMessage& );

      __Checker public:
        bool isValid() const;

      __Setter public:
        void setRawCommand( const String& );
        void setGetFileCommand( const String& target, const String& outputFileName );
        void setChangeDirCommand( const String& );

        void setURLForGettingFile( const String& url, const String& outputfile );
        void setURLForGettingDirInfo( const String& url );

        void setUserNamePassword( const String& name, const String& psw );

      __Getter public:
        const String& getCommandString() const{
          return m_commandString;
        }
        const String& getOutputFileName() const{
          return m_outputFileName;
        }

        String getHost() const;
        String getURLString() const{
          return m_URLString;
        }

      __Data_Field private:
        String m_outputFileName;
        String m_commandString;
        String m_URLString;
    };
    
  }//namespace Network
}//namespace Magna

#endif  /*  FTPREQUESTMESSAGE_H  */