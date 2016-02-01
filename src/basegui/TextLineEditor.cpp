#include "TextLineEditor.h"

#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include <typeinfo>

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "Controller_p.h"
#include "TextLineEditorImplementor.h"

namespace Magna{
  namespace GUI{
    
    TextLineEditor::TextLineEditor()
      :Controller(){

      if( !m_root.isNull() ){
        m_root->_size_set( IntegerSize( 120, 40 ) );
        m_root->_border_init( GUIConstants::BorderStyle_Solid, 2,  Color() );

        TextLineEditorImplementor *impl = new TextLineEditorImplementor( *this );
        m_root->_impl_init( SharedPtr<ControllerImplementor>( impl ) );
      }

    }

    TextLineEditor::TextLineEditor( const String& hintText )
      :Controller(){

      if( !m_root.isNull() ){
        m_root->_size_set( IntegerSize( 80, 30 ) );
        m_root->_border_init( GUIConstants::BorderStyle_Solid, 2,  Color() );

        TextLineEditorImplementor *impl = new TextLineEditorImplementor( *this, hintText );
        m_root->_impl_init( SharedPtr<ControllerImplementor>( impl ) );
      }
    }


    TextLineEditor::TextLineEditor( const String& hintText, const String& text )
      :Controller(){

      if( !m_root.isNull() ){
        m_root->_size_set( IntegerSize( 80, 30 ) );
        m_root->_border_init( GUIConstants::BorderStyle_Solid, 2,  Color() );

        TextLineEditorImplementor *impl = new TextLineEditorImplementor( *this, hintText, text );
        m_root->_impl_init( SharedPtr<ControllerImplementor>( impl ) );
      }

    }

    TextLineEditor::~TextLineEditor(){

    }

    void TextLineEditor::setHintText( const String& hint ){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            TextLineEditorImplementor & _edit_impl = dynamic_cast< TextLineEditorImplementor &>(*_impl );
            _edit_impl.m_hintText;

            _edit_impl._measureHintText();
            if( !isFocussed() ){              
              update();
            }

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

    void TextLineEditor::setText( const String& text ){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            TextLineEditorImplementor & _edit_impl = dynamic_cast< TextLineEditorImplementor &>( *_impl );
            _edit_impl.m_text = text;

            _edit_impl._remeasureText();
            if( isFocussed() ){              
              update();
            }

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

    void TextLineEditor::clearText(){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            TextLineEditorImplementor & _edit_impl = dynamic_cast< TextLineEditorImplementor &>( *_impl );
            _edit_impl.m_text.clear();

            _edit_impl.m_textBoundingRect = IntegerRectRegion();
            if( isFocussed() ){              
              update();
            }

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

  }//namespace GUI
}//namespace Magna
