#ifndef OSGUIBEHAVIOUREXREQUESTER_H
#define OSGUIBEHAVIOUREXREQUESTER_H

#include "basegui/OSGUIBehaviourRequester.h"
using namespace Magna::GUI;

namespace Magna{
  namespace Application{
    
    //application level
    class OSGUIBehaviourExRequester : public OSGUIBehaviourRequester{
      public:
        virtual ~OSGUIBehaviourExRequester(){}

        virtual void requestStartNewWindow( const SharedPtr<Window::WindowRoot>& ) = 0;
        virtual void requestStartNewApplication( const String& , RunnableContext * = Nullptr ) = 0;

        virtual void requestStartNewApplicationWithDialog( const String& , RunnableContext * = Nullptr ) = 0;

        virtual void askObtainApplicationInfo( const String&, String&, String& ) = 0;
    };

  }//namespace Application
}//namespace Magna

#endif  /*  OSGUIBEHAVIOUREXREQUESTER_H  */
