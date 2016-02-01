#include "Label.h"

#include <typeinfo>

#include "Controller_p.h"
#include "LabelImplementor.h"

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

namespace Magna{
  namespace GUI{
    
    Label::Label()
      :Controller(){

      if( !m_root.isNull() ){
        m_root->_size_set( IntegerSize( 40, 30 ) );
        m_root->_font_init( Font(L"Times", 10 ) );
        
        LabelImplementor *_impl = new LabelImplementor( *this );
        m_root->_impl_init( SharedPtr<ControllerImplementor>( _impl ) );
      }    
    }

    Label::Label( const String& text )
      :Controller(){

      if( !m_root.isNull() ){

        String _verified_text = text;
        String _replaced_char = L"\\";
        size_t pos = 0;
        while(true){
          pos = text.find(_replaced_char, pos);
          if (pos != String::npos) {
            _verified_text.replace(pos, _replaced_char.size(), L"\\\\" );
            pos += _replaced_char.size();
          }
          else{
            break;
          }          
        } 

        m_root->_size_set( IntegerSize( 40, 30 ) );
        m_root->_font_init( Font(L"Times", 10 ) );

        LabelImplementor *_impl = new LabelImplementor( *this, _verified_text, TextRenderContants::TextAlignment_Left | TextRenderContants::TextAlignment_Top );
        m_root->_impl_init( SharedPtr<ControllerImplementor>( _impl ) );

      }    
    }

    Label::Label( const String& text,  TextAlignment alig)
      :Controller(){

      if( !m_root.isNull() ){

        String _verified_text = text;
        String _replaced_char = L"\\";
        size_t pos = 0;
        while(true){
          pos = text.find(_replaced_char, pos);
          if (pos != String::npos) {
            _verified_text.replace(pos, _replaced_char.size(), L"\\\\" );
            pos += _replaced_char.size();
          }
          else{
            break;
          }          
        } 

        m_root->_size_set( IntegerSize( 40, 30 ) );
        m_root->_font_init( Font(L"Times", 10 ) );

        LabelImplementor *_impl = new LabelImplementor( *this, _verified_text, alig );
        m_root->_impl_init( SharedPtr<ControllerImplementor>( _impl ) );

      }    
    }

    Label::~Label(){

    }

    void Label::setTextFillBrush( const FillBrush& b){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            LabelImplementor * _label_impl = reinterpret_cast< LabelImplementor *>(_impl.operator->() );
            //invalid characters replace
            _label_impl->m_textFillBrush = b;

            update();
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
    }

    void Label::setTextEffect( const SharedPtr<AppearanceEffect>& effect){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            LabelImplementor * _label_impl = reinterpret_cast< LabelImplementor *>(_impl.operator->() );
            //invalid characters replace
            _label_impl->m_effect = effect;

            update();
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
    }

    void Label::setTextAlignment( TextAlignment alignment ){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            LabelImplementor * _label_impl = reinterpret_cast< LabelImplementor *>(_impl.operator->() );
            //invalid characters replace
            _label_impl->m_alignment = alignment;

            update();
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
    }

    void Label::setVerticalTextSpacing( const uint32& v){
      assert( v <= 256 );
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            LabelImplementor & _label_impl = dynamic_cast< LabelImplementor &>(*_impl );
            //invalid characters replace

            _label_impl.m_vtextSpacing = v;
          
            update();
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      catch( const std::bad_cast& _ex ){
        _ex.what();
      }
    }

    void Label::setText( const String& text ){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            LabelImplementor & _label_impl = dynamic_cast< LabelImplementor &>(*_impl );
            //invalid characters replace

            String _verified_text = text;
            String _replaced_char = L"\\";
            size_t pos = 0;
            while(true){
              pos = text.find(_replaced_char, pos);
              if (pos != String::npos) {
                _verified_text.replace(pos, _replaced_char.size(), L"\\\\" );
                pos += _replaced_char.size();
              }
              else{
                break;
              }          
            } 

            _label_impl.m_text = _verified_text;

            _label_impl._remeasureText();
            //update
            update();
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      catch( const std::bad_cast& _ex ){
        _ex.what();
      }
    }

    String Label::getText() const{
      String _ret_str;
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            LabelImplementor & _label_impl = dynamic_cast< LabelImplementor &>(*_impl );
            _ret_str = _label_impl.m_text ;
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      catch( const std::bad_cast& _ex ){
        _ex.what();
      }
      return _ret_str;
    }

  }//namespace GUI
}//namespace Magna
