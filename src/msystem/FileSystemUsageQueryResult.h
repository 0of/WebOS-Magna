#ifndef FILESYSTEMUSAGEQUERYRESULT_H
#define FILESYSTEMUSAGEQUERYRESULT_H

#include "system_lib.h"

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/String.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

namespace Magna{
  namespace System{
    
    class SYSTEM_LIB_EXPORT FileSystemUsageQueryResult{
      friend class SystemInfo;
      __Constructor_Destructor protected:
        FileSystemUsageQueryResult();

      __Constructor_Destructor public:
        FileSystemUsageQueryResult( const FileSystemUsageQueryResult& );
        ~FileSystemUsageQueryResult();

      __Overloaded_Methods public:
        FileSystemUsageQueryResult & operator =( const FileSystemUsageQueryResult& );

      __Checker public:
        inline bool isNull() const{ return m_data.isNull(); }

      __Getter public:
        double getUsedPercentage() const;
        uint64 getTotal() const;
        uint64 getFree() const;
        uint64 getUsed() const;
        uint64 getAvail() const;
        uint64 getFiles() const;
        uint64 getFreeFiles() const;

      __Data_Field private:
        struct PrivateData;
        SharedPtr<PrivateData> m_data;
    };

  }//namespace System
}//namespace Magna

#endif  /*  FILESYSTEMUSAGEQUERYRESULT_H  */