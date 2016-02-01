#ifndef STATICBUFFER_H
#define STATICBUFFER_H

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"

namespace Magna{  
   namespace GUI{
     template<uint32 op1, uint32 op2>
     class MulCalculator{ public: enum {result = op1 * op2}; };

     template<typename BufferType, uint32 size>
     class StaticBuffer{
      typedef BufferType & Ref ;
      public:
        StaticBuffer(){         
          ::memset(m_buffer,0, MulCalculator<sizeof(BufferType), size>::result ); }
        ~StaticBuffer(){}
      
      __Overloaded_Methods public:
        operator BufferType *(){
          return m_buffer;
        }    
      private:
        BufferType m_buffer[ size ];
     };

     template<typename BufferType>
     class StaticBuffer<BufferType,0>{};
    
   }//GUI
}//Magna
#endif  /*  STATICBUFFER_H  */