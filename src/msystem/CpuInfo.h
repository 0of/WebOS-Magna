#ifndef CPUINFO_H
#define CPUINFO_H

#include "system_lib.h"

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/String.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

namespace Magna{
  namespace System{

    class SYSTEM_LIB_EXPORT CpuInfo{
        friend class SystemInfo;
      __Constructor_Destructor protected:
        CpuInfo();
      
        __Constructor_Destructor public:
        CpuInfo( const CpuInfo& info );
        ~CpuInfo();

        __Overloaded_Methods public:
        CpuInfo& operator = ( const CpuInfo& info );

      __Getter public:
        uint64 getCacheSize() const;      
        uint32 getCoresPerSocket() const;    
        uint32 getMhz() const;
        String getModel() const;
        uint32 getTotalCores() const;
        uint32 getTotalSockets() const;
    
        String   getVendor() const;

      __Data_Field private:
        struct PrivateData;
        SharedPtr<PrivateData> m_data;
    };

  }//namespace System
}//namespace Magna

#endif  /*  CPUINFO_H  */