#ifndef OSDETACHCONTROLLERSBEHAVIOURNOTIFIER_H
#define OSDETACHCONTROLLERSBEHAVIOURNOTIFIER_H

#include <vector>

#include "basedef/RunnableContext.h"
using namespace Magna::Core;

#include "basegui/Controller_p.h"
using namespace Magna::GUI;

#include "OSBehaviourNotifier.h"

namespace Magna{
  namespace Runtime{

    class OSDetachControllersBehaviourNotifier : public OSBehaviourNotifier{
      __Constructor_Destructor public:
        explicit OSDetachControllersBehaviourNotifier( const std::vector< uint64 >& );
        virtual ~OSDetachControllersBehaviourNotifier();

      __Override_Methods public:
        virtual void notifyOS() ;

      __Data_Field private:
         std::vector< uint64 >  m_ids;  
    };

  }
}//namespace Magna
#endif  /*  OSDETACHCONTROLLERSBEHAVIOURNOTIFIER_H  */