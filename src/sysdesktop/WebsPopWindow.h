#ifndef WEBSPOPWINDOW_H
#define WEBSPOPWINDOW_H

#include "basegui/PopOutWindow.h"
#include "basegui/Button.h"
#include "basegui/TableLayout.h"
#include "basegui/WebFrameController.h"
using namespace Magna::GUI;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class WebsPopWindow : public PopOutWindow{
      public:
        WebsPopWindow();
        virtual ~WebsPopWindow();

      private:
        SharedPtr<WebFrameController> m_webFrameCtrl;
      };

    }
  }
}

#endif  /*  WEBSPOPWINDOW_H  */