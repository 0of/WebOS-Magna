#pragma warning(disable:4251)

#ifndef SCRIPTRESOURCEHANDLER_H
#define SCRIPTRESOURCEHANDLER_H

#include "resource_lib.h"

#include "basedef/SpinMutex.h"
#include "basedef/Trigger.h"
using namespace Magna::Core;

#include "ScriptResourceHandleBehaviour.h"
#include "ScriptResourceObject.h"

#include <string>

namespace Magna{
  namespace Resource{
    
    class RESOURCE_LIB_EXPORT ScriptResourceHandler{
      public:
        TRIGGER_DEF(OnceLoadActed, SharedPtr<ScriptResourceObject::PrivateData> , const std::string& )
        TRIGGER_DEF(OnceUnloadActed, SharedPtr<ScriptResourceObject::PrivateData> , const std::string& )

      public:
        static ScriptResourceHandler & getScriptResourceHandler();

        void setLoadBehaviour( ScriptResourceHandleBehaviour *behaviour);

        void actLoad( ScriptResourceObject &obj );
        void actUnload( ScriptResourceObject &obj );

      protected:
        ScriptResourceHandler();
        ~ScriptResourceHandler();

      private:
        SpinMutex m_mutex;
        std::string m_scriptString;
        ScriptResourceHandleBehaviour *m_behaviour;
    };

  }//namespace Resource
}//namespace Magna

#endif  /*  ScriptResourceHandler_H  */