#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include "qt_glue_lib.h"

#include "basedef/String.h"
using namespace Magna::Core;

namespace Magna{
  namespace Glue{
    
    class QT_GLUE_LIB_EXPORT FileDialog {
      public:
        static String getFilePath( const String& title, const String& startDir, const String& filter );
    };


  }//namespace Glue
}//namespace Magna

#endif  /*  FILEDIALOG_H  */