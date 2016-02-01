#include "DesktopDateTimeController.h"

#include "basegui/Controller_p.h"
using namespace Magna::GUI;

#include "glue/FontMetrics.h"
using namespace Magna::Glue;

#include "DesktopWindow.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class DesktopDateTimeImplementor : public ControllerImplementor{
        public :
          DesktopDateTimeImplementor( DesktopDateTimeController& binding );
          virtual ~DesktopDateTimeImplementor();
          virtual void rendering( RenderingEventArgs& eventArgs );

          DesktopDateTimeController &m_binding;
          Font m_timeFont;
          Font m_dateFont;
          FillBrush m_fillBrush;

          IntegerRectRegion m_dateStringBoundingRect;
          IntegerRectRegion m_timeStringBoundingRect;
      };

      DesktopDateTimeImplementor::DesktopDateTimeImplementor( DesktopDateTimeController& binding )
        :m_binding( binding )
        ,m_timeFont()
        ,m_dateFont()
        ,m_fillBrush( Color( 255,255,255 ) ){

        m_timeFont.setFontSize( 32 );
        m_dateFont.setFontSize( 20 );

      }

      DesktopDateTimeImplementor::~DesktopDateTimeImplementor(){

      }

      void DesktopDateTimeImplementor::rendering( RenderingEventArgs& eventArgs ){
        if( eventArgs.isAccepted() ){
          auto *_2d_manager = eventArgs.getRenderManager2D();
          if( _2d_manager != Nullptr ){
            Canvas2DDrawer _drawer;
            if( _2d_manager->retrieveDrawer( _drawer ) != false ){
              _drawer.setFillBrush( m_fillBrush );

              _drawer.setFont( m_timeFont );

              String& _time_str = m_binding.getTimeInString() ;
              String& _date_str = m_binding.getDateInString() ;

              auto &_measured_time_str_size = FontMetrics::measureSize( _time_str, m_timeFont );
              _drawer.drawText( IntegerDyadCoordinate( 0, _measured_time_str_size.getHeight() ), _time_str );

              auto &_measured_date_str_size = FontMetrics::measureSize( _date_str, m_dateFont );
              _drawer.setFont( m_dateFont );
              _drawer.drawText( IntegerDyadCoordinate( 0, _measured_time_str_size.getHeight() + _measured_time_str_size.getHeight() ), _date_str );

              _2d_manager->pullbackDrawer( _drawer );
            }
          }
        }
      }

      DesktopDateTimeController::DesktopDateTimeController()
        :m_updateTimer( new Timer)
        ,m_currentTime( 0, 0, 0, 0 )
        ,m_currentDate( 0, 0, 0 )
        ,m_dateInString()
        ,m_timeInString(){
        m_updateTimer->setInterval( 60000 );

        m_updateTimer->OnceTimeOut.connectAction( this, &DesktopDateTimeController::updateEachMin );

        if( !m_root.isNull() ){
          DesktopDateTimeImplementor *_impl = new DesktopDateTimeImplementor( *this );

          auto &_time_size = FontMetrics::measureSize(L"00:00", _impl->m_timeFont );
          auto &_date_size = FontMetrics::measureSize(L"1900/01/01", _impl->m_timeFont );

          _impl->m_timeStringBoundingRect.setSize( _time_size );
          _impl->m_dateStringBoundingRect = IntegerRectRegion( IntegerDyadCoordinate( 0, _time_size.getHeight() )
                , _date_size.getWidth(), _date_size.getHeight() );

          const auto& _width = _time_size.getWidth() > _date_size.getWidth() ?  _time_size.getWidth() : _date_size.getWidth() ;

          m_root->_impl_init( _impl );
          m_root->_size_set( IntegerSize( _width , _time_size.getHeight() + _date_size.getHeight() ) );

          auto &_desktop_rect = DesktopWindow::getDesktopRectRegion();
          m_root->_pos_set( IntegerDyadCoordinate( _desktop_rect.getWidth() - 120 , 0 ) );

          m_root->OnceRun.connectAction( this, &DesktopDateTimeController::startTictoc );
        }
      }

      DesktopDateTimeController:: ~DesktopDateTimeController(){

      }

      void DesktopDateTimeController::startTictoc(){
        Date::currentDate( m_currentDate );
        Time::currentTime( m_currentTime );

        m_dateInString = m_currentDate.toString( L"yyyy/MM/dd");
        m_timeInString = m_currentTime.toString( L"HH:mm");

        m_updateTimer->start();
      }

      //timer runs on main thread
      void DesktopDateTimeController::updateEachMin(){
        Date::currentDate( m_currentDate );
        Time::currentTime( m_currentTime );

        m_dateInString = m_currentDate.toString( L"yyyy/MM/dd");
        m_timeInString = m_currentTime.toString( L"HH:mm");

        update();
      }

    }
  }
}