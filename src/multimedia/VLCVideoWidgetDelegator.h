#ifndef VLCVIDEOWIDGET_H
#define VLCVIDEOWIDGET_H

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"

#include <QWidget>

#include <vlc/vlc.h>

namespace Magna{
  namespace MultiMedia{

    class VLCVideoWidgetDelegator {
      public:
        VLCVideoWidgetDelegator();
        VLCVideoWidgetDelegator( const QString& );
        virtual ~VLCVideoWidgetDelegator();

      public:
        void loadVideoFromFile( const QString& );
        void play();
        void pause();
        void stop();

        //use in main thread
        void attachVLCRenderContext(QWidget *);
        
        inline QWidget *getWidget(){
          return m_widgetInstance;
        }

      private:
        QWidget *m_widgetInstance;

        libvlc_instance_t *m_instance;
        libvlc_media_player_t *m_player;
        libvlc_media_t *m_currentMedia;

        //flags
        bool m_isPlaying;
        bool m_hasPaused;
    };


  }//namespace MultiMedia
}//namespace Magna

#endif  /*  VLCVIDEOWIDGET_H  */
