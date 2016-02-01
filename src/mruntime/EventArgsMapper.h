#ifndef EVENTARGSMAPPER_H
#define EVENTARGSMAPPER_H

#include "basegui/EventArgConstants.h"
using namespace Magna::GUI;

namespace Magna{
  namespace Runtime{

    class EventArgsMapper{
      public:
        const static MouseEventArgConstants::MouseButton shared_mouseButton_mapper[] ;
        

    };

    const MouseEventArgConstants::MouseButton EventArgsMapper::shared_mouseButton_mapper[] 
    = { MouseEventArgConstants::MouseButton_LeftButton
      , MouseEventArgConstants::MouseButton_MidButton
      , MouseEventArgConstants::MouseButton_RightButton
      , MouseEventArgConstants::MouseButton_Other };
  }
}//namespace Magna
#endif  /*  EVENTARGSMAPPER_H  */