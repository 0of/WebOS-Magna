#ifndef FILESYSTEMINFO_H
#define FILESYSTEMINFO_H

#include "system_lib.h"

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/String.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

namespace Magna{
  namespace System{
      
    class SYSTEM_LIB_EXPORT FileSystemInfo{
      friend class SystemInfo;

      __Constants public:
        enum FileSystemType{
          FileSystemType_Unknow,
          FileSystemType_None,
          FileSystemType_LocalDisk,
          FileSystemType_Network,
          FileSystemType_RamDisk,
          FileSystemType_CDRom,
          FileSystemType_Swap
        };

      __Constructor_Destructor protected:
        FileSystemInfo();
          
      __Constructor_Destructor public:
        FileSystemInfo( const FileSystemInfo& );
        ~FileSystemInfo();

      __Overloaded_Methods public:
        FileSystemInfo& operator = ( const FileSystemInfo& );

      __Getter public:
        String getDirPath() const;
        String getDeviceName() const;
        String getTypeName() const;
        String getSystemTypeName() const;

        String getOptions() const;
        FileSystemType getType() const;

      __Data_Field private:
        struct PrivateData;
        SharedPtr<PrivateData> m_data;
    };

  }//namespace System
}//namespace Magna

#endif  /*  FILESYSTEMINFO_H  */