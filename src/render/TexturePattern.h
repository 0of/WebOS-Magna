#ifndef TEXTUREPATTERN_H
#define TEXTUREPATTERN_H

#include "render_lib.h"

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"

#include <string>

namespace Magna{
   namespace Render{
     __Abstracted class RENDER_LIB_EXPORT TexturePattern{
       friend class FillBrush;
       __Constants public:
        enum PatternType{
          PatternType_Unknow = 0x0,
          PatternType_Repeat = 0x1
        };
       __Constructor_Destructor protected:
        TexturePattern( PatternType type );
      __Constructor_Destructor public:
        virtual ~TexturePattern() {}
      protected:
        virtual String _toString() const = 0;
      __Data_Field protected:
        PatternType m_type;
     };

   }//Render
}//Magna

#endif  /*  TEXTUREPATTERN_H  */
