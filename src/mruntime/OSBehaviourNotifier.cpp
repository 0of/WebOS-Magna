#include "OSBehaviourNotifier.h"

namespace Magna{
  namespace Runtime{
    

    QEvent::Type OSBehaviourNotifier::shared_OSMessage_Type = static_cast< QEvent::Type >(QEvent::registerEventType( 2000 ));

  }//namespace Runtime
}//namespace Magna