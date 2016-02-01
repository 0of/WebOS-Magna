#pragma warning(disable:4355)

#include "Window.h"

#include "Window_p.h"

#include "Layout_p.h"

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include <sstream>

namespace Magna{  
   namespace GUI{
     Window::WindowDelegatorCollection::WindowDelegatorCollection()
       :DelegatorCollection( WindowDelegatorCollection::DelegatorCollectionType_Window, false ){


     }

     Window::WindowDelegatorCollection::WindowDelegatorCollection( const WindowDelegatorCollection& collection)
       :DelegatorCollection( collection ){
         ::memcpy( this, &collection, sizeof( Window::WindowDelegatorCollection ) );
     }

     Window::WindowDelegatorCollection::~WindowDelegatorCollection(){

     }

     Window::WindowDelegatorCollection& Window::WindowDelegatorCollection::operator = ( const WindowDelegatorCollection& collection){
       ::memcpy( this, &collection, sizeof( Window::WindowDelegatorCollection ) );
       return *this;
     }

     Window::Window()
       :ManipulateDevice()
       ,m_wndRoot( new WindowRoot( *this ) ){
       m_wndRoot->_initPropertySet();
     }

     Window::Window( WindowAttributes init_attr ) 
       :ManipulateDevice()
       ,m_wndRoot( new WindowRoot( *this , init_attr ) ){
      m_wndRoot->_initPropertySet();
     }

     Window::~Window(){

     }

     void Window::setWindowAttribute( WindowAttribute attr, bool on ){
      // try{
          if( !m_wndRoot.isNull() ){
           // if( m_wndRoot->m_properties.m_windowAttributes & attr
          }
      // }

     }
     void Window::turnOnWindowAttributes( WindowAttributes attrs ){

     }

