#include "AbsoluteLayout.h"

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "Layout_p.h"
#include "ControllerAccessor.h"

namespace Magna{
  namespace GUI{
    AbsoluteLayout::AbsoluteLayout()
      :Layout(){

    }

    AbsoluteLayout::~AbsoluteLayout(){

    }

  //reversed linear search
  //O(n)
  SharedPtr<Controller> AbsoluteLayout::getControllerAt( const IntegerDyadCoordinate& pos ) const {
    SharedPtr<Controller> _ret_ctrl;
    try{
      if( !m_layout.isNull() ){
        auto _rev_iter = m_layout->m_controllers.rbegin();
        for( ; _rev_iter !=  m_layout->m_controllers.rend(); ++_rev_iter ){
          if( !_rev_iter->isNull() ){
            auto _each_rect = (*_rev_iter)->getBoundingRectRegion();

            if ( _each_rect.contains( pos ) ){
              _ret_ctrl = (*_rev_iter);
              break;
            }
          }
          else{
            //In common these lines won't be ran at
            throw InnerPrivateDataNullPointerException();
          }
        }
      }
      else{
        throw InnerPrivateDataNullPointerException();
      }
    }
    catch( const std::exception& _ex){
      _ex.what();
    }
    return _ret_ctrl;
  }

  AbsoluteLayout & AbsoluteLayout::addController( const SharedPtr<Controller>& controller ){
    Layout::addChildController(controller);
    return *this;
  }

  AbsoluteLayout & AbsoluteLayout::addController( SharedPtr<Controller>& controller, const LayoutAttribute & attr ){
    Layout::addChildController(controller);
    controller->setLayoutAttribute( attr );
    return *this;
  }

  void AbsoluteLayout::measure() {
    try{
      if( !m_layout.isNull() ){
        Layout::measure();
        m_layout->m_realRect = IntegerRectRegion();
        auto _iter = m_layout->m_controllers.begin();
        for( ; _iter != m_layout->m_controllers.end(); ++_iter ){
          if( !_iter->isNull() ){
            m_layout->m_realRect.joinedBy( (*_iter)->getBoundingRectRegion() );
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        m_layout->m_realRect.translatedBy( m_layout->m_layoutOffset );
      }
      else{
        throw InnerPrivateDataNullPointerException();
      }
    }
    catch( const std::exception& _ex){
      _ex.what();
    }
  }

  void AbsoluteLayout::deploy(){
    try{
      if( !m_layout.isNull() ){
        Layout::deploy();

        if( !m_layout->m_layoutOffset.isOrigin() ){
          auto _iter = m_layout->m_controllers.begin();
          for( ; _iter != m_layout->m_controllers.end(); ++_iter ){
            if( !_iter->isNull() ){
              //get root
              auto _each_root  = ControllerAccessor::getRoot( *_iter );
              if( !_each_root.isNull() ){
                auto _each_pos = _each_root->_pos_get();
                _each_pos.translatedBy( m_layout->m_layoutOffset );
                _each_root->_pos_set( _each_pos );
              }
            }
            else{
              throw InnerPrivateDataNullPointerException();
            }
          }
        }
      }
      else{
        throw InnerPrivateDataNullPointerException();
      }
    }
    catch( const std::exception& _ex){
      _ex.what();
    }
  }

  }//namespace GUI
}//namespace Magna
