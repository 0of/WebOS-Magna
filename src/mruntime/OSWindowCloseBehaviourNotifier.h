#ifndef OSWINDOWCLOSEBEHAVIOURNOTIFIER_H
#define OSWINDOWCLOSEBEHAVIOURNOTIFIER_H

#include <QtCore/QString>

#include "OSBehaviourNotifier.h"

namespace Magna{
  namespace Runtime{

    class OSWindowCloseBehaviourNotifier : public OSBehaviourNotifier{
      __Constructor_Destructor public:
        explicit OSWindowCloseBehaviourNotifier( uint32 sc );
        virtual ~OSWindowCloseBehaviourNotifier();

      __Override_Methods public:
        virtual void notifyOS() ;

      __Data_Field private:
        uint32 m_int_Wid;
    };

  }
}//namespace Magna

#endif  /*  OSWINDOWCLOSEBEHAVIOURNOTIFIER_H  */