#ifndef DESKTOPWINDOW_H
#define DESKTOPWINDOW_H

#include "render/FillBrush.h"
using namespace Magna::Render;

#include "basegui/Window.h"
#include "basegui/AbsoluteLayout.h"
#include "basegui/ImageLabel.h"
using namespace Magna;
using namespace Magna::GUI;

#include "glue_img/Image.h"
using namespace Magna::Glue;

#include "CategoryBar.h"
#include "DesktopStatusBar.h"
#include "DesktopDateTimeController.h"

//desktop tools
#include "WeatherForecastDesktopTool.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{
      
      class DesktopWindow : public Window{
        public:
          static SharedPtr<DesktopWindow>& getDesktopWindow();

        __Constructor_Destructor protected:
          DesktopWindow();
        public:
          virtual ~DesktopWindow();

        public:
          void replaceWallPaper( const String& path );

          inline SharedPtr<WindowStatusBar>& getWindowStatusBar() {
            assert( !m_statusBar.isNull() );
            return m_statusBar->getWindowStatusBar();
          }

          inline static const IntegerRectRegion& getUserRectRegion() {
            return shared_userRectRegion;
          }
          inline static const IntegerRectRegion& getDesktopRectRegion() {
            return shared_desktopRectRegion;
          }

          inline static const String& getDesktopResDir() {
            static String shared_desktopResDir = L"/res/sysdesktop/";
            return shared_desktopResDir;
          }

          inline static Image getPopWindowBG(){
            static Image _bg( getDesktopResDir() + L"popwnd_bg.png" );
            return _bg;
          }

          inline static Image getPressedImage(){
            static Image _img( DesktopWindow::getDesktopResDir() + L"icon_pressed.png" ) ;
            _img.scale( 84, 112 );
            return _img;
          }

        __Data_Field private:
          //needs for dynamically loading
          //otherwise, those values is not predicable
          static IntegerRectRegion shared_userRectRegion;
          static IntegerRectRegion shared_desktopRectRegion;        

          Image m_wallpaperImg;        

          SharedPtr<CategoryBar> m_categoryBar;
          SharedPtr<DesktopStatusBar> m_statusBar;
          SharedPtr<DesktopDateTimeController> m_datetimeController;

          SharedPtr<WeatherForecastDesktopToolController> m_weatherForecast;


      };

    }//namespace Desktop
  }//namespace SystemComponent
}//namespace Magna

#endif  /*  DESKTOPWINDOW_H  */