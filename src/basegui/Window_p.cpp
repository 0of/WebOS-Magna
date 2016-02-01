//privates
#include "Window_p.h"
#include "Controller_p.h"
#include "Layout_p.h"

//inner
#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "GUIEventDelegatorManager.h"
#include "AbsoluteLayout.h"
#include "LinearLayout.h"
//accessor
#include "ControllerAccessor.h"
#include "RenderingEventArgsAccessor.h"
#include "GUIConstantMapper.h"

#include <sstream>
//c++ 11 STL

namespace Magna{  
   namespace GUI{

     Window::WindowRoot::WindowRoot( Window &bindingWindow)
       :m_properties()
       ,m_binding( bindingWindow )
       ,m_impl( Nullptr )
       ,m_int_runtimeId(0)
      ,m_runtime_Id( Nullptr )
      ,m_RunnableContext( Nullptr )
      ,m_requester( Nullptr ){
  

     }

     Window::WindowRoot::WindowRoot( Window &bindingWindow, Window::WindowAttributes attributes  )
       :m_properties()
       ,m_binding( bindingWindow )
       ,m_impl( Nullptr )
       ,m_int_runtimeId(0)
       ,m_runtime_Id( Nullptr )
       ,m_RunnableContext( Nullptr )
       ,m_requester( Nullptr ){

      m_properties.m_windowAttributes = attributes;
  
     }

    Window::WindowRoot::~WindowRoot(){
      
     }

    std::vector<SharedPtr<Controller::ControllerRoot> > Window::WindowRoot::_ctrls_get() const{
      std::vector<SharedPtr<Controller::ControllerRoot> > _ret_list;

      //frame layout
      auto &_frame = m_properties.m_frameController;
      if( !_frame.isNull() ){
        auto &_root = _frame->m_root;
        if( !_root.isNull() ){
          _ret_list.push_back( _root );

          auto &&_each_controller_roots = _root->_ctrls_get();
          _ret_list.insert( _ret_list.end(), _each_controller_roots.begin(), _each_controller_roots.end() );
        }            
      }


      auto &_layout = m_properties.m_centreLayout;
      //only contains frame
      if( !_layout.isNull() ){
        m_properties.m_mutex.acquires();

        auto &&_controllers = _layout->getChildControllers();

        auto _iter = _controllers.begin();
        for( ; _iter != _controllers.end() ; ++_iter){
          auto &_each = (*_iter);
          if( ! _each.isNull() ){
            auto &_each_root = _each->m_root;
            if( !_each_root.isNull() ){
              _ret_list.push_back( _each_root );

              auto &&_each_controller_roots = _each_root->_ctrls_get();
              _ret_list.insert( _ret_list.end(), _each_controller_roots.begin(), _each_controller_roots.end() );
            }
          }
        }    
        m_properties.m_mutex.releases();
      }  
      return _ret_list;
    }

    void Window::WindowRoot::_impl_init( const SharedPtr<WindowImplementor>& impl ){
      if( !impl.isNull() ){
        m_impl = impl;
      }
    }

    void Window::WindowRoot::_script_eval( const String& sc ){
      if( !sc.empty() && m_int_runtimeId != 0 
        && m_RunnableContext != Nullptr && m_requester != Nullptr ){
        m_requester->requestScriptEval( sc );
      }
    }

    void Window::WindowRoot::_impl_set( const SharedPtr<WindowImplementor>& impl ){
      if( !impl.isNull() ){
        m_properties.m_mutex.acquires();
        m_impl = impl;
        m_properties.m_mutex.releases();
      }
    }
  

    SharedPtr<WindowImplementor> Window::WindowRoot::_impl_get(){
      SharedPtr<WindowImplementor> _ret_impl;
      m_properties.m_mutex.acquires();
      _ret_impl = m_impl;
      m_properties.m_mutex.releases();
      return _ret_impl;
    }
  
