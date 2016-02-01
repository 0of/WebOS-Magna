#ifndef DESKTOPSTATUSBAR_H
#define DESKTOPSTATUSBAR_H

#include "basegui/Controller.h"
#include "basegui/Label.h"
#include "basegui/ProgressBar.h"
#include "basegui/LinearLayout.h"
#include "basegui/TableLayout.h"
using namespace Magna::GUI;

#include "WindowStatusBar.h"
#include "BatteryDetailsWindow.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class DesktopStatusBar : public Controller{
        public:
          static uint32 shared_status_bar_width;

          DesktopStatusBar( uint32 init_height );
          virtual ~DesktopStatusBar();

        public:
          inline SharedPtr<WindowStatusBar>& getWindowStatusBar() {
            return m_winStatusBar;
          }

        private:
          void showBatteryDetailsWindow();

        private:
          SharedPtr<WindowStatusBar> m_winStatusBar;

          SharedPtr<Controller> m_sysStatusColumn;

          SharedPtr<Button> m_powerStatusButton;
          SharedPtr<Button> m_networkConnectionStatusButton;
          SharedPtr<Button> m_volumeStatusButton;

          SharedPtr<BatteryDetailsWindow> m_batteryDetailsWnd;
      };

    }
  }
}//namespace Magna
#endif  /*  DESKTOPSTATUSBAR_H  */