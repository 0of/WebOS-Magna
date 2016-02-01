#ifndef MONITOR_H
#define MONITOR_H

#include "RunableContext.h"

namespace Magna{
  namespace Core{

    class Monitor{
      protected:
        explicit Monitor( const RunableContext& );
        virtual ~Monitor() = 0{}

      protected:
        RunableContext m_runableContext;
    };
  }
}//namespace Magna

#endif  /*  MONITOR_H  */