    String Window::WindowRoot::_createWindowNode(){
      assert( m_int_runtimeId != 0 && m_runtime_Id != Nullptr );
      //d3d3d3
      OutStringStream _outter;
      _outter << m_runtime_Id
        << L", 'border:3px solid #000000; position: absolute; overflow:hidden;outline:none;\
        -webkit-box-shadow: 5px 5px 3px rgba(0,0,0,0.1), 4px 4px 3px rgba(0,0,0,0.1), 3px 3px 3px rgba(0,0,0,0.1), 2px 2px 3px rgba(0,0,0,0.1), 1px 1px 3px rgba(0,0,0,0.1);"
        << L"left:" << m_properties.m_boundingRect.getTopLeftCoord().getX() 
        << L"px; top:" << m_properties.m_boundingRect.getTopLeftCoord().getY() 
        <<L"px; width:" <<  m_properties.m_boundingRect.getWidth()
        <<L"px; height:" << m_properties.m_boundingRect.getHeight() 
        << L"px;border-style:" << GUIConstantMapper::BorderStyleMapper[ m_properties.m_borderStyle ]
        <<L";border-width: " << m_properties.m_borderWidth 
        <<L"px;border-color: " 
        << m_properties.m_borderColor.toString( Color::ColorStringFormat_Numeric_RGB, Color::ColorStringQualifier_NumberSign)
        << L";";

      if( !m_properties.m_backgroundBrush.isNull() ){
        const auto &_content = m_properties.m_backgroundBrush.getBrushContent();
      
        if( _content == FillBrush::BrushContent_Texture ){
          const auto &_texture_img = m_properties.m_backgroundBrush.getTexture();
          const String &_path = _texture_img.getLoadPath();
          if( !_path.empty() ){
            _outter << L"background:url(\""
              //url format
              << "file:///"  << _path << L"\");background-size: 100% 100%;";
          }    
        }
        else if( _content == FillBrush::BrushContent_Color ){
          const auto &_content_color = m_properties.m_backgroundBrush.getColor();
            _outter << L"background:";
            //url format
            if( _content_color.getAlphaChannel() != 255 ){
              _outter << _content_color.toString( Color::ColorStringFormat_Warpper_RGBA
                , Color::ColorStringQualifier_None
                ,  Color::ColorStringNumericBase_Decimal );
            }
            else{
              _outter << _content_color.toString( Color::ColorStringFormat_Numeric_RGB 
                , Color::ColorStringQualifier_NumberSign );
            }
          _outter << L";";
        }
      }
      else{
        _outter << L"background: #FFFFFF; ";
      }

      _outter << "'";

      return _outter.str();
    }

    void Window::WindowRoot::_assignRuntimeId( const uint32& id){
      try{
        if( m_int_runtimeId == 0 
          && m_runtime_Id == Nullptr ){
          m_int_runtimeId = id;

          const String& _id_seri =  std::to_wstring( static_cast<uint64>(id) );
          size_t _len = _id_seri.size();
          m_runtime_Id = new unicode_char[ (_len + 3) ];

          ::memcpy( (m_runtime_Id + 1), _id_seri.c_str(), _len * sizeof( unicode_char )  );

          *(m_runtime_Id) = L'\'';
          *(m_runtime_Id + _len + 1 ) = L'\'';
          *(m_runtime_Id + _len + 2 ) = L'\0';

          //start the window
          //binding layout
          if( !m_properties.m_centreLayout.isNull() ){
            auto &_layout_data = m_properties.m_centreLayout->m_layout;
            if( !_layout_data.isNull() ){
              _layout_data->bindWindow( &m_binding );
            }  
          }

          if( !m_properties.m_frameController.isNull() 
            && !m_properties.m_frameController->m_root.isNull() ){
              m_properties.m_frameController->m_root->_width_set( _size_get().getWidth() );
          }

          //
          //frame controller
          if( !m_properties.m_frameLayout.isNull() ){
            auto &_layout_data = m_properties.m_frameLayout->m_layout;
            if( !_layout_data.isNull() ){
              _layout_data->bindWindow( &m_binding );
            }  

            m_properties.m_frameLayout->measure();
            m_properties.m_frameLayout->deploy();
          }
          /*
          if( !m_properties.m_frameController.isNull() ){
            auto &_frame_layout = m_properties.m_frameController->getLayout();
            if( !_frame_layout.isNull() ){
              auto &_frame_layout_data = _frame_layout->m_layout;
              if( !_frame_layout_data.isNull() ){
                _frame_layout_data->bindWindow( &m_binding );
              }

              _frame_layout->measure();
              _frame_layout->deploy();
            }
          }    
          */

          if( !m_properties.m_centreLayout.isNull() ){        
            m_properties.m_centreLayout->measure();
            m_properties.m_centreLayout->deploy();
          }
          
        }
        else{
          throw std::runtime_error("Running Window Exists");
        }
      }
      catch( const std::runtime_error& ex ){
        //pass to Ex-handler
        ex.what();
      }    
    }

