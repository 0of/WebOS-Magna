#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H

#include "basedef/String.h"
using namespace Magna::Core;

#include "XMLNode.h"

namespace Magna{
  namespace Network{
    
    class XMLDocument{
      __Constructor_Destructor public:
        XMLDocument();
        explicit XMLDocument( const String& filename );
        XMLDocument( const XMLDocument& );
        virtual ~XMLDocument();

      public:
        void readFromFile( const String& );

        bool isNull() const;

        XMLNode getRootNode() const;

      private:
        class DocumentData;
        DocumentData *m_data;
    };

  }//namespace Network
}//namespace Magna

#endif  /*  XMLDOCUMENT_H  */