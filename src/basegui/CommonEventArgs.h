#ifndef CLOSEEVENTARGS_H
#define CLOSEEVENTARGS_H

#include "basegui_lib.h"

#include "basedef/AbstractedEventArgs.h"
using namespace Magna::Core;

#include "EventArgConstants.h"

namespace Magna{  
   namespace GUI{
     class BASEGUI_LIB_EXPORT CloseEventArgs : public __Generalizes AbstractedEventArgs{
     public:
       explicit CloseEventArgs()
         :AbstractedEventArgs( GUIEventConstants::GUIEvent_WindowClose, false ){}
       virtual ~CloseEventArgs(){}
     };

     class BASEGUI_LIB_EXPORT ShowEventArgs  : public __Generalizes AbstractedEventArgs{
     public:
       explicit ShowEventArgs()
         :AbstractedEventArgs( GUIEventConstants::GUIEvent_Shown, false ){}
       virtual ~ShowEventArgs(){}
     };

     class BASEGUI_LIB_EXPORT HideEventArgs :  public __Generalizes AbstractedEventArgs{
       public:
        explicit HideEventArgs()
          :AbstractedEventArgs( GUIEventConstants::GUIEvent_Hidden, false ){}
        virtual ~HideEventArgs(){}
     };

     class BASEGUI_LIB_EXPORT FocusEventArgs :  public __Generalizes AbstractedEventArgs{
      public:
        explicit FocusEventArgs( GUIEventConstants::EventType type )
          :AbstractedEventArgs( [&]()->uint16{
          assert( type == GUIEventConstants::GUIEvent_FocusIn
            || type == GUIEventConstants::GUIEvent_FocusOut );
          return static_cast<uint16>(type);
        }(), false ){}
        virtual ~FocusEventArgs(){}
     };
   }//GUI
}//Magna
#endif  /*  CLOSEEVENTARGS_H  */