#ifndef RUNNABLECONTEXT_P_H
#define RUNNABLECONTEXT_P_H

#include "../basedef_lib.h"

#include <vector>

#include "../RunnableContext.h"
#include "../RunnableMessageLooper.h"

namespace Magna{
  namespace Core{

    class BASEDEF_LIB_EXPORT RunnableContext::RunnableContextEntity{
      public:
        uint32 m_int_runningId;
        String m_contextName;
        RunnableMessageLooper m_looper;
        SharedPtr<RunnableContext> m_parentContext;
        std::vector< SharedPtr<RunnableContext> > m_childContext;

      public:
        explicit RunnableContextEntity( const String& );
        explicit RunnableContextEntity( const String& , const SharedPtr<RunnableContext>& );
        ~RunnableContextEntity();
    };

  }
}//namespace Magna

#endif  /*  RUNNABLECONTEXT_P_H  */