    void Window::WindowRoot::_de_assignRuntimeId(){
      m_int_runtimeId = 0;
      if( m_runtime_Id != Nullptr ){
        delete [] m_runtime_Id;
        m_runtime_Id = Nullptr;

        //de-running window
        if( !m_properties.m_centreLayout.isNull() ){
          auto &_layout_data = m_properties.m_centreLayout->m_layout;
          if( !_layout_data.isNull() ){
            _layout_data->unbindWindow();
          }
        }

      }
    }

    const unicode_char * Window::WindowRoot::_getPlainElementId() {
      const unicode_char *_ret_str = Nullptr;
      if( m_runtime_Id == Nullptr ){
        if( m_int_runtimeId != 0 ){
          const String& _id_seri =  std::to_wstring( static_cast<uint64>(m_int_runtimeId) );
          size_t _len = sizeof( uint64 );
          m_runtime_Id = new unicode_char[ ++_len ];

          ::memcpy( m_runtime_Id , _id_seri.c_str(), _len );
        }
        _ret_str = m_runtime_Id;
      }
      else{
        _ret_str = m_runtime_Id;
      }
      return _ret_str;
    }

    void Window::WindowRoot::_stateChanged( const WindowPropertySet::StateValue& stateName, bool isTurnOn){

      switch( stateName ){
        case WindowPropertySet::State_Show:
          if( isTurnOn ){
            ShowEventArgs _gen_args;
            windowShown(_gen_args);
          }
          else{
            HideEventArgs _gen_args;
            windowHidden( _gen_args );
          }
          break;

        case WindowPropertySet::State_Focus:
          if( isTurnOn ){
            FocusEventArgs _gen_args( GUIEventConstants::GUIEvent_FocusIn );
            windowFocused( _gen_args );
          }
          else{
            FocusEventArgs _gen_args( GUIEventConstants::GUIEvent_FocusOut );
            windowFocused( _gen_args );
          }
          break;

        default:
          break;
      }    

    }

    void Window::WindowRoot::_dispatchEventMessage( AbstractedEventArgs &eventArgs ){

      WindowRootDelegatorManager &_manager = WindowRootDelegatorManager::obtainDelegator();
      auto _delegator = _manager.getDelegator( static_cast< GUIEventConstants::EventType >(eventArgs.getType()) );
      assert( _delegator != NullDelegator() );
      if(_delegator != NullDelegator() ){
        _delegator.invoke( *this , eventArgs );
      }

    }

    void Window::WindowRoot::_attachController( SharedPtr<Controller::ControllerRoot>& _ctrl_root){
      if( m_int_runtimeId != 0 && m_RunnableContext != Nullptr
        && !_ctrl_root.isNull() && m_requester != Nullptr){

        std::vector<SharedPtr<Controller::ControllerRoot> > _sum_ctrls ;
        std::vector<SharedPtr<Controller::ControllerRoot> > && _moved_ctrls = _ctrl_root->_ctrls_get();
        _sum_ctrls.reserve( ( _moved_ctrls.size() + 1 )  );

        _sum_ctrls.push_back( _ctrl_root );
        _sum_ctrls.insert(  _sum_ctrls.end(), _moved_ctrls.begin(), _moved_ctrls.end() );

        auto *_parent_layout = _ctrl_root->m_parentLayout;
        if(_parent_layout != Nullptr ){
          _parent_layout->measure();
          _parent_layout->deploy();
        }    

        //sum controllers vector will be cleared
        m_requester->requestControllersAttached( _sum_ctrls, m_RunnableContext );
        //OnceControllersAttached.triggers( _sum_ctrls,m_RunnableContext );
      }
    }

