#include "LabelImplementor.h"

#include "Label.h"

#include "qt_glue/FontMetrics.h"
using namespace Magna::Glue;

namespace Magna{
  namespace GUI{

    LabelImplementor::LabelImplementor( Label & bindingLabel )
      :m_text( L"Label" )
      ,m_textBoundingRect()
      ,m_bindingLabel( bindingLabel )
      ,m_avgHeight( 0 )
      ,m_lineBreakStrings()
      ,m_vtextSpacing(0)
      ,m_effect()
      ,m_alignment( TextRenderContants::TextAlignment_Left | TextRenderContants::TextAlignment_Top ){

      _remeasureText();
    }

    LabelImplementor::LabelImplementor(  Label & bindingLabel , const String& text, TextAlignment align )
      :m_text( text )
      ,m_textBoundingRect()
      ,m_bindingLabel( bindingLabel )
      ,m_avgHeight( 0 )
      ,m_lineBreakStrings()
      ,m_vtextSpacing(0)
      ,m_effect()
      ,m_alignment( align ){

      _remeasureText();
    }

    LabelImplementor::~LabelImplementor(){

    }

    void LabelImplementor::rendering( RenderingEventArgs& eventArgs ){
      if( eventArgs.isAccepted() ){
        auto *_2d_manager = eventArgs.getRenderManager2D();
        if( _2d_manager != Nullptr ){
          Canvas2DDrawer _drawer;
          if( _2d_manager->retrieveDrawer( _drawer ) != false ){
            //normal state
            _drawer.clearRectRegion( eventArgs.getRenderingRectRegion() );
            
            _drawer.setFont( m_bindingLabel.getFont() );
            _drawer.setFillBrush( m_textFillBrush );
            if( !m_effect.isNull() ){
              _drawer.setAppearanceEffect( m_effect );
            }
            auto _each_x = m_textBoundingRect.getBottomLeftCoord().getX();
            auto _each_y = m_textBoundingRect.getBottomLeftCoord().getY();
            for( auto _iter = m_lineBreakStrings.begin(); _iter != m_lineBreakStrings.end(); ++_iter ){        
              _each_y += m_avgHeight;
              _drawer.drawText( IntegerDyadCoordinate(_each_x, _each_y ), *_iter );
              _each_y += m_vtextSpacing;
            }        
            _2d_manager->pullbackDrawer( _drawer );
          }
        }
      }
    }



    void LabelImplementor::_remeasureText(){
      //get split strings
      m_lineBreakStrings = m_text.split( L"\n" );

      FontMetrics _metrics = FontMetrics( m_bindingLabel.getFont() );

      IntegerSize _boundingTextSize;

      //label size
      const auto &_label_size = m_bindingLabel.getSize();
      IntegerDyadCoordinate _text_offset;
      //calculate the offset
      //###NOT each line for now
      //###
      

      for( auto _iter = m_lineBreakStrings.begin(); _iter != m_lineBreakStrings.end(); ++_iter ){
        _metrics.setMetricsText( *_iter );
        const auto &_each_size = _metrics.measureSize();

        m_avgHeight += _each_size.getHeight();
        _boundingTextSize.joinedBy( _each_size );
      }

      //get average height
      m_avgHeight /= m_lineBreakStrings.size();

      m_textBoundingRect.setSize( _boundingTextSize );

      //get bounding size and center pos
      const auto &_half_size = (m_bindingLabel.getSize() / 2);

      //###
      if( (m_alignment & TextRenderContants::TextAlignment_HCenter) != 0 ){
        if( _boundingTextSize.getWidth() < _label_size.getWidth() ){
          _text_offset = IntegerDyadCoordinate( 
            ((_label_size.getWidth() >> 1 ) - (_boundingTextSize.getWidth() >> 1) ) , 0 );
          m_textBoundingRect.translatedBy( _text_offset );
        }
      }
      

      if( _half_size.getWidth() - _boundingTextSize.getWidth() > 0
        && _half_size.getHeight() - _boundingTextSize.getHeight() > 0){
        IntegerDyadCoordinate _translated_coord( _half_size.getWidth() - (_boundingTextSize.getWidth() / 2 ) + _text_offset.getX()
        , _half_size.getHeight() - (_boundingTextSize.getHeight()  / 2 ) - (_boundingTextSize.getHeight()  / 4 ) );    /* normalized value  */
        m_textBoundingRect.translatedBy( _translated_coord );
      }
    

    ///  auto &_size = FontMetrics::measureSize(m_text, m_bindingLabel.getFont() );
    ///  m_textBoundingRect.setSize( _size );

      //default alignment is center
    //  auto &_center = m_bindingLabel.getBoundingRectRegion().getCenterCoord();
    //  if( _center.getX() - _size.getWidth() > 0
    //    && _center.getY() - _size.getHeight() > 0){
    //      IntegerDyadCoordinate _translated_coord( _center.getX() - (_size.getWidth() / 2 )
    //        , _center.getY() - (_size.getHeight()  / 2 ) - (_size.getHeight()  / 4 ) );    /* normalized value  */
    //      m_textBoundingRect.translatedBy( _translated_coord );

    //  }
    }
  }//namespace GUI
}//namespace Magna

