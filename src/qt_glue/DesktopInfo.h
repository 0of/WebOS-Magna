#ifndef DESKTOPINFO_H
#define DESKTOPINFO_H

#include "qt_glue_lib.h"

#include "basedef/Uncopyable.h"
#include "basedef/RectRegion.h"
using namespace Magna::Core;

namespace Magna{
  namespace Glue{
    
    class QT_GLUE_LIB_EXPORT DesktopInfo : Uncopyable{
      public:
        static DesktopInfo& getDesktopInfo();

      protected:
        DesktopInfo();
        ~DesktopInfo();

      public:
        sint32  screenCount () const;
        sint32  getPrimaryScreenIndex () const;

        IntegerRectRegion getScreenBoundingRect( sint32 screenIndex = -1 ) const;

        IntegerRectRegion getMagnaOSScreenBoundingRect() const;


    };

  }//namespace Glue
}//namespace Magna

#endif  /*  DESKTOPINFO_H  */