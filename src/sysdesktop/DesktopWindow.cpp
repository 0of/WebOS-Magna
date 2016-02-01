#include "DesktopWindow.h"

#include "basegui/Window_p.h"

#include "glue/DesktopInfo.h"
using namespace Magna::Glue;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      SharedPtr<DesktopWindow>& DesktopWindow::getDesktopWindow(){
        static SharedPtr<DesktopWindow> _desktop_wnd = new DesktopWindow;
        return _desktop_wnd;
      }    

      IntegerRectRegion DesktopWindow::shared_userRectRegion 
        = IntegerRectRegion( DesktopInfo::getDesktopInfo().getMagnaOSScreenBoundingRect().getTopLeftCoord().translatedByX( CategoryBar::shared_default_width )
        ,  DesktopInfo::getDesktopInfo().getMagnaOSScreenBoundingRect().getBottomRightCoord().translatedByX( -static_cast<sint32>(CategoryBar::shared_default_width) ) );

      IntegerRectRegion DesktopWindow::shared_desktopRectRegion 
        = DesktopInfo::getDesktopInfo().getMagnaOSScreenBoundingRect();

      DesktopWindow::DesktopWindow()
        :Window( Window::WindowAttribute_NoWindowFrame 
        | Window::WindowAttribute_NoBorder
        | Window::WindowAttribute_PositionFixed
        | Window::WindowAttribute_SizeFixed )
        ,m_categoryBar( new CategoryBar( shared_desktopRectRegion.getHeight() ) )
        ,m_statusBar( new DesktopStatusBar( shared_desktopRectRegion.getHeight() ) )
        ,m_wallpaperImg( L"/res/sysdesktop/def_bg3.jpg" )
        ,m_datetimeController( new DesktopDateTimeController )
        ,m_weatherForecast( new WeatherForecastDesktopToolController ){

        m_wndRoot->_rect_set( shared_desktopRectRegion );

        //loc tools
        m_weatherForecast->setPos( IntegerDyadCoordinate( shared_desktopRectRegion.getWidth() - 400 , 200 ) );

        auto _absLayout = new AbsoluteLayout;
        _absLayout->addController( m_categoryBar );    
        _absLayout->addController( m_statusBar );
        _absLayout->addController( m_datetimeController );

        _absLayout->addController( m_weatherForecast );

        setCenterLayout( _absLayout );
        setBackgroundFillBrush( FillBrush( m_wallpaperImg ) );

      }

      DesktopWindow::~DesktopWindow(){

      }

      void DesktopWindow::replaceWallPaper( const String& path ){
        m_wallpaperImg = Image( path );
        
      }

    }
  }
}//namespace Magna