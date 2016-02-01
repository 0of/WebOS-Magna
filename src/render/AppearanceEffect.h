#ifndef APPEARANCEEFFECT_H
#define APPEARANCEEFFECT_H

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"
#include "basedef/String.h"
using namespace Magna::Core;

#include "render_lib.h"

namespace Magna{
   namespace Render{
     __Abstracted class RENDER_LIB_EXPORT AppearanceEffect{
      public:
        virtual String toString() const = 0;

      protected:
        AppearanceEffect(){}

      public:
        virtual ~AppearanceEffect() {} 
     };


   }//Render
}//Magna
#endif  /*  APPEARANCEEFFECT_H  */
