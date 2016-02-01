#include "Controller_p.h"

#include "WindowAccessor.h"
#include "MouseEventArgsAccessor.h"
#include "RenderingEventArgsAccessor.h"

#include "GUIEventDelegatorManager.h"

namespace Magna{  
   namespace GUI{

    Controller::ControllerRoot::ControllerRoot(  Controller &bindingController  ) 
      :m_binding( bindingController )
      ,m_centreLayout()
      ,m_stateSwitcher()
      ,m_mouseEventDelegatorCollections( Nullptr )
      ,m_brush()
      ,m_pen()
      ,m_font()
      ,m_opacity( 1.0 )
      //,m_mutex()
      ,m_attributes()
      ,m_layoutAttr()
      ,m_parentLayout( Nullptr )
      ,m_int_runtimeId( 0 )
      ,m_borderWidth(1)
      ,m_borderStyle( GUIConstants::BorderStyle_None )
      ,m_borderColor()
      ,m_realBoundingRect(){

      
     }

    Controller::ControllerRoot::~ControllerRoot(){

     }

    void Controller::ControllerRoot::onWindowBound(){
    
    }

    void Controller::ControllerRoot::onControllerRun(){

    }
    void Controller::ControllerRoot::onWindowUnbound(){

    }
    void Controller::ControllerRoot::onControllerFinished(){

    }
    void Controller::ControllerRoot::onLayoutMeasured(){

    }

    void Controller::ControllerRoot::onLayoutDeployed(){

    }

    String Controller::ControllerRoot::_createControllerNode() const{
      assert( m_int_runtimeId != 0 ); 
      return m_binding.toElementString();
    }

    void Controller::ControllerRoot::_border_init( GUIConstants::BorderStyle style, uint32 width,  const Color& color ){
      m_borderColor = color;
      m_borderStyle = style;
      m_borderWidth = width;
    }


    std::vector<SharedPtr<Controller::ControllerRoot> >  Controller::ControllerRoot::_ctrls_get() const{
      std::vector<SharedPtr<Controller::ControllerRoot> > _ret_controllers;
      if( !m_centreLayout.isNull() ){
        m_binding.m_mutex.acquires();
        //R-value Ref
        auto &&_controllers = m_centreLayout->getChildControllers();

        auto _iter = _controllers.begin();
        for( ; _iter != _controllers.end(); ++_iter){
          auto &_each = (*_iter);
          if( ! _each.isNull() ){
            auto &_each_root = _each->m_root;
            if( !_each_root.isNull() ){
              _ret_controllers.push_back( _each_root );

              auto &&_each_controller_roots = _each_root->_ctrls_get();
              _ret_controllers.insert( _ret_controllers.end(), _each_controller_roots.begin(), _each_controller_roots.end() );      

            }    
          }  
        }
        m_binding.m_mutex.releases();
      }  
      return _ret_controllers;
    }        


    RenderManager * Controller::ControllerRoot::_render_manager_get() const{
      return m_binding.m_manager;
    }

    void Controller::ControllerRoot::_dispatchEventMessage( AbstractedEventArgs& eventArgs ){

      ControllerRootDelegatorManager &_manager = ControllerRootDelegatorManager::obtainDelegator();
      auto _delegator = _manager.getDelegator( static_cast< GUIEventConstants::EventType >(eventArgs.getType()) );
      assert( _delegator != NullDelegator() );
      if(_delegator != NullDelegator() ){
        _delegator.invoke( *this , eventArgs );
      }

    }

    void Controller::ControllerRoot::_offset_coord_update(){
      //assume global coordinate (0,0)
      IntegerDyadCoordinate _global_origin;

      //if Nullptr, which means won't bind to window
      //throw Unbinding exception
      if(m_parentLayout  != Nullptr ){
        auto *_attachedWnd = m_parentLayout->getAttachedWindow();
        if( _attachedWnd != Nullptr ){
          _global_origin -= _attachedWnd->getPos();
        }    

        //convert from window
        _global_origin = m_parentLayout->fromCoordOnManipulateDevice( _global_origin );

        _global_origin -= _pos_get();
      }

      m_offsetCoord = _global_origin;
    }

