#include "ScrollableController.h"

#include "ScrollableController_p.h"

#include "Controller_p.h"
#include "Window_p.h"
#include "Layout_p.h"
#include "GUIConstantMapper.h"

#include "inner/InnerPrivateDataNullPointerException.h"
#include "inner/InnerIndexNotFoundException.h"
using namespace Inner;  

namespace Magna{
  namespace GUI{
    

    void ScrollableController::ScrollableControllerRoot::onLayoutMeasured(){
      auto &&_layout = m_scrollableController.getLayout();
      if( !_layout.isNull() ){
        m_scrollSize = _layout->getMeasuredRect().getSize();
      }
    }

    void ScrollableController::ScrollableControllerRoot::scrolled( ScrollEventArgs& eventArgs ){

      if( eventArgs.isAccepted() ){

        m_scrollX = eventArgs.getNewScrollX();
        m_scrollY = eventArgs.getNewScrollY();


        m_scrollableController.OnceScrolled.triggers( m_scrollX, m_scrollY );

      }

    }
      

    ScrollableController::ScrollableController()
      :Controller( new ScrollableControllerRoot( *this ) )
      ,m_sroot( reinterpret_cast<ScrollableControllerRoot *>( m_root.operator->() ) ){

    }

    ScrollableController::~ScrollableController(){
      
    }

    String ScrollableController::toStyleString() const {
      OutStringStream _outter;

      if( !m_root.isNull() && m_root->m_parentLayout != Nullptr ){
        auto *_attached_wind = m_root->m_parentLayout->getAttachedWindow();
        if( _attached_wind != Nullptr ){

          IntegerDyadCoordinate _mapped_pos;
          if( m_root->m_parentLayout->isWindowParent() ){
            const auto& _y_diff = _attached_wind->getContentPos().getY()  - _attached_wind->getPos().getY() ;
            _mapped_pos = m_renderableRect.getTopLeftCoord().translatedByY( _y_diff ) ;        
          }
          else{
            _mapped_pos = m_renderableRect.getTopLeftCoord();
          }

          //wrapper style
          ////
          if( m_sroot->m_policy == ScrollableController::ScrollBarPolicy_AlwaysOff ){
            _outter << L" 'overflow: hidden;";
          }
          else if( m_sroot->m_policy == ScrollableController::ScrollBarPolicy_AlwaysShow  ){
            _outter << L" 'overflow: scroll;";
          }
          _outter << L"display: inline-block;position: absolute; -webkit-tap-highlight-color: rgba(0, 0, 0, 0);"
            << L"left:" << _mapped_pos.getX() << L"px; top:" << _mapped_pos.getY() 
            //border style
            <<L"px; border-style:" << GUIConstantMapper::BorderStyleMapper[ m_root->m_borderStyle ]
          <<L";border-width: " << m_root->m_borderWidth 
            <<L"px;border-color: " 
            << m_root->m_borderColor.toString( Color::ColorStringFormat_Numeric_RGB, Color::ColorStringQualifier_NumberSign)
            << L";width:" << m_renderableRect.getWidth() << L"px;height:"
            << m_renderableRect.getHeight() << L"px;'";
        }
      }

      return _outter.str();
    }

    String ScrollableController::toElementString () const {
      OutStringStream _ret_str(m_elementId);
      _ret_str << m_elementId
        << L",";
      Window *_wnd_parent = Nullptr;
      Controller *_ctrl_parent = Nullptr;
      String _id_str;
      if( !m_root.isNull() && m_root->m_parentLayout != Nullptr ){
        if( m_root->m_parentLayout->getParent( _wnd_parent ) 
          && _wnd_parent != Nullptr ){
            //parent id
            if( !(_wnd_parent->m_wndRoot.isNull()) ){
              _id_str.append( _wnd_parent->m_wndRoot->m_runtime_Id);  
            }        
        }
        else if( m_root->m_parentLayout->getParent( _ctrl_parent ) 
          && _ctrl_parent != Nullptr  ){
            _id_str.append( _ctrl_parent->m_elementId );
            auto _insert_it = _id_str.end() - 1;
            _id_str.insert( _insert_it , L'w' );        
        }
        else{
          //throw exception
        }      
        _ret_str << _id_str
          << L",";  
      }
      _ret_str << toStyleString();

      if( (m_root->m_attributes & Controller::ControllerRoot::Attribute_Protogenous) != 0 ) {
        _ret_str << L","
          << m_elementTagName
          << L","
          << toProtogenousInitString();
      }
      else{
        //width & height
        _ret_str << L"," 
          << m_sroot->m_scrollSize.getWidth() 
          << L","
          << m_sroot->m_scrollSize.getHeight()  ;    
      }

      return _ret_str.str();
    }

