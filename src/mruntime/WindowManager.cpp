#include "WindowManager.h"
#include "basegui/Window_p.h"
#include "basegui/WindowAccessor.h"

#include "basegui/MouseWheelEventArgs.h"
#include "basegui/EventArgConstants.h"
#include "basegui/GUIEventIndexer.h"
using namespace Magna;

#include "basedef/RunnableContextAccessor.h"
using namespace Magna::Core;

#include "application/Application.h"
#include "application/Application_p.h"
#include "application/ApplicationWindowManager_p.h"
#include "application/ApplicationWindowManager.h"
#include "application/WindowEventNotifier.h"
using namespace Magna::Application;

#include "RuntimeScript.h"
#include "RuntimeContainer.h"
using namespace Magna::Runtime;

#include "SystemComObjectManager.h"
using namespace Magna::SystemComponent;

#include "ControllerManager.h"

#include <cassert>
  
//c++ 11 STL
#include <random>

namespace Magna{
  namespace Kernel{
    WindowManager & WindowManager::getWindowManager(){
      static WindowManager shared_windowManager;
      return shared_windowManager;
    }

    WindowManager::WindowManager()
      :m_runingWnds()
      ,m_mutex(){

    }

    WindowManager::~WindowManager(){

    }

    bool WindowManager::_startWindow( const SharedPtr<Window::WindowRoot>& wnd_root , WindowManager::WindowType type){
      bool _start_ok = false;

      SharedPtr<Window::WindowRoot> _root = wnd_root;
      if( !_root.isNull()  && _root->m_RunnableContext != Nullptr ){
        auto &&_entity = RunnableContextAccessor::getEntity( _root->m_RunnableContext );

        if( !_entity.isNull() ){

          std::random_device _dev_gen;

          std::mt19937 _base32_ram( _dev_gen() );

          uint32 _id = 0;

          //ensure id unique
          //enter critical section
          m_mutex.acquires();    
          while( [&]() -> bool{ _id = _base32_ram()
            ; return m_runingWnds.count( _id )  != 0; }() ){}         

          _root->_assignRuntimeId( _id );

          m_runingWnds.emplace( std::make_pair(_id,  std::make_pair( _root, type ) ) );
          //leave critical section
          m_mutex.releases();

          //get runtime 
          RuntimeContainer &_container = RuntimeContainer::getRuntimeContainer();

          //generate JS script
          String _element_sc =  _root->_createWindowNode();
          QString _new_wnd_sr( RuntimeScript::shared_JavaScript_Service_Provider_Window );      
          _new_wnd_sr.append( RuntimeScript::shared_JavaScript_Service_open_new_window )
            .append( "(" )
#ifdef _MSC_VER
            .append( QString::fromUtf16( reinterpret_cast<const ushort *>(_element_sc.c_str()), _element_sc.size() ) )
#else
            .append( QString::fromStdWString(_element_sc ) )
#endif
            .append( ");");
          _container.evalJavaScript( _new_wnd_sr );

          //append controllers 
          //get controller manager
          ControllerManager &_controller_manager = ControllerManager::getControllerManager();
#ifdef MAGNA_DIV_CANVAS_WRAPPER
          _controller_manager.registerControllers(_root->_ctrls_get(), &_entity->m_looper );
#else
          _controller_manager.registerControllers(_root->m_runtime_Id, _root->_ctrls_get(), loop );
#endif
          //first render
          _root->windowRender();

          _start_ok = !false;
        }
      }
      return _start_ok;
    }


    void WindowManager::startWindow( const SharedPtr<Window::WindowRoot>& wnd_root){
    //void WindowManager::startWindow( const SharedPtr<Window::WindowRoot>& wnd_root, ApplicationEventLoop &loop){
      
      if( _startWindow(wnd_root) ){
        SystemComObjectManager& _sysComObjManager = SystemComObjectManager::getSystemComObjectManager();
        auto & _desktop_obj = _sysComObjManager.getDesktopObject();
        _desktop_obj.actDispatchNewWindowRun( wnd_root );
      }
            
    }

      
        //running counter increasement
        //wndManagerData.increaseRunningWindow();

        //element id

        //generate the element  script
        //element CSS
        //append script 
        //OnceJSOpenNewWindow.triggers( _root->_createWindowNode() );  
        //_root->windowRender();
        //OnceJSRenderWindow.triggers(  _root->_getPlainElementId() , _root->_getRenderingScript() );

        //connect triggers
        //connect repeater
        //_root->OnceControllerRendered.connectAction( &OnceJSEval,  &Trigger<const std::string&>::triggers );
        //_root->OnceRendered.connectAction( &OnceJSEval,  &Trigger<const std::string&>::triggers );

