#include "RelativeLayout.h"

#include "basedef/Comparer.h"
using namespace Magna::Core;

#include "inner/InnerIndexNotFoundException.h"
#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "Layout_p.h"
#include "ControllerAccessor.h"

#include <vector>

namespace Magna{
  namespace GUI{
    
    struct RelativeElement{
      //for horizontal direction, left side next to parent's right
      static const sint32 shared_Postive_Boundary = 1000;
      //for horizontal direction, right side next to parent's right 
      static const sint32 shared_Negative_Boundary = -1000;

      sint32 m_hPercentMulThousand : 15 ;
      sint32 m_vPercentMulThousand : 15 ;
      uint32 m_isHCenter : 1 ;
      uint32 m_isVCenter : 1 ;
      RelativeElement()
        :m_hPercentMulThousand(0)
        ,m_vPercentMulThousand(0)
        ,m_isHCenter( false )
        ,m_isVCenter( false ){

      }

      RelativeElement( const RelativeElement& e )
        :m_hPercentMulThousand(e.m_hPercentMulThousand)
        ,m_vPercentMulThousand(e.m_vPercentMulThousand)
        ,m_isHCenter( e.m_isHCenter )
        ,m_isVCenter( e.m_isVCenter ){

      }

      ~RelativeElement(){

      }

    };

    class RelativeLayout::PrivateData{
      public:
        PrivateData()
          :m_relElements(){

        }

        ~PrivateData(){

        }


      std::vector<RelativeElement> m_relElements; 

    };

    RelativeLayout::RelativeLayout()
      :Layout()
      ,m_data( new PrivateData ){

    }

    RelativeLayout::~RelativeLayout(){

    }

    void RelativeLayout::addController( const SharedPtr<Controller>& ctrl, RelativeHorizontalPostition h, RelativeVerticalPostition v){

      if( !ctrl.isNull() ){

        try{
          if( !m_data.isNull() ){
            RelativeElement _element;

            switch( h ){
            case RelativeLayout::Left:
              break;

            case RelativeLayout::HCenter:
              _element.m_isHCenter = !false;
              break;

            case RelativeLayout::Right:
              _element.m_hPercentMulThousand = RelativeElement::shared_Postive_Boundary;
              break;

            default:
              throw InnerIndexNotFoundException();
            }

            switch( v ){
            case RelativeLayout::Top:
              break;

            case RelativeLayout::VCenter:
              _element.m_isVCenter = !false;
              break;

            case RelativeLayout::Bottom:
              _element.m_vPercentMulThousand = RelativeElement::shared_Postive_Boundary ;
              break;

            default:
              throw InnerIndexNotFoundException();
            }

            Layout::addChildController( ctrl );

            m_data->m_relElements.push_back( _element );
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        catch( const InnerIndexNotFoundException _ex ){
          _ex.what();
        }
        catch( const InnerPrivateDataNullPointerException _ex ){
          _ex.what();
        }
      }
    }

    void RelativeLayout::addController( const SharedPtr<Controller>& ctrl, float hPercent, float vPercent){
      assert( !Comparer<float>::isLowerThan( hPercent , -1.0f ) 
        && !Comparer<float>::isHigherThan( hPercent , 1.0f )  );

      assert( !Comparer<float>::isLowerThan( vPercent , -1.0f ) 
        && !Comparer<float>::isHigherThan( vPercent , 1.0f )  );

      if( !ctrl.isNull() ){
        try{
          if( !m_data.isNull() ){
            Layout::addChildController( ctrl );
            RelativeElement _element;
            _element.m_hPercentMulThousand = static_cast<sint32>(RelativeElement::shared_Postive_Boundary * hPercent);
            _element.m_vPercentMulThousand = static_cast<sint32>(RelativeElement::shared_Postive_Boundary * vPercent);
            
            if( _element.m_hPercentMulThousand < 0 ){
              _element.m_hPercentMulThousand = RelativeElement::shared_Negative_Boundary - _element.m_hPercentMulThousand;
            }

            if( _element.m_vPercentMulThousand < 0 ){
              _element.m_vPercentMulThousand = RelativeElement::shared_Negative_Boundary - _element.m_vPercentMulThousand;
            }

            m_data->m_relElements.push_back( _element );
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        catch( const InnerPrivateDataNullPointerException _ex ){
          _ex.what();
        }
      }
    }

    void RelativeLayout::measure() {
      try{
        if( !m_data.isNull() && !m_layout.isNull() ){

          if( m_data->m_relElements.size() == m_layout->m_controllers.size() ){
            //get parent's size
            IntegerSize _parent_size;
            if( m_layout->m_windowAsParent ){
              if( m_layout->m_wnd != Nullptr ){
                _parent_size = m_layout->m_wnd->getSize();
              }
              else{
                throw InnerPrivateDataNullPointerException();
              }
            }
            else{
              if( m_layout->m_contr != Nullptr ){
                _parent_size = m_layout->m_contr->getSize();
              }
              else{
                throw InnerPrivateDataNullPointerException();
              }
            }

            Layout::measure();

            //clear rect data 
            m_layout->m_realRect = IntegerRectRegion();

            const auto &_offset = m_layout->m_layoutOffset;

            for( auto i = 0; i != m_layout->m_controllers.size(); ++i ){
              auto &_each_ctrl = m_layout->m_controllers[i];
              auto &_each_element = m_data->m_relElements[i];
              auto &&_each_root = ControllerAccessor::getRoot(_each_ctrl);
              const auto &_each_size = _each_root->_size_get();

              if( !_each_ctrl.isNull() && !_each_root.isNull() ){
                //calculate the pos
                sint32 _x = 0;
                sint32 _y = 0;

                if( _each_element.m_isHCenter != false ){
                  _x = (_parent_size.getWidth() >> 1) - ( _each_size.getWidth() >> 1 );
                }
                else{
                  float _perc = std::abs( static_cast<float>(_each_element.m_hPercentMulThousand) 
                            / static_cast<float>(RelativeElement::shared_Postive_Boundary) );

                  _x = static_cast<sint32> ( _perc * _parent_size.getWidth() )         
                    - ( _each_element.m_hPercentMulThousand > -1 ?
                    0 : _each_size.getWidth() );            
                }

                if( _each_element.m_isVCenter != false ){
                  _y = (_parent_size.getHeight() >> 1) - ( _each_size.getHeight() >> 1 );
                }
                else{
                  float _perc = std::abs( static_cast<float>(_each_element.m_vPercentMulThousand) 
                    / static_cast<float>(RelativeElement::shared_Postive_Boundary) );

                  _y = static_cast<sint32> ( _perc * _parent_size.getHeight() ) 
                    - (_each_element.m_vPercentMulThousand > -1 ?
                    0 : _each_size.getHeight() );
                }

                
                IntegerDyadCoordinate _each_pos( _x + _offset.getX()
                  , _y + _offset.getY() );

                _each_root->_pos_set( _each_pos );

                m_layout->m_realRect.joinedBy( _each_root->_rect_get() );
              }
            }
          }
          else{
            throw std::runtime_error("Element Size Won't Match");
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



  }//namespace GUI
}//namespace Magna
