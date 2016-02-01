#ifndef GUIEVENTINDEXER_H
#define GUIEVENTINDEXER_H

#include "EventIndexer.h"
using namespace Magna;

namespace Magna{  
    EVENT_DEFINE(WindowClose,0x00000001)
    EVENT_DEFINE(Hidden,0x00000002)
    EVENT_DEFINE(Shown,0x00000003)  

    EVENT_DEFINE(Moved,0x00000004)  
    EVENT_DEFINE(Resized,0x00000005)  

    EVENT_DEFINE(MousePressed,0x0000000A)  
    EVENT_DEFINE(MousePressingMoved,0x0000000B)  
    EVENT_DEFINE(MouseReleased,0x0000000C)  
    EVENT_DEFINE(MouseClicked,0x0000000D)  
    EVENT_DEFINE(MouseDoubleClicked,0x000000E)  

    EVENT_DEFINE(MouseWheelUp,0x0000000F)  
    EVENT_DEFINE(MouseWheelDown,0x00000010)  

    EVENT_DEFINE(MouseHoverIn,0x00000011)  
    EVENT_DEFINE(MouseHovered,0x00000012)  
    EVENT_DEFINE(MouseHoverOut,0x00000013)  

    EVENT_DEFINE(KeyPressed,0x00000014)  
    EVENT_DEFINE(KeyReleased,0x00000015)  

    EVENT_DEFINE(Rendering,0x00000020)  

    EVENT_DEFINE(FocusIn,0x00000030)  
    EVENT_DEFINE(FocusOut,0x00000031)  
  
    EVENT_DEFINE(Scrolled,0x00000040)
}//Magna
#endif  /*  GUIEVENTINDEXER_H  */