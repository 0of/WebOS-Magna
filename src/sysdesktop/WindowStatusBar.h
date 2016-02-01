#ifndef WINDOWSTATUSBAR_H
#define WINDOWSTATUSBAR_H

#include <vector>
#include <queue>
#include <map>

#include "basegui/Button.h"
#include "basegui/ButtonGroup.h"
#include "basegui/Window_p.h"
#include "basegui/LinearLayout.h"
#include "basegui/ScrollableController.h"
using namespace Magna::GUI;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      //window icon
      //window title
      //
      // 

      class WindowStatusBar : public Controller{
        public:
          WindowStatusBar();
          virtual ~WindowStatusBar();

        public:
          void openNewWindow( const SharedPtr<Window::WindowRoot>& wnd );
          void closeWindow( uint32 wid );
          void actWhenWindowFocusChanged( uint32 , bool );

        private:
          void buttonToggledAction( const uint32& );
          void buttonUntoggledAction( const uint32& );

        private:
          ButtonGroup m_group;
          uint32 m_toggledIndex;

          std::map< uint32 , uint32 > m_widMapsButtonIndex;
          std::map< uint32, SharedPtr<Window::WindowRoot> > m_runningWnds;
          std::queue< SharedPtr<Button> > m_reservedButtons;

          SharedPtr<LinearLayout> m_layout;
          
          FillBrush m_buttonSharedFillBrush;
          FillBrush m_pressedButtonSharedFillBrush;

          IntegerSize m_unitSize;

      };

    }
  }
}//namespace Magna

#endif  /*  WINDOWSTATUSBAR_H  */