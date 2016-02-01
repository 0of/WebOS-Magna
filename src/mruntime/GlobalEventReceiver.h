#ifndef GLOBALEVENTRECEIVER_H
#define GLOBALEVENTRECEIVER_H

#include "basedef/SpinMutex.h"
#include "basedef/DyadCoordinate.h"
#include "basedef/RectRegion.h"
#include "basedef/RunnableContext.h"
#include "basedef/AbstractedNotifier.h"
using namespace Magna::Core;

#include "render/ManipulateEngine.h"
using namespace Magna::Render;

#include "basegui/Controller_p.h"
#include "basegui/Window.h"
#include "basegui/Window_p.h"
using namespace Magna::GUI;

#include "application/OSGUIBehaviourExRequester.h"
using namespace Magna::Application;
#include "OSBehaviourNotifierHandler.h"

namespace Magna{
  namespace Runtime{

    class GlobalEventReceiver : public __Generalizes OSGUIBehaviourExRequester{
      public:
        static GlobalEventReceiver& getGlobalEventReceiver();

      protected:
        GlobalEventReceiver( OSBehaviourNotifierHandler *handler );
      public:
        ~GlobalEventReceiver();

      public:
        virtual void requestWindowRendering( ManipulateEngine& engine ) ;

        //just in script system these would be work
        virtual void requestWindowMoved( const unicode_char *, const IntegerDyadCoordinate& );
        virtual void requestDraggableWindowMove( const unicode_char *, const IntegerDyadCoordinate& , const IntegerDyadCoordinate&  );
        virtual void requestWindowResized( const unicode_char *, const IntegerSize&) ;
        virtual void requestWindowVisibilityChanged( const unicode_char *, bool ) ;
        virtual void requestWindowFocusChanged( const unicode_char *, uint32, bool ) ;

        virtual void requestControllersAttached(  std::vector<SharedPtr<Controller::ControllerRoot> > & ,RunnableContext * ) ;
        virtual void requestControllersDetached( const std::vector< uint64 > & ) ;

        virtual void requestControllerResized( const unicode_char *, const IntegerSize&  ) ;
        virtual void requestControllerMoved( const unicode_char *, const IntegerDyadCoordinate&  ) ;

        virtual void requestContentResized( const unicode_char *id, const IntegerSize& a2 ); 
        virtual void requestWrapperResized( const unicode_char *id, const IntegerSize&  a2) ;

        virtual void requestWindowClose( uint32 ) ;

        virtual void requestStartPopOutWindow( const SharedPtr<Window::WindowRoot>& ) ;
        virtual void requestStartNewWindow( const SharedPtr<Window::WindowRoot>& ) ;

        virtual void requestStartNewApplication( const String& , RunnableContext * = Nullptr ) ;
        virtual void requestStartNewApplicationWithDialog( const String& , RunnableContext * = Nullptr ) ;

        virtual void requestScriptEval( const String& sc );

        virtual void requestQtWidgetInit( QtWidgetInitializer * ) ;
        virtual void requestNotifierRunOnCore( const SharedPtr<AbstractedNotifier>& n ) ;

        virtual void askObtainApplicationInfo( const String& a1, String& a2, String& a3);

      private:
        SpinMutex m_mutex;
        OSBehaviourNotifierHandler *m_handler;
    };
  }
}//namespace Magna


#endif  /*  GLOBALEVENTRECEIVER_H  */