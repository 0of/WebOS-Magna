#ifndef IFRAME_H
#define IFRAME_H

#include "basegui_lib.h"

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"

#include "RenderEventArgs.h"

namespace Magna{
  namespace GUI{
    __Interface class BASEGUI_LIB_EXPORT IFrame{
      __Constructor_Destructor public:
        IFrame(){}
        virtual ~IFrame() {}

      public:
        virtual uint32 getFrameHeight() const = 0;
        virtual void renderingFrame( const String& title
                                , const IntegerSize& textSize
                                , const uint32& frameWidth                        
                                , const Image& icon  //already scaled to IFrame height  * height 
                                , RenderingEventArgs& args ) = 0;
    };
  }//namespace GUI
}//namespace Magna

#endif  /*  IFRAME_H  */
