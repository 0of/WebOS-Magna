#ifndef APPLICATIONWINDOWMANAGERACCESSOR_H
#define APPLICATIONWINDOWMANAGERACCESSOR_H

#include "application_lib.h"

#include "basedef/Uninstantiable.h"

#include "ApplicationWindowManager.h"
#include "ApplicationWindowManager_p.h"

namespace Magna{
  namespace Application{
    
    class APPLICATION_LIB_EXPORT ApplicationWindowManagerAccessor : Uninstantiable{
      public:
        inline static ApplicationWindowManager::PrivateData *accessAppWindowManager( ApplicationWindowManager &manager ){
          ApplicationWindowManager::PrivateData *_ret_data = Nullptr;
          _ret_data = manager.m_data;
          return _ret_data;
        }
    };

  }//namespace Application
}//namespace Magna

#endif  /*  APPLICATIONWINDOWMANAGERACCESSOR_H  */