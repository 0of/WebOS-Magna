#include "OSAttachControllersBehaviourNotifier.h"

#include "basedef/RunnableContextAccessor.h"
#include "basedef/RunnableMessageLooper.h"
using namespace Magna::Core;

#include "ControllerManager.h"
using namespace Magna::Kernel;

namespace Magna{
  namespace Runtime{
    
    OSAttachControllersBehaviourNotifier::OSAttachControllersBehaviourNotifier( RunnableContext *context, std::vector< SharedPtr<Controller::ControllerRoot> >& roots)
      :OSBehaviourNotifier()
      ,m_roots( std::move( roots ) )
      ,m_context( context ) {

    }

    OSAttachControllersBehaviourNotifier::~OSAttachControllersBehaviourNotifier(){

    }

     void OSAttachControllersBehaviourNotifier::notifyOS() {
       auto &_ctrl_manager = ControllerManager::getControllerManager();
       auto &&_entity = RunnableContextAccessor::getEntity(m_context );
       if( !_entity.isNull() ){
         _ctrl_manager.registerDynamicControllers( m_roots,  &_entity->m_looper);       
       }
      
     }

  }//namespace Runtime
}//namespace Magna
