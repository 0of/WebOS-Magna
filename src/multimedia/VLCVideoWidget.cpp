#include "VLCVideoWidgetDelegator.h"

namespace Magna{
  namespace MultiMedia{
    
    VLCVideoWidgetDelegator::VLCVideoWidgetDelegator()
      :m_widgetInstance( Nullptr )
      ,m_instance( Nullptr )
      ,m_player( Nullptr )
      ,m_currentMedia( Nullptr )
      ,m_hasPaused( false )
      ,m_isPlaying( false ){ 

      const char * const vlc_args[] = {
      "--plugin-path=plugins\\"
      };

      m_instance= libvlc_new( sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args );

      if( m_instance != Nullptr ){
        m_player = libvlc_media_player_new (m_instance);
      }
    }

    VLCVideoWidgetDelegator::VLCVideoWidgetDelegator( const QString& path)
      :m_widgetInstance( Nullptr )
      ,m_instance( Nullptr )
      ,m_player( Nullptr )
      ,m_currentMedia( Nullptr )
      ,m_hasPaused( false )
      ,m_isPlaying( false ){

      const char * const vlc_args[] = {
        "--plugin-path=plugins\\"
      };

      m_instance= libvlc_new( sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args );

      if( m_instance != Nullptr ){
        m_player = libvlc_media_player_new (m_instance);

        m_currentMedia = libvlc_media_new_path (m_instance, path.toAscii().data() );
        libvlc_media_player_set_media (m_player, m_currentMedia);      
      }
    }

    void VLCVideoWidgetDelegator::attachVLCRenderContext( QWidget * parent){
      if( m_player != Nullptr && m_widgetInstance == Nullptr ){
        m_widgetInstance = new QWidget( parent );
#if defined(Q_OS_MAC)
        libvlc_media_player_set_nsobject(m_player, m_widgetInstance->winId());
#elif defined(Q_OS_UNIX)
        libvlc_media_player_set_xwindow(m_player, m_widgetInstance->winId());
#elif defined(Q_OS_WIN)
        libvlc_media_player_set_hwnd(m_player, m_widgetInstance->winId());
#endif
      }
    }

    VLCVideoWidgetDelegator:: ~VLCVideoWidgetDelegator(){
      //may run on the main thread
      if( m_widgetInstance != Nullptr ){
        delete m_widgetInstance;
      }

      if( m_player != Nullptr ){
        if( m_isPlaying ){
          libvlc_media_player_stop ( m_player );
        }
      }

      if( m_currentMedia != Nullptr ){
        libvlc_media_release( m_currentMedia );
      }

      if( m_player != Nullptr ){
        /* Free the media_player */
        libvlc_media_player_release (m_player);
      }
      
      if( m_instance != Nullptr ){
        libvlc_release (m_instance);
      }

    }

    void VLCVideoWidgetDelegator::loadVideoFromFile( const QString& path){
      if( m_player != Nullptr ){
        if( m_isPlaying ){
          libvlc_media_player_stop ( m_player );
        }
      }

      if( m_currentMedia != Nullptr ){
        libvlc_media_release( m_currentMedia );
        m_currentMedia = Nullptr;
      }

      if( m_instance != Nullptr ){
        m_currentMedia = libvlc_media_new_path (m_instance, path.toAscii().data() );
        libvlc_media_player_set_media (m_player, m_currentMedia);
      }
    }

    void VLCVideoWidgetDelegator::play(){
      if( m_player != Nullptr ){
        if( m_hasPaused ){
           m_hasPaused = false;
           libvlc_media_player_set_pause   ( m_player, 0 );    
        }
        else{
          if( !m_isPlaying ){
            m_isPlaying = !false;
            libvlc_media_player_play ( m_player );      
          }
        }

      }
    }

    void VLCVideoWidgetDelegator::pause(){
      if( m_player != Nullptr ){
        m_hasPaused = !false;
        m_isPlaying = false;
        libvlc_media_player_pause   ( m_player ) ;
      }
    }

    void VLCVideoWidgetDelegator::stop(){
      if( m_player != Nullptr ){
        m_isPlaying = false;
        libvlc_media_player_stop ( m_player ) ;
      }
    }

  }//namespace MultiMedia
}//namespace Magna
