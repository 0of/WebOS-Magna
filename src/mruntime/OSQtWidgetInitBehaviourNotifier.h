#ifndef OSQTWIDGETINITBEHAVIOURNOTIFIER_H
#define OSQTWIDGETINITBEHAVIOURNOTIFIER_H

#include "basegui/QtWidgetInitializer.h"
using namespace Magna::GUI;

#include "OSBehaviourNotifier.h"

namespace Magna{
  namespace Runtime{

    class OSQtWidgetInitBehaviourNotifier : public OSBehaviourNotifier{
      __Constructor_Destructor public:
      explicit OSQtWidgetInitBehaviourNotifier( QtWidgetInitializer *);
      virtual ~OSQtWidgetInitBehaviourNotifier();

    __Override_Methods public:
      virtual void notifyOS() ;

    __Data_Field private:
      QtWidgetInitializer *m_initializer;
    };

  }
}//namespace Magna
#endif  /*  OSATTACHCONTROLLERSBEHAVIOURNOTIFIER_H  */