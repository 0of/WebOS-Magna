#ifndef APPLICATIONLOADER_H
#define APPLICATIONLOADER_H

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/SpinMutex.h"

#include "application/Application.h"
#include "ApplicationTaskBlock.h"

#include "DesktopObject.h"
using namespace Magna::SystemComponent::Desktop;

#include <string>

namespace Magna{
  namespace Application{

    class ApplicationLoader{
      public:
        static ApplicationLoader &obtainLoader();

        __Constructor_Destructor private:
        ApplicationLoader();
        ~ApplicationLoader();

      public:
        ApplicationTaskBlock *loads( const String& path );
        ApplicationTaskBlock *loadDesktopApplication( DesktopObject& _out_ );

        void loadApplicationExpInfo( const String&_app_path, String &_out_ap_name, String &_out_icon_path );

      private:
        SpinMutex m_mutex;
    };

  }//namespace Application
}//namespace Magna

#endif  /*  APPLICATIONLOADER_H  */