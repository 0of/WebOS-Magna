#include "ListGroupController.h"

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "qt_glue/FontMetrics.h"
using namespace Magna::Glue;

#include "ListGroupControllerImplementor.h"

namespace Magna{
  namespace GUI{
    
    ListGroupController::ListGroupController()
      :ScrollableController(){

    }

    ListGroupController::~ListGroupController(){

    }

    void ListGroupController::addListItem( const String& text ){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ListGroupControllerImplementor * _impl_ = reinterpret_cast< ListGroupControllerImplementor *>(_impl.operator->() );
            _impl_->m_items.push_back( text );
            
            _impl_->_remeasureAvgRect();

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

    void ListGroupController::addListItems( const std::vector<String>& strs){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ListGroupControllerImplementor * _impl_ = reinterpret_cast< ListGroupControllerImplementor *>(_impl.operator->() );
            _impl_->m_items.insert( _impl_->m_items.end() ,strs.begin(), strs.end() );
            
            _impl_->_remeasureAvgRect();

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

    void ListGroupController::removeItemAt( sint32 index ){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ListGroupControllerImplementor * _impl_ = reinterpret_cast< ListGroupControllerImplementor *>(_impl.operator->() );

            if( index > 0 && (static_cast<uint32>(index) <  _impl_->m_items.size()) ){
              auto _iter_at = _impl_->m_items.begin() + index;
              _impl_->m_items.erase( _iter_at );

              _impl_->_remeasureAvgRect();

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

    void ListGroupController::selectAt( sint32 index){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ListGroupControllerImplementor * _impl_ = reinterpret_cast< ListGroupControllerImplementor *>(_impl.operator->() );

            if( index > 0 && (static_cast<uint32>(index) <  _impl_->m_items.size()) ){
              //_impl_->m_selectedIndex

              _impl_->_remeasureAvgRect();

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

    //void setSeqNumberVisible( bool );
    void ListGroupController::setSeparateLineVisible( bool ){

    }

  }//namespace GUI
}//namespace Magna
