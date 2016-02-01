#include "WebFrameController.h"

#include "Controller_p.h"
#include "Window_p.h"

#include "WindowAccessor.h"

namespace Magna{
  namespace GUI{
    
    WebFrameController::WebFrameController()
      :Controller( L"\"iframe\"")
      ,m_currentURL(){

    }

    WebFrameController::WebFrameController( const String& url)
      :Controller( L"\"iframe\"")
      ,m_currentURL( url ){

    }

    WebFrameController::~WebFrameController(){

    }


    void WebFrameController::setAccessURL( const String& url){
      m_currentURL = url;

      if( !m_currentURL.empty() && !m_root.isNull() && m_root->m_int_runtimeId != 0 ){
        auto *_parent_layout = getParentLayout();
        if( _parent_layout != Nullptr ){
          auto *_attached_wnd = _parent_layout->getAttachedWindow();
          if( _attached_wnd != Nullptr ){
            auto &&_wnd_root = WindowAccessor::getRoot( _attached_wnd );

            if( _wnd_root != Nullptr ){
              //play script
              OutStringStream _outer ;
              _outer << L"var _e=document.getElementById("
                << m_elementId
                << L");_e.src=\"" 
                << m_currentURL << L"\";";

              _wnd_root->m_requester->requestScriptEval( _outer.str() );
            }
          }
        }
      }  

    }

    String WebFrameController::toProtogenousInitString( const String& start 
      , const String& end , const String& element ) const {

        OutStringStream _outer ;

        _outer << start
          << L"element.width=" << getWidth() << L";"
          << L"element.height=" << getHeight() << L";";
          if( !m_currentURL.empty() ){
            _outer << L"element.src=\""
              << m_currentURL << L"\";";      
          }  

        _outer<< end;
        return _outer.str();
    }


  }//namespace GUI
}//namespace Magna
