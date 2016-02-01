#ifndef MUSICPOPWINDOW_H
#define MUSICPOPWINDOW_H

#include "basegui/PopOutWindow.h"
#include "basegui/Button.h"
#include "basegui/LinearLayout.h"
#include "basegui/WebFrameController.h"
#include "basegui/Label.h"
using namespace Magna::GUI;

#include "MusicPlayWindow.h"
#include "FileInfoController.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class MusicPopWindow : public PopOutWindow{
        public:
          MusicPopWindow();
          virtual ~MusicPopWindow();

        private:
          void processAboutToPlay(FileInfoController & info );

        private:
          std::vector<SharedPtr<Controller> > m_musicInfos;
          SharedPtr<MusicPlayWindow> m_playWindow;
          Image m_musicIcon;
      };

    }
  }
}//namespace Magna

#endif  /*  MUSICPOPWINDOW_H  */