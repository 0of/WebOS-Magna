#ifndef TIME_H
#define TIME_H

#include "qt_glue_lib.h"

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/SharedPtr.h"
#include "basedef/String.h"
using namespace Magna::Core;

namespace Magna{
  namespace Glue{
    
    class QT_GLUE_LIB_EXPORT Time{
      __Constructor_Destructor public:
        Time();
        explicit Time( uint32 h, uint32 m, uint32 s, uint32 ms );
        Time( const Time& );
        ~Time();
      
      __Getter public:
        uint32  getHour () const;
        uint32  getMinute () const;
        uint32  getMsec () const;
        uint32  getSecond () const;

      __Checker public:
        bool  isValid () const;
        String toString ( const String & format ) const;
  
      public:
        static Time currentTime() ;
        static void currentTime( Time & ) ;

      private:
        class PrivateData;
        SharedPtr<PrivateData> m_data;
    };

  }//namespace Glue
}//namespace Magna

#endif  /*  TIME_H  */