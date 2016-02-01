#ifndef OSSTARTApplicationBEHAVIOURNOTIFIER_H
#define OSSTARTApplicationBEHAVIOURNOTIFIER_H

#include "basedef/RunnableContext.h"
#include "basedef/String.h"
using namespace Magna::Core;

#include "OSBehaviourNotifier.h"

namespace Magna{
  namespace Runtime{

    class OSStartApplicationBehaviourNotifier : public OSBehaviourNotifier{
      __Constructor_Destructor public:
        explicit OSStartApplicationBehaviourNotifier( bool, const String& , RunnableContext * );
        virtual ~OSStartApplicationBehaviourNotifier();

      __Override_Methods public:
        virtual void notifyOS() ;

      __Data_Field private:
        String m_appPath;    
        RunnableContext * m_parent;
        uint32 m_needDialog;
    };

  }
}//namespace Magna
#endif  /*  OSSTARTApplicationBEHAVIOURNOTIFIER_H  */