    void Controller::ControllerRoot::_assignRuntimeId( const uint64& id){
      try{
        if( m_int_runtimeId == 0 
          && m_binding.m_elementId == Nullptr ){
            m_int_runtimeId = id;

            const String& _id_seri =  std::to_wstring( id );
            size_t _len = _id_seri.size();
            m_binding.m_elementId = new unicode_char[ (_len + 3) ];

            ::memcpy( (m_binding.m_elementId + 1), _id_seri.c_str(), _len * sizeof( unicode_char ) );

            *(m_binding.m_elementId) = L'\'';
            *(m_binding.m_elementId + _len + 1 ) = L'\'';
            *(m_binding.m_elementId + _len + 2 ) = L'\0';
        

            //offset init
            ///except Frame controller 
            _offset_coord_update();

            onControllerRun();

            OnceRun.triggers();
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
    void Controller::ControllerRoot::_de_assignRuntimeId(){
      m_int_runtimeId = 0;
      if( m_binding.m_elementId != Nullptr ){
        delete [] m_binding.m_elementId;
        m_binding.m_elementId = Nullptr;

        onControllerFinished();
      }
    }
    const unicode_char *Controller::ControllerRoot:: _runtime_elementId_get() const{
      return m_binding.m_elementId;
    }

    void Controller::ControllerRoot::_impl_init( const SharedPtr<ControllerImplementor> & impl ){
      m_impl = impl;
    }

    void Controller::ControllerRoot::_impl_set( const SharedPtr<ControllerImplementor> & impl ){
      m_binding.m_mutex.acquires();
      m_impl = impl;
      m_binding.m_mutex.releases();
    }

    void Controller::ControllerRoot::_dispose_state_changed_delegator_init( 
      const Delegator<ControllerImplementor, const StateValue& >& delegator ){
      if( delegator != NullDelegator() ){
         m_disposeStateChangedDelegator = delegator;
      }
    }

    Delegator<ControllerImplementor, const Controller::ControllerRoot::StateValue& > 
    Controller::ControllerRoot::_dispose_state_changed_delegator_get() const{
      return m_disposeStateChangedDelegator;
    }

    SharedPtr<ControllerImplementor> Controller::ControllerRoot::_impl_get() const{
      SharedPtr<ControllerImplementor> _ret_impl;
      m_binding.m_mutex.acquires();
      _ret_impl = m_impl;
      m_binding.m_mutex.releases();
      return _ret_impl;
    }


     void Controller::ControllerRoot::_initProperties(){
  
       m_stateSwitcher.addState( State<StateValue>( State_Show, 255 ) );
       m_stateSwitcher.addState( State<StateValue>( State_Enabled, 242 ) );
       m_stateSwitcher.addState( State<StateValue>( State_Focus, 224 ) );

       m_stateSwitcher.beginSwitching();
       m_stateSwitcher.switches( State_Show );
       m_stateSwitcher.switches( State_Enabled );
       m_stateSwitcher.endSwitching();

       
       m_stateSwitcher.OnceStateSwitchedWithStateName.connectAction( this,  &ControllerRoot::_disposeStateChanged );     
     }

      void Controller::ControllerRoot::_disposeStateChanged( const StateValue& value, bool ){
        switch( value ){
        case State_Focus :{
          FocusEventArgs _event_args( GUIEventConstants::GUIEvent_FocusIn );
          focusIn( _event_args );       
        } break;


        default:
          break;

        }

        if( !m_impl.isNull() ){
          m_disposeStateChangedDelegator.invoke( *m_impl, value );
        }
      }

     void Controller::ControllerRoot::mousePressed( MouseEventArgs& event ){
       if( m_stateSwitcher.isStateOn( State_Show ) 
         && m_stateSwitcher.isStateOn( State_Enabled )
         && event.isAccepted() ){    
           //get focus
           m_stateSwitcher.attachState( ControllerRoot::State_Focus );    

           //convert to coordinate on global 
           IntegerDyadCoordinate &convertedCoord = MouseEventArgsAccessor::getMouseEventArgsCoord(event);
           
           convertedCoord += m_offsetCoord;
        
          //inherited private implementations
          if( !m_impl.isNull() ){
            m_impl->mousePressed( event );
          }

          //user implementations
          if( m_mouseEventDelegatorCollections != Nullptr ){
            auto &_delegator = m_mouseEventDelegatorCollections->onMousePressed;
            if( _delegator != NullDelegator() ){
              _delegator.invoke( m_binding, event );
            }
          }
        }
       
     }

     void Controller::ControllerRoot::mousePressingMoved( MouseEventArgs& event ){
       if( m_stateSwitcher.isStateOn( State_Show ) 
         && event.isAccepted() ){              
        //coordinate conversion
        // event.m_eventPos ;
        //

        if( m_stateSwitcher.isStateOn( State_Enabled ) ){
          //inherited private implementations
          if( !m_impl.isNull() ){
            m_impl->mousePressingMoved( event );
          }

          //user implementations
          if( m_mouseEventDelegatorCollections != Nullptr ){
            auto &_delegator = m_mouseEventDelegatorCollections->onMousePressingMoved;
            if( _delegator != NullDelegator() ){
              _delegator.invoke( m_binding, event );
            }
          }
        }
       }
     }

     void Controller::ControllerRoot::mouseReleased( MouseEventArgs& event ){
       if( m_stateSwitcher.isStateOn( State_Show ) 
         && event.isAccepted() ){        
        //coordinate conversion
        // event.m_eventPos ;
        // 
    
        if( m_stateSwitcher.isStateOn( State_Enabled ) ){
          //inherited private implementations
          if( !m_impl.isNull() ){
            m_impl->mouseReleased( event );
          }

          //user implementations
          if( m_mouseEventDelegatorCollections != Nullptr ){
            auto &_delegator = m_mouseEventDelegatorCollections->onMouseReleased;
            if( _delegator != NullDelegator() ){
              _delegator.invoke( m_binding, event );
            }
          }
        }
       }
     }

     void Controller::ControllerRoot::hoverIn( HoverEventArgs& event ){
       if( event.isAccepted() 
         && event.isHoverIn() ){

        if( !m_impl.isNull() ){
           m_impl->hoverIn( event );
         }        
       }
     }

     void Controller::ControllerRoot::hovered( HoverEventArgs& event ){
        if( event.isAccepted() 
          && ((m_attributes & ControllerRoot::Attribute_MouseHovered) != 0) ){

        if( !m_impl.isNull() ){
            m_impl->hovered( event );
         }  
        }
     }

     void Controller::ControllerRoot::hoverOut( HoverEventArgs& event ){
       if( event.isAccepted() 
         && event.isHoverOut() ){

        if( !m_impl.isNull() ){
           m_impl->hoverOut( event );
        }  
       }
     }

     void Controller::ControllerRoot::mouseWheelUp( MouseWheelEventArgs& event ){
       //if the state won't be focus
       if( m_stateSwitcher.isStateOn( State_Show )  
         && m_stateSwitcher.isStateOn( State_Focus )  
         && m_stateSwitcher.isStateOn( State_Enabled )
         && event.isAccepted() ){
        //coordinate conversion
        // event.m_eventPos ;
        // 
        // 
        //inherited private implementations
        if( !m_impl.isNull() ){
          m_impl->mouseWheelUp( event );
        }

        //user implementations
        if( m_mouseEventDelegatorCollections != Nullptr ){
          auto &_delegator = m_mouseEventDelegatorCollections->onMouseWheelUp;
          if( _delegator != NullDelegator() ){
            _delegator.invoke( m_binding, event );
          }
        }          
       }
     }

     void Controller::ControllerRoot::mouseWheelDown( MouseWheelEventArgs& event ){
       //if the state won't be focus
       if( m_stateSwitcher.isStateOn( State_Show )  
         && m_stateSwitcher.isStateOn( State_Focus )  
         && m_stateSwitcher.isStateOn( State_Enabled )
         && event.isAccepted() ){
        //coordinate conversion
        // event.m_eventPos ;
        // 
        
        if( !m_impl.isNull() ){
          m_impl->mouseWheelDown( event );
        }

        //user implementations
        if( m_mouseEventDelegatorCollections != Nullptr ){
          auto &_delegator = m_mouseEventDelegatorCollections->onMouseWheelDown;
          if( _delegator != NullDelegator() ){
            _delegator.invoke( m_binding, event );
          }
        }

        //#deprecated
  
       }
     }

     //ex event , do not explicitly pass to children
     void Controller::ControllerRoot::mouseClicked( MouseEventArgs& event ){

       if( m_stateSwitcher.isStateOn( State_Show )  
         && m_stateSwitcher.isStateOn( State_Enabled ) 
         && event.isAccepted() ){
        //coordinate conversion
        // event.m_eventPos ;

        if( !m_impl.isNull() ){
          m_impl->mouseClicked( event );
        }

        //user implementations
        if( m_mouseEventDelegatorCollections != Nullptr ){
          auto &_delegator = m_mouseEventDelegatorCollections->onMouseClicked;
          if( _delegator != NullDelegator() ){
            _delegator.invoke( m_binding, event );
          }
        }
        //focus state may changed
        m_stateSwitcher.attachState( ControllerRoot::State_Focus );
       }
     }

     void Controller::ControllerRoot::mouseDoubleClicked( MouseEventArgs& event ){
       if( m_stateSwitcher.isStateOn( State_Show )  
         && m_stateSwitcher.isStateOn( State_Enabled )
         && event.isAccepted() ){
        //coordinate conversion
        //TO-DO
      
        //inherited private implementations
        if( !m_impl.isNull() ){
          m_impl->mouseDoubleClicked( event );
        }

        if( m_mouseEventDelegatorCollections != Nullptr ){
          auto &_delegator = m_mouseEventDelegatorCollections->onMouseDoubleClicked;
          if( _delegator != NullDelegator() ){
            _delegator.invoke( m_binding, event );
          }
        }
        //focus state may changed
        m_stateSwitcher.attachState( ControllerRoot::State_Focus );          

       }

     }

     void Controller::ControllerRoot::keyPressed( KeyEventArgs& eventArgs ){
       if( m_stateSwitcher.isStateOn( State_Show )  
         && m_stateSwitcher.isStateOn( State_Enabled )
         && m_stateSwitcher.isStateOn( State_Focus  )
         && eventArgs.isAccepted() ){
          
         if( !m_impl.isNull() ){
          m_impl->keyPressed( eventArgs );
         }

         auto &_delegator = m_keyEventDelegatorCollections.onKeyPressed;
         if( _delegator != NullDelegator() ){
           _delegator.invoke( m_binding, eventArgs );
         }

         //dispatches to child-controllers
         if( !m_centreLayout.isNull() ){
           auto && _controllers = m_centreLayout->getChildControllers();
           auto _iter = _controllers.begin();
           for( ; _iter != _controllers.end(); [&](){
             if( !_iter->isNull() ){
               SharedPtr<ControllerRoot> _root = (*_iter)->m_root;          
               //dispatches
               if( !_root.isNull() )
                 _root->keyPressed(eventArgs);
             } 
             ++_iter;
           }()) {}

         }
       }
     }

     void Controller::ControllerRoot::keyReleased(KeyEventArgs& eventArgs ){
       if( m_stateSwitcher.isStateOn( State_Show )  
         && m_stateSwitcher.isStateOn( State_Enabled )
         && m_stateSwitcher.isStateOn( State_Focus  )
         && eventArgs.isAccepted() ){

           if( !m_impl.isNull() ){
             m_impl->keyPressed( eventArgs );
           }

           auto &_delegator = m_keyEventDelegatorCollections.onKeyReleased;
           if( _delegator != NullDelegator() ){
             _delegator.invoke( m_binding, eventArgs );
           }

           //dispatches to child-controllers
           if( !m_centreLayout.isNull() ){
             auto && _controllers = m_centreLayout->getChildControllers();
             auto _iter = _controllers.begin();
             for( ; _iter != _controllers.end(); [&](){
               if( !_iter->isNull() ){
                 SharedPtr<ControllerRoot> _root = (*_iter)->m_root;          
                 //dispatches
                 if( !_root.isNull() )
                   _root->keyPressed(eventArgs);
               } 
               ++_iter;
             }()) {}

           }
       }
     }

     void Controller::ControllerRoot::rendering( RenderingEventArgs& eventArgs ){
       if( m_stateSwitcher.isStateOn( State_Show )
         && eventArgs.isAccepted() ){
        //render the background
           
      
        auto *_2d_manager = eventArgs.getRenderManager2D();
        if( _2d_manager != Nullptr ){
          Canvas2DDrawer _drawer;
          if( _2d_manager->retrieveDrawer( _drawer ) != false ){
            //normal state
            _drawer.clearRectRegion( eventArgs.getRenderingRectRegion() );
            
            if( !m_brush.isNull() ){
              _drawer.pushState();
              _drawer.setFillBrush( m_brush );
              _drawer.fillRectRegion( eventArgs.getRenderingRectRegion() );
              _drawer.popState();
            }
              
            _2d_manager->pullbackDrawer( _drawer );
          }
        }
      

         //inherited private implementations
         if( !m_impl.isNull() ){
           m_impl->rendering( eventArgs );
         }

         auto &_delegator = m_renderEventDelegatorCollections.onRendering;
         if( _delegator != NullDelegator() ){
           _delegator.invoke( m_binding, eventArgs );
         }

       }
     }

     void Controller::ControllerRoot::renderChildren(){

       //dispatches to child-controllers
       //#specific region rendering
       //#verify the rect of the event arguments
       //#Check its bounding 
       //#If exists, clip into a new rect region
       //#grab current pixel array of the controller and restore it
       //#draw the controller and get the updated pixel array
       //#put back the original pixels and move undated pixel
       //#on it within the specific rect
       //# 
       if( !m_centreLayout.isNull() ){
         auto _controllers = m_centreLayout->getChildControllers();

         auto *_window = m_centreLayout->getAttachedWindow();

         if( _window != Nullptr ){

           auto & _engine = _window->getEngine();

           auto _iter = _controllers.begin();
           for( ; _iter != _controllers.end(); [&](){
             if( !_iter->isNull() ){
               SharedPtr<ControllerRoot> _root = (*_iter)->m_root;  

               auto *_manager = _root->_render_manager_get();

               if( _manager != Nullptr ){
                 _root->renderChildren();

                 _manager->activate( _engine, _root->_runtime_elementId_get() );
                 //controller coordinate
                 IntegerRectRegion _render_rect( IntegerDyadCoordinate(0,0)
                   , _root->_size_get().getWidth()
                   , _root->_size_get().getHeight() );
                 RenderingEventArgs _renderingEventArgs(_render_rect, _manager );              

                 _root->rendering( _renderingEventArgs );
                 _manager->deactivate();
               }
             } 
             ++_iter;
           }()) {}

         }
       }
     }

     void Controller::ControllerRoot::focusIn( FocusEventArgs&eventArgs ){
       if( m_stateSwitcher.isStateOn( State_Show )
         && m_stateSwitcher.isStateOn( State_Enabled )
         && eventArgs.isAccepted() ){
         if( m_parentLayout != Nullptr ){
           auto *_wnd = m_parentLayout->getAttachedWindow();
           //must be attached to a window    
           if( _wnd != Nullptr ){
             auto &&_wnd_root = WindowAccessor::getRoot( _wnd );
             if( !_wnd_root.isNull() ){
               _wnd_root->_controller_focus( &m_binding );
              m_stateSwitcher.attachState( State_Focus );
             }
           }
         }
       }
     }

     void Controller::ControllerRoot::focusOut( FocusEventArgs&eventArgs ){
       if( m_stateSwitcher.isStateOn( State_Show )
         && m_stateSwitcher.isStateOn( State_Enabled )
         && eventArgs.isAccepted() ){
           if( m_parentLayout != Nullptr ){
             auto *_wnd = m_parentLayout->getAttachedWindow();
             //must be attached to a window    
             if( _wnd != Nullptr ){
               auto &&_wnd_root = WindowAccessor::getRoot( _wnd );
               if( !_wnd_root.isNull() ){
                 _wnd_root->_controller_de_focus( &m_binding );

                 m_stateSwitcher.detachState( State_Focus );
               }
             }
           }
       }
     }


     void Controller::ControllerRoot::moved( MovedEventArgs&eventArgs ){
       if( eventArgs.isAccepted() ){

          _pos_set( eventArgs.getNewCoord() );

         if( !m_impl.isNull() ){
           m_impl->moved( eventArgs );
         }
        
         if( m_stateSwitcher.isStateOn( State_Show ) ){

           if( m_int_runtimeId != 0 
             && m_parentLayout != Nullptr ){
             
            auto *_wnd = m_parentLayout->getAttachedWindow();
            if( _wnd != Nullptr){

              if( !_wnd->m_wndRoot.isNull() 
                && _wnd->m_wndRoot->m_requester != Nullptr){
                _wnd->m_wndRoot->m_requester->requestControllerMoved( m_binding.m_elementId, eventArgs.getNewCoord());
              }

            }      

            m_parentLayout->measure();
            
           }

           //user
           //auto &_on_moved = m_delegatorCollection.onMoved;
           //if( _on_moved != NullDelegator() ){
            // _on_moved.invoke( m_binding, eventArgs );
           //}
         }

       }
     }
     void Controller::ControllerRoot::resized( ResizedEventArgs&eventArgs ){
       if( eventArgs.isAccepted() ){

           _size_set( eventArgs.getNewSize() );

           if( !m_impl.isNull() ){
             m_impl->resized( eventArgs );
           }

           if( m_int_runtimeId != 0 
             && m_parentLayout != Nullptr ){

               auto *_wnd = m_parentLayout->getAttachedWindow();
               if( _wnd != Nullptr ){

                 if( !_wnd->m_wndRoot.isNull() ){
                   _wnd->m_wndRoot->m_requester->requestControllerResized( m_binding.m_elementId, eventArgs.getNewSize()  ) ;
                 }
              
                m_parentLayout->measure();
                m_parentLayout->deploy();
                 
                 if( m_stateSwitcher.isStateOn( State_Show ) ){
                   _wnd->m_wndRoot->renderController( &m_binding ) ;
                 }

              }    
           }    

       }
     }

    

   }//GUI
}//Magna
