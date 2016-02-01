#ifndef FTPRESPONSEMESSAGE_H
#define FTPRESPONSEMESSAGE_H

#include <vector>
#include <sstream>

namespace Magna{
  namespace Network{
    
    class FtpResponseMessage{
      friend class FtpClient;
      friend class FtpResponseFactory;

      public:
        enum ResponseCode{
          ResponseCode_Invalid = 0

          ,ResponseCode_RestartMarkerReply = 110
          ,ResponseCode_ServiceReadyInMin = 120
          ,ResponseCode_TransferStart = 125
          ,ResponseCode_AboutToOpenConnection = 150

          ,ResponseCode_OK = 200
          ,ResponseCode_CommandNotExecute = 202
          ,ResponseCode_SystemStatus = 211
          ,ResponseCode_DirectoryStatus = 212
          ,ResponseCode_FileStatus = 213
          ,ResponseCode_HelpMessage = 214
          ,ResponseCode_SystemType = 215
          ,ResponseCode_ServiceReadyForNewUser = 220
          ,ResponseCode_ServiceClosingConnection = 221
          ,ResponseCode_DataConnectionOpen = 225
          ,ResponseCode_DataConnectionClose = 226
          ,ResponseCode_EnterPassiveMode = 227
          ,ResponseCode_LoggedIn = 230
          ,ResponseCode_RequestedFileActionOK = 250
          ,ResponseCode_CreatePathOK = 257

          ,ResponseCode_RequirePassword = 331
          ,ResponseCode_RequireUsername = 332
          ,ResponseCode_RequestedFileActionPending = 350

          ,ResponseCode_ServiceNotAvailable = 421
          ,ResponseCode_DataConnectionOpenFailed = 425
          ,ResponseCode_TransferAborted = 426
          ,ResponseCode_FileUnavailable = 450
          ,ResponseCode_LocalError = 451
          ,ResponseCode_InsufficientStorageSpace = 452

          ,ResponseCode_CommandUnrecognized = 500
          ,ResponseCode_ArgumentsSyntaxError = 501
          ,ResponseCode_CommandNotImplemented = 502
          ,ResponseCode_BadSequenceOfCommands = 503
          ,ResponseCode_InvalidCommandArgument = 504
          ,ResponseCode_NotLoggedIn = 530
          ,ResponseCode_NeedAccountForStoringFile = 532
          ,ResponseCode_FileNotAccess = 550
          ,ResponseCode_PageTypeUnknown = 551
          ,ResponseCode_StorageAllocationExceeded = 552
          ,ResponseCode_FileNameNotAllowed = 553    
        };

        typedef std::vector<ResponseCode> ResponseCodeList;

      private:
        FtpResponseMessage()
          :m_responseCodeList()
          ,m_headerData(){

        }

        ~FtpResponseMessage(){

        }

      public:
        const std::stringstream& getHeaderData() const{
          return m_headerData;
        }

        const ResponseCodeList& getResponseCodeList() const{
          return m_responseCodeList;
        }

      private:
        ResponseCodeList m_responseCodeList;
        std::stringstream m_headerData;
        std::stringstream m_contentData;
    };

  }//namespace Network
}//namespace Magna

#endif  /*  FTPRESPONSEMESSAGE_H  */