#include "TextLineEditorImplementor.h"

#include "qt_glue/FontMetrics.h"
using namespace Magna::Glue;

namespace Magna{
  namespace GUI{
    
    TextLineEditorImplementor::TextLineEditorImplementor( TextLineEditor &bindingEditor )
      :ControllerImplementor()
      ,m_bindingEditor( bindingEditor )
      ,m_curCoordLogicalX(0)
      ,m_hintText( L"Edit")
      ,m_text( L"Input Text" )
      ,m_textBoundingRect()
      ,m_hintTextBoundingRect(){

      _remeasureText();
      _measureHintText();
    }

    TextLineEditorImplementor::TextLineEditorImplementor( TextLineEditor &bindingEditor, const String hint )
      :ControllerImplementor()
      ,m_bindingEditor( bindingEditor )
      ,m_curCoordLogicalX(0)
      ,m_hintText( hint )
      ,m_text( L"Input Text" )
      ,m_textBoundingRect()
      ,m_hintTextBoundingRect(){

      _remeasureText();
      _measureHintText();
    }

    TextLineEditorImplementor::TextLineEditorImplementor( TextLineEditor &bindingEditor, const String hint, const String text )
      :ControllerImplementor()
      ,m_bindingEditor( bindingEditor )
      ,m_curCoordLogicalX(0)
      ,m_hintText( hint )
      ,m_text( text )
      ,m_textBoundingRect()
      ,m_hintTextBoundingRect(){      

      _remeasureText();
      _measureHintText();
    }

    TextLineEditorImplementor::~TextLineEditorImplementor(){

    }



    void TextLineEditorImplementor::mousePressed( MouseEventArgs& event ){
      if( event.isAccepted() ){
        m_startCoord = event.getTriggeredCoord();

        _updateCursorPos();

        m_bindingEditor.update();
      }
    }

    void TextLineEditorImplementor::mouseReleased( MouseEventArgs& event ){
      if( event.isAccepted() ){
        
      }
    }

    void TextLineEditorImplementor::_measureHintText(){

      const auto &_size = FontMetrics::measureSize(m_hintText, m_bindingEditor.getFont() );
      m_hintTextBoundingRect.setSize( _size );

      //default alignment is center
      const auto &_center = m_bindingEditor.getBoundingRectRegion().getCenterCoord();
      if( _center.getX() - _size.getWidth() > 0
        && _center.getY() - _size.getHeight() > 0){
          IntegerDyadCoordinate _translated_coord( _center.getX() - (_size.getWidth() / 2 )
            , _center.getY() - (_size.getHeight()  / 2 ) - (_size.getHeight()  / 4 ) );    /* normalized value  */
          m_hintTextBoundingRect.translatedBy( _translated_coord );

      }
    }

    void TextLineEditorImplementor::_remeasureText(){
      //m_mutex.acquires();
      const auto &_size = FontMetrics::measureSize(m_text, m_bindingEditor.getFont() );
      m_textBoundingRect.setSize( _size );

      //default alignment is center
      const auto &_center = m_bindingEditor.getBoundingRectRegion().getCenterCoord();
      if( _center.getX() - _size.getWidth() > 0
        && _center.getY() - _size.getHeight() > 0){
          IntegerDyadCoordinate _translated_coord( _center.getX() - (_size.getWidth() / 2 )
            , _center.getY() - (_size.getHeight()  / 2 ) - (_size.getHeight()  / 4 ) );    /* normalized value  */
          m_textBoundingRect.translatedBy( _translated_coord );

      }
      //m_mutex.releases();
    }

    void TextLineEditorImplementor::_updateCursorPos(){
      //calculate the ratio
      const auto &_lead_coord = m_textBoundingRect.getTopLeftCoord();
      const auto _width = m_textBoundingRect.getWidth();
      const auto &_x_diff = m_startCoord.getX() - _lead_coord.getX();

      float _at_percent = static_cast<float>(_x_diff) / _width;

      sint32 _appro_at = 0;
      _appro_at = (m_text.size() * _at_percent);
  
      if( _appro_at > 0 && _appro_at < m_text.size() ){

        //calculate the approached position
        FontMetrics _cur_metrics( m_text.substr( 0, _appro_at ), m_bindingEditor.getFont() );
        FontMetrics _nex_metrics( m_text.substr( 0, ++_appro_at ), m_bindingEditor.getFont() );

        auto _cur_measured_width = _cur_metrics.measureWidth();
        auto _nex_measured_width = _nex_metrics.measureWidth();

        while( _x_diff < _cur_measured_width 
          || _x_diff > _nex_measured_width ){
            _cur_metrics.setMetricsText( m_text.substr(0, _appro_at ) );
            _nex_metrics.setMetricsText(m_text.substr( 0, ++_appro_at ) );

            _cur_measured_width = _cur_metrics.measureWidth();
            _nex_measured_width = _nex_metrics.measureWidth();
        }

        auto _half_div = (_nex_measured_width - _cur_measured_width) / 2;

        //assign x
        m_curCoordLogicalX = (_x_diff - _cur_measured_width) < _half_div ?
          m_curCoordLogicalX = _cur_measured_width + _lead_coord.getX()  
          : _nex_measured_width + _lead_coord.getX();//normalized value

      }

      else if( _appro_at <= 0 ){
        m_curCoordLogicalX = _lead_coord.getX();
      }

      else{
        m_curCoordLogicalX = m_textBoundingRect.getBottomRightCoord().getX();
      }

    }

    void TextLineEditorImplementor::rendering( RenderingEventArgs& eventArgs ){
      if( eventArgs.isAccepted() ){
        auto *_2d_manager = eventArgs.getRenderManager2D();
        if( _2d_manager != Nullptr ){
          Canvas2DDrawer _drawer;
          if( _2d_manager->retrieveDrawer( _drawer ) != false ){
            //normal state
            _drawer.clearRectRegion( eventArgs.getRenderingRectRegion() );
            _drawer.pushState();
            
            if( m_bindingEditor.isFocussed() ){
              //draw text
              _drawer.setFont( m_bindingEditor.getFont() );
              _drawer.drawText( m_textBoundingRect.getBottomLeftCoord(), m_text ); 
            
              //draw line
              uint32 _logicalY1 = m_textBoundingRect.getTopLeftCoord().getY();
              uint32 _logicalY2 = m_textBoundingRect.getBottomLeftCoord().getY();
              IntegerLine _curLine( m_curCoordLogicalX, _logicalY1, m_curCoordLogicalX, _logicalY2 );
              _drawer.drawLine( _curLine );
            }
            else{
              //draw text
              _drawer.setFont( m_bindingEditor.getFont() );
              _drawer.drawText( m_textBoundingRect.getBottomLeftCoord(), m_hintText ); 
            }

          }
        }
      }
    }


  }//namespace GUI
}//namespace Magna
