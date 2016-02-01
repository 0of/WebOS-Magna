#include "ToolBarImplementor.h"

#include "ToolBar.h"

namespace Magna{
  namespace GUI{
    
    ToolBarImplementor::ToolBarImplementor( ToolBar& toolBar )
      :ControllerImplementor()
      ,m_toolBar( toolBar )
      ,m_realRect()
      ,m_elements()
      ,m_orientation()
      ,m_pressedBrush()
      ,m_borderPen()
      ,m_renderElementIndex(0)
      ,m_renderElementHovered( false )
      ,m_renderElementPressed( false )
      ,m_startRenderIndex(0)
      ,m_endRenderIndex(0)
      ,m_eachElementSize()
      ,m_elmentSideLen( 64 )
      ,m_textHangingPolicy()
      ,m_spacing( 16 )
      ,m_logicalVerticalSpacing( 10 ){

      Color _mask_color(156,156,156,96); 
      m_pressedBrush = FillBrush( _mask_color );

      m_borderPen = Pen( Color(224,224,224), 2 );

    }

    ToolBarImplementor::~ToolBarImplementor(){

    }

    void ToolBarImplementor::mousePressed( MouseEventArgs& event ){
      if( event.isAccepted() ){

        auto &_triggered_pos = event.getTriggeredCoord();
        
        //
        if(_triggered_pos.getY() > m_logicalVerticalSpacing 
          && _triggered_pos.getY() < m_logicalVerticalSpacing + m_elmentSideLen ){

          sint32 _index = _triggered_pos.getX() / ( m_eachElementSize.getWidth() );
          sint32 _offset = _triggered_pos.getX() % ( m_eachElementSize.getWidth() );

          if( _index > -1 && _offset > -1 
            && _index < m_elements.size() ){

            if( _offset >= m_spacing ){
              m_renderElementPressed = !false;
              m_renderElementIndex = _index;
              
              //redraw
              m_toolBar.update();    
            }
          }

        }

      }
    }

    void ToolBarImplementor::mouseReleased( MouseEventArgs& event ){

      if( event.isAccepted() ){

        if( m_renderElementPressed 
          && m_renderElementIndex > -1 
          && m_renderElementIndex < m_elements.size() ){
          m_toolBar.OnceElementTriggeredWithIndex.triggers( m_renderElementIndex );
          m_toolBar.OnceElementTriggered.triggers( m_elements[ m_renderElementIndex ] );

          //redraw
          m_toolBar.update();    

          m_renderElementIndex = 0;
          m_renderElementPressed = false;
        }
      }
    }


    void ToolBarImplementor::rendering( RenderingEventArgs& eventArgs ){

      if( eventArgs.isAccepted() ){
        auto *_2d_manager = eventArgs.getRenderManager2D();
        if( _2d_manager != Nullptr ){
          Canvas2DDrawer _drawer;
          if( _2d_manager->retrieveDrawer( _drawer ) != false ){

            if( m_renderElementPressed 
              && m_renderElementIndex > -1 
              && m_renderElementIndex < m_elements.size() ){
              //horizontal
              auto _leading = (m_renderElementIndex * m_eachElementSize.getWidth());
              //clear rect
              IntegerRectRegion _clear_rect( IntegerDyadCoordinate(_leading, 0) , _leading + m_spacing, m_realRect.getHeight() );

              _drawer.clearRectRegion( _clear_rect );

              auto & _element = m_elements[m_renderElementIndex];
              _drawer.drawImage( IntegerDyadCoordinate( _leading + m_spacing , m_logicalVerticalSpacing ),  _element.getIcon() );

              //draw border & mask
              IntegerRectRegion _border_rect( IntegerDyadCoordinate( _leading + (m_spacing >> 1 ), m_logicalVerticalSpacing >> 1 )
                , m_eachElementSize.getWidth(), m_eachElementSize.getHeight() + m_logicalVerticalSpacing );

              _drawer.setFillBrush( m_pressedBrush );
              _drawer.setPen( m_borderPen );

              _drawer.drawRect( _border_rect );
            }
            //draw all
            else{
              for( auto i = m_startRenderIndex; i != m_endRenderIndex; ++i ){
                auto & _element = m_elements[i];
                _drawer.drawImage( IntegerDyadCoordinate( i * m_eachElementSize.getWidth() + m_spacing , m_logicalVerticalSpacing ),  _element.getIcon() );
              }
            }

            _2d_manager->pullbackDrawer( _drawer );
          }
        }
      }
    }

    //element size would be 64 * 64
    void ToolBarImplementor::_updateRenderArguments(){
      if( m_orientation == ToolBar::ToolBarOrientation_Horizontal ){
        m_eachElementSize.setWidth( m_spacing + m_elmentSideLen );
        m_eachElementSize.setHeight( m_elmentSideLen );
        
        m_realRect.setWidth( m_eachElementSize.getWidth() * m_elements.size() + m_spacing );
        m_realRect.setHeight( m_elmentSideLen + ( m_logicalVerticalSpacing << 1 ) );    

        //update index
        const auto &_real_size = m_toolBar.getSize();

        m_endRenderIndex = _real_size.getWidth() / m_eachElementSize.getWidth() + 1;
      }
      else{

        m_eachElementSize.setWidth( m_elmentSideLen );
        m_eachElementSize.setHeight( m_spacing + m_elmentSideLen );

        m_realRect.setWidth( m_eachElementSize.getHeight() * m_elements.size() + m_spacing );
        m_realRect.setHeight( m_elmentSideLen + ( m_logicalVerticalSpacing << 1 ) );    
      }

    }
  }//namespace GUI
}//namespace Magna
