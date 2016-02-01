#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include "system_lib.h"

#include <vector>

#include "basedef/Uncopyable.h"
using namespace Magna::Core;

#include "CpuInfo.h"
#include "FileSystemInfo.h"
#include "FileSystemUsageQueryResult.h"
#include "BatteryDeviceInfo.h"

namespace Magna{
  namespace System{
    
    class SYSTEM_LIB_EXPORT SystemInfo : Uncopyable{
      public:
        static SystemInfo & getSystemInfo();

      protected:
        SystemInfo();
        ~SystemInfo();

      public:
        std::vector<CpuInfo> getCpuInfos() const;
        std::vector<FileSystemInfo> getFileSystemInfos() const;
        BatteryDeviceInfo getBatteryDeviceInfo() const;

        FileSystemUsageQueryResult queryFileSystemUsage( const FileSystemInfo& ) const; 

      private:
        struct PrivateData;
        PrivateData *m_data;
    };

  }//namespace System
}//namespace Magna

#endif  /*  SYSTEMINFO_H  */