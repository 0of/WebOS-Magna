#include "ControllerManager.h"

#include "RuntimeScript.h"
#include "RuntimeContainer.h"
using namespace Magna::Runtime;

#include <random>

namespace Magna{
  namespace Kernel{

    ControllerManager & ControllerManager::getControllerManager(){
      static ControllerManager controllerManager;
      return controllerManager;
    }

    /*
    void ControllerManager::registerControllers( const std::vector<SharedPtr<Controller::ControllerRoot> >&& ctrl_roots,  RunnableMessageLooper * loop){
      auto _iter = ctrl_roots.begin();
      //get runtime 
      RuntimeContainer &_container = RuntimeContainer::getRuntimeContainer();

      for( ; _iter != ctrl_roots.end() ; ++_iter ){
        SharedPtr<Controller::ControllerRoot> controller_root = (*_iter);
        if( !controller_root.isNull() && loop != Nullptr ){
          std::random_device _dev_gen;

          std::ranlux48_base _base64_ram( _dev_gen() );

          uint64 _id = 0;

          //ensure id unique
          //enter critical section
          m_mutex.acquires();    
          while( [&]() -> bool{ _id = _base64_ram()
            ; return m_runingCtrls.count( _id )  != 0; }() ){}         

          controller_root->_assignRuntimeId( _id );

          m_runingCtrls.emplace( std::make_pair(_id,  std::make_pair( controller_root, loop ) ) );
          //leave critical section
          m_mutex.releases();

          //generate JS script
          String _element_sc =  controller_root->_createControllerNode();
          QString _new_wnd_sr( RuntimeScript::shared_JavaScript_Service_Provider_Controller );      
          _new_wnd_sr.append( RuntimeScript::shared_JavaScript_Service_register_new_controller)
            .append( "(" )
#ifdef _MSC_VER
            .append( QString::fromUtf16( reinterpret_cast<const ushort *>(_element_sc.c_str()), _element_sc.size() ) )
#else
            .append( QString::fromStdWString(_element_sc ) )
#endif
            .append( ");");
          _container.evalJavaScript( _new_wnd_sr );
        }
      }    
    }
    */

#ifdef MAGNA_DIV_CANVAS_WRAPPER
    //void ControllerManager::registerController( const SharedPtr<Controller::ControllerRoot>& controller_root,  ApplicationEventLoop &loop ){
    void ControllerManager::registerController(  const SharedPtr<Controller::ControllerRoot>& controller_root ,  RunnableMessageLooper *loop ){
#else  
    void ControllerManager::registerController( const unicode_char* wnd_id, const SharedPtr<Controller::ControllerRoot>& controller_root,  ApplicationEventLoop &loop ){
#endif
      SharedPtr<Controller::ControllerRoot> _controller_root = controller_root;
      if( !controller_root.isNull() && loop != Nullptr){
        std::random_device _dev_gen;

        std::ranlux48_base _base64_ram( _dev_gen() );

        uint64 _id = 0;

        //ensure id unique
        //enter critical section
        m_mutex.acquires();    
        while( [&]() -> bool{ _id = _base64_ram()
          ; return m_runingCtrls.count( _id )  != 0; }() ){}         

        _controller_root->_assignRuntimeId( _id );

        m_runingCtrls.emplace( std::make_pair(_id,  std::make_pair( controller_root, loop ) ) );
        //leave critical section
        m_mutex.releases();

        //get runtime 
        RuntimeContainer &_container = RuntimeContainer::getRuntimeContainer();

        //generate JS script
        String _element_sc =  _controller_root->_createControllerNode();
        QString _new_wnd_sr( RuntimeScript::shared_JavaScript_Service_Provider_Controller );      
        _new_wnd_sr.append( (controller_root->m_attributes & Controller::ControllerRoot::Attribute_Protogenous) != 0 ?
          RuntimeScript::shared_JavaScript_Service_register_protogenous_controller :
        RuntimeScript::shared_JavaScript_Service_register_new_controller )
          .append( "(" )
#ifdef _MSC_VER
          .append( QString::fromUtf16( reinterpret_cast<const ushort *>(_element_sc.c_str()), _element_sc.size() ) )
#else
          .append( QString::fromStdWString(_element_sc ) )
#endif
          .append( ");");
        _container.evalJavaScript( _new_wnd_sr );

      }

    }

#ifdef MAGNA_DIV_CANVAS_WRAPPER 
    //void ControllerManager::registerControllers( const std::vector<SharedPtr<Controller::ControllerRoot> >& ctrl_roots,  ApplicationEventLoop &loop ){
    void ControllerManager::registerControllers( const std::vector<SharedPtr<Controller::ControllerRoot> >& ctrl_roots,  RunnableMessageLooper *loop ){
#else  
    void ControllerManager::registerControllers( const unicode_char* wnd_id, const std::vector<SharedPtr<Controller::ControllerRoot> >& wnd_roots,  ApplicationEventLoop &loop ){
#endif
      auto _iter = ctrl_roots.begin();
      //get runtime 
      RuntimeContainer &_container = RuntimeContainer::getRuntimeContainer();

      for( ; _iter != ctrl_roots.end() ; ++_iter ){
        SharedPtr<Controller::ControllerRoot> controller_root = (*_iter);
        if( !controller_root.isNull() && loop != Nullptr ){
          std::random_device _dev_gen;

          std::ranlux48_base _base64_ram( _dev_gen() );

          uint64 _id = 0;

          //ensure id unique
          //enter critical section
          m_mutex.acquires();    
          while( [&]() -> bool{ _id = _base64_ram()
            ; return m_runingCtrls.count( _id )  != 0; }() ){}         

          controller_root->_assignRuntimeId( _id );

          m_runingCtrls.emplace( std::make_pair(_id,  std::make_pair( controller_root, loop ) ) );
          //leave critical section
          m_mutex.releases();

          //generate JS script
          String _element_sc =  controller_root->_createControllerNode();
          QString _new_wnd_sr( RuntimeScript::shared_JavaScript_Service_Provider_Controller );    

      _new_wnd_sr.append( (controller_root->m_attributes & Controller::ControllerRoot::Attribute_Protogenous) != 0 ?
        RuntimeScript::shared_JavaScript_Service_register_protogenous_controller :
        RuntimeScript::shared_JavaScript_Service_register_new_controller )
          .append( "(" )
#ifdef _MSC_VER 
            .append( QString::fromUtf16( reinterpret_cast<const ushort *>(_element_sc.c_str()), _element_sc.size() ) )
#else
            .append( QString::fromStdWString(_element_sc ) )
#endif
            .append( ");");
          _container.evalJavaScript( _new_wnd_sr );
        }
      }    
    }

    void ControllerManager::unregisterController( const uint64& id ){
      if( id != 0 ){
        auto _found = m_runingCtrls.find( id );
        if( _found != m_runingCtrls.end() ){
          auto &_found_root =_found->second.first;
          if( !_found_root.isNull() ){
            _found_root->_de_assignRuntimeId();
          }

          m_runingCtrls.erase( _found );
        }
      }
    }

    void ControllerManager::unregisterController( const std::vector<uint64>& ids ){
      auto _iter = ids.begin();
      for(; _iter != ids.end(); ++_iter ){

        auto _found = m_runingCtrls.find( *_iter );
        if( _found != m_runingCtrls.end() ){
          auto &_found_root =_found->second.first;
          if( !_found_root.isNull() ){
            _found_root->_de_assignRuntimeId();
          }

          m_runingCtrls.erase( _found );
        }
      }
    }

    void ControllerManager::unregisterController( const std::vector<SharedPtr<Controller::ControllerRoot> >& ctrls){
      m_mutex.acquires();  
      auto _iter = ctrls.begin();
      for(; _iter != ctrls.end(); ++_iter ){
        auto _id = (*_iter)->m_int_runtimeId;
        auto _found = m_runingCtrls.end();
        if( _id != 0 ){
          auto _found = m_runingCtrls.find( _id );

          if( _found != m_runingCtrls.end() ){
            auto &_found_root =_found->second.first;
            if( !_found_root.isNull() ){
              _found_root->_de_assignRuntimeId();
            }

            m_runingCtrls.erase( _found );
          }
        }    
      }
      m_mutex.releases();  
    }

    void ControllerManager::registerDynamicControllers( const std::vector<SharedPtr<Controller::ControllerRoot> >& c ,  RunnableMessageLooper *l ){
      if( !c.empty() ){
        registerControllers( c, l );
        //get first one which its the top one
        auto &_top = c.at(0);

        if( !_top.isNull() && _top->m_int_runtimeId != 0 ){
            //update it's parent
          if( _top->m_parentLayout != Nullptr ){
            auto *_attached_wnd = _top->m_parentLayout->getAttachedWindow() ;
            if( _attached_wnd != Nullptr
              && _top->m_parentLayout->isWindowParent() ){
              _attached_wnd->update();
            }
            else{
              Controller *_parent_ = Nullptr;
              _top->m_parentLayout->getParent( _parent_ );
              if( _parent_!= Nullptr ){
                _parent_->update();
              }
            }
          }
        }
      }    

    }

    void ControllerManager::unregisterDynamicController( const std::vector<uint64>& ids ){
      if( !ids.empty() ){
        uint64 _top = ids.at(0);
        m_mutex.acquires();  
        auto _found = m_runingCtrls.find( _top );

        if( _found != m_runingCtrls.end() ){
          auto &_found_root =_found->second.first;
          //remove script
          QString _unregister_sc( RuntimeScript::shared_JavaScript_Service_Provider_Controller );      
          _unregister_sc.append( RuntimeScript::shared_JavaScript_Service_unregister_controller )
            .append( "(" )
#ifdef _MSC_VER 
            .append( QString::fromUtf16( reinterpret_cast<const ushort *>( _found_root->_runtime_elementId_get() ) ) )
#else
            .append( QString::fromStdWString( _found_root->_runtime_elementId_get() ) )
#endif
            .append( ");");
    
          RuntimeContainer &_container = RuntimeContainer::getRuntimeContainer();
          _container.evalJavaScript( _unregister_sc );
        }
        m_mutex.releases();  

        unregisterController( ids );      
      }
    }

  }
}//namespace Magna
