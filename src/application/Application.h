#ifndef APPLICATION_H
#define APPLICATION_H

#include "application_lib.h"

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/AtomicInt.h"
#include "basedef/SpinMutex.h"
#include "basedef/SharedPtr.h"

#include "basedef/RunnableContext.h"

using namespace Magna::Core;

#include "basegui/Window.h"
using namespace Magna::GUI;

#include "ApplicationWindowManager.h"

namespace Magna{
  namespace Application{


    class APPLICATION_LIB_EXPORT MagnaApplication : public RunnableContext{
      friend class ApplicationWindowManager;
      friend class ApplicationAccessor;
      friend class WindowIntroducer;

      __Constructor_Destructor public:
        explicit MagnaApplication( const String& appName );
        virtual ~MagnaApplication();

      private:
        MagnaApplication( const MagnaApplication& );
        MagnaApplication & operator = ( const MagnaApplication& );

      public:
        void exec();
        void aboutToQuit();
        void quit();


        void setupMainWindow( const SharedPtr<Window>& mainWnd );
        ApplicationWindowManager &getAppWindowManager();
        SharedPtr<Window> getMainWindow();

        String getApplicationName() const;


      public:
        class PrivateData;
        static MagnaApplication *shared_Obtain_Application();

        static void introducesApplication( const String& );
        static void introducesApplicationWithDialog( const String& );

      private:
        static SpinMutex shared_mutex;
        static SpinMutex shared_confirm_mutex;
        static MagnaApplication *shared_current_application;  

      private:    
        SharedPtr<PrivateData> m_data;

    };

    /*
    class APPLICATION_LIB_EXPORT MagnaApplication{
      friend class ApplicationWindowManager;
      friend class ApplicationAccessor;

      __Constructor_Destructor public:
      explicit MagnaApplication( const assic_char* appName );
      virtual ~MagnaApplication();

      public:
        void exec();
        void setupMainWindow( const SharedPtr<Window>& mainWnd );
        ApplicationWindowManager &getAppWindowManager();
        SharedPtr<Window> getMainWindow();

        const assic_char * getApplicationName() const;

        //###what if it goes when application is quited by user
        void sendMessageCode(sint32 code);

      public:
        class PrivateData;
        static MagnaApplication *shared_Obtain_Application();


      private:
        static SpinMutex shared_mutex;
        static SpinMutex shared_confirm_mutex;
        static MagnaApplication *shared_current_application;  

      private:    
        SharedPtr<PrivateData> m_data;
        
    };
    */

  }//namespace Application
}//namespace Magna

#endif  /*  APPLICATION_H  */