#ifndef SYSTEMCOMOBJECTMANAGER_H
#define SYSTEMCOMOBJECTMANAGER_H

#include "DesktopObject.h"
using namespace Magna::SystemComponent::Desktop;

namespace Magna{
  namespace SystemComponent{

    class SystemComObjectManager{
      public:
        static SystemComObjectManager & getSystemComObjectManager(){
          static SystemComObjectManager _manager;
          return _manager;
        }

      protected:
        SystemComObjectManager()
          :m_desktopObj(){

        }

        ~SystemComObjectManager(){

        }

      public:
        inline DesktopObject & getDesktopObject(){
          return m_desktopObj;
        }

      private:
        DesktopObject m_desktopObj;
    };

  }
}//namespace Magna

#endif  /*  SYSTEMCOMOBJECTMANAGER_H  */