#include "PopOutWindow.h"

#include "Window_p.h"
#include "GlobalPopOutWindowIntroducer.h"

#include "qt_glue/DesktopInfo.h"
using namespace Magna::Glue;

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

namespace Magna{
  namespace GUI{
    
    PopOutWindow::PopOutWindow()
      :Window(){

    }

    PopOutWindow::PopOutWindow( WindowAttributes a)
      :Window( a ){

    }

    PopOutWindow::PopOutWindow( const IntegerDyadCoordinate& global_coord )
      :Window(){

      m_wndRoot->_pos_set( global_coord );
    }

    PopOutWindow::~PopOutWindow(){

    }

    void PopOutWindow::popOutAt( const IntegerDyadCoordinate& global_coord ){
      try{
        if( !m_wndRoot.isNull() ){

          setVisible( !false );

          MovedEventArgs eventArg( m_wndRoot->_pos_get(), global_coord );
          m_wndRoot->windowMoved(eventArg);

          if( m_wndRoot->m_int_runtimeId == 0 ){
            auto &_introducer = GlobalPopOutWindowIntroducer::getGlobalPopOutWindowIntroducer();
            _introducer.introducePopOutWindow( m_wndRoot );
          }

        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
    }

    //void popOutCenter();
    void PopOutWindow::popOut(){
      try{
        if( !m_wndRoot.isNull() ){

          setVisible( !false );

          if( m_wndRoot->m_int_runtimeId == 0 ){
            auto &_introducer = GlobalPopOutWindowIntroducer::getGlobalPopOutWindowIntroducer();
            _introducer.introducePopOutWindow( m_wndRoot );
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
    }

    void PopOutWindow::popOutAtCenter(){    
      try{
        if( !m_wndRoot.isNull() ){

          setVisible( !false );

          const auto &_rect = DesktopInfo::getDesktopInfo().getMagnaOSScreenBoundingRect();
          const auto &_desktop_top_left = _rect.getTopLeftCoord();
          //calculate the left top coordinate
          const auto &_size = _rect.getSize();
          const auto &_wnd_size = m_wndRoot->_size_get();

          IntegerDyadCoordinate _top_left ( _desktop_top_left.getX() + (_size.getWidth() >> 1 ) - ( _wnd_size.getWidth() >> 1 ) 
            , _desktop_top_left.getY() +  (_size.getHeight() >> 1 ) - ( _wnd_size.getHeight() >> 1 )  );

          MovedEventArgs eventArg( m_wndRoot->_pos_get(), _top_left );
          m_wndRoot->windowMoved(eventArg);

          if( m_wndRoot->m_int_runtimeId == 0 ){
            auto &_introducer = GlobalPopOutWindowIntroducer::getGlobalPopOutWindowIntroducer();
            _introducer.introducePopOutWindow( m_wndRoot );
          }

        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
    }

    void PopOutWindow::popIn(){
      setVisible( false );
    }



  }//namespace GUI
}//namespace Magna
