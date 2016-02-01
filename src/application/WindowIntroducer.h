#ifndef WINDOWINTRODUCER_H
#define WINDOWINTRODUCER_H

#include "application_lib.h"

#include "Application.h"

namespace Magna{
  namespace Application{
    
    class APPLICATION_LIB_EXPORT WindowIntroducer{
      friend class MagnaApplication;
      public:
        static void introduceWindow( MagnaApplication &, const SharedPtr<Window> & );
    };

  }//namespace Application
}//namespace Magna

#endif  /*  WINDOWINTRODUCER_H  */
