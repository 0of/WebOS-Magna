#include "ProgressBarImplementor.h"

#include "qt_glue/FontMetrics.h"
using namespace Magna::Glue;

#include "render/LinearGradient.h"
using namespace Magna::Render;

namespace Magna{
  namespace GUI{
    
    ProgressBarImplementor::ProgressBarImplementor( ProgressBar &progressBar )
      :ControllerImplementor()
      ,m_progressBar( progressBar )
      ,m_min( 0 )
      ,m_max( 100 )
      ,m_value( 50 )
      ,m_text( L"50%" )
      ,m_textBoundingRect()
      ,m_barBoundingRect()
      ,m_barBrush()
      ,m_baseBarBrush()
      ,m_baseBorderPen( Color( 36,36,36), 3 ){

      const auto &_size = m_progressBar.getSize();
      LinearGradient *_linearGradient = new LinearGradient( 0, 0, _size.getWidth(), _size.getHeight() );
      _linearGradient->setColorAt( Color( 224, 246, 200 ), 0.0 );
      _linearGradient->setColorAt( Color( 152, 173, 132 ), 1.0 );
      m_barBrush = FillBrush( _linearGradient );

      //init bar bounding rect
      m_barBoundingRect.setSize( IntegerSize( _size.getWidth() / 2, _size.getHeight() ) );

      LinearGradient *_baseLinearGradient = new LinearGradient( 0, 0,0, m_barBoundingRect.getHeight() );
      _baseLinearGradient->setColorAt( Color( 218,218,218 ), 0.11 );
      _baseLinearGradient->setColorAt( Color( 232,235,214 ), 0.5 );
      //_baseLinearGradient->setColorAt( Color( 198,198,198 ), 1.0 );
      m_baseBarBrush = FillBrush( _baseLinearGradient );

      //measure text
      _remeasureText();
    }  

    ProgressBarImplementor::ProgressBarImplementor( ProgressBar &progressBar , sint32 int_val )
      :ControllerImplementor()
      ,m_progressBar( progressBar )
      ,m_min( 0 )
      ,m_max( 100 )
      ,m_value()
      ,m_text()
      ,m_textBoundingRect()
      ,m_barBoundingRect()
      ,m_barBrush()
      ,m_baseBarBrush(){

      const auto &_size = m_progressBar.getSize();
      LinearGradient *_baseLinearGradient = new LinearGradient( 0, 0, 0, _size.getHeight() );
      _baseLinearGradient->setColorAt( Color( 218,218,218 ), 0.11 );
      _baseLinearGradient->setColorAt( Color( 232,235,214 ), 0.5 );
      //_baseLinearGradient->setColorAt( Color( 198,198,198 ), 1.0 );
      m_baseBarBrush = FillBrush( _baseLinearGradient );

      _setProgressValue( int_val );
      _remeasureText();

      LinearGradient *_linearGradient = new LinearGradient( 0, 0, 0, m_barBoundingRect.getHeight() );
      _linearGradient->setColorAt( Color( 224, 246, 200 ), 0.0 );
      _linearGradient->setColorAt( Color( 152, 173, 132 ), 1.0 );
      m_barBrush = FillBrush( _linearGradient );

    }

    ProgressBarImplementor::~ProgressBarImplementor(){

    }

    void ProgressBarImplementor::_setProgressValue( sint32 value ){
      if( value <= m_max
        && value >= m_min ){
          m_value = value;

          float _precentage = (static_cast<float>( (m_value - m_min) ) 
            / static_cast<float>( (m_max - m_min ) ) ) ;

          OutStringStream _stream;
          _stream << static_cast<uint32>(_precentage * 100)
            << L"%";
          m_text = _stream.str();

          const auto &_base_size = m_progressBar.getSize();
          IntegerSize _bar_size( _base_size.getWidth() * _precentage, _base_size.getHeight() );
          m_barBoundingRect.setSize( _bar_size );

      }
      else if( value < m_min ){
        m_value =  m_min;

        m_text = String( L"0%");
        m_barBoundingRect.setSize( IntegerSize( 0, 0 ) );
      }
      else{
        m_value =  m_max;

        m_text = String( L"100%");
        m_barBoundingRect.setSize( m_progressBar.getSize() );
      }        
    }

    void ProgressBarImplementor::rendering( RenderingEventArgs& eventArgs ){
      if( eventArgs.isAccepted() ){
        auto *_2d_manager = eventArgs.getRenderManager2D();
        if( _2d_manager != Nullptr ){
          Canvas2DDrawer _drawer;
          if( _2d_manager->retrieveDrawer( _drawer ) != false ){
            //normal state
            _drawer.pushState();

            //base round rect

            _drawer.setFillBrush( m_baseBarBrush );
          //  _drawer.setPen( m_baseBorderPen );
            _drawer.drawRoundedRect( eventArgs.getRenderingRectRegion(), 5 );

            _drawer.popState();

            if( m_value != m_min ){
              _drawer.pushState();
              _drawer.setFillBrush(m_barBrush);
              _drawer.drawRoundedRect( m_barBoundingRect, 5 );
              _drawer.popState();
            }
            
            _drawer.setFont( m_progressBar.getFont() );
            _drawer.drawText( m_textBoundingRect.getBottomLeftCoord(), m_text );

            _2d_manager->pullbackDrawer( _drawer );
          }
        }
      }
    }

    void ProgressBarImplementor::_remeasureText(){
      const auto &_size = FontMetrics::measureSize(m_text, m_progressBar.getFont() );
      m_textBoundingRect.setSize( _size );

      //default alignment is center
      const auto &_center = m_progressBar.getBoundingRectRegion().getCenterCoord();
      if( _center.getX() - (_size.getWidth() >> 1) >= 0
        && _center.getY() - (_size.getHeight()  >> 1) >= 0){
          IntegerDyadCoordinate _translated_coord( _center.getX() - (_size.getWidth() / 2 )
            , _center.getY() - (_size.getHeight()  / 2 ) - (_size.getHeight()  / 4 ) );    /* normalized value  */
          m_textBoundingRect.translatedBy( _translated_coord );

      }
    }


  }//namespace GUI
}//namespace Magna
