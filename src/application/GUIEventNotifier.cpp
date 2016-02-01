#include "GUIEventNotifier.h"

#include "basegui/Controller_p.h"

namespace Magna{
  namespace Application{
    
    const uint32 GUIEventNotifier::shared_GUIEventNotifierType = AbstractedNotifier::registerNotifierType( 7289 );

    GUIEventNotifier::GUIEventNotifier( const SharedPtr<Controller::ControllerRoot>& r, const SharedPtr<AbstractedEventArgs>& a)
      :AbstractedNotifier( shared_GUIEventNotifierType )
      ,m_eventRoot( r )
      ,m_eventArgs( a ){

    }

    GUIEventNotifier::~GUIEventNotifier(){

    }

    void GUIEventNotifier::notify(){

      if( !m_eventRoot.isNull()
        && !m_eventArgs.isNull() ){

        m_eventRoot->_dispatchEventMessage( *m_eventArgs );
      }

    }

  }//namespace Application
}//namespace Magna