#include "DesktopEventDispatcher.h"

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "DesktopWindow.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      DesktopEventDispatcher::DesktopEventDispatcher( RunnableContext *context)
        :m_context( context ){

      }

      DesktopEventDispatcher::~DesktopEventDispatcher(){

      }

      void DesktopEventDispatcher::postNewWindowRun( const SharedPtr<Window::WindowRoot>& wnd ){
        if( !wnd.isNull() ){
          auto& _desktop_wnd =  DesktopWindow::getDesktopWindow();
          assert( !_desktop_wnd.isNull() );

          try{
            if( !_desktop_wnd.isNull() ){
              auto &_wnd_status_bar = _desktop_wnd->getWindowStatusBar();
              if( !_wnd_status_bar.isNull() ){
                _wnd_status_bar->openNewWindow( wnd );
              }
              else{
                throw InnerPrivateDataNullPointerException();
              }
            }
            else{
              throw InnerPrivateDataNullPointerException();
            }
          }
          catch( const InnerPrivateDataNullPointerException& _ex ){
            abort();
          }
        }      
      }

    }
  }
}