        //close
        //_root->OnceClosed.connectAction( this, &WindowManager::finishWindow );
        //show
        //_root->OnceShown.connectAction( this, &WindowManager::showWindow );
        //hide
        //_root->OnceHidden.connectAction( this, &WindowManager::hideWindow );
  
    /*
    void WindowManager::startWindow( const SharedPtr<Window::WindowRoot>& wnd_root, ApplicationEventLoop &loop){
      SharedPtr<Window::WindowRoot> _root = wnd_root;
      if( !_root.isNull()  ){
        std::random_device _dev_gen;

        //clip 64 into 48 bits
        std::ranlux48_base _base64_ram( _dev_gen() );
      //  std::mersenne_twister_engine<uint64, 48, 312,156,31,0xb5026f5aa96619e9,
      //                            29,0x5555555555555555,
      //                            17,0x71d67fffeda60000,
      //                             37,0xfff7eee000000000,
      //                            43,6364136223846793005> _base64_ram( _dev_gen() );

        uint64 _id = 0;
        
        //ensure id unique
        //enter critical section
        m_mutex.acquires();    
        while( [&]() -> bool{ _id = _base64_ram()
          ; return m_runingWnds.count( _id )  != 0; }() ){}         

        _root->_assignRuntimeId( _id );
                    
        m_runingWnds.emplace( std::make_pair(_id,  std::make_pair( _root, &loop ) ) );
        //leave critical section
        m_mutex.releases();

        //running counter increasement
        //wndManagerData.increaseRunningWindow();

        //element id

        //generate the element  script
        //element CSS
        //append script 
        OnceJSOpenNewWindow.triggers( _root->_createWindowNode() );  
        _root->windowRender();
        //OnceJSRenderWindow.triggers(  _root->_getPlainElementId() , _root->_getRenderingScript() );
    
        //connect triggers
        //connect repeater
        //_root->OnceControllerRendered.connectAction( &OnceJSEval,  &Trigger<const std::string&>::triggers );
        //_root->OnceRendered.connectAction( &OnceJSEval,  &Trigger<const std::string&>::triggers );

        //close
        _root->OnceClosed.connectAction( this, &WindowManager::finishWindow );
        //show
        _root->OnceShown.connectAction( this, &WindowManager::showWindow );
        //hide
        _root->OnceHidden.connectAction( this, &WindowManager::hideWindow );
      }
    }
    */
    
    void WindowManager::finishWindow( const uint32& runtime_wid ){

      m_mutex.acquires();
      auto _it = m_runingWnds.find( runtime_wid );
      auto _end = m_runingWnds.end() ;

      if( _it != _end ){
        auto &_info = _it->second;
        auto &_root = _info.first;

        if( !_root.isNull() ){
          //ask child controllers to unregister
          ControllerManager &_ctrl_manager = ControllerManager::getControllerManager();
          _ctrl_manager.unregisterController(   _root->_ctrls_get() );

          //script
          QString _wnd_finish_script = QString( RuntimeScript::shared_JavaScript_Service_Provider_Window );
          _wnd_finish_script.append( RuntimeScript::shared_JavaScript_Service_close_window )
                          .append( "(" )
#ifdef _MSC_VER
                          .append( QString::fromUtf16( reinterpret_cast<const ushort *>( _root->m_runtime_Id ) ) )
#else
                          .append( QString::fromStdWString(  _root->m_runtime_Id ) )
#endif
                          .append( ")" );
          RuntimeContainer::getRuntimeContainer().evalJavaScript( _wnd_finish_script );

          _root->_de_assignRuntimeId();
        }
        
        if( _info.second == WindowManager::WindowType_Normal  ){
          SystemComObjectManager& _sysComObjManager = SystemComObjectManager::getSystemComObjectManager();
          auto & _desktop_obj = _sysComObjManager.getDesktopObject();
          _desktop_obj.actDispatchFinishWindow( runtime_wid );
        }

        m_runingWnds.erase( _it );
      }

      m_mutex.releases();
    }
    
    void WindowManager::showWindow( const uint32& runtime_wid){
      m_mutex.acquires();
      auto _it = m_runingWnds.find( runtime_wid );
      auto _end = m_runingWnds.end() ;
      m_mutex.releases();


      if( _it != _end ){
        auto &_info = _it->second;
        auto &_root = _info.first;

        if( !_root.isNull() ){
          //get runtime 
          RuntimeContainer &_container = RuntimeContainer::getRuntimeContainer();

          QString _new_wnd_sr( RuntimeScript::shared_JavaScript_Service_Provider_Window );      
          _new_wnd_sr.append( RuntimeScript::shared_JavaScript_Service_set_window_visible )
            .append( "(" )
#ifdef _MSC_VER
            .append( QString::fromUtf16( reinterpret_cast<const ushort *>(  _root->m_runtime_Id ) ) )
#else
            .append( QString::fromWCharArray( _root->m_runtime_Id ) )
#endif
            .append( ");");
          _container.evalJavaScript( _new_wnd_sr );
        }
        
      }
      
    }
    
