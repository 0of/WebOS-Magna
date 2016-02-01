#ifndef OSSTARTWINDOWBEHAVIOURNOTIFIER_H
#define OSSTARTWINDOWBEHAVIOURNOTIFIER_H

#include "basegui/Window_p.h"
using namespace Magna::GUI;

#include "WindowManager.h"
using namespace Magna::Kernel;

#include "OSBehaviourNotifier.h"

namespace Magna{
  namespace Runtime{

    class OSStartWindowBehaviourNotifier : public OSBehaviourNotifier{
      __Constructor_Destructor public:
        explicit OSStartWindowBehaviourNotifier( const SharedPtr<Window::WindowRoot>& , WindowManager::WindowType );
        virtual ~OSStartWindowBehaviourNotifier();

      __Override_Methods public:
        virtual void notifyOS() ;

      __Data_Field private:
        SharedPtr<Window::WindowRoot> m_root;    
        WindowManager::WindowType m_wndType;
    };

  }
}//namespace Magna
#endif  /*  OSSTARTWINDOWBEHAVIOURNOTIFIER_H  */