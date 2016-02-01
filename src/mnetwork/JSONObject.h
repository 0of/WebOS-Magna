#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include <map>

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/String.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

namespace Magna{
  namespace Core{

    class JSONValue;
    class JSONObject{
      public:
        JSONObject();
        virtual ~JSONObject();
        JSONObject( const JSONObject& );
        JSONObject& operator = ( const JSONObject& );

      public:
        JSONValue operator [] ( const String& key );
        const JSONValue operator [] ( const String& key ) const;

        JSONValue getBy( const String& key );
        const JSONValue getBy( const String& key ) const;

      private:
        typedef SharedPtr<std::map< String, JSONValue > > Members;
        Members m_members;
    };

  }
}//namespace Magna
#endif  /*  JSONOBJECT_H  */