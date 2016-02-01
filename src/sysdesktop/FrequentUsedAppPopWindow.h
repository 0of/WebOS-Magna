#ifndef FREQUENTUSEDAPPPOPWINDOW_H
#define FREQUENTUSEDAPPPOPWINDOW_H

#include <vector>

#include "basegui/PopOutWindow.h"
#include "basegui/Button.h"
#include "basegui/TableLayout.h"
#include "basegui/Label.h"
#include "basegui/LinearLayout.h"
using namespace Magna::GUI;

#include "FrequentUsedAppData.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class AppInfoController : public Controller{
        public:
          AppInfoController( const FrequentUsedAppData& );
          virtual ~AppInfoController();

        public:
          SharedPtr<Button> m_appEntryButton;
          SharedPtr<Label> m_appNameLabel;

          FrequentUsedAppData m_data;
      };

      class FrequentUsedAppPopWindow : public PopOutWindow{
        __Constructor_Destructor public:
          FrequentUsedAppPopWindow();
          virtual ~FrequentUsedAppPopWindow();

        public:
          void addFrequentUsedApp( const FrequentUsedAppData& );

        private:
          void processAboutToRun( const String& path);

        __Data_Field private:
          SharedPtr<TableLayout> m_centerLayout; 
          Image m_appCommonIcon;
          std::vector<SharedPtr<AppInfoController> > m_appButtons;
      };

    }
  }
}//namespace Magna

#endif  /*  FREQUENTUSEDAPPPOPWINDOW_H  */