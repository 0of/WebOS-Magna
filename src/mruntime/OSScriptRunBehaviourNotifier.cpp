#include "OSScriptRunBehaviourNotifier.h"

#include "RuntimeContainer.h"
using namespace Magna::Runtime;

namespace Magna{
  namespace Runtime{

    OSScriptRunBehaviourNotifier::OSScriptRunBehaviourNotifier( const QString& sc)
      :OSBehaviourNotifier()
      ,m_script( sc ){

    }

    OSScriptRunBehaviourNotifier::~OSScriptRunBehaviourNotifier(){

    }

    void OSScriptRunBehaviourNotifier::notifyOS() {
      //get runtime 
      RuntimeContainer &_container = RuntimeContainer::getRuntimeContainer();
      _container.evalJavaScript( m_script );
    }

  }
}