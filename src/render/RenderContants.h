#ifndef RENDERCONTANTS_H
#define RENDERCONTANTS_H

#include "render_lib.h"

namespace Magna{
  namespace Render{
    
    class RENDER_LIB_EXPORT TextRenderContants{
    public:
      enum TextHAlignment{
        TextAlignment_Left = 0x00000001,
        TextAlignment_Right = 0x00000002,
        TextAlignment_HCenter = 0x00000004,
      };

      enum TextVAlignment{
        TextAlignment_Top  =  0x00010000,
        TextAlignment_Bottom = 0x00020000,
        TextAlignment_VCenter = 0x00040000,
      };
    };

    typedef uint32 TextAlignment;

  }//namespace Render
}//namespace Magna

#endif  /*  RENDERCONTANTS_H  */