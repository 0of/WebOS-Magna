#ifndef POINTER_H
#define POINTER_H

#include "SystemDef.h"

namespace Magna{  
   namespace Core{
     /*!  \brief
         free and clone the pointee inside the Pointer.
       */
     __Interface Pointer{
      public:
        virtual void Free() = 0;
        virtual void *Clone() = 0;
     };
   }//Core
}//Magna

#endif  /*  POINTER_H  */