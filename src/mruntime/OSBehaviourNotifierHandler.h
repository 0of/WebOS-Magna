#ifndef OSBEHAVIOURNOTIFIERHANDLER_H
#define OSBEHAVIOURNOTIFIERHANDLER_H

#include <QObject>

namespace Magna{
  namespace Runtime{
    
    class OSBehaviourNotifierHandler : public QObject{
      public:
        static OSBehaviourNotifierHandler & getOSBehaviourNotifierHandler();

      protected:
        OSBehaviourNotifierHandler();
        virtual ~OSBehaviourNotifierHandler();

      public:
        virtual bool event ( QEvent * e );
    };

  }//namespace Runtime
}//namespace Magna

#endif  /*  OSBEHAVIOURNOTIFIERHANDLER_H  */