#include "OSBehaviourNotifierHandler.h"

#include "OSBehaviourNotifier.h"

namespace Magna{
  namespace Runtime{
    OSBehaviourNotifierHandler & OSBehaviourNotifierHandler::getOSBehaviourNotifierHandler(){
      static OSBehaviourNotifierHandler handler;
      return handler;
    }

    OSBehaviourNotifierHandler::OSBehaviourNotifierHandler()
      :QObject(){

    }

    OSBehaviourNotifierHandler::~OSBehaviourNotifierHandler(){

    }

    bool OSBehaviourNotifierHandler::event ( QEvent * e ){
      bool _ret_handler = false;
      if( e != Nullptr && e->type() == OSBehaviourNotifier::shared_OSMessage_Type ){
        //pointer cast
        OSBehaviourNotifier *_behaviour_notifier = reinterpret_cast<OSBehaviourNotifier *>( e );
        _behaviour_notifier->notifyOS();
      }
      return _ret_handler;
    }

  }//namespace Runtime
}//namespace Magna