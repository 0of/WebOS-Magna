#ifndef SCRIPTRESOURCEHANDLEBEHAVIOUR_H
#define SCRIPTRESOURCEHANDLEBEHAVIOUR_H

#include "resource_lib.h"

#include "basedef/BaseTypes.h"

#include "ScriptResourceObject.h"

#include <string>

namespace Magna{
  namespace Resource{
    
    __Interface class RESOURCE_LIB_EXPORT ScriptResourceHandleBehaviour{
      public:
        virtual bool load( ScriptResourceObject &obj, std::string& scriptOutter ) = 0;
        virtual void unload( ScriptResourceObject &obj, std::string& scriptOutter ) = 0;
    };

  }//namespace Resource
}//namespace Magna

#endif  /*  SCRIPTRESOURCEHANDLEBEHAVIOUR_H  */
