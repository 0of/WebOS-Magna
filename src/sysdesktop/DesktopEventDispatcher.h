#ifndef DESKTOPEVENTDISPATCHER_H
#define DESKTOPEVENTDISPATCHER_H

#include "basedef/RunnableContext.h"
using namespace Magna::Core;

#include "basegui/Window.h"
#include "basegui/Window_p.h"
using namespace Magna::GUI;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class DesktopEventDispatcher{
        public:
          DesktopEventDispatcher( RunnableContext *context );
          ~DesktopEventDispatcher();

        public:
          void postNewWindowRun( const SharedPtr<Window::WindowRoot>& );

        private:
          RunnableContext *m_context;
      };
    }
  }
}//namespace Magna

#endif /*  DESKTOPEVENTDISPATCHER_H  */