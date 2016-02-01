#ifndef SCRIPTRESOURCEOBJECT_H
#define SCRIPTRESOURCEOBJECT_H

#include "resource_lib.h"

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"
#include "basedef/SharedPtr.h"
#include "basedef/SpinMutex.h"
using namespace Magna::Core;

#include <string>
#include <set>

namespace Magna{
  namespace Resource{
    
    class RESOURCE_LIB_EXPORT ScriptResourceObject{
      public:
        class PrivateData;
        friend class ScriptResourceHandler;
        static std::set<uint16> &getRegisteredTypeFactory();
        static uint16 registerObjectType( uint16 hint );

      protected:
        explicit ScriptResourceObject( uint16 type );
        explicit ScriptResourceObject( uint16 type, const std::string& src );
        virtual ~ScriptResourceObject();

      public:
        bool isLoaded() const;
        std::string getSourcePath() const;

        virtual bool load( const std::string& src ) = 0;
        virtual void unload() = 0;

      protected:
        SharedPtr<PrivateData> m_data;
    };

  }//namespace Resource
}//namespace Magna

#endif  /*  SCRIPTRESOURCEOBJECT_H  */