     void Window::setBorderStyle( GUIConstants::BorderStyle style ){
       try{
         if( !m_wndRoot.isNull() ){
           //not running controller
           if( m_wndRoot->m_int_runtimeId == 0 ){
             m_wndRoot->m_properties.m_borderStyle = style;
           }


         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
     }

     void Window::setBorderWidth( uint32 width ){
       try{
         if( !m_wndRoot.isNull() ){
           //not running controller
           if( m_wndRoot->m_int_runtimeId == 0 ){
             m_wndRoot->m_properties.m_borderWidth = width;
           }


         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
     }

     void Window::setBorderColor( const Color& color ){
       try{
         if( !m_wndRoot.isNull() ){
           //not running controller
           if( m_wndRoot->m_int_runtimeId == 0 ){
             m_wndRoot->m_properties.m_borderColor = color;
           }


         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
     }

     void Window::setVisible( bool visible){
       try{
         if( !m_wndRoot.isNull() ){
           auto & _stateSwitcher = m_wndRoot->m_properties.m_stateSwitcher;
           if( visible ){
             //only in PC visibility changed the focus changed
             _stateSwitcher.attachState( WindowPropertySet::State_Show );
             _stateSwitcher.attachState( WindowPropertySet::State_Focus );
           }
           else{
             _stateSwitcher.detachState( WindowPropertySet::State_Focus );
             _stateSwitcher.detachState( WindowPropertySet::State_Show );
           }       
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }   
     }

     void Window::setFocus( bool focus){
       try{
         if( !m_wndRoot.isNull() ){
           auto & _stateSwitcher = m_wndRoot->m_properties.m_stateSwitcher;
           if( focus ){
             _stateSwitcher.attachState( WindowPropertySet::State_Focus );
           }
           else{
             _stateSwitcher.detachState( WindowPropertySet::State_Focus );
           }       
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }   
     }

     void Window::setBackgroundFillBrush( const FillBrush& brush ){     
       try{
         if( !m_wndRoot.isNull() ){
           if( m_wndRoot->m_int_runtimeId == 0 ){
             m_wndRoot->m_properties.m_backgroundBrush = brush;
           }
           else{
             //running

             //push message
           }  
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }   
     }

     void Window::close(){
       try{
         if( !m_wndRoot.isNull() ){
            CloseEventArgs _args;
            m_wndRoot->windowClose( _args );       
         } else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }   
     }

     bool Window::isVisible() const{
       bool _ret_visible = false;
       try{
         if( !m_wndRoot.isNull() ){
            auto & _stateSwitcher = m_wndRoot->m_properties.m_stateSwitcher;
           _ret_visible = _stateSwitcher.isStateOn( WindowPropertySet::State_Show );      
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }   
       return _ret_visible;
     }

     bool Window::isHidden() const{
       bool _ret_hidden = false;
       try{
         if( !m_wndRoot.isNull() ){
           auto & _stateSwitcher = m_wndRoot->m_properties.m_stateSwitcher;
           _ret_hidden = !_stateSwitcher.isStateOn( WindowPropertySet::State_Show );      
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }   
       return _ret_hidden;
     }

     bool Window::isFocused() const{
       bool _ret_focused = false;
       try{
         if( !m_wndRoot.isNull() ){
           auto & _stateSwitcher = m_wndRoot->m_properties.m_stateSwitcher;
           _ret_focused = _stateSwitcher.isStateOn( WindowPropertySet::State_Focus );      
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }   
       return _ret_focused;
     }

     void Window::update(){
       try{
         if( !m_wndRoot.isNull() ){
           m_wndRoot->windowRender();
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }   
     }

     SharedPtr<Layout> Window::getCenterLayout() const{
        SharedPtr<Layout> _ret_layout;
        try{
           if( !m_wndRoot.isNull() ){
             _ret_layout = m_wndRoot->m_properties.m_centreLayout;
           }
           else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }   
        
       return _ret_layout;
     }

     void Window::setWindowFrame( WindowFrameController *frameController ){
       try{
         if( !m_wndRoot.isNull() ){
           m_wndRoot->m_properties.m_frameController  
             = frameController != Nullptr ? SharedPtr<WindowFrameController>(frameController)
             : SharedPtr<WindowFrameController>(new WindowFrameController);
         } 
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }     
     }

     void Window::setCenterLayout( Layout *layout ){
       if( layout != Nullptr ){
         try{
           if( !m_wndRoot.isNull() && !layout->m_layout.isNull() ){
            //assign its parent and unbind the window
            layout->m_layout->assignParent( this );
            //set values
            m_wndRoot->m_properties.m_centreLayout = SharedPtr<Layout> ( layout );

            if( m_wndRoot->m_int_runtimeId != 0 ){
              auto &_layout_data = m_wndRoot->m_properties.m_centreLayout->m_layout;
              if( !_layout_data.isNull() && !_layout_data->m_hasBound ){
                _layout_data->bindWindow( this );
              }

              m_wndRoot->m_properties.m_centreLayout->measure();

              m_wndRoot->m_properties.m_centreLayout->deploy();

              m_wndRoot->windowRender();
            }      
          }     
           else{
             throw InnerPrivateDataNullPointerException();
           }
         }
         catch( const InnerPrivateDataNullPointerException& ex ){
           ex.what();
           abort();
         }
       }
     }

     void Window::setPos( const IntegerDyadCoordinate& coord ){
       try{
         if( !m_wndRoot.isNull() ){
           const auto & _old_coord = m_wndRoot->_pos_get();
           if( _old_coord != coord ){
             MovedEventArgs _moved_args( _old_coord, coord );

             m_wndRoot->windowMoved(  _moved_args );
           }
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }    
     }

    void Window::setPos( sint32 x, sint32 y ){
      setPos( IntegerDyadCoordinate( x, y ) );
    }
     
    void Window::setSize( const IntegerSize& size ){
      try{
        if( !m_wndRoot.isNull() ){
          const auto& _old_size = m_wndRoot->_size_get();
          if( _old_size != size ){
            ResizedEventArgs _resized_args( _old_size, size );

            m_wndRoot->windowResized( _resized_args );
          }

        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& ex ){
        ex.what();
        abort();
      }      
    }

     void Window::setSize( uint32 w, uint32 h ){
       setSize( IntegerSize( w, h ) );
     }

    void Window::setRectRegion( const IntegerRectRegion& rect ){
      setPos( rect.getTopLeftCoord() );
      setSize( rect.getSize() );
    }

    IntegerSize Window::getSize() const{
      IntegerSize _ret_size;
      try{        
        if( !m_wndRoot.isNull() ){
          _ret_size = m_wndRoot->_size_get();
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
      return _ret_size;
    }

    sint32 Window::getWidth() const{
      sint32 _ret_width = 0;
      try{        
        if( !m_wndRoot.isNull() ){
          _ret_width = m_wndRoot->_width_get();
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
      return _ret_width;
    }

    sint32 Window::getHeight() const{
      sint32 _ret_height = 0;
      try{        
        if( !m_wndRoot.isNull() ){
          _ret_height = m_wndRoot->_height_get();
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
      return _ret_height;
    }

    std::vector<SharedPtr<Controller> > Window::getControllers() const{
      std::vector<SharedPtr<Controller> > _ret_list;
      try{
        if( !m_wndRoot.isNull() ){
          auto &_frame = m_wndRoot->m_properties.m_frameController;
          if( !_frame.isNull() ){
            auto _frame_ = sharedptr_cast<Controller>(_frame);
            _ret_list.push_back( _frame_ );
          }      

          auto &_layout = m_wndRoot->m_properties.m_centreLayout;
          if( !_layout.isNull() ){
            
            auto &&_controllers = _layout->getChildControllers();
            _ret_list.insert( _ret_list.end(), _controllers.begin(), _controllers.end() );


            auto _iter = _controllers.begin();

            for( ; _iter != _controllers.end() ; [&](){
              auto &_each = (*_iter++);
              if( ! _each.isNull() ){
                auto &&_each_controllers = _each->getControllers();
                _ret_list.insert( _ret_list.end(), _each_controllers.begin(), _each_controllers.end() );
              }      
            
            }()){}

          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
      return _ret_list;
    }

    IntegerRectRegion Window::getBoundingRectRegion() const{
      IntegerRectRegion _ret_rect;
      try{
        if( !m_wndRoot.isNull() ){
          _ret_rect = m_wndRoot->_rect_get();
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
      return _ret_rect;
    }

    IntegerDyadCoordinate Window::getPos() const{
      IntegerDyadCoordinate _ret_pos;
      try{
        if( !m_wndRoot.isNull() ){
          _ret_pos = m_wndRoot->_pos_get();
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
      return _ret_pos;
    }

    IntegerDyadCoordinate Window::getContentPos() const{
      IntegerDyadCoordinate _ret_pos;
      try{
        if( !m_wndRoot.isNull() ){
          auto &_frame = m_wndRoot->m_properties.m_frameController;
          _ret_pos = m_wndRoot->_pos_get();
          if( !_frame.isNull() ){
            _ret_pos.translatedByY( _frame->getHeight() );
          }
          
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
      return _ret_pos;
    }

    Window::WindowDelegatorCollection & Window::getWindowDelegatorCollection(){
      Window::WindowDelegatorCollection & _wnd_delegators_col 
        = m_wndRoot->m_properties.m_delegatorCollection;
      return _wnd_delegators_col;
    }

    const Window::WindowDelegatorCollection & Window::getWindowDelegatorCollection() const{
      const Window::WindowDelegatorCollection & _wnd_delegators_col 
        = m_wndRoot->m_properties.m_delegatorCollection;
      return _wnd_delegators_col;
    }

    void Window::addDelegatorCollection( const DelegatorCollection& collection ){
      if( collection.getType() == Window::WindowDelegatorCollection::DelegatorCollectionType_Window ){
        m_wndRoot->m_properties.m_delegatorCollection = *reinterpret_cast<const WindowDelegatorCollection *>(&collection);
      }
    }

    bool Window::isRunning() const{
      bool _is_running = false;
      if( !m_wndRoot.isNull() ){
        _is_running = (m_wndRoot->m_int_runtimeId != 0);
      }
      return _is_running;
    }

    void Window::setWindowTitle( const String& title){
      try{
        if( !m_wndRoot.isNull() ){
          auto &_wnd_properties = m_wndRoot->m_properties;
          _wnd_properties.m_title = title;

          if( m_wndRoot->m_int_runtimeId != 0 ){
            if( ( _wnd_properties.m_windowAttributes 
              & Window::WindowAttribute_NoWindowFrame)  == 0 ){
                if( !_wnd_properties.m_frameController.isNull() ){
                  _wnd_properties.m_frameController->update();
                }                  
            }
          } 
          
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
    }

    void Window::setWindowIcon( const Image& icon){
      try{
        if( !m_wndRoot.isNull() ){
          auto &_wnd_properties = m_wndRoot->m_properties;
  
          _wnd_properties.m_icon = icon;

          bool _has_frame = false;
          if( ( _wnd_properties.m_windowAttributes 
            & Window::WindowAttribute_NoWindowFrame)  == 0
            && !_wnd_properties.m_frameController.isNull() ){
            _has_frame = !false;
          }

          if( _has_frame ){
            const auto &_height = _wnd_properties.m_frameController->getHeight() - 4;
            Image _scaled_icon = icon;
            _scaled_icon.scale( _height, _height );
            _wnd_properties.m_scaledIcon = _scaled_icon;
          }
          

          if( m_wndRoot->m_int_runtimeId != 0 ){
            if( _has_frame ){      
              _wnd_properties.m_frameController->update();                
            }
          } 

        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
    }

    String Window::getWindowTitle() const{
      String _ret_title;
      try{
        if( !m_wndRoot.isNull() ){
          auto &_wnd_properties = m_wndRoot->m_properties;
          _ret_title = _wnd_properties.m_title;      
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
      return _ret_title;
    }

    Image Window::getWindowIcon() const{
      Image _ret_icon;
      try{
        if( !m_wndRoot.isNull() ){
          auto &_wnd_properties = m_wndRoot->m_properties;
          _ret_icon = _wnd_properties.m_icon;      
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
      return _ret_icon;
    }

   }//GUI
}//Magna
