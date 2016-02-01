#ifndef OSSCRIPTRUNBEHAVIOURNOTIFIER_H
#define OSSCRIPTRUNBEHAVIOURNOTIFIER_H

#include <QtCore/QString>

#include "OSBehaviourNotifier.h"

namespace Magna{
  namespace Runtime{

    class OSScriptRunBehaviourNotifier : public OSBehaviourNotifier{
      __Constructor_Destructor public:
        explicit OSScriptRunBehaviourNotifier( const QString& sc );
        virtual ~OSScriptRunBehaviourNotifier();

      __Override_Methods public:
        virtual void notifyOS() ;

      __Data_Field private:
        QString m_script;
    };

  }
}//namespace Magna

#endif  /*  OSSCRIPTRUNBEHAVIOURNOTIFIER_H  */