#ifndef DELEGATORCOLLECTION_H
#define DELEGATORCOLLECTION_H

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"

namespace Magna{
  namespace GUI{
     
    class DelegatorCollection{

      __Constructor_Destructor protected:
        explicit DelegatorCollection( uint16 type, uint16 shared = !false );
        DelegatorCollection( const DelegatorCollection& collection );
        ~DelegatorCollection();

      __Checker public:
        inline bool isShared() const{
          return m_shared;
        }

      __Getter public:
        inline uint16 getType() const{
          return m_type;
        }

      __Data_Field private:
        const uint16 m_type;
        const uint16 m_shared;
    };


  }//namespace GUI
}//namespace Magna

#endif  /*  DELEGATORCOLLECTION_H  */