    void Window::WindowRoot::_detachController( SharedPtr<Controller::ControllerRoot>& _ctrl_root ){
      if( m_int_runtimeId != 0 
        && m_RunnableContext != Nullptr
        && !_ctrl_root.isNull() 
        && _ctrl_root->m_int_runtimeId != 0 ){

        std::vector< uint64 > _sum_ids;
        auto && _moved_ctrls = _ctrl_root->_ctrls_get();
        _sum_ids.reserve( ( _moved_ctrls.size() + 1 ) );

        _sum_ids.push_back( _ctrl_root->m_int_runtimeId );
        for( auto _iter = _moved_ctrls.begin(); _iter != _moved_ctrls.end(); ++_iter ){
          if( !_iter->isNull() ){
            _sum_ids.push_back( (*_iter)->m_int_runtimeId );
          }  
        }
  
        OnceControllersDetached.triggers( _sum_ids );

        if( !m_properties.m_centreLayout.isNull() ){
          m_properties.m_centreLayout->measure();
          m_properties.m_centreLayout->deploy();
        }

        m_requester->requestControllersDetached( _sum_ids );
      }
    }

    void Window::WindowRoot::_controller_focus( Controller *_controller ){
      
      if( m_properties.m_focusController != Nullptr ){
        auto && _root = ControllerAccessor::getRoot( m_properties.m_focusController );
        if( !_root.isNull() ){
          FocusEventArgs _focus_event_args( GUIEventConstants::GUIEvent_FocusIn );
          _root->focusOut( _focus_event_args );
        }      
        m_properties.m_focusController = _controller;
      }
    }

    void Window::WindowRoot::_controller_de_focus( Controller *_controller ){
      if( m_properties.m_focusController == _controller ){
        m_properties.m_focusController = Nullptr;
      }
    }  

    void Window::WindowRoot::windowClose( CloseEventArgs& eventArgs ){

      if( m_int_runtimeId != 0 && eventArgs .isAccepted() ){      
        if( !m_impl.isNull() ){
          m_impl->windowClose(eventArgs);
        }

        //users
        auto &_delegator = m_properties.m_delegatorCollection.onClose;
        if( _delegator != NullDelegator() ){
          _delegator.invoke( m_binding, eventArgs );
        }  

        //triggers
        m_binding.OnceClosed.triggers();

        m_requester->requestWindowClose( m_int_runtimeId );
      }
    }

    void Window::WindowRoot::windowHidden( HideEventArgs& eventArgs ){
      if( eventArgs .isAccepted() 
        && !m_properties.m_stateSwitcher.isStateOn( WindowPropertySet::State_Show  ) ){    

        if( !m_impl.isNull() ){
          m_impl->windowHide( eventArgs );
        }

        //users
        auto &_delegator = m_properties.m_delegatorCollection.onHide;
        if( _delegator != NullDelegator() ){
          _delegator.invoke( m_binding, eventArgs );
        }

        //    hide & close
        if( m_int_runtimeId != 0 ){
          m_requester->requestWindowVisibilityChanged( m_runtime_Id, false );
        }
        
        //triggers
        m_binding.OnceHidden.triggers();
      }
    }

    void Window::WindowRoot::windowShown( ShowEventArgs& eventArgs ){

      if( eventArgs .isAccepted() ){  

        if( !m_impl.isNull() ){
          m_impl->windowShow( eventArgs );
        }

        //users
        auto &_delegator = m_properties.m_delegatorCollection.onShow;
        if( _delegator != NullDelegator() ){
          _delegator.invoke( m_binding, eventArgs );
        }
      
        //triggers
        m_binding.OnceShown.triggers();

        if( m_int_runtimeId != 0 ){
          m_requester->requestWindowVisibilityChanged( m_runtime_Id, !false );
        }
        
      }
    }


