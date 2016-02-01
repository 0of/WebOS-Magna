#include "VideoPopWindow.h"

#include "basegui/Window_p.h"
#include "basegui/LinearLayout.h"
using namespace Magna::GUI;

#include "glue/FileDir.h"
using namespace Magna::Glue;

#include "application/WindowIntroducer.h"
using namespace Magna::Application;

#include "DesktopWindow.h"
#include "DesktopApplication.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      String replace(const String& str, const String& src, const String& dest)
      {
        String ret;

        String::size_type pos_begin = 0;
        String::size_type pos       = str.find(src);
        while (pos != String::npos)
        {
          ret.append(str.data() + pos_begin, pos - pos_begin);
          ret += dest;
          pos_begin = pos + 1;
          pos       = str.find(src, pos_begin);
        }
        if (pos_begin < str.length())
        {
          ret.append(str.begin() + pos_begin, str.end());
        }
        return ret;
      }
    

      VideoPopWindow::VideoPopWindow()
        :PopOutWindow( Window::WindowAttribute_NoWindowFrame )
        ,m_videoWatchWindow( new VideoWatchWindow() )
        ,m_videoInfos()
        ,m_videoIcon( DesktopWindow::getDesktopResDir() + L"Files-Movie-File-icon.png"){

        //window infos
        auto &_userRect = DesktopWindow::getUserRectRegion();
        uint32 _take_width = (_userRect.getWidth()  - 80);
        uint32 _take_height = (_userRect.getHeight()  - 100);

        auto &_desktop_rect = DesktopWindow::getDesktopRectRegion();
        auto &_desktop_top_left = _desktop_rect.getTopLeftCoord();
        auto &_size = _desktop_rect.getSize();
        //top 30px bottom 30px
        //left 20px right 20px
        IntegerDyadCoordinate _top_left ( _desktop_top_left.getX() + (_size.getWidth() >> 1 ) - ( _take_width >> 1 ) 
          , _desktop_top_left.getY() +  (_size.getHeight() >> 1 ) - ( _take_height >> 1 )  );

        m_wndRoot->_pos_set( _top_left );
        m_wndRoot->_size_set( IntegerSize( _take_width,_take_height ));


        m_videoIcon.scale( 84, 112, Image::ImageTransformationMode_Smooth );
        //load video infos
        auto &_filePaths = FileDir::getAbsPath( DesktopApplication::shared_usr_dir + L"video/", L"*.mp4;*.rmvb" );

        TableLayout *layout = new TableLayout;
        layout->setLayoutOffset( IntegerDyadCoordinate( 24, 24 ) );
        layout->setHorizontalSpacing( 18 );

        std::vector< SharedPtr<Controller> > _ctrls;

        for( auto _iter = 0; _iter != _filePaths.size(); ++_iter ){

          FileInfoController*each = new FileInfoController( m_videoIcon, _filePaths.at(_iter) , _iter );
        
          _ctrls.push_back( each );
          //connect
          each->OnceAboutToEnter.connectAction( this, &VideoPopWindow::processWatchVideo);      
        }
        layout->addAutoDeployControllers( _ctrls );
        
        setCenterLayout(layout);
        //window style    
        setBackgroundFillBrush( FillBrush( DesktopWindow::getPopWindowBG() ) );

        setBorderStyle( GUIConstants::BorderStyle_None );    
      }

      VideoPopWindow::~VideoPopWindow(){

      }

      void VideoPopWindow::processWatchVideo(const String& path ){
        //path convert to VLC path format
        auto _conv_path = replace( path, L"/", L"\\" );
        m_videoWatchWindow->loadVideoFile( _conv_path ); 
        if( !m_videoWatchWindow->isRunning() ){        
          WindowIntroducer::introduceWindow(*DesktopApplication::pInstance, m_videoWatchWindow);    
        }
      }
  

    }
  }
}