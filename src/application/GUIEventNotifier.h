#ifndef GUIEVENTNOTIFIER_H
#define GUIEVENTNOTIFIER_H

#include "application_lib.h"

#include "basedef/AbstractedNotifier.h"
#include "basedef/AbstractedEventArgs.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include "basegui/Controller.h"
using namespace Magna::GUI;

namespace Magna{
  namespace Application{
    
    class APPLICATION_LIB_EXPORT GUIEventNotifier : public __Generalizes AbstractedNotifier{
    public:
      static const uint32 shared_GUIEventNotifierType;

    public:
      explicit GUIEventNotifier( const SharedPtr<Controller::ControllerRoot>&, const SharedPtr<AbstractedEventArgs>& );
      virtual ~GUIEventNotifier();

    __Override_Methods public:
      virtual void notify();

    private:
      SharedPtr<Controller::ControllerRoot> m_eventRoot;
      SharedPtr<AbstractedEventArgs> m_eventArgs;
    };


  }//namespace Application
}//namespace Magna

#endif  /*  GUIEVENTNOTIFIER_H  */