#ifndef SCRIPTRESOURCEMANAGER_H
#define SCRIPTRESOURCEMANAGER_H

#include "basedef/String.h"
#include "basedef/SpinMutex.h"
using namespace Magna::Core;

#include "resource/ScriptResourceObject.h"
#include "resource/ScriptResourceObject_p.h"
using namespace Magna::Resource;

#include <unordered_map>
#include <random>

namespace Magna{
  namespace Kernel{

    class ScriptResourceManager{
      public:
        ScriptResourceManager & getScriptResourceManager();

      protected:
        ScriptResourceManager();
        ~ScriptResourceManager();

      public:
        void loadResource( SharedPtr<ScriptResourceObject::PrivateData> privateObj, const String& script );
        void unloadResource( SharedPtr<ScriptResourceObject::PrivateData> privateObj , const String& script );

        void notifyLoadFinished( const uint64& id );

        void unloadAll();

      private:
        typedef std::unordered_map<uint64, SharedPtr<ScriptResourceObject::PrivateData> > LoadedObjects;
        LoadedObjects m_loadedResObjs;
      
        SpinMutex m_mutex;
    };

  }
}//namespace Magna

#endif  /*  SCRIPTRESOURCEMANAGER_H  */