#ifndef APPLICATION_P_H
#define APPLICATION_P_H

#include "basedef/AbstractedEventArgs.h"

#include "NotifierMessage.h"
#include "Application.h"
#include "ApplicationWindowManager.h"
#include "ApplicationEventHandler.h"
#include "ApplicationEventLoop.h"

namespace Magna{
  namespace Application{


    class APPLICATION_LIB_EXPORT MagnaApplication::PrivateData{
    public:
      PrivateData(const String& appName);
      ~PrivateData();

      String m_appName;
      String m_appPath;

      ApplicationEventHandler m_eventHandler;

      ApplicationWindowManager m_wndManager;
    };

    /*
    class APPLICATION_LIB_EXPORT MagnaApplication::PrivateData{
      public:
        PrivateData(const assic_char* appName);
        ~PrivateData();

        assic_char *m_appName;
        assic_char *m_appPath;
        //AtomicInt m_messageCode;
        ApplicationEventLoop m_loop;
        ApplicationEventHandler m_eventHandler;

        ApplicationWindowManager m_wndManager;
        //event handler
        //send and receive event
        

        //std::queue< GUINotifierMessage > m_messageQueue;
        //SpinMutex m_messageMutex;

        //SharedPtr<Window> m_mainWnd;

      public:
        //void sendWindowNotifierMessage( const NotifierMessage<SharedPtr<Window::WindowRoot> , AbstractedEventArgs *>& message );
        //ApplicationWindowManager::PrivateData &getAppWindowManagerData();
    };
    */
  }//namespace Application
}//namespace Magna

#endif  /*  APPLICATION_P_H  */