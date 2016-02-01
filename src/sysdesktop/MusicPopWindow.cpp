#include "MusicPopWindow.h"

#include "basegui/Window_p.h"
#include "basegui/LinearLayout.h"
using namespace Magna::GUI;

#include "application/WindowIntroducer.h"
using namespace Magna::Application;

#include "glue/FileDir.h"

#include "DesktopWindow.h"
#include "DesktopApplication.h"
#include "FileInfoController.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

    
      MusicPopWindow::MusicPopWindow()
        :PopOutWindow( WindowAttribute_NoWindowFrame )
        ,m_musicInfos()
        ,m_playWindow( new MusicPlayWindow )
        ,m_musicIcon( DesktopWindow::getDesktopResDir() + L"MyMusic-icon.png" ){

          m_musicIcon.scale( 84, 112, Image::ImageTransformationMode_Smooth );

          auto &_userRect = DesktopWindow::getUserRectRegion();
          uint32 _take_width = (_userRect.getWidth()  - 80);
          uint32 _take_height = (_userRect.getHeight() - 100 );

          auto &_desktop_rect = DesktopWindow::getDesktopRectRegion();
          auto &_desktop_top_left = _desktop_rect.getTopLeftCoord();
          auto &_size = _desktop_rect.getSize();
          //top 30px bottom 30px
          //left 20px right 20px
          IntegerDyadCoordinate _top_left ( _desktop_top_left.getX() + (_size.getWidth() >> 1 ) - ( _take_width >> 1 ) 
            , _desktop_top_left.getY() +  (_size.getHeight() >> 1 ) - ( _take_height >> 1 )  );

          m_wndRoot->_pos_set( _top_left );
          //_take_height must be higher than 160 px
          m_wndRoot->_size_set( IntegerSize( _take_width,_take_height ));

          auto &_filePaths = FileDir::getAbsPath( DesktopApplication::shared_usr_dir + L"music/", L"*.mp3" );

          TableLayout *layout = new TableLayout;
          layout->setHorizontalSpacing( 18  );
          layout->setLayoutOffset( 24, 24 );

          for( auto _iter = 0; _iter != _filePaths.size(); ++_iter ){
            FileInfoController*each = new FileInfoController( m_musicIcon, _filePaths.at(_iter), _iter );
  
            m_musicInfos.push_back(each);
            each->OnceAboutToEnterByInfo.connectAction( this, &MusicPopWindow::processAboutToPlay);
          }
          
          
          layout->addAutoDeployControllers(m_musicInfos);

          m_playWindow->setPlayQueue( _filePaths );

          setCenterLayout( layout );
          setBackgroundFillBrush( FillBrush( DesktopWindow::getPopWindowBG() ) );
          setBorderStyle( GUIConstants::BorderStyle_None );

      }

      void MusicPopWindow::processAboutToPlay( FileInfoController & info){
        if( !m_playWindow->isRunning() ){
          WindowIntroducer::introduceWindow(*DesktopApplication::pInstance, m_playWindow);    
        }
        m_playWindow->setAboutToPlayAt( info.m_seq );
      }

      MusicPopWindow::~MusicPopWindow(){

      }

    }
  }
}