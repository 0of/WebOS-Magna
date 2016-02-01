#pragma once

#include <exception>

#include "basedef/AbstractedNotifier.h"
using namespace Magna::Core;

#include "application/Application.h"
#include "application/ApplicationEntry.h"
using namespace Magna::Application;

#include "DesktopWindow.h"
#include "DesktopEventDispatcher.h"
using namespace Magna::SystemComponent::Desktop;

//notifier
namespace Magna{
  namespace SystemComponent{
    namespace Desktop{
      class DesktopApplication{
        public:
          static MagnaApplication *pInstance;
          static const String shared_usr_dir;
      };
      
    }
  }
}