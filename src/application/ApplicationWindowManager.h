#ifndef APPLICATIONWINDOWMANAGER_H
#define APPLICATIONWINDOWMANAGER_H

#include "application_lib.h"

#include "basedef/Uncopyable.h"
#include "basedef/SpinMutex.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include "basegui/Window.h"
using namespace Magna::GUI;

namespace Magna{
  namespace Application{
    class MagnaApplication;
    class ApplicationEventHandler;
    class APPLICATION_LIB_EXPORT ApplicationWindowManager : Uncopyable{
      friend class ApplicationWindowManagerAccessor;
      friend class MagnaApplication;
      friend class WindowIntroducer;

      public:
        class PrivateData;

      __Constructor_Destructor protected:      
        ApplicationWindowManager();
        //ApplicationWindowManager( ApplicationEventHandler &handler/*ApplicationEventLoop & loop*/ ) ;
        ~ApplicationWindowManager();

      public:

        //void registerMainWindow( const SharedPtr<Window>& window );
        SharedPtr<Window> getMainWindow();

      __Data_Field private:      
        PrivateData *m_data;
    };
    

  }//namespace Application
}//namespace Magna

#endif  /*  APPLICATIONWINDOWMANAGER_H  */