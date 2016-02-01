#include "TextViewController.h"

#include <clocale>
#include <string>

#include "TextViewControllerImplementor.h"

#include "Controller_p.h"
#include "Window_p.h"
#include "WindowAccessor.h"
#include "ScrollableController_p.h"

namespace Magna{
  namespace GUI{
    

    TextViewController::TextViewController()
      :ScrollableController(){

      TextViewControllerImplementor *impl = new TextViewControllerImplementor( *this );
      m_root->_impl_init( impl );
    }

    TextViewController::TextViewController( const String& t)
      :ScrollableController(){

      TextViewControllerImplementor *impl = new TextViewControllerImplementor( *this );
      impl->m_text = t;
      impl->_remeasureText();

      //calculate the size
      IntegerSize _size( impl->m_textBoundingRect.getWidth() , (impl->m_avgHeight) * (impl->m_lineBreakStrings.size() ) );

      m_sroot->m_scrollSize = _size ;

      m_root->_impl_init( impl );
    }

    TextViewController::TextViewController( std::wifstream& wif)
      :ScrollableController(){

      TextViewControllerImplementor *impl = new TextViewControllerImplementor( *this );  
        
      if( wif.is_open() ){
        String _buffer ;
        while( !wif.eof() && wif.good() ){
          std::getline( wif, _buffer );
          impl->m_text.append( _buffer ).append( L"\\n" ) ;
        }

        wif.close();
      }
      //calculate the size
      IntegerSize _size( impl->m_textBoundingRect.getWidth() , (impl->m_avgHeight) * (impl->m_lineBreakStrings.size() ) );

      m_sroot->m_scrollSize = _size ;

      m_root->_impl_init( impl );
    }

    TextViewController::~TextViewController(){

    }

    String TextViewController::toProtogenousInitString( const String& start 
      , const String& end , const String& element ) const {

        OutStringStream _outer ;

        _outer << start
          << L"element.cols=20;"
          << L"element.style.width='" << getWidth() << L"px';"
          << L"element.style.height='" << getHeight() << L"px';";
        //if( !m_text.empty() ){
        //  _outer << L"element.innerHTML=\""
        //    << m_text << L"\";";      
        //}  

        _outer<< end;
        return _outer.str();
    }

    void TextViewController::setText( const String& str){
      //m_text = str;

      if( !m_root.isNull() ){
        auto *_parent_layout = getParentLayout();
        if( _parent_layout != Nullptr ){
          auto *_attached_wnd = _parent_layout->getAttachedWindow();
          if( _attached_wnd != Nullptr ){
            auto &&_wnd_root = WindowAccessor::getRoot( _attached_wnd );

            if( _wnd_root != Nullptr ){

              //get implementor
              auto &&_impl = m_root->_impl_get();
              if( !_impl.isNull() ){
                auto *_impl_ = reinterpret_cast<TextViewControllerImplementor *>(_impl.operator->());
                _impl_->m_text = str;
                _impl_->_remeasureText();

                //calculate the size
                IntegerSize _size( _impl_->m_textBoundingRect.getWidth() , (_impl_->m_avgHeight) * (_impl_->m_lineBreakStrings.size()) );

                //not running
                setScrollSize( _size );
              }
            }
          }
        }
      }
        
      /*
      if( !m_root.isNull() && m_root->m_int_runtimeId != 0 ){
        auto *_parent_layout = getParentLayout();
        if( _parent_layout != Nullptr ){
          auto *_attached_wnd = _parent_layout->getAttachedWindow();
          if( _attached_wnd != Nullptr ){
            auto &_wnd_root = WindowAccessor::getRoot( _attached_wnd );

            if( _wnd_root != Nullptr ){
              //play script
              OutStringStream _outer ;
              _outer << L"var _e=document.getElementById("
                << m_elementId
                << L");_e.innerHTML=\"" 
                << m_text << L"\";";

              _wnd_root->m_requester->requestScriptEval( _outer.str() );
            }
          }
        }
      }  
      */
    }



    void TextViewController::loadFromFile( const String& filePath ){

      std::string _buff_str;
      if( !filePath.empty() ){
        std::ifstream _stream( filePath.toString(), std::ios::in );
        //std::wifstream _stream( filePath,std::ios::in );
        if( _stream.is_open() ){
          std::string _each_buff;
          _each_buff.reserve( 255 );
          while( !_stream.eof() && _stream.good() ){  
            std::getline( _stream, _each_buff );
            _buff_str.append( _each_buff );
            _buff_str.append( "\\n" ) ;
          }

          if( !m_root.isNull() ){
            auto &&_impl = m_root->_impl_get();
            if( !_impl.isNull() ){
              auto *_impl_ = reinterpret_cast<TextViewControllerImplementor *>(_impl.operator->());
              _impl_->m_text = String::fromString(_buff_str);
              _impl_->_remeasureText();

              IntegerSize _size( _impl_->m_textBoundingRect.getWidth() , (_impl_->m_avgHeight) * (_impl_->m_lineBreakStrings.size()) );
              setScrollSize( _size );
            }

            update();
            /*
            auto *_parent_layout = getParentLayout();
            if( _parent_layout != Nullptr ){
              auto *_attached_wnd = _parent_layout->getAttachedWindow();
              if( _attached_wnd != Nullptr ){
                auto &_wnd_root = WindowAccessor::getRoot( _attached_wnd );

                if( _wnd_root != Nullptr ){
                  //play script
                  OutStringStream _outer ;
                  _outer << L"var _e=document.getElementById("
                    << m_elementId
                    << L");_e.innerHTML=\"" 
                    << m_text << L"\";";

                  _wnd_root->m_requester->requestScriptEval( _outer.str() );
                  
                }
              }
              */
            }
          }  
        _stream.close();
      }
    }

  }//namespace GUI
}//namespace Magna
