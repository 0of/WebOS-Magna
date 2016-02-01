#ifndef IMAGERESOURCEHANDLERHELPER_H
#define IMAGERESOURCEHANDLERHELPER_H

#include "qt_glue_img.h"

#include "basedef/Uninstantiable.h"
#include "basedef/String.h"
using namespace Magna::Core;

#include "Image.h"

namespace Magna{
  namespace Glue{
    
    class QT_GLUE_LIB_EXPORT ImageResourceHandlerHelper : Uninstantiable{
      public:
        static bool getImageResourceString( const Image& img, OutStringStream& outter );

    };

  }//namespace Glue
}//namespace Magna

#endif  /*  IMAGERESOURCEHANDLERHELPER_H  */