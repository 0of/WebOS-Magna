#include "Layout_p.h"

#include "Controller_p.h"

namespace Magna{  
  namespace GUI{

    //###
    //An issue about the layout loop circuit 
    //e.g. A Controller has A Layout
    // A Layout lays out the B Controller
    // B Controller has B Layout
    // However B Layout lays out A Controller
    // which results a loop circuit

    Layout::PrivateLayout::PrivateLayout()
      :m_controllers()
      ,m_wnd( Nullptr )
      ,m_contr( Nullptr )
      ,m_flags( 0 )
      ,m_hasBound( false ){

    }

    Layout::PrivateLayout::~PrivateLayout(){

    }

    void Layout::PrivateLayout::bindWindow( Window *binder ){
      assert( binder != Nullptr );
    
      m_wnd = binder;
      m_hasBound = !false;

      auto _iter = m_controllers.begin();
      for( ; _iter != m_controllers.end() ; [&](){
        auto &_ctrl_root = (*_iter++)->m_root;
          if( !_ctrl_root.isNull() ){
            _ctrl_root->onWindowBound();
          }

          auto _each_layout = _ctrl_root->m_centreLayout;
          if( !_each_layout.isNull() ){
            if( !_each_layout->m_layout.isNull() ){
              _each_layout->m_layout ->bindWindow( binder );
            }
          }
      }()) {}

      /*
      m_hasBound = !false;

      auto _iter = m_controllers.begin();
      for( ; _iter != m_controllers.end() ; [&](){
        auto &_ctrl_root = (*_iter++)->m_root;
        if( !_ctrl_root.isNull() ){
          _ctrl_root->onWindowBound();
        }
        
        auto _each_layout = _ctrl_root->m_centreLayout;
        if( !_each_layout.isNull() ){
          if( !_each_layout->m_layout.isNull() ){
            _each_layout->m_layout ->bindWindow( binder );

            _each_layout->m_layout->m_wnd = binder;
            _each_layout->m_layout->m_hasBound = !false;
          }
        }
      }()) {}
      */
    }

    void Layout::PrivateLayout::unbindWindow(){
      auto _iter = m_controllers.begin();
      for( ; _iter != m_controllers.end() ; [&](){
        auto &_ctrl_root = (*_iter++)->m_root;
        if( !_ctrl_root.isNull() ){
          _ctrl_root->onWindowBound();
        }

        auto _each_layout = _ctrl_root->m_centreLayout;
          if( !_each_layout.isNull() ){
            if( !_each_layout->m_layout.isNull() ){
              _each_layout->m_layout ->unbindWindow();

              _each_layout->m_layout->m_wnd = Nullptr;
              _each_layout->m_layout->m_hasBound = false;
            }
          }
      }()) {}

      m_hasBound = false;
    }

    void Layout::PrivateLayout::assignParent( Window *wnd ){
      assert( wnd != Nullptr );

      m_wnd = wnd;
      m_windowAsParent = !false;

      auto _layout = wnd->getCenterLayout();
      if( !_layout.isNull() 
        && !_layout->m_layout.isNull() ){
        if(  _layout->m_layout->m_hasBound ){
           _layout->m_layout->unbindWindow();
        }
      }    
        
    }
    //something wrong here
    void Layout::PrivateLayout::assignParent( Controller *controller ){
      assert( controller != Nullptr );

      m_contr = controller;
      m_windowAsParent = false;

      auto _layout = controller->getLayout();
      if( !_layout.isNull() 
        && !_layout->m_layout.isNull() ){
          if(  _layout->m_layout->m_hasBound ){

            if( m_hasBound ){
              unbindWindow();
            }

            bindWindow( _layout->m_layout->m_wnd );
          }  
      }
        
    }

  }
}