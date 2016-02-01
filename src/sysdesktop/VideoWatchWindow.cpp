#include "VideoWatchWindow.h"

#include "DesktopWindow.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class PlayerIconSet{
      public:
        static PlayerIconSet shared_icon_set;

        static const String getVideoPlayResDir(){
          static String _dir = L"/res/sysdesktop/videoplayer/";
          return _dir;
        }

        PlayerIconSet()
          :m_playIcon( getVideoPlayResDir() + L"play-icon.png"  )
          ,m_pauseIcon( getVideoPlayResDir() + L"pause-icon.png"  )
          ,m_stopIcon( getVideoPlayResDir() + L"stop-icon.png" )
          ,m_nextIcon(  getVideoPlayResDir() + L"next-track-icon.png" )
          ,m_preIcon( getVideoPlayResDir() + L"previous-track-icon.png"){

          m_playIcon.scale( 84, 84 , Image::ImageTransformationMode_Smooth );
          m_pauseIcon.scale( 84, 84 , Image::ImageTransformationMode_Smooth );
          m_stopIcon.scale( 64, 64 , Image::ImageTransformationMode_Smooth);
          m_nextIcon.scale( 64, 64, Image::ImageTransformationMode_Smooth );
          m_preIcon.scale( 64, 64, Image::ImageTransformationMode_Smooth );
        }

        ~PlayerIconSet(){

        }

        Image m_playIcon;
        Image m_pauseIcon;
        Image m_stopIcon;
        Image m_nextIcon;
        Image m_preIcon;
      };

      PlayerIconSet PlayerIconSet::shared_icon_set = PlayerIconSet();

      ControlBar::ControlBar( const SharedPtr<VLCVideoController>& vlc)
        :Controller()
        ,m_vlcVideoController( vlc )
        ,m_stopButton( new Button( L"" ) )
        ,m_playNPauseButton( new Button( L"" ) )
        ,m_previousButton( new Button( L"" ) )
        ,m_nextButton( new Button( L"" ) )
        ,m_hasPlayed( false ){

        m_playNPauseButton->setSize( IntegerSize( 84 , 84 ) );
        m_stopButton->setSize( IntegerSize( 64 , 64 ) );
        m_previousButton->setSize( IntegerSize( 64 , 64 ) );
        m_nextButton->setSize( IntegerSize( 64 , 64 ) );

        FillBrush _brush;

        auto &_set = PlayerIconSet::shared_icon_set;

        m_playNPauseButton->setPressedBrush( FillBrush(_set.m_playIcon) );
        m_previousButton->setPressedBrush(FillBrush( _set.m_pauseIcon ) );
        m_nextButton->setPressedBrush( _brush );
        m_stopButton->setPressedBrush( _brush );

        m_playNPauseButton->setIcon( _set.m_playIcon );
        m_playNPauseButton->setToggleable( !false );

        m_playNPauseButton->setPressedIcon( _set.m_pauseIcon );

        m_stopButton->setIcon( _set.m_stopIcon );
        m_nextButton->setIcon( _set.m_nextIcon );
        m_previousButton->setIcon( _set.m_preIcon );
        
        LinearLayout *layout = new LinearLayout;

        (*layout) << m_stopButton
          << m_previousButton
          << m_playNPauseButton
          << m_nextButton;

        setLayout(layout);

        setSize( IntegerSize( 600, 110 ) );

        LinearGradient *gradient = new LinearGradient( 0, 0, 0 , 100 );
        gradient->setColorAt( Color( 64, 64, 64 ), 0.0f );
        gradient->setColorAt( Color( 224, 224, 224 ), 0.1f );
        gradient->setColorAt( Color( 64, 64, 64 ), 0.16f );
        gradient->setColorAt( Color( 72, 72, 72 ), 1.0f );

        setBrush( FillBrush ( gradient ) );

        //connections
        m_playNPauseButton->OnceToggled.connectAction( this, &ControlBar::startToPlay);
        m_stopButton->OnceClicked.connectAction(this ,&ControlBar::startToStop);
      }

      void ControlBar::startToPlay( bool isPlayed){
        if( isPlayed ){
          if( !m_vlcVideoController.isNull() ){
            m_vlcVideoController->play();
          }
        }
        else{
          if( !m_vlcVideoController.isNull() ){
            m_vlcVideoController->pause();
          }
        }
      }

      void ControlBar::startToStop(){
        if( !m_vlcVideoController.isNull() ){
          m_vlcVideoController->stop();
        }          
      }

      ControlBar:: ~ControlBar(){

      }

      VideoWatchWindow::VideoWatchWindow()
        :Window()
        ,m_vlcVideoController( new VLCVideoController )
        ,m_ctrlBar(){  //init later

        m_vlcVideoController->setSize( IntegerSize( 600, 530 ) );
        m_ctrlBar =  new ControlBar(m_vlcVideoController ) ;

        setWindowTitle( L"magna视频播放器" );
        //icon
        Image _icon ( PlayerIconSet::getVideoPlayResDir() + L"Movies-icon.png" );
        setWindowIcon( _icon );

        //default size 600, 500 
        setSize( 600, 650 );
        auto &_desktop_rect = DesktopWindow::getDesktopRectRegion();
        auto &_desktop_top_left = _desktop_rect.getTopLeftCoord();
        auto &_size = _desktop_rect.getSize();
        //top 30px bottom 30px
        //left 20px right 20px
        IntegerDyadCoordinate _top_left ( _desktop_top_left.getX() + (_size.getWidth() >> 1 ) - ( 300 ) 
          , _desktop_top_left.getY() +  (_size.getHeight() >> 1 ) - ( 320 )  );

        m_wndRoot->_pos_set( _top_left );

        LinearLayout *layout = new LinearLayout( LinearLayout::LinearLayoutOrientation_Vertical );
        layout->addController( m_vlcVideoController );
        layout->addController( m_ctrlBar );

        setCenterLayout(layout);
      }

      VideoWatchWindow::VideoWatchWindow( const String& filePath )
        :Window()
        ,m_vlcVideoController( new VLCVideoController( filePath ) )
        ,m_ctrlBar(){

        m_vlcVideoController->setSize( IntegerSize( 600, 530 ) );
        m_ctrlBar =  new ControlBar(m_vlcVideoController );

        setWindowTitle( L"magna视频播放器" );
        //icon
        Image _icon ( PlayerIconSet::getVideoPlayResDir() + L"Movies-icon.png" );
        setWindowIcon( _icon );

        //default size 600, 540 
        setSize( 600, 650 );
        //set center
        auto &_desktop_rect = DesktopWindow::getDesktopRectRegion();
        auto &_desktop_top_left = _desktop_rect.getTopLeftCoord();
        auto &_size = _desktop_rect.getSize();
        //top 30px bottom 30px
        //left 20px right 20px
        IntegerDyadCoordinate _top_left ( _desktop_top_left.getX() + (_size.getWidth() >> 1 ) - ( 300 ) 
          , _desktop_top_left.getY() +  (_size.getHeight() >> 1 ) - ( 320 )  );

        m_wndRoot->_pos_set( _top_left );


        LinearLayout *layout = new LinearLayout( LinearLayout::LinearLayoutOrientation_Vertical );
        layout->addController( m_vlcVideoController );
        layout->addController( m_ctrlBar );

        setCenterLayout(layout);
      }

      VideoWatchWindow::~VideoWatchWindow(){

      }

      void VideoWatchWindow::loadVideoFile( const String& filePath ){
        if( !m_vlcVideoController.isNull() ){
          m_vlcVideoController->setVideoSource( filePath );
        }
      }

      void VideoWatchWindow::play(){
        if(  !m_vlcVideoController.isNull() ){
          m_vlcVideoController->play();
        }
      }

      void VideoWatchWindow::pause(){
        if(  !m_vlcVideoController.isNull() ){
          m_vlcVideoController->pause();
        }
      }

      void VideoWatchWindow::stop(){
        if(  !m_vlcVideoController.isNull() ){
          m_vlcVideoController->stop();
        }
      }

    }
  }
}