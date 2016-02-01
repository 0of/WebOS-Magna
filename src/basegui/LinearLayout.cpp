#include "LinearLayout.h"

#include "inner/InnerIndexNotFoundException.h"
#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "Layout_p.h"
#include "ControllerAccessor.h"

namespace Magna{
  namespace GUI{

    LinearLayout::LinearLayout()
      :Layout()
      ,m_orientation( LinearLayout::LinearLayoutOrientation_Horizontal )
      ,m_spacing( 10 ){

    }

    LinearLayout::LinearLayout( LinearLayout::LinearLayoutOrientation orientation )
      :Layout()
      ,m_orientation( orientation )
      ,m_spacing( 10 ){

    }

    LinearLayout::~LinearLayout(){

    }

    void LinearLayout::addController( const SharedPtr<Controller>& controller ){
      Layout::addChildController( controller );
    }

    void LinearLayout::insertController( uint32 index, const SharedPtr<Controller>& controller ){
      try{
        if( !m_layout.isNull() ){
          assert( index <= m_layout->m_controllers.size() );
          auto _inserted_iter = m_layout->m_controllers.begin() + index;

          m_layout->m_controllers.insert( _inserted_iter, controller );

        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
    }

    LinearLayout& LinearLayout::operator << ( const SharedPtr<Controller>& controller ){
      Layout::addChildController( controller );
      return *this;
    }

    void LinearLayout::measure() {
      try{
        if(  !m_layout.isNull() ){
          Layout::measure();

          m_layout->m_realRect = IntegerRectRegion();

          auto &_bounding_rect = m_layout->m_realRect;
          auto _height = 0;
          auto _width = 0;

          auto _iter = m_layout->m_controllers.begin();
          if( m_orientation == LinearLayoutOrientation_Horizontal ){

            for( ; _iter != m_layout->m_controllers.end(); ++_iter ){

              if( !_iter->isNull() ){
                const auto &_each_size = (*_iter)->getSize();

                if( _each_size.getHeight() >_height ){
                  _height = _each_size.getHeight();
                }
                _width += _each_size.getWidth() + m_spacing;
              }
              else{
                throw InnerPrivateDataNullPointerException();
              }
            }

          }
          else if( m_orientation == LinearLayoutOrientation_Vertical ){

            for( ; _iter != m_layout->m_controllers.end(); ++_iter ){

              if( !_iter->isNull() ){
                const auto &_each_size = (*_iter)->getSize();

                if( _each_size.getWidth() >_width ){
                  _width = _each_size.getWidth();
                }
                _height += _each_size.getHeight() + m_spacing;
              }
              else{
                throw InnerPrivateDataNullPointerException();
              }
            }
          }
          else{
            throw InnerIndexNotFoundException();
          }

          _bounding_rect = IntegerRectRegion( m_layout->m_layoutOffset, _width, _height ) ;

        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
    }

    void LinearLayout::deploy() {
      try{
        if(  !m_layout.isNull() ){
          Layout::deploy();

          auto _each_pos = 0;
          auto _iter = m_layout->m_controllers.begin();
          const auto &_offset = m_layout->m_layoutOffset;

          if( m_orientation == LinearLayoutOrientation_Horizontal ){
            for( ; _iter != m_layout->m_controllers.end(); ++_iter ){
              if( !_iter->isNull() ){            
                //get root
                auto &&_each_root  = ControllerAccessor::getRoot( *_iter );
                if( !_each_root.isNull() ){
                  _each_root->_pos_set( IntegerDyadCoordinate( _each_pos + _offset.getX() , _offset.getY() ) );

                  const auto & _size = _each_root->_size_get();
                  _each_pos += _size.getWidth() + m_spacing;
                }
              }
              else{
                throw InnerPrivateDataNullPointerException();
              }
            }
          }
          else if( m_orientation == LinearLayoutOrientation_Vertical ){
            for( ; _iter != m_layout->m_controllers.end(); ++_iter ){
              if( !_iter->isNull() ){            
                //get root
                auto &&_each_root  = ControllerAccessor::getRoot( *_iter );
                if( !_each_root.isNull() ){
                  _each_root->_pos_set( IntegerDyadCoordinate( _offset.getX(),_each_pos + _offset.getY() ) );

                  const auto & _size = _each_root->_size_get();
                  _each_pos += _size.getHeight() + m_spacing;
                }
              }
              else{
                throw InnerPrivateDataNullPointerException();
              }
            }
          }
          else{
            throw InnerIndexNotFoundException();
          }
        }
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
    }

    void LinearLayout::setOrientation( LinearLayoutOrientation orientation ){
      m_orientation = orientation;
    }

    void LinearLayout::setSpacing( uint32 spacing ){
      m_spacing = spacing;
    }


  }//namespace GUI
}//namespace Magna
