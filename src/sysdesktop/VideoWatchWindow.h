#ifndef VIDEOWATCHWINDOW_H
#define VIDEOWATCHWINDOW_H

#include "render/LinearGradient.h"
using namespace Magna::Render;

#include "basegui/PopOutWindow.h"
#include "basegui/Button.h"
#include "basegui/TableLayout.h"
#include "basegui/LinearLayout.h"
using namespace Magna::GUI;

#include "multimedia/VLCVideoController.h"
using namespace Magna::MultiMedia;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class ControlBar : public Controller{
        public:
          ControlBar( const SharedPtr<VLCVideoController>& );
          virtual ~ControlBar();

        private :
          void startToPlay( bool );
          void startToStop();
        public:
          SharedPtr<Button> m_stopButton;
          SharedPtr<Button> m_playNPauseButton;
          SharedPtr<Button> m_previousButton;
          SharedPtr<Button> m_nextButton;

          uint32 m_hasPlayed;

          SharedPtr<VLCVideoController> m_vlcVideoController;
      };

      class VideoWatchWindow : public Window{
        public:
          VideoWatchWindow();
          explicit VideoWatchWindow( const String& filePath );
          virtual ~VideoWatchWindow();

        public:
          void loadVideoFile( const String& filePath );

        public:
          void play();
          void pause();
          void stop();

        private:
          //SharedPtr<Controller> 
          SharedPtr<ControlBar> m_ctrlBar;
          SharedPtr<VLCVideoController> m_vlcVideoController;
      };

    }
  }
}

#endif  /*  VIDEOWATCHWINDOW_H  */