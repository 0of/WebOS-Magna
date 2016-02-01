#include "Button.h"

#include <exception>
#include <stdexcept>
#include <typeinfo>

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "render/LinearGradient.h"
using namespace Magna::Render;

#include "Controller_p.h"
#include "ButtonImplementor.h"

namespace Magna{
  namespace GUI{

    Button::Button()
      :Controller(){

      if( !m_root.isNull() ){
        m_root->_size_set( IntegerSize( 60, 40 ) );

        const auto &_rect = m_root->_rect_get();
        const auto &_topLeft = _rect.getTopLeftCoord();
        const auto &_bottomRight = _rect.getBottomRightCoord();

        LinearGradient *linearGradient = new LinearGradient ( _topLeft.getX()
          , _topLeft.getY()
          , _topLeft.getX()
          , _bottomRight.getY() );
        linearGradient->setColorAt( Color( 255,255,255 ), 0.0 );
        linearGradient->setColorAt( Color( 128,128,128 ), 1.0 );
        FillBrush _gradientBrush( linearGradient );

        m_root->_brush_init( _gradientBrush );
        //m_root->_font_init( Font(L"Times", 13 ) );
        m_root->_impl_init( SharedPtr<ControllerImplementor>( new ButtonImplementor( *this ) ) );
      }
    }

    Button::Button( const String& text )
      :Controller(){
      if( !m_root.isNull() ){
        m_root->_size_set( IntegerSize( 60, 40 ) );
        ButtonImplementor *_impl = new ButtonImplementor( *this );
        _impl->m_text = text;

        m_root->_impl_init( SharedPtr<ControllerImplementor>( _impl ) );
      }

    }

    Button::Button( const Image& img )
      :Controller(){
        if( !m_root.isNull() ){
          m_root->_size_set( IntegerSize( 60, 40 ) );
          ButtonImplementor *_impl = new ButtonImplementor( *this );
          _impl->m_icon = img;

          m_root->_impl_init( SharedPtr<ControllerImplementor>( _impl ) );
        }

    }

    Button::~Button(){

    }

    void Button::setFontBrush( const FillBrush& brush ){
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor & _button_impl = dynamic_cast< ButtonImplementor &>(*_impl );
            _button_impl.m_fontBrush = brush;
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      catch( const std::bad_cast& bad_ex ){
        bad_ex.what();
      }
    }

    //for temp, use dynamic cast
    //later, will bring implementor_cast
    //and controller type id
    bool Button::isPressedDown() const{
      bool _is_pressed = false;
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor & _button_impl = dynamic_cast< ButtonImplementor &>(*_impl );
            _is_pressed = _button_impl.m_isPressed;
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
      return _is_pressed;
    }

    bool Button::isCheckable() const{
      bool _is_checkable = false;
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor & _button_impl = dynamic_cast< ButtonImplementor &>(*_impl );
            _is_checkable = _button_impl.m_checkable;
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
      return _is_checkable;
    }

    bool Button::isToggleable() const{
      bool _is_toggleable = false;
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor & _button_impl = dynamic_cast< ButtonImplementor &>(*_impl );
            _is_toggleable = _button_impl.m_toggleable;
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
      return _is_toggleable;
    }

    bool Button::isChecked() const{
      bool _is_checked = false;
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor & _button_impl = dynamic_cast< ButtonImplementor &>(*_impl );
            _is_checked = _button_impl.m_checked;
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
      return _is_checked;
    }

    bool Button::isToggled() const{
      bool _is_toggled = false;
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor & _button_impl = dynamic_cast< ButtonImplementor &>(*_impl );
            _is_toggled = _button_impl.m_toggled;
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
      return _is_toggled;
    }

    void Button::setCheckable( bool checkable ){
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor & _button_impl = dynamic_cast< ButtonImplementor &>(*_impl );
            _button_impl.m_checkable = checkable;
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

    void Button::setToggleable( bool toggleable ){
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor & _button_impl = dynamic_cast< ButtonImplementor &>(*_impl );
            _button_impl.m_toggleable = toggleable;

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

    void Button::setChecked( bool checked ){
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor & _button_impl = dynamic_cast< ButtonImplementor &>(*_impl );
            if( _button_impl.m_checked != checked){
              _button_impl.m_checked = checked;

              OnceChecked.triggers( checked );
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

    void Button::setToggled( bool toggled ){
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor * _button_impl = reinterpret_cast< ButtonImplementor *>( _impl.operator->() );

            if( _button_impl->m_toggleable ){

              if( _button_impl->m_toggled != toggled ){
                _button_impl->m_toggled = toggled;

                OnceToggled.triggers( toggled );


                if( toggled != false ){
                  _button_impl->m_bindingGroup->setButtonToggled( _button_impl->m_groupIndex);
                }
                else{
                  _button_impl->m_bindingGroup->setButtonUntoggled( _button_impl->m_groupIndex );
                }

                //update
                update();
              }

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

    void Button::setText( const String& text){
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor & _button_impl = dynamic_cast< ButtonImplementor &>(*_impl );
            _button_impl.m_text = text;

            _button_impl._remeasureText();
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

    String Button::getText() const{
      String  _ret_text;
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor & _button_impl = dynamic_cast< ButtonImplementor &>(*_impl );
            _ret_text = _button_impl.m_text;
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
      return _ret_text;
    }

    void Button::setData( uint32 data ){
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor & _button_impl = dynamic_cast< ButtonImplementor &>(*_impl );
            _button_impl.m_data = data;
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

    uint32 Button::getData(){
      uint32 data = 0;
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor * _button_impl = reinterpret_cast< ButtonImplementor *>(_impl.operator->() );
            data = _button_impl->m_data;
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
      return data;
    }

    void Button::setIcon(const Image& img){
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor & _button_impl = dynamic_cast< ButtonImplementor &>(*_impl );
            _button_impl.m_icon = img;
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

    void Button::setHoverIcon( const Image& img){
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor * _button_impl = reinterpret_cast< ButtonImplementor *>(_impl.operator->() );
              _button_impl->m_hoverIcon = img;
            _button_impl->m_hasHoverParaSet = !false;
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

    void Button::setPressedBrush( const FillBrush& fillBrush ){
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor * _button_impl = reinterpret_cast< ButtonImplementor *>(_impl.operator->() );
            _button_impl->m_pressedBrush = fillBrush;
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

    void Button::setHoverBrush( const FillBrush& fillBrush ){
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor * _button_impl = reinterpret_cast< ButtonImplementor *>(_impl.operator->() );
            _button_impl->m_hoveredBrush = fillBrush;
            if( !fillBrush.isNull() ){
              _button_impl->m_hasHoverParaSet = !false;
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
    }

    void Button::setPressedIcon( const Image& i){
      try{
        if( !m_root.isNull() ){
          auto  _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ButtonImplementor * _button_impl = reinterpret_cast< ButtonImplementor *>(_impl.operator->() );
            _button_impl->m_pressedIcon = i;
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

  }//namespace GUI
}//namespace Magna
