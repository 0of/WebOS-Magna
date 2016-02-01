#ifndef MUSICPLAYWINDOW_H
#define MUSICPLAYWINDOW_H

#include "basegui/Window.h"
#include "basegui/Button.h"
#include "basegui/LinearLayout.h"
#include "basegui/WebFrameController.h"
using namespace Magna::GUI;

#include "multimedia/AudioOutObject.h"
using namespace Magna::MultiMedia;

#include "MusicPlayerContrController.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class MusicEffectController : public Controller{
      public:
        MusicEffectController();
        virtual ~MusicEffectController();

      public:
        void startEffect();
        void stopEffect();
      };

      class MusicPlayWindow : public Window{
        public:
          MusicPlayWindow();
          virtual ~MusicPlayWindow();

        public:
          void setPlayQueue( const std::vector<String>& );
          void setAboutToPlayAt( const uint32 &);

        private:
          void processPlayButton();
          void processStopButton();
          void processPlayNext();
          void processPlayPre();

          uint32 m_isPlaying;

          SharedPtr<MusicPlayerContrController> m_playerCtrl;
          SharedPtr<MusicEffectController> m_effectController;

      };
    }
  }
}

#endif  /*  MUSICPLAYWINDOW_H  */
