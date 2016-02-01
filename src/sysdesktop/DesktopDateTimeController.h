#ifndef DESKTOPDATETIMECONTROLLER_H
#define DESKTOPDATETIMECONTROLLER_H

#include "basedef/Timer.h"
using namespace Magna::Core;

#include "basegui/Controller.h"
#include "basegui/Label.h"
#include "basegui/ProgressBar.h"
#include "basegui/LinearLayout.h"
#include "basegui/TableLayout.h"
using namespace Magna::GUI;

#include "glue/Date.h"
#include "glue/TimeObject.h"
using namespace Magna::Glue;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class DesktopDateTimeController : public Controller{
        __Constructor_Destructor public:
          DesktopDateTimeController();
          virtual ~DesktopDateTimeController();

        public:
          inline String& getDateInString(){
            return m_dateInString;
          }

          inline String& getTimeInString(){
            return m_timeInString;
          }

        private:
          void updateEachMin();
          void startTictoc();

        __Data_Field private:
          SharedPtr<Timer> m_updateTimer;
          Date m_currentDate;
          Time m_currentTime;

          String m_dateInString;
          String m_timeInString;
    
      };

    }
  }
}//namespace Magna

#endif  /*  DESKTOPDATETIMECONTROLLER_H  */