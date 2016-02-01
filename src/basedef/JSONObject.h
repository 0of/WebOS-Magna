#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include "basedef_lib.h"

#include <map>

#include "BaseTypes.h"
#include "SystemDef.h"
#include "String.h"
#include "SharedPtr.h"

namespace Magna{
  namespace Core{

    class BASEDEF_LIB_EXPORT JSONValue;

    //!    JSON object
    class JSONObject{
      public:
        //!  Default constructor
        JSONObject();
        //!  Destructor
        virtual ~JSONObject();
        //!  Copy constructor
        JSONObject( const JSONObject& );
        //!  Assign constructor
        JSONObject& operator = ( const JSONObject& );

      public:
        //!  emplace with key and value        
        /*!  
         *  \param key
         *    the unique key for current JSONObject.
         *  \param value
         *    value
         *    
         *    if the key is NOT unique, the value will replace the existed one.
         */
        void emplace( const String& key, const JSONValue& value );

        //!  get JSONValue by key
        /*!  
         *  \param key
         *    index key
         *  \return
         *    if key does NOT exist, the return JSONValue would be a invalid value.
         *  
         *  \sa getBy()
         */
        JSONValue operator [] ( const String& key );

        //!  get const JSONValue by key
        const JSONValue operator [] ( const String& key ) const;

        //!  get JSONValue by key
        /*!  
         *  \param key
         *    index key
         *  \return
         *    if key does NOT exist, the return JSONValue would be a invalid value.
         *
         */
        JSONValue getBy( const String& key );

        //!  get const JSONValue by key
        const JSONValue getBy( const String& key ) const;

        //!  serialize all its children to strings
        String toString() const;

      private:
        typedef SharedPtr<std::map< String, JSONValue > > Members;
        Members m_members;
    };

  }
}//namespace Magna
#endif  /*  JSONOBJECT_H  */