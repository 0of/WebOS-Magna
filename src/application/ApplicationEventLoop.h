#ifndef APPLICATIONEVENTLOOP_H
#define APPLICATIONEVENTLOOP_H

#include "application_lib.h"

#include "basedef/SpinMutex.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include "basegui/Window.h"
#include "basegui/Controller.h"
using namespace Magna::GUI;

#include "NotifierMessage.h"

#include <queue>

namespace Magna{
  namespace Application{
    typedef NotifierMessage<SharedPtr<Controller::ControllerRoot>,AbstractedEventArgs*> GUINotifierMessage;

    class ApplicationEventHandler;
    class APPLICATION_LIB_EXPORT ApplicationEventLoop{
      friend class MagnaApplication;
      friend class ApplicationWindowManager;

      public:
        ApplicationEventLoop();
        ~ApplicationEventLoop();

      public:
        void exec();
        void receiveEvent( const GUINotifierMessage& message );

      private:
        std::queue< GUINotifierMessage > m_messageQueue;
        SpinMutex m_messageMutex;

        ApplicationEventHandler *m_handler;
    };

  }//namespace Application
}//namespace Magna

#endif  /*  APPLICATIONEVENTLOOP_H  */