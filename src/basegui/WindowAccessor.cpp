#include "WindowAccessor.h"

//////////////////////////////////////////////////////////////////////////
//#define Nullptr nullptr
// 

namespace Magna{
  namespace GUI{
    
    SharedPtr<Window::WindowRoot> WindowAccessor::getRoot( const SharedPtr<Window>& wnd ){
      SharedPtr<Window::WindowRoot> _ret_root;
      if( !wnd.isNull() ){
        _ret_root = wnd->m_wndRoot;
      }
      return _ret_root;
    }

  }//namespace GUI
}//namespace Magna
