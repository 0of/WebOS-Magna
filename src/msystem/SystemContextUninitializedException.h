#ifndef SYSTEMCONTEXTUNINITIALIZEDEXCEPTION_H
#define SYSTEMCONTEXTUNINITIALIZEDEXCEPTION_H

#include <exception>
#include <stdexcept>

namespace Magna{
  namespace System{
    
    class SystemContextUninitializedException : public std::runtime_error{
      public:
        SystemContextUninitializedException()
          :std::runtime_error( "System Context Uninitialized!" ){}
    };

  }//namespace System
}//namespace Magna

#endif  /*  SYSTEMCONTEXTUNINITIALIZEDEXCEPTION_H  */
