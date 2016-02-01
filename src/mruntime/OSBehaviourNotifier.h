#ifndef OSBEHAVIOURNOTIFIER_H
#define OSBEHAVIOURNOTIFIER_H

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"
#include "basedef/Uncopyable.h"
using namespace Magna::Core;

#include <QEvent>

namespace Magna{
  namespace Runtime{

    class OSBehaviourNotifier : public QEvent
                          , public Uncopyable{
      public:
        static QEvent::Type shared_OSMessage_Type;

      __Constructor_Destructor protected:
        OSBehaviourNotifier()
          :QEvent( shared_OSMessage_Type ){

        }

        virtual ~OSBehaviourNotifier(){

        }

      public:
        virtual void notifyOS() = 0;

    };

  }
}//namespace Magna
#endif  /*  OSBEHAVIOURNOTIFIER_H  */