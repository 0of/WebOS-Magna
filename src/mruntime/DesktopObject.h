#ifndef DESKTOPOBJECT_H
#define DESKTOPOBJECT_H

#include "basedef/RunnableContext.h"
using namespace Magna::Core;

#include "basegui/Window.h"
#include "basegui/Window_p.h"
using namespace Magna::GUI;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class DesktopObject{
        public:
          typedef void (MAGNA_CDECL *disp_new_wnd_run) ( const SharedPtr<Window::WindowRoot>& );
          typedef void (MAGNA_CDECL *disp_fin_wnd_run) ( uint32 );
          typedef void (MAGNA_CDECL *disp_wnd_focus_changed) ( uint32 , bool );

        public:
          explicit DesktopObject()
            :m_RunnableContext( Nullptr )
            ,act_dispatchNewWindowRun( Nullptr )
            ,act_dispatchFinishWindow( Nullptr )
            ,act_dispatchWindowFocusChanged( Nullptr ){

          }

          ~DesktopObject(){

          }

        public:
          inline void init( RunnableContext *c
            , disp_new_wnd_run d1
            , disp_fin_wnd_run d2
            , disp_wnd_focus_changed d3){
            m_RunnableContext = ( c );
            act_dispatchNewWindowRun = ( d1 );
            act_dispatchFinishWindow = ( d2 );
            act_dispatchWindowFocusChanged = ( d3 );
          }

          inline void actDispatchNewWindowRun(  const SharedPtr<Window::WindowRoot>& _wnd_root ){
            if( act_dispatchNewWindowRun != Nullptr ){
              act_dispatchNewWindowRun( _wnd_root );
            }
          }

          inline void actDispatchFinishWindow( uint32 id ){
            if( act_dispatchFinishWindow != Nullptr ){
              act_dispatchFinishWindow( id );
            }
          }

          inline void actDispatchWindowFocusChanged( uint32 id, bool isFocusIn ){
            if( act_dispatchWindowFocusChanged != Nullptr ){
              act_dispatchWindowFocusChanged( id, isFocusIn );
            }
          }

        private:
          RunnableContext *m_RunnableContext;
          disp_new_wnd_run act_dispatchNewWindowRun;
          disp_fin_wnd_run act_dispatchFinishWindow;
          disp_wnd_focus_changed act_dispatchWindowFocusChanged;
      };

    }
  }//namespace Runtime
}//namespace Magna

#endif  /*  DESKTOPOBJECT_H  */
