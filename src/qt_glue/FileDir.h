#ifndef FILEDIR_H
#define FILEDIR_H

#include "qt_glue_lib.h"

#include "basedef/String.h"
using namespace Magna::Core;

#include <vector>

namespace Magna{
  namespace Glue{
    
    class QT_GLUE_LIB_EXPORT FileDir{

      public:
        static std::vector<String> getAbsPath( const String& dir, const String filter );
    };

  }//namespace Glue
}//namespace Magna

#endif  /*  FILEDIR_H  */