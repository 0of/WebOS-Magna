#ifndef OSATTACHCONTROLLERSBEHAVIOURNOTIFIER_H
#define OSATTACHCONTROLLERSBEHAVIOURNOTIFIER_H

#include <vector>

#include "basedef/RunnableContext.h"
using namespace Magna::Core;

#include "basegui/Controller_p.h"
using namespace Magna::GUI;

#include "OSBehaviourNotifier.h"

namespace Magna{
  namespace Runtime{

    class OSAttachControllersBehaviourNotifier : public OSBehaviourNotifier{
      __Constructor_Destructor public:
        explicit OSAttachControllersBehaviourNotifier( RunnableContext *context, std::vector< SharedPtr<Controller::ControllerRoot> >& roots);
        virtual ~OSAttachControllersBehaviourNotifier();

      __Override_Methods public:
        virtual void notifyOS() ;

      __Data_Field private:
        std::vector< SharedPtr<Controller::ControllerRoot> > m_roots;    
        RunnableContext *m_context;
    };

  }
}//namespace Magna
#endif  /*  OSATTACHCONTROLLERSBEHAVIOURNOTIFIER_H  */