#include "SpinMutex.h"

#include "Thread.h"

namespace Magna{
  namespace Core{
    void SpinMutex::acquires() const{  
      for(; 0 != m_atomicCounter.read(); Thread::yield() ){}
      m_atomicCounter.write( 1 );
    }

    void SpinMutex::releases() const {
      m_atomicCounter.write( 0 );
    }

    void SpinMutex::acquires() {  
      for(; 0 != m_atomicCounter.read(); Thread::yield() ){}
      m_atomicCounter.write( 1 );
    }
    void SpinMutex::releases() {
      m_atomicCounter.write( 0 );
    }
  }//namespace Core
}//namespace Magna