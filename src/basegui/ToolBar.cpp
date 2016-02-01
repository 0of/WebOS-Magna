#include "ToolBar.h"

#include "Controller_p.h"
#include "ToolBarImplementor.h"

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

namespace Magna{
  namespace GUI{
    
    ToolBar::ToolBar()
      :Controller(){
      
      if( !m_root.isNull() ){
        m_root->_size_set( IntegerSize(120, 40 ) );

        ToolBarImplementor *_impl = new ToolBarImplementor( *this );
        m_root->_impl_init( SharedPtr<ControllerImplementor>( _impl ) );      
      }  
    }

    ToolBar::~ToolBar(){

    }


    void ToolBar::setTextHangingPolicy( TextHangingPolicy policy ){
      try{
        if( !m_root.isNull() ){

          auto &&_impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = _impl.operator->();
            //force convert to ToolBar impl

            auto _tool_bar_impl_ptr = reinterpret_cast<ToolBarImplementor *>( _impl_ptr );

            _tool_bar_impl_ptr->m_textHangingPolicy = policy;

            update();
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
        _ex.what();
      }
    }

    void ToolBar::setOrientation( ToolBarOrientation orientation ){
      try{
        if( !m_root.isNull() ){

          auto &&_impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = _impl.operator->();
            //force convert to ToolBar impl

            auto _tool_bar_impl_ptr = reinterpret_cast<ToolBarImplementor *>( _impl_ptr );

            _tool_bar_impl_ptr->m_orientation = orientation;

            update();
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
        _ex.what();
      }
    }

    void ToolBar::setSpacing( uint32 spacing){
      try{
        if( !m_root.isNull() ){

          auto &&_impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = _impl.operator->();
            //force convert to ToolBar impl

            auto _tool_bar_impl_ptr = reinterpret_cast<ToolBarImplementor *>( _impl_ptr );

            _tool_bar_impl_ptr->m_spacing = spacing;

            update();
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
        _ex.what();
      }
    }

    ToolBar::TextHangingPolicy ToolBar::getTextHangingPolicy() const{
      auto _ret_policy = ToolBar::TextHangingPolicy_NoText;
      try{
        if( !m_root.isNull() ){

          auto &&_impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = _impl.operator->();
            //force convert to ToolBar impl
          
            auto _tool_bar_impl_ptr = reinterpret_cast<ToolBarImplementor *>( _impl_ptr );
            _ret_policy = static_cast<decltype(_ret_policy)>(_tool_bar_impl_ptr->m_textHangingPolicy);
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
        _ex.what();
      }
      return _ret_policy;
    }

    uint32 ToolBar::getSpacing(){
      uint32 _ret_spacing = 0;
      try{
        if( !m_root.isNull() ){

          auto &&_impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = _impl.operator->();
            //force convert to ToolBar impl

            auto _tool_bar_impl_ptr = reinterpret_cast<ToolBarImplementor *>( _impl_ptr );
            _ret_spacing = _tool_bar_impl_ptr->m_spacing;
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
        _ex.what();
      }
      return _ret_spacing;
    }

    ToolBar::ToolBarOrientation ToolBar::getOrientation() const{
      auto _ret_orientation = ToolBar::ToolBarOrientation_Horizontal;
      try{
        if( !m_root.isNull() ){

          auto &&_impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = _impl.operator->();
            //force convert to ToolBar impl

            auto _tool_bar_impl_ptr = reinterpret_cast<ToolBarImplementor *>( _impl_ptr );
            _ret_orientation = static_cast<decltype(_ret_orientation)>(_tool_bar_impl_ptr->m_orientation);
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
        _ex.what();
      }
      return _ret_orientation;
    }

    std::vector<ToolBarElement> ToolBar::getElements() const{
      std::vector<ToolBarElement> _ret_elements;
      try{
        if( !m_root.isNull() ){

          auto &&_impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = _impl.operator->();
            //force convert to ToolBar impl

            auto _tool_bar_impl_ptr = reinterpret_cast<ToolBarImplementor *>( _impl_ptr );
            _ret_elements = _tool_bar_impl_ptr->m_elements ;
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
        _ex.what();
      }
      return _ret_elements;
    }

    void ToolBar::addElement( const ToolBarElement& elment ){
      try{
        if( !m_root.isNull() ){

          auto &&_impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = _impl.operator->();
            //force convert to ToolBar impl

            auto _tool_bar_impl_ptr = reinterpret_cast<ToolBarImplementor *>( _impl_ptr );
            _tool_bar_impl_ptr->m_elements.push_back( elment ) ;

            //update elements

            if( m_root->m_int_runtimeId != 0 ){
              update();
            }
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
        _ex.what();
      }
    }

    void ToolBar::insertElement( const ToolBarElement& elment,  uint32 index ){
      try{
        if( !m_root.isNull() ){

          auto &&_impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = _impl.operator->();
            //force convert to ToolBar impl

            auto _tool_bar_impl_ptr = reinterpret_cast<ToolBarImplementor *>( _impl_ptr );

            //assert
            assert( index <= _tool_bar_impl_ptr->m_elements.size() );

            //get iterator
            auto _insert_iter = _tool_bar_impl_ptr->m_elements.begin() + index;
            _tool_bar_impl_ptr->m_elements.insert( _insert_iter, elment );

            //update elements

            if( m_root->m_int_runtimeId != 0 ){
              update();
            }
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
        _ex.what();
      }
    }

    void ToolBar::clearElement(){
      try{
        if( !m_root.isNull() ){

          auto &&_impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = _impl.operator->();
            //force convert to ToolBar impl

            auto _tool_bar_impl_ptr = reinterpret_cast<ToolBarImplementor *>( _impl_ptr );

            _tool_bar_impl_ptr->m_elements.clear();
            _tool_bar_impl_ptr->m_realRect = IntegerRectRegion();

            if( m_root->m_int_runtimeId != 0 ){
              update();
            }
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
        _ex.what();
      }
    }

  }//namespace GUI
}//namespace Magna
