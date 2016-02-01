#include "WindowEventNotifier.h"

#include "basegui/Window_p.h"

namespace Magna{
  namespace Application{

    const uint32 WindowEventNotifier::shared_WindowEventNotifierType  = AbstractedNotifier::registerNotifierType(  63571 );

    WindowEventNotifier::WindowEventNotifier( const SharedPtr<Window::WindowRoot>&root, const SharedPtr<AbstractedEventArgs>& eventArgs)
      :AbstractedNotifier(shared_WindowEventNotifierType)
      ,m_eventRoot( root )
      ,m_eventArgs( eventArgs ){

    }

    WindowEventNotifier::~WindowEventNotifier(){

    }

    void WindowEventNotifier::notify(){

      if( !m_eventRoot.isNull()
        && !m_eventArgs.isNull() ){

          m_eventRoot->_dispatchEventMessage( *m_eventArgs );
      }

    }

  }//namespace Application
}//namespace Magna