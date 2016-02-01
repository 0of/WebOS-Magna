#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include "basedef/Uncopyable.h"
#include "basedef/SpinMutex.h"
using namespace Magna::Core;

#include "application/Application.h"
#include "ApplicationTaskBlock.h"

#include <unordered_map>

namespace Magna{
  namespace Application{
    class ApplicationManager :Uncopyable{
      public:
        static ApplicationManager &getApplicationManager();
      private:
        ApplicationManager();
        ~ApplicationManager();

      public:
        void pushAppTaskBlock( ApplicationTaskBlock *app );
        void pushSpecificAppTaskBlock( ApplicationTaskBlock *app, uint32 id );
        void endAppTaskBlock( uint32 aid );

      private:
        //?  priority queue
        std::unordered_map<uint32, ApplicationTaskBlock * > m_blocks;
        SpinMutex m_mutex;

    };

  }//namespace Application
}//namespace Magna

#endif  /*  APPLICATIONMANAGER_H  */