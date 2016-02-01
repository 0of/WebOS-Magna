#include "OSQtWidgetInitBehaviourNotifier.h"

#include "GlobalQtWidgetInitReceptionist.h"

namespace Magna{
  namespace Runtime{

    OSQtWidgetInitBehaviourNotifier::OSQtWidgetInitBehaviourNotifier( QtWidgetInitializer *init)
      :OSBehaviourNotifier()
      ,m_initializer( init ){

    }

    OSQtWidgetInitBehaviourNotifier::~OSQtWidgetInitBehaviourNotifier(){

    }

    void OSQtWidgetInitBehaviourNotifier::notifyOS() {
      if( m_initializer != Nullptr ){
        GlobalQtWidgetInitReceptionist&_rec = GlobalQtWidgetInitReceptionist::getGlobalQtWidgetInitReceptionist();
        m_initializer->actInitialization( _rec );
      }
    }

  }
}