    void ScrollableController::scrollTo( sint32 x, sint32 y ){

      if( m_sroot != Nullptr ){
        if ( m_elementId != Nullptr ){

          if( x != m_sroot->m_scrollX 
            || y != m_sroot->m_scrollY ){

            ScrollEventArgs _event_args( x, y, m_sroot->m_scrollX , m_sroot->m_scrollY, m_sroot->m_scrollSize );
            m_sroot->scrolled( _event_args );
          }      
        }  
      }
    }

    void ScrollableController::scrollToX( sint32 x ){
      if( m_sroot != Nullptr ){
        if ( m_elementId != Nullptr ){

          if( x != m_sroot->m_scrollX ){

            ScrollEventArgs _event_args( x, m_sroot->m_scrollY, m_sroot->m_scrollX , m_sroot->m_scrollY, m_sroot->m_scrollSize );
            m_sroot->scrolled( _event_args );
          }
        }  
      }
    }

    void ScrollableController::scrollToY( sint32 y ){
      if( m_sroot != Nullptr ){
        if ( m_elementId != Nullptr ){

          if( y != m_sroot->m_scrollY ){

            ScrollEventArgs _event_args( m_sroot->m_scrollX, y, m_sroot->m_scrollX , m_sroot->m_scrollY, m_sroot->m_scrollSize );
            m_sroot->scrolled( _event_args );
          }

        }  
      }
    }

    IntegerSize ScrollableController::getScrollSize() const{
      IntegerSize _size;

      auto &&_layout = getLayout();
      if( !_layout.isNull() ){
        _size = _layout->getMeasuredRect().getSize();
      }

      return _size;
    }

    void ScrollableController::setScrollSize( const IntegerSize& size){

      if( !m_sroot.isNull() ){
        m_sroot->m_scrollSize = size;

        if( m_root->m_int_runtimeId != 0 
          && m_root->m_parentLayout != Nullptr ){

          auto *_wnd = m_root->m_parentLayout->getAttachedWindow();
          if( _wnd != Nullptr ){

            if( !_wnd->m_wndRoot.isNull() ){
              _wnd->m_wndRoot->m_requester->requestContentResized( m_elementId, size ) ;
            }

            if( m_root->m_stateSwitcher.isStateOn( Controller::ControllerRoot::State_Show ) ){
              _wnd->m_wndRoot->renderController( this ) ;
            }
          }
        }
      }    
    }

    void ScrollableController::setSize( const IntegerSize& size){

      //will not pass root to process
      //get root first
      if( !m_root.isNull() ){

        //generate size event
        ResizedEventArgs _args( m_root->_size_get(), size );

        m_root->_size_set( size );

        if( !m_root->m_impl.isNull() ){
          m_root->m_impl->resized( _args );
        }

        if( m_root->m_int_runtimeId != 0 
          && m_root->m_parentLayout != Nullptr ){

          auto *_wnd = m_root->m_parentLayout->getAttachedWindow();
          if( _wnd != Nullptr ){

            if( !_wnd->m_wndRoot.isNull() ){
              _wnd->m_wndRoot->m_requester->requestWrapperResized( m_elementId, size ) ;
            }

            m_root->m_parentLayout->measure();
            m_root->m_parentLayout->deploy();

            if( m_root->m_stateSwitcher.isStateOn( Controller::ControllerRoot::State_Show ) ){
              _wnd->m_wndRoot->renderController( this ) ;
            }
          }
        }
      }
    }

    sint32 ScrollableController::getScrollHeight() const{
      sint32 _scroll_height = 0;
      auto &&_layout = getLayout();
      if( !_layout.isNull() ){
        _scroll_height = _layout->getMeasuredRect().getSize().getHeight();
      }
      return _scroll_height;
    }

    sint32 ScrollableController::getScrollWidth() const{
      sint32 _scroll_width = 0;
      auto &&_layout = getLayout();
      if( !_layout.isNull() ){
        _scroll_width = _layout->getMeasuredRect().getSize().getWidth();
      }
      return _scroll_width;
    }

    void ScrollableController::setScrollBarPolicy( ScrollBarPolicy policy){

    }


  }//namespace GUI
}//namespace Magna
