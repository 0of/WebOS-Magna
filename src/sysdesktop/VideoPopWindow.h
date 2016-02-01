#ifndef VIDEOPOPWINDOW_H
#define VIDEOPOPWINDOW_H

#include "basegui/PopOutWindow.h"
#include "basegui/Button.h"
#include "basegui/TableLayout.h"
using namespace Magna::GUI;

#include "VideoWatchWindow.h"
#include "FileInfoController.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class VideoPopWindow : public PopOutWindow{
        __Constructor_Destructor public:
          VideoPopWindow();
          virtual ~VideoPopWindow();

        private:
          void processWatchVideo(const String& );

        private:
          SharedPtr<VideoWatchWindow> m_videoWatchWindow;
          std::vector<SharedPtr<Controller> > m_videoInfos;
          Image m_videoIcon;
      };

    }
  }
}

#endif  /*  VIDEOPOPWINDOW_H  */