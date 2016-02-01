#ifndef OSGUIBEHAVIOURREQUESTER_H
#define OSGUIBEHAVIOURREQUESTER_H

#include "basegui_lib.h"

#include "basedef/RunnableContext.h"
#include "basedef/AbstractedNotifier.h"
using namespace Magna::Core;

#include "Window.h"
#include "Controller.h"
#include "Controller_p.h"
#include "QtWidgetInitializer.h"
using namespace Magna::GUI;

namespace Magna{
  namespace GUI{
    //interface
    //GUI level  
    __Interface class BASEGUI_LIB_EXPORT OSGUIBehaviourRequester{
      public:
        virtual ~OSGUIBehaviourRequester() {};

        virtual void requestWindowRendering( ManipulateEngine& engine ) = 0;

        //just in script system these would be work
        virtual void requestWindowMoved( const unicode_char *, const IntegerDyadCoordinate& ) = 0;
        virtual void requestDraggableWindowMove( const unicode_char *, const IntegerDyadCoordinate& , const IntegerDyadCoordinate&  ) = 0;
        virtual void requestWindowResized( const unicode_char *, const IntegerSize&) = 0;
        virtual void requestWindowVisibilityChanged( const unicode_char *, bool ) = 0;
        virtual void requestWindowFocusChanged( const unicode_char *, uint32, bool ) = 0;

        virtual void requestControllersAttached(  std::vector<SharedPtr<Controller::ControllerRoot> > & ,RunnableContext * ) = 0;

        virtual void requestControllerResized( const unicode_char *, const IntegerSize&  ) = 0;
        virtual void requestControllerMoved( const unicode_char *, const IntegerDyadCoordinate&  ) = 0;

        virtual void requestContentResized( const unicode_char *, const IntegerSize&  ) = 0;
        virtual void requestWrapperResized( const unicode_char *, const IntegerSize&  ) = 0;

        virtual void requestWindowClose( uint32 ) = 0;
        virtual void requestControllersDetached( const std::vector< uint64 > & ) = 0;

        virtual void requestStartPopOutWindow( const SharedPtr<Window::WindowRoot>& ) = 0;

        virtual void requestScriptEval( const String& sc ) = 0;
        virtual void requestQtWidgetInit( QtWidgetInitializer * ) = 0;
    
        virtual void requestNotifierRunOnCore( const SharedPtr<AbstractedNotifier>& ) = 0;
      protected:
        OSGUIBehaviourRequester(){}
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  OSGUIBEHAVIOURREQUESTER_H  */
