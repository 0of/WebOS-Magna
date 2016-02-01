#ifndef MONITOREDTARGET_H
#define MONITOREDTARGET_H

#include "BaseTypes.h"
#include "SystemDef.h"

#include "Monitor.h"

namespace Magna{
  namespace Core{

    __Abstracted MonitoredTarget{

      __Constructor_Destructor protected:
        MonitoredTarget();
        virtual ~MonitoredTarget() = 0 {}

      public:
        template<typename MonitorType>
        void registerMonitor();

      protected
        void registerMonitor( );
    };
  }
}//namespace Magna

#endif  /*  MONITOREDTARGET_H  */