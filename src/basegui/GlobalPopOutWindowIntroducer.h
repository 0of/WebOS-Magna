#ifndef GLOBALPOPOUTWINDOWMANAGER_H
#define GLOBALPOPOUTWINDOWMANAGER_H

#include "basegui_lib.h"

#include "PopOutWindow.h"
#include "OSGUIBehaviourRequester.h"

namespace Magna{
  namespace GUI{
    
    //run on the main thread
    class BASEGUI_LIB_EXPORT GlobalPopOutWindowIntroducer{
      public:
        static GlobalPopOutWindowIntroducer &getGlobalPopOutWindowIntroducer();

      protected:
        GlobalPopOutWindowIntroducer();
        ~GlobalPopOutWindowIntroducer();

      public:
        void introducePopOutWindow( SharedPtr<Window::WindowRoot>& );
        void init(  RunnableContext *c, OSGUIBehaviourRequester *r );

      __Data_Field private:
        static GlobalPopOutWindowIntroducer shared_global_popout_wnd_introducer;

        RunnableContext *m_context;
        OSGUIBehaviourRequester *m_requester;
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  GLOBALPOPOUTWINDOWMANAGER_H  */