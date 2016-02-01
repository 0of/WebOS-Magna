#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/StaticTypeTrait.h"
#include "basedef/SpinMutex.h"
#include "basedef/SharedPtr.h"
#include "basedef/Trigger.h"
using namespace Magna::Core;

#include "basegui/Window.h"
using namespace Magna::GUI;

#include "render/DyadCoordinateMapper.h"
using namespace Magna::Render;

#include "application/ApplicationWindowManager.h"
#include "application/ApplicationEventLoop.h"
using namespace Magna::Application;

#include <unordered_map>
#include <hash_map>

namespace Magna{
  namespace Kernel{

      //  The main progress of dispatch window events would be shown in details:
      //  Each unit contains its runtime-id , a window root and application window manager
      //  a window root can be deemed as a core window 
      //  a window manager is a application unique element and it's binding to application object
      //  when a event occurs, Window manager would receive event arguments and triggered id
      //  then find the id and retrieve the window root and app window manager
      //  pack the arguments and root into a notifier message object
      //  send the message to the application object
      //  all the event callbacks would be implemented in application thread
      //  
      //  some flaws:
      //  1)  Window root expose to much to WindowManager
      //  2) ApplicationWindowManager & Application their granularity  seems too high
      //  3) ### Event arguments shall be deleted within application
      //    which enhance the limitations of the event dispatching.
      //  4) Repeated code too much
      //  
      //  Base on the deadline, these problems would be solved later.
      //  
      class  WindowManager{
        //typedef void( WindowManager:: *EmplaceAction)( SharedPtr<Window::WindowRoot>& );

        __Constants public:
          enum WindowType{
            WindowType_Normal,
            WindowType_PopOut,
            WindowType_Desktop
          };

        public:
          //lasting till power off
          static WindowManager & getWindowManager();

        __Constructor_Destructor private:
          WindowManager();
          ~WindowManager();

        public:      
          void startWindow( const SharedPtr<Window::WindowRoot>& wnd_root );
          void startDesktopWindow( const SharedPtr<Window::WindowRoot>& wnd_root );
          void startPopOutWindow(  const SharedPtr<Window::WindowRoot>& wnd_root  );
          //void startWindow( const SharedPtr<Window::WindowRoot>& wnd_root,  ApplicationEventLoop &loop );
      
          //void activateWindow( const uint32& runtime_wid );
          void finishWindow( const uint32& runtime_wid );
          void showWindow( const uint32& runtime_wid);
          void hideWindow( const uint32& runtime_wid);

          //void focusWindow( const uint32& runtime_wid);

          void finishAll();      

          void dispatchMoveEvent( const uint32& runtime_wid, sint32 x, sint32 y );
          void dispatchResizeEvent( const uint32& runtime_wid, sint32 w, sint32 h );    

        private:
          bool _startWindow( const SharedPtr<Window::WindowRoot>& wnd_root, WindowType type = WindowType_Normal );

        private:
          typedef std::pair<SharedPtr<Window::WindowRoot>, WindowType > WindowInfo;
          typedef std::unordered_map<uint32,  WindowInfo > WindowInfoCollection;
          
          //typedef std::pair<SharedPtr<Window::WindowRoot>, ApplicationEventLoop *> WindowDataPack;
    
          WindowInfoCollection m_runingWnds;
          
          //std::unordered_map<uint64, SharedPtr<Window::WindowRoot> > m_runingWnds;
          SpinMutex m_mutex;

          //uint32 *m_
        
      };

    }//namespace Kernel
}//namespace Magna

#endif  /*  WINDOWMANAGER_H  */