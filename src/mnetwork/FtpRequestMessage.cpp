#include "FtpRequestMessage.h"

namespace Magna{
  namespace Network{
    
    FtpRequestMessage::FtpRequestMessage()
      :m_URLString()
      ,m_commandString()
      ,m_outputFileName(){

    }

    FtpRequestMessage::FtpRequestMessage( const String& url, const String& outputfile)
      :m_URLString()
      ,m_commandString()
      ,m_outputFileName(){

    }

    FtpRequestMessage::FtpRequestMessage( const FtpRequestMessage& message)
      :m_URLString( message.m_URLString )
      ,m_commandString( message.m_commandString )
      ,m_outputFileName( message.m_outputFileName ){

    }

    FtpRequestMessage& FtpRequestMessage::operator = ( const FtpRequestMessage& message){
      m_URLString = message.m_URLString;
      m_commandString = message.m_commandString;
      m_outputFileName = message.m_outputFileName;

      return *this;
    }

    FtpRequestMessage::~FtpRequestMessage(){

    }

    void FtpRequestMessage::setRawCommand( const String& cmd){
      m_commandString = cmd;
    }

    void FtpRequestMessage::setGetFileCommand( const String& target, const String& outputFileName ){
      m_commandString = target;
      m_outputFileName = outputFileName;
    }

    void FtpRequestMessage::setChangeDirCommand( const String& cmd){
      m_commandString = cmd;
    }

    void FtpRequestMessage::setURLForGettingFile( const String& url, const String& outputfile ){
      m_URLString = url;
      m_outputFileName = outputfile;
    }

    void FtpRequestMessage::setURLForGettingDirInfo( const String& url ){
      m_URLString = url;
    }

    void FtpRequestMessage::setUserNamePassword( const String& name, const String& psw ){

    }

    String FtpRequestMessage::getHost() const{
      String _ret_host_str;
      auto _found_start = m_URLString.find( L"://" );

      //ftp://user:psw@host/
      if( _found_start != std::string ::npos ){
        _found_start += 3;
        if( _found_start < m_URLString.size() ){

          //find if contains username & password
          auto _found_login_para = m_URLString.find( L"@" );
          if( _found_login_para != std::string ::npos 
            && _found_login_para >= _found_start ){
            _found_start = _found_login_para;
          }

          auto _found_end = m_URLString.find( L"/" , _found_start );
          _ret_host_str = m_URLString.substr( _found_start , _found_end - _found_start );
        }  
      }  

      return _ret_host_str;
    }

    bool FtpRequestMessage::isValid() const{
      bool _ret_valid = false;

      if( !m_URLString.empty() ){



      }

      return _ret_valid;
    }

  }//namespace Network
}//namespace Magna