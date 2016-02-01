#include "ListGroupControllerImplementor.h"

#include "qt_glue/FontMetrics.h"
using namespace Magna::Glue;

#include "ControllerImplementor.h"

namespace Magna{
  namespace GUI{
    
    ListGroupControllerImplementor::ListGroupControllerImplementor(ListGroupController &b)
      :ControllerImplementor()
      ,m_isSeparateLineVisible( false )
      ,m_isSeqNumVisible( false )
      ,m_items()
      ,m_selectedIndex( -1 )
      ,m_isPartlyUpdate( false )
      ,m_binding( b ){

    }

    void ListGroupControllerImplementor::mousePressed( MouseEventArgs& event ){

      if( event.isAccepted() ){

        //get index
        auto _trigger_y = event.getTriggeredCoord().getY();
        auto _avg_height = m_avgRect.getHeight();
        if( _avg_height > 0 ){

          uint32 _at = _trigger_y / _avg_height;

          //get triggered rect
          IntegerRectRegion _rect( IntegerDyadCoordinate( 0, _avg_height * _at ), m_avgRect.getWidth(), _avg_height );

          m_isPartlyUpdate = !false;
          m_binding.update( _rect );
        }
      }
    }

    void ListGroupControllerImplementor::rendering( RenderingEventArgs& eventArgs ){
      if( eventArgs.isAccepted() ){
        auto *_2d_manager = eventArgs.getRenderManager2D();
        if( _2d_manager != Nullptr ){
          Canvas2DDrawer _drawer;
          if( _2d_manager->retrieveDrawer( _drawer ) != false ){
            const auto &_render_rect = eventArgs.getRenderingRectRegion() ;
            _drawer.clearRectRegion( _render_rect );

            if( m_isPartlyUpdate ){      
              if( m_selectedIndex != -1 
                && (static_cast<uint32>(m_selectedIndex) < m_items.size())){
                _drawer.drawText( _render_rect.getBottomLeftCoord(), m_items.at( m_selectedIndex ) );
              }        
            }
            else{

              for( auto _i = 0; _i != m_items.size(); ++_i ){
                auto _each_text_y = (_i + 1) * m_avgRect.getHeight();
                _drawer.drawText( IntegerDyadCoordinate( 0, _each_text_y) , m_items.at( _i ) );
              }

            }
            _2d_manager->pullbackDrawer( _drawer );
          }
        }
      }  
    }

    //not support \n
    //will not validate the string for now
    void ListGroupControllerImplementor::_remeasureAvgRect(){
      FontMetrics _metrics;
      _metrics.setMetricsFont( Font() );

      IntegerSize _avg_rect_size;

      for( auto _iter = m_items.begin(); _iter != m_items.end(); ++_iter ){

        _metrics.setMetricsText( *_iter );
        const auto &_size = _metrics.measureSize();

        if( _size.getWidth() > _avg_rect_size.getWidth() ){
          _avg_rect_size.setWidth( _size.getWidth() );
        }

        if(  _size.getHeight() > _avg_rect_size.getHeight()  ){
          _avg_rect_size.setHeight( _size.getHeight() );
        }

      }

      m_avgRect = IntegerRectRegion( IntegerDyadCoordinate(0,0), _avg_rect_size.getWidth(), _avg_rect_size.getHeight() );
    }


    ListGroupControllerImplementor::~ListGroupControllerImplementor(){

    }


  }//namespace GUI
}//namespace Magna
