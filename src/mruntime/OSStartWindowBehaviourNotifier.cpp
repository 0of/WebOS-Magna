#include "OSStartWindowBehaviourNotifier.h"

namespace Magna{
  namespace Runtime{

    OSStartWindowBehaviourNotifier::OSStartWindowBehaviourNotifier( const SharedPtr<Window::WindowRoot>& r , WindowManager::WindowType t)
      :OSBehaviourNotifier()
      ,m_root( r )
      ,m_wndType( t ){

    }

    OSStartWindowBehaviourNotifier::~OSStartWindowBehaviourNotifier(){

    }

    void OSStartWindowBehaviourNotifier::notifyOS() {
      if( !m_root.isNull() ){
        if( m_wndType == WindowManager::WindowType_Normal ){
          WindowManager::getWindowManager().startWindow(m_root);
        }
        else if( m_wndType == WindowManager::WindowType_PopOut ){
          WindowManager::getWindowManager().startPopOutWindow(m_root);
        }
        else{

        }
      }
    }

  }
}//namespace Magna