    void WindowManager::hideWindow( const uint32& runtime_wid){
      m_mutex.acquires();
      auto _it = m_runingWnds.find( runtime_wid );
      auto _end = m_runingWnds.end() ;
      m_mutex.releases();

      if( _it != _end ){
        auto &_info = _it->second;
        auto &_root = _info.first;

        if( !_root.isNull() ){
          //get runtime 
          RuntimeContainer &_container = RuntimeContainer::getRuntimeContainer();

          QString _new_wnd_sr( RuntimeScript::shared_JavaScript_Service_Provider_Window );      
          _new_wnd_sr.append( RuntimeScript::shared_JavaScript_Service_set_window_hidden )
            .append( "(" )
#ifdef _MSC_VER
            .append( QString::fromUtf16( reinterpret_cast<const ushort *>(  _root->m_runtime_Id ) ) )
#else
            .append( QString::fromWCharArray( _root->m_runtime_Id ) )
#endif
            .append( ");");
          _container.evalJavaScript( _new_wnd_sr );
        }
      }
    }
    
    void WindowManager::finishAll(){     
      m_mutex.acquires();
      for( auto _each = m_runingWnds.begin()
        ; _each != m_runingWnds.end()
        ; [ & ] () {  auto &_info = _each->second;
        auto &_root = _info.first;
      _root->_de_assignRuntimeId();++_each; 
      //ApplicationWindowManager::PrivateData &_app_manager_data = _each->second.second;
      //_app_manager_data.decreaseRunningWindow();
      }() ){}        

      m_runingWnds.clear();
      m_mutex.releases();
    }

    void WindowManager::dispatchMoveEvent( const uint32& runtime_wid, sint32 x, sint32 y ){

      m_mutex.acquires();
      auto _it = m_runingWnds.find( runtime_wid );
      auto _end = m_runingWnds.end() ;
      m_mutex.releases();

      if( _it != _end ){
        //generate Event argument
        auto &_info = _it->second;
        auto &_root = _info.first;

        if( !_root.isNull() && _root->m_RunnableContext != Nullptr ){
          SharedPtr<AbstractedEventArgs> eventArgs = new MovedEventArgs( _root->_pos_get(),  IntegerDyadCoordinate( x, y) );

          SharedPtr<Message> _gen_message = new WindowEventNotifier( _root, eventArgs );

          _root->m_RunnableContext->postMessage( _gen_message );
        }      
      }

    }

    void WindowManager::dispatchResizeEvent( const uint32& runtime_wid, sint32 w, sint32 h ){

      m_mutex.acquires();
      auto _it = m_runingWnds.find( runtime_wid );
      auto _end = m_runingWnds.end() ;
      m_mutex.releases();

      if( _it != _end ){
        //generate Event argument
        auto &_info = _it->second;
        auto &_root = _info.first;

        if( !_root.isNull() && _root->m_RunnableContext != Nullptr ){
          SharedPtr<AbstractedEventArgs> eventArgs = new ResizedEventArgs( _root->_size_get(),  IntegerSize( w, h) );

          SharedPtr<Message> _gen_message = new WindowEventNotifier( _root, eventArgs );

          _root->m_RunnableContext->postMessage( _gen_message );
        }      
      }

    }

    void WindowManager::startDesktopWindow( const SharedPtr<Window::WindowRoot>& wnd_root ){
      _startWindow(wnd_root , WindowManager::WindowType_Desktop ) ;  
      //run init script
      QString _script( RuntimeScript::shared_JavaScript_Functionality_Window_Rubber_Band );
      _script.append( RuntimeScript::shared_JavaScript_Functionality_rubber_band_init )
        .append( "(" )
#ifdef _MSC_VER
        .append( QString::fromUtf16( reinterpret_cast<const ushort *>(  wnd_root->m_runtime_Id ) ) )
#else
        .append( QString::fromStdWString( wnd_root->m_runtime_Id ) )
#endif
        .append( ")" );

      RuntimeContainer &_container = RuntimeContainer::getRuntimeContainer();
      _container.evalJavaScript(_script);
    }

    void WindowManager::startPopOutWindow(  const SharedPtr<Window::WindowRoot>& wnd_root  ){
      _startWindow(wnd_root , WindowManager::WindowType_PopOut ) ;      
    }
    
  }//namespace Kernel
}//namespace Magna
