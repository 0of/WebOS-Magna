#ifndef APPLICATIONWINDOWMANAGER_P_H
#define APPLICATIONWINDOWMANAGER_P_H

#include "Application.h"
#include "Application_p.h"
#include "ApplicationEventHandler.h"

#include "basegui/Window.h"
using namespace Magna::GUI;

#include <list>

namespace Magna{
  namespace Application{
    
    class APPLICATION_LIB_EXPORT ApplicationWindowManager::PrivateData{
      public:
        /*
        explicit PrivateData( ApplicationEventHandler &handler  )
        //  :m_loop( loop )
          :m_handler( handler )
          ,m_list()
          ,m_runningWndCounter( 0 )
          ,m_mainWindow(){
            
        }
        ~PrivateData(){
          
        }

      public:
        //void postRunningWindow( Window &)

        inline void increaseRunningWindow(){ ++m_runningWndCounter; }
        //  check all the window down 
        //  when the running counter turns to zero
        void decreaseRunningWindow();

      public:
        //ApplicationEventLoop& m_loop;
        ApplicationEventHandler &m_handler;
        std::list< SharedPtr<Window> > m_list;
        uint32 m_runningWndCounter;
        SharedPtr<Window> m_mainWindow;
        */

      explicit PrivateData()
        :m_list()
          ,m_runningWndCounter( 0 )
          ,m_mainWindow(){

        }
        ~PrivateData(){

        }

    public:
      void postRunningWindow( const SharedPtr<Window>& wnd){
        m_list.push_back( wnd );
        ++m_runningWndCounter;
      }

      void postMainWindow( const SharedPtr<Window>& wnd){
        m_mainWindow = wnd;
        ++m_runningWndCounter;
      }

      inline void increaseRunningWindow(){ ++m_runningWndCounter; }
      //  check all the window down 
      //  when the running counter turns to zero
      void decreaseRunningWindow();

    public:
      //ApplicationEventLoop& m_loop;
      //ApplicationEventHandler &m_handler;
      std::list< SharedPtr<Window> > m_list;
      uint32 m_runningWndCounter;
      SharedPtr<Window> m_mainWindow;
    };
  }//namespace Application
}//namespace Magna

#endif  /*  APPLICATIONWINDOWMANAGER_P_H  */
