#include "OSWindowCloseBehaviourNotifier.h"

#include "WindowManager.h"
using namespace Magna::Kernel;

namespace Magna{
  namespace Runtime{

    OSWindowCloseBehaviourNotifier::OSWindowCloseBehaviourNotifier(uint32 id)
      :OSBehaviourNotifier()
      ,m_int_Wid( id ){

    }

    OSWindowCloseBehaviourNotifier::~OSWindowCloseBehaviourNotifier(){

    }

    void OSWindowCloseBehaviourNotifier::notifyOS() {
      //get window manager 
      auto &_manager = WindowManager::getWindowManager();
      _manager.finishWindow( m_int_Wid );
    }

  }
}
