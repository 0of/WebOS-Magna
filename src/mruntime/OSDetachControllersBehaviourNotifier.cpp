#include "OSDetachControllersBehaviourNotifier.h"

#include "basedef/RunnableContextAccessor.h"
#include "basedef/RunnableMessageLooper.h"
using namespace Magna::Core;

#include "ControllerManager.h"
using namespace Magna::Kernel;

namespace Magna{
  namespace Runtime{

    OSDetachControllersBehaviourNotifier::OSDetachControllersBehaviourNotifier( const std::vector< uint64 >& ids)
      :OSBehaviourNotifier()
      ,m_ids( std::move( ids ) ){

    }

    OSDetachControllersBehaviourNotifier::~OSDetachControllersBehaviourNotifier(){

    }

    void OSDetachControllersBehaviourNotifier::notifyOS() {
      auto &_ctrl_manager = ControllerManager::getControllerManager();
      _ctrl_manager.unregisterDynamicController( m_ids );       
    }

  }//namespace Runtime
}//namespace Magna