    void Window::WindowRoot::windowRender(){
      if( m_int_runtimeId != 0 && m_requester != Nullptr 
        &&m_properties.m_stateSwitcher.isStateOn( WindowPropertySet::State_Show)){
        
        //get engine
        ManipulateEngine & _engine = m_binding.getEngine();
    
        auto &_layout = m_properties.m_centreLayout;
        auto &_wnd_frame_layout = m_properties.m_frameLayout;

        //frame
        
        if( !_wnd_frame_layout .isNull () ){
          auto &&_controllers = _wnd_frame_layout->getChildControllers();
          auto _cont_iter = _controllers.begin();

          for(; _cont_iter != _controllers.end(); ++_cont_iter){
            auto &_each_root = (*_cont_iter)->m_root;
            if( !_each_root.isNull() ){

              //#
              auto *_each_Manager = _each_root->_render_manager_get();
              if( _each_Manager != Nullptr ){
                _each_root->renderChildren();

                _each_Manager->activate( _engine,  _each_root->_runtime_elementId_get() );
                IntegerRectRegion _render_rect( IntegerDyadCoordinate(0,0)
                  , _each_root->_size_get().getWidth()
                  , _each_root->_size_get().getHeight() );
                RenderingEventArgs _renderingEventArgs( _render_rect , _each_Manager );
                _each_root->rendering( _renderingEventArgs );
                _each_Manager->deactivate();
              }

            }
          }
        }
        
        //draw frame
        /*
        if ( !m_properties.m_frameController.isNull() ){
          auto &_frame_root = m_properties.m_frameController->m_root;
          if( !_frame_root.isNull() ){
            //#
            //get controller render manager
            //activate it
            auto *_manager = _frame_root->_render_manager_get();

            if( _manager != Nullptr ){
              _frame_root->renderChildren();

              _manager->activate( _engine, _frame_root->_runtime_elementId_get() );
              IntegerRectRegion _render_rect( IntegerDyadCoordinate(0,0)
                , _frame_root->_size_get().getWidth()
                , _frame_root->_size_get().getHeight() );
              RenderingEventArgs _renderingEventArgs( _render_rect, _manager );
              _frame_root->rendering( _renderingEventArgs );
              _manager->deactivate();
            }          
          }
        }
        */

        //draw content controllers

        if( !_layout .isNull () ){
          auto &&_controllers = _layout->getChildControllers();
          auto _cont_iter = _controllers.begin();
        
          for(; _cont_iter != _controllers.end(); ++_cont_iter){
            auto &_each_root = (*_cont_iter)->m_root;
            if( !_each_root.isNull() ){

              //#
              auto *_each_Manager = _each_root->_render_manager_get();
              if( _each_Manager != Nullptr ){
                _each_root->renderChildren();

                _each_Manager->activate( _engine,  _each_root->_runtime_elementId_get() );
                IntegerRectRegion _render_rect( IntegerDyadCoordinate(0,0)
                  , _each_root->_size_get().getWidth()
                  , _each_root->_size_get().getHeight() );
                RenderingEventArgs _renderingEventArgs( _render_rect , _each_Manager );
                _each_root->rendering( _renderingEventArgs );
                _each_Manager->deactivate();
              }
        
            }
          }
        }

        m_binding.getEngine().makeReservation();
        m_requester->requestWindowRendering( m_binding.getEngine() );
        //OnceRendered.triggers( m_binding.getEngine() );        
      }
  
    }

    void Window::WindowRoot::renderController( Controller *contr ){
      assert( contr != Nullptr );

      auto &_ctrl_root = contr->m_root;

      if( !_ctrl_root.isNull() && _ctrl_root->m_int_runtimeId != 0 
        && m_int_runtimeId != 0 && m_requester != Nullptr ){

        Layout *_contr_pare_layout = _ctrl_root->m_parentLayout;
        if( _contr_pare_layout != Nullptr ){      
          ManipulateEngine & _engine = m_binding.getEngine();
          //#    
          auto *_each_Manager =  _ctrl_root->_render_manager_get();

          if( _each_Manager != Nullptr  && !_ctrl_root.isNull() ){
            _ctrl_root->renderChildren();

            _each_Manager->activate( _engine,  _ctrl_root->_runtime_elementId_get() );
            IntegerRectRegion _render_rect( IntegerDyadCoordinate(0,0)
              , _ctrl_root->_size_get().getWidth()
              , _ctrl_root->_size_get().getHeight() );
            RenderingEventArgs _renderingEventArgs( _render_rect, _each_Manager );
            _ctrl_root->rendering( _renderingEventArgs );
            _each_Manager->deactivate();
          }
          m_binding.getEngine().makeReservation();
          m_requester->requestWindowRendering( m_binding.getEngine() );
          //OnceRendered.triggers( _engine );
        }

      }
      
    }

