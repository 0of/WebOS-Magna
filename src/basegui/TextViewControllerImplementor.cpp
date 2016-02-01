#include "TextViewControllerImplementor.h"

#include "TextViewController.h"

#include "qt_glue/FontMetrics.h"
using namespace Magna::Glue;

namespace Magna{
  namespace GUI{

    TextViewControllerImplementor::TextViewControllerImplementor( TextViewController & binding )
      :m_textBoundingRect()
      ,m_binding( binding )
      ,m_avgHeight( 0 )
      ,m_lineBreakStrings()
      ,m_vtextSpacing(0)
      ,m_text(){

      _remeasureText();
    }

    TextViewControllerImplementor::TextViewControllerImplementor( TextViewController & binding , const String& text )
      :m_textBoundingRect()
      ,m_binding( binding )
      ,m_avgHeight( 0 )
      ,m_lineBreakStrings()
      ,m_vtextSpacing(0)
      ,m_text( text ){

      _remeasureText();
    }

    TextViewControllerImplementor::~TextViewControllerImplementor(){

    }

    void TextViewControllerImplementor::rendering( RenderingEventArgs& eventArgs ){
      if( eventArgs.isAccepted() ){
        auto *_2d_manager = eventArgs.getRenderManager2D();
        if( _2d_manager != Nullptr ){
          Canvas2DDrawer _drawer;
          if( _2d_manager->retrieveDrawer( _drawer ) != false ){
            //normal state
            _drawer.clearRectRegion( eventArgs.getRenderingRectRegion() );

            _drawer.setFont( m_binding.getFont() );

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

    void TextViewControllerImplementor::_remeasureText(){
      //get split strings
      m_lineBreakStrings = m_text.split( L"\\n" );

      FontMetrics _metrics = FontMetrics( m_binding.getFont() );

      IntegerSize _boundingTextSize;

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
      const auto &_half_size = (m_binding.getSize() / 2);


      if( _half_size.getWidth() - _boundingTextSize.getWidth() > 0
        && _half_size.getHeight() - _boundingTextSize.getHeight() > 0){
          IntegerDyadCoordinate _translated_coord( _half_size.getWidth() - (_boundingTextSize.getWidth() / 2 )
            , _half_size.getHeight() - (_boundingTextSize.getHeight()  / 2 ) - (_boundingTextSize.getHeight()  / 4 ) );    /* normalized value  */
          m_textBoundingRect.translatedBy( _translated_coord );
      }
    }
  }
}
