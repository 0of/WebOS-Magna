#ifndef APPLICATIONACCESSOR_H
#define APPLICATIONACCESSOR_H

#include "application_lib.h"

#include "basedef/Uninstantiable.h"

#include "Application.h"
#include "Application_p.h"

#include <cassert>

namespace Magna{
  namespace Application{
    class APPLICATION_LIB_EXPORT ApplicationAccessor : Uninstantiable{
    public:
      inline static SharedPtr<MagnaApplication::PrivateData>  accessApplication( MagnaApplication *app ){
        assert( app != Nullptr );
        return app->m_data;
      }
    };
  }//namespace Application
}//namespace Magna

#endif  /*  APPLICATIONACCESSOR_H  */