    void Window::WindowRoot::partlyRenderController( Controller *contr, const IntegerRectRegion& dirtyRegion  ){
      assert( contr != Nullptr );

      auto &_ctrl_root = contr->m_root;

      if( !_ctrl_root.isNull() && _ctrl_root->m_int_runtimeId != 0 
        && m_int_runtimeId != 0 && m_requester != Nullptr ){

          Layout *_contr_pare_layout = _ctrl_root->m_parentLayout;
          if( _contr_pare_layout != Nullptr ){      
            ManipulateEngine & _engine = m_binding.getEngine();
            //#    
            auto *_each_Manager =  _ctrl_root->_render_manager_get();

            if( _each_Manager != Nullptr  && !_ctrl_root.isNull() ){
              _ctrl_root->renderChildren();

              _each_Manager->activate( _engine,  _ctrl_root->_runtime_elementId_get() );
              RenderingEventArgs _renderingEventArgs( dirtyRegion, _each_Manager );
              _ctrl_root->rendering( _renderingEventArgs );
              _each_Manager->deactivate();
            }
            m_binding.getEngine().makeReservation();
            m_requester->requestWindowRendering( m_binding.getEngine() );
            //OnceRendered.triggers( _engine );
          }

      }

    }

    void Window::WindowRoot::windowMoved( MovedEventArgs & eventArgs ){
      if( eventArgs.isAccepted() ){
        //set values
        _pos_set( eventArgs.getNewCoord() );

        if( m_properties.m_stateSwitcher.isStateOn( WindowPropertySet::State_Show) ){
          //not running
          if( m_int_runtimeId != 0 ){
            OnceMoved.triggers( m_runtime_Id, eventArgs.getNewCoord() );
          }

          //user
          auto &_on_moved = m_properties.m_delegatorCollection.onMoved;
          if( _on_moved != NullDelegator() ){
            _on_moved.invoke( m_binding, eventArgs );
          }
        }
        
      }
    }

    void Window::WindowRoot::windowResized( ResizedEventArgs & eventArgs ){
      if( eventArgs.isAccepted() ){

        _size_set( eventArgs.getNewSize() );
        if( m_properties.m_stateSwitcher.isStateOn( WindowPropertySet::State_Show)){
          if( m_int_runtimeId != 0 ){
            OnceResized.triggers( m_runtime_Id, eventArgs.getNewSize() );
          }

          //user
          auto &_on_resized = m_properties.m_delegatorCollection.onResized;
          if( _on_resized != NullDelegator() ){
            _on_resized.invoke( m_binding, eventArgs );
          }
        }
      }
    }

    void Window::WindowRoot::windowFocused( FocusEventArgs& eventArgs ){
      if( eventArgs.isAccepted() ){
        if( m_int_runtimeId != 0 ){
          m_requester->requestWindowFocusChanged( m_runtime_Id, m_int_runtimeId,eventArgs.getType() == GUIEventConstants::GUIEvent_FocusIn );
        }      
      }
    }


     void Window::WindowRoot::_initPropertySet(){
       //state switcher init
       m_properties.m_stateSwitcher.addState( State<WindowPropertySet::StateValue>( WindowPropertySet::State_Show, 255 ) );
       m_properties.m_stateSwitcher.addState( State<WindowPropertySet::StateValue>( WindowPropertySet::State_Enabled, 242 ) );
       m_properties.m_stateSwitcher.addState( State<WindowPropertySet::StateValue>( WindowPropertySet::State_Focus, 224 ) );

       m_properties.m_stateSwitcher.beginSwitching();
       m_properties.m_stateSwitcher.switches( WindowPropertySet::State_Focus );
       m_properties.m_stateSwitcher.switches( WindowPropertySet::State_Enabled );
       m_properties.m_stateSwitcher.switches( WindowPropertySet::State_Show );
       m_properties.m_stateSwitcher.endSwitching();

       m_properties.m_stateSwitcher.OnceStateSwitchedWithStateName.connectAction( this, &WindowRoot::_stateChanged);
       
      if( ( m_properties.m_windowAttributes & Window::WindowAttribute_NoWindowFrame ) == 0 ){
        m_properties.m_frameController = new WindowFrameController ;
        m_properties.m_frameController->setBindingWindow( &m_binding );

        auto *_layout = new AbsoluteLayout;
        _layout->addController( m_properties.m_frameController );
        if( !_layout->m_layout.isNull() ){
          _layout->m_layout->assignParent( &m_binding );
        }      
        m_properties.m_frameLayout = SharedPtr<Layout>(_layout);      
      }

     }
   }//GUI
}//Magna

