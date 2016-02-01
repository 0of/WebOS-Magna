#include "WindowIntroducer.h"

#include "basedef/CompilerTimeAssert.h"
#include "basedef/IsBaseOf.h"
#include "basedef/private/RunnableContext_p.h"
using namespace Magna::Core;

#include "basegui/WindowAccessor.h"
using namespace Magna::GUI;

#include "Application_p.h"
#include "ApplicationWindowManager_p.h"

namespace Magna{
  namespace Application{
    /*
    template<typename WindowType>
    static SharedPtr<WindowType> WindowIntroducer::introduceWindow(MagnaApplication &app){
      typedef IsBaseOf<WindowType, Window> IsKindOfWindow;

      COMPILTER_TIME_ASSERT( IsKindOfWindow::isTrue, Must_Be_Kind_Of_Window);

      
      if( app.m_entity->m_int_runningId != 0 ){
        WindowType *_wnd = new WindowType;
        //assign runable context to window

        auto &_root = WindowAccessor::getRoot( _wnd );

        auto &_handler = app.m_data->m_eventHandler;

        //application event handler
        if( !_root.isNull() ){
          _root->OnceRendered.connectAction( &_handler.OnceWindowRender
            , &Trigger<ManipulateEngine&>::triggers );
        }

      }
    }
*/
    void WindowIntroducer::introduceWindow( MagnaApplication &app,  const SharedPtr<Window>& wnd){
      if( app.m_entity->m_int_runningId != 0
        && !wnd.isNull() ){
      
        //assign runable context to window
        auto &&_root = WindowAccessor::getRoot( wnd );

        if( _root->m_int_runtimeId == 0 ){

          auto &_handler = app.m_data->m_eventHandler;

          //application event handler
          if( !_root.isNull() ){
            _root->m_requester = &_handler;
          }
           //binding application
          _root->m_RunnableContext = &app;

          //push into window manager
          auto &_manager = app.m_data->m_wndManager;
          if( _manager.m_data != Nullptr ){
            _manager.m_data->postRunningWindow( wnd );
          }

          _handler.requestStartNewWindow(_root );
        }      

      }
    }

  }//namespace Application
}//namespace Magna
