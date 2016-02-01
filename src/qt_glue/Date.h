#ifndef DATE_H
#define DATE_H

#include "qt_glue_lib.h"

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/SharedPtr.h"
#include "basedef/String.h"
using namespace Magna::Core;

namespace Magna{
  namespace Glue{
    
    class QT_GLUE_LIB_EXPORT Date{
      __Constructor_Destructor public:
        Date ();
        explicit Date ( uint32 y, uint32 m, uint32 d );
        Date( const Date& );
        ~Date();
      
      __Getter public:
        uint32 getDay () const;
        uint32  getDayOfWeek () const;
        uint32  getDayOfYear () const;

        uint32  getDaysNumberInMonth () const;
        uint32  getDaysNumberInYear () const;
        uint32  getWeekNumber () const;
        uint32  getYear () const;
        uint32  getMonth () const;

      __Checker public:
        bool  isValid () const;
        
      __Setter public:
        bool  setDate ( uint32 year, uint32 month, uint32 day );

      public:
        String  toString ( const String & format ) const;
        static Date currentDate ();
        static void currentDate ( Date& );

      __Data_Field private:
        class PrivateData;
        SharedPtr<PrivateData> m_data;
    };

  }//namespace Glue
}//namespace Magna

#endif  /*  DATE_H  */