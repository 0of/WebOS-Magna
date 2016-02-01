#ifndef WINDOWACCESSOR_H
#define WINDOWACCESSOR_H

#include "basegui_lib.h"
#include "Window_p.h"

namespace Magna{
  namespace GUI{
    class BASEGUI_LIB_EXPORT WindowAccessor{
      public:
        static SharedPtr<Window::WindowRoot> getRoot( const SharedPtr<Window>&  wnd );

        MAGNA_FORCEINLINE static SharedPtr<Window::WindowRoot> getRoot( Window *  wnd ){
          SharedPtr<Window::WindowRoot> _ret_root;
          if( wnd != Nullptr ){
            _ret_root = wnd->m_wndRoot;
          }
          return _ret_root;
        }
    };
  }//namespace GUI
}//namespace Magna

#endif  /*  WINDOWACCESSOR_H  */
