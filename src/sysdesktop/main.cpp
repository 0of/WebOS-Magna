
#include "DesktopApplication.h"

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#ifdef __cplusplus
extern "C"{
#endif  /*  __cplusplus  */
  //External Entry Def
  //__declspec(dllexport)  SharedPtr<DesktopEventDispatcher> __cdecl _magna_fetch_desktop_disp( RunnableContext *);  
  __declspec(dllexport)  void __cdecl _magna_desktop_disp_new_wnd_run( const SharedPtr<Window::WindowRoot>& );  
  __declspec(dllexport)   void __cdecl _magna_desktop_disp_finish_wnd( uint32 id );
  __declspec(dllexport)   void __cdecl _magna_desktop_disp_wnd_focus_changed( uint32 , bool  );
#ifdef __cplusplus
}
#endif  /*  __cplusplus  */

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{
      static uint32 shared_desktop_notifier = AbstractedNotifier::registerNotifierType( 55360 );  
      static MagnaApplication shared_desktop_instance( L"desktop" );

      class NewWindowNotifier : public AbstractedNotifier{
      public:
        NewWindowNotifier( const SharedPtr<Window::WindowRoot>& wnd_root)
          :AbstractedNotifier( shared_desktop_notifier )
          ,m_wnd_root( wnd_root ){}
        virtual ~NewWindowNotifier(){}

      public:
        virtual void notify(){
          if( !m_wnd_root.isNull() ){
            auto& _desktop_wnd =  DesktopWindow::getDesktopWindow();
            assert( !_desktop_wnd.isNull() );
            try{
              if( !_desktop_wnd.isNull() ){
                auto &_wnd_status_bar = _desktop_wnd->getWindowStatusBar();
                if( !_wnd_status_bar.isNull() ){
                  _wnd_status_bar->openNewWindow( m_wnd_root );
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

      private:
        SharedPtr<Window::WindowRoot> m_wnd_root;
      };

      class FinishWindowNotifier : public AbstractedNotifier{
      public:
        FinishWindowNotifier( uint32 id )
          :AbstractedNotifier( shared_desktop_notifier )
          ,m_id( id ){}
        virtual ~FinishWindowNotifier(){}

      public:
        virtual void notify(){
          if( m_id != 0 ){
            auto& _desktop_wnd =  DesktopWindow::getDesktopWindow();
            assert( !_desktop_wnd.isNull() );
            try{
              if( !_desktop_wnd.isNull() ){
                auto &_wnd_status_bar = _desktop_wnd->getWindowStatusBar();
                if( !_wnd_status_bar.isNull() ){
                  _wnd_status_bar->closeWindow( m_id );
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

      private:
        uint32 m_id;
      };

      class WindowFocusChangedNotifier : public AbstractedNotifier{
      public:
        WindowFocusChangedNotifier( uint32 id , bool isFocusIn )
          :AbstractedNotifier( shared_desktop_notifier )
          ,m_id( id )
          ,m_isFocusIn( isFocusIn ){}
        virtual ~WindowFocusChangedNotifier(){}

      public:
        virtual void notify(){
          if( m_id != 0 ){
            auto& _desktop_wnd =  DesktopWindow::getDesktopWindow();
            assert( !_desktop_wnd.isNull() );
            try{
              if( !_desktop_wnd.isNull() ){
                auto &_wnd_status_bar = _desktop_wnd->getWindowStatusBar();
                if( !_wnd_status_bar.isNull() ){
                  _wnd_status_bar->actWhenWindowFocusChanged( m_id, m_isFocusIn );
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

      private:
        //align 4 bytes
        uint32 m_id;
        bool m_isFocusIn;
      };
    }
  }
}


void _Main(){
  DesktopApplication::pInstance = &shared_desktop_instance;

  auto &_wnd = DesktopWindow::getDesktopWindow();

  shared_desktop_instance.setupMainWindow( _wnd );

  shared_desktop_instance.exec();
}

extern "C"__declspec(dllexport) 
void __cdecl _magna_desktop_disp_new_wnd_run( const SharedPtr<Window::WindowRoot>& _wnd_root){
  if( !_wnd_root.isNull() ){
    SharedPtr<Message> _gen = new NewWindowNotifier( _wnd_root );
    shared_desktop_instance.postMessage( _gen );
  }      
}

extern "C"__declspec(dllexport) 
  void __cdecl _magna_desktop_disp_finish_wnd( uint32 id ){
    if( id != 0 ){
      SharedPtr<Message> _gen = new FinishWindowNotifier( id );
      shared_desktop_instance.postMessage( _gen );
    }      
}

extern "C"__declspec(dllexport) 
void __cdecl _magna_desktop_disp_wnd_focus_changed( uint32 id, bool isFocusIn ){
  if( id != 0 ){
    SharedPtr<Message> _gen = new WindowFocusChangedNotifier( id , isFocusIn );
    shared_desktop_instance.postMessage( _gen );
  }      
}

/*
extern "C"__declspec(dllexport) 
SharedPtr<DesktopEventDispatcher>  __cdecl _magna_fetch_desktop_disp( RunnableContext * desktopObj ){
  assert( desktopObj != Nullptr );
  SharedPtr<DesktopEventDispatcher>_dispatch = new DesktopEventDispatcher( desktopObj );
  return _dispatch;
}
*/
