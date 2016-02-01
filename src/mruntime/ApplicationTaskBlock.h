#ifndef APPLICATIONTASKBLOCK_H
#define APPLICATIONTASKBLOCK_H

#include "basedef/Uncopyable.h"
#include "basedef/Thread.h"
using namespace Magna::Core;

#include "application/Application.h"

#include <QLibrary>

namespace Magna{
  namespace Application{
    typedef void(MAGNA_CDECL *app_entry)();
    typedef QLibrary AppInstance;

    class ApplicationTaskBlock : public Thread
                            , Uncopyable{
      public:
        ApplicationTaskBlock() ;
        explicit ApplicationTaskBlock(app_entry entry,AppInstance* instance);
        
        ~ApplicationTaskBlock();

      public:
        void assignBlockId( uint32 id );
        void assignRunningApplication( MagnaApplication * app );

        inline MagnaApplication *getApplication(){ return m_appObj; }

        bool isValid(){ return m_id != 0; }

        bool operator == ( const ApplicationTaskBlock& block ) ;
        bool operator != ( const ApplicationTaskBlock& block ) ;
        
      private:
        uint32 m_id;
        AppInstance *m_instance;
        MagnaApplication *m_appObj;
    };
  }//namespace Application
}//namespace Magna
#endif  /*  APPLICATIONTASKBLOCK_H  */