#ifndef WINDOWEVENTNOTIFIER_H
#define WINDOWEVENTNOTIFIER_H

#include "application_lib.h"

#include "basedef/AbstractedNotifier.h"
#include "basedef/AbstractedEventArgs.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include "basegui/Window.h"
using namespace Magna::GUI;

namespace Magna{
  namespace Application{

    class APPLICATION_LIB_EXPORT WindowEventNotifier : public __Generalizes AbstractedNotifier{
    public:
      static const uint32 shared_WindowEventNotifierType;

    public:
      explicit WindowEventNotifier( const SharedPtr<Window::WindowRoot>&, const SharedPtr<AbstractedEventArgs>& );
      virtual ~WindowEventNotifier();

      __Override_Methods public:
      virtual void notify();

    private:
      SharedPtr<Window::WindowRoot> m_eventRoot;
      SharedPtr<AbstractedEventArgs> m_eventArgs;
    };


  }//namespace Application
}//namespace Magna

#endif  /*  WINDOWEVENTNOTIFIER_H  */