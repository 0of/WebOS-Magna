#ifndef BATTERYDETAILSWINDOW_H
#define BATTERYDETAILSWINDOW_H

#include "basegui/Controller.h"
#include "basegui/Label.h"
#include "basegui/ProgressBar.h"
#include "basegui/LinearLayout.h"
#include "basegui/ImageLabel.h"
#include "basegui/TableLayout.h"
using namespace Magna::GUI;

#include "system/SystemInfo.h"
#include "system/BatteryDeviceInfo.h"
using namespace Magna::System;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class BatteryDetailsWindow : public Window{
        public:
          static Image shared_full_status_icon;
          static Image shared_charing_status_icon;
          static Image shared_low_status_icon;
          static Image shared_medium_status_icon;
          static Image shared_high_status_icon;

        public:
          BatteryDetailsWindow();
          virtual ~BatteryDetailsWindow();

          inline const Image &getCurrentStatusIcon(){
            return m_currentStatusIcon;
          }

        private:
          BatteryDeviceInfo m_currentBatteryInfo;

          SharedPtr<Label> m_infoLabel;
          SharedPtr<ImageLabel> m_currentSymb;

          Image m_currentStatusIcon;
      };

    }
  }
}

#endif  /*  BATTERYDETAILSWINDOW_H  */