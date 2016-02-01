#include "WeatherForecastDesktopTool.h"

#include "basegui/Controller_p.h"

#include "glue/FontMetrics.h"
using namespace Magna::Glue;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class WeatherForecastDesktopToolImplmentor : public ControllerImplementor{
      public:
        WeatherForecastDesktopToolImplmentor( WeatherForecastDesktopToolController& binding );
        virtual ~WeatherForecastDesktopToolImplmentor();

        virtual void rendering( RenderingEventArgs& eventArgs );

        WeatherForecastDesktopToolController& m_binding;
        Font m_degreeFont;
        Font m_detailsFont;
        Font m_weatherFont;
        FillBrush m_fontFillBrush;
        Image m_textBackgroundImage;

        IntegerRectRegion m_degreeStringBoundingRect;
        IntegerRectRegion m_locationStringBoundingRect;
        IntegerRectRegion m_detailsBoundingRect;
        IntegerRectRegion m_weatherBoundingRect;

        static const String WeatherStringMapper[] ;
        static const Image WeatherIconMapper[];
        static const String WeatherToolResDir ;
      };

      const String WeatherForecastDesktopToolImplmentor::WeatherToolResDir  
        = L"sysdesktop/weatherforecast/";

      const String  WeatherForecastDesktopToolImplmentor::WeatherStringMapper[] = {
        L"晴", L"多云", L"局部多云", L"小雨", L"中雨", L"大雨", L"雷阵雨"
      };

      const Image WeatherForecastDesktopToolImplmentor::WeatherIconMapper[] = {
        Image( WeatherToolResDir + L"1.png" ),
        Image( WeatherToolResDir + L"2.png" ),
        Image( WeatherToolResDir + L"3.png" ),
        Image( WeatherToolResDir + L"4.png" ),
        Image( WeatherToolResDir + L"5.png" ),
        Image( WeatherToolResDir + L"6.png" ),
        Image( WeatherToolResDir + L"7.png" )
      };

      WeatherForecastDesktopToolImplmentor::WeatherForecastDesktopToolImplmentor( WeatherForecastDesktopToolController& binding )
        :m_binding( binding )
        ,m_degreeFont()
        ,m_detailsFont()
        ,m_weatherFont()
        ,m_fontFillBrush( Color( 255, 255, 255 ) )
        ,m_detailsBoundingRect()
        ,m_degreeStringBoundingRect()
        ,m_locationStringBoundingRect()
        ,m_weatherBoundingRect()
        ,m_textBackgroundImage( WeatherToolResDir + L"bg.png" ){

        m_degreeFont.setFontSize( 32 );
        m_weatherFont.setFontSize( 20 );
        m_detailsFont.setFontSize( 13 );

        FontMetrics _met( m_binding.m_locationName, m_detailsFont );
        auto &_loc_size = _met.measureSize();
        //
        m_locationStringBoundingRect 
          = IntegerRectRegion( IntegerDyadCoordinate( 84, 50  ),  _loc_size.getWidth(), _loc_size.getHeight() );

        _met.setMetricsText( m_binding.m_weatherDetails );
        auto &_det_size = _met.measureSize();
        //
        m_detailsBoundingRect 
          = IntegerRectRegion( IntegerDyadCoordinate( 84, 60 + _loc_size.getHeight() ),  _det_size.getWidth(), _det_size.getHeight() );

        auto &_deg_size = FontMetrics ::measureSize( m_binding.m_celciusDegrees, m_degreeFont );
        //
        m_degreeStringBoundingRect 
          = IntegerRectRegion( IntegerDyadCoordinate( 16, 80 ),  _deg_size.getWidth(), _deg_size.getHeight() );

        //
        auto &_weather_size = FontMetrics::measureSize( WeatherStringMapper[ m_binding.m_weather ] , m_weatherFont);
        m_weatherBoundingRect
          = IntegerRectRegion( IntegerDyadCoordinate( 90, m_detailsBoundingRect.getBottomLeftCoord().getY() + 4 ) 
          ,  _weather_size.getWidth(), _weather_size.getHeight() );
      }

      WeatherForecastDesktopToolImplmentor::~WeatherForecastDesktopToolImplmentor(){

      }

      void WeatherForecastDesktopToolImplmentor::rendering( RenderingEventArgs& eventArgs ){
        if( eventArgs.isAccepted() ){
          auto *_2d_manager = eventArgs.getRenderManager2D();
          if( _2d_manager != Nullptr ){
            Canvas2DDrawer _drawer;
            if( _2d_manager->retrieveDrawer( _drawer ) != false ){
              _drawer.drawImage( IntegerDyadCoordinate( 0, 0 ) , m_textBackgroundImage );

              _drawer.drawImage(  IntegerDyadCoordinate( 10, 12 ),  WeatherIconMapper[ m_binding.m_weather ] );

              _drawer.setFillBrush( m_fontFillBrush );

              _drawer.setFont( m_degreeFont );
              _drawer.drawText( m_degreeStringBoundingRect.getBottomLeftCoord(), m_binding.m_celciusDegrees );

              _drawer.setFont( m_detailsFont );
              _drawer.drawText( m_locationStringBoundingRect.getBottomLeftCoord(), m_binding.m_locationName );
              _drawer.drawText( m_detailsBoundingRect.getBottomLeftCoord(), m_binding.m_weatherDetails );
            
              _drawer.setFont( m_weatherFont );
              _drawer.drawText( m_weatherBoundingRect.getBottomLeftCoord(), WeatherStringMapper[ m_binding.m_weather ] );

              _2d_manager->pullbackDrawer( _drawer );
            }
          }
        }
      }

      WeatherForecastDesktopToolController::WeatherForecastDesktopToolController()
        :Controller()
        ,m_weather( WeatherForecastDesktopToolController::Cloudy )
        ,m_locationName( L"江西 南昌" )
        ,m_weatherDetails( L"风向/风力:南风 2级;  湿度:89%")
        ,m_celciusDegrees( L"28℃" )
        ,m_service( L"南昌" ){


        if( !m_root.isNull() ){
          WeatherForecastDesktopToolImplmentor *_impl 
            = new WeatherForecastDesktopToolImplmentor( *this );

          m_service.requestTodayForecast(m_celciusDegrees, m_weatherDetails );
          
          auto _ctrl_size = IntegerSize( _impl->m_textBackgroundImage.getWidth() 
                ,_impl->m_textBackgroundImage.getHeight() );

          m_root->_size_set( _ctrl_size );
          m_root->_impl_init( _impl );
        }    

      }

      WeatherForecastDesktopToolController::~WeatherForecastDesktopToolController(){

      }

      void WeatherForecastDesktopToolController::updateWeatherInfos(){
        m_service.requestTodayForecast(m_celciusDegrees, m_weatherDetails );
        update();
      }

    }
  }
}