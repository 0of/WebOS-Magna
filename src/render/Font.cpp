#pragma warning( disable: 4101)

#include "Font.h"
#include "private/Font_p.h"

#include "inner/InnerPrivateDataNullPointerException.h"

using namespace Magna::Core;
using namespace Magna::Inner;


namespace Magna{
  namespace Render{
    Font::Font()
      :m_data( new PrivateData ){

    }

    Font::Font( const String& font_family
      , uint32 font_size
      , FontWeightValue font_weight
      , FontStyle font_style  )
      :m_data( new PrivateData(font_family, font_size, font_weight, font_style)){

    }

    Font::Font( const Font& font )
      :m_data( font.m_data ){

    }

    Font::~Font(){

    }

    void Font::setFontFamily( const String&family ){
      try{
        if( !m_data.isNull() ){
          size_t rawLen = (family.size() + 1);

          if( m_data->m_fontFamily != Nullptr ){
            delete [] m_data->m_fontFamily;
          }

          m_data->m_fontFamily = new unicode_char[ rawLen ];
          ::memcpy( m_data->m_fontFamily ,  family.c_str(), rawLen * sizeof( unicode_char ) );

          m_data->m_fontTheme = Font::FontTheme_Customized;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& ex ){
        //ex.what();
        //level
        abort();
      }
    }

    void Font::setFontWeight( FontWeightValue value ){
      assert( value < 1000 && value > 0 );
      try{
        if( !m_data.isNull() ){
          m_data->m_fontWeight = (value - (value % 100));

          m_data->m_fontTheme = Font::FontTheme_Customized;
        }
      }
      catch( const InnerPrivateDataNullPointerException& ex ){
        //ex.what();
        //level
        abort();
      }
    }

    void Font::setFontStyle( FontStyle style ){
      try{
        if( !m_data.isNull() ){
          m_data->m_fontStyle =style;

          m_data->m_fontTheme = Font::FontTheme_Customized;
        }
      }
      catch( const InnerPrivateDataNullPointerException& ex ){
        //ex.what();
        //level
        abort();
      }
    }

    void Font::setFontSize( uint32 pixelSize ){
      assert( pixelSize < 5120 );
      try{
        if( !m_data.isNull() ){
          m_data->m_fontPixelSize = pixelSize;

          m_data->m_fontTheme = Font::FontTheme_Customized;
        }
      }
      catch( const InnerPrivateDataNullPointerException& ex ){
        ex.what();
        //level
        abort();
      }
    }

    String Font::getFontFamily() const{
      String _ret_str;
      try{
        if( !m_data.isNull() && m_data->m_fontFamily != Nullptr ){
          _ret_str.append( m_data->m_fontFamily );
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }

      }
      catch( const InnerPrivateDataNullPointerException& ex ){
        //ex.what();
        //level
        abort();
      }
      return _ret_str;
    }

    Font::FontWeightValue Font::getFontWeight() const{
      Font::FontWeightValue _ret_weight_v = Font::FontWeight_Normal;
      try{
        if( !m_data.isNull() ){
          _ret_weight_v = m_data->m_fontWeight;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& ex ){
        //ex.what();
        //level
        abort();
      }
      return _ret_weight_v;
    }

    Font::FontStyle Font::getFontStyle() const{
      Font::FontStyle _ret_style = Font::FontStyle_Normal;
      try{
        if( !m_data.isNull() ){
          _ret_style = m_data->m_fontStyle;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& ex ){
        //ex.what();
        //level
        abort();
      }
      return _ret_style;
    }

    uint32 Font::getFontSize() const{
      uint32 _ret_size = 0;
      try{
        if( !m_data.isNull() ){
          _ret_size = m_data->m_fontPixelSize;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& ex ){
        //ex.what();
        //level
        abort();
      }
      return _ret_size;
    }

    Font & Font::operator = ( const Font & font ){
            m_data = font.m_data;
            return *this;
        }

    bool Font::operator == ( const Font & font ){
      bool _ret_equal = !false;
      try{
        if( !m_data.isNull() && !font.m_data.isNull() ){
          _ret_equal = ( m_data->m_fontTheme == font.m_data->m_fontTheme
                  && m_data->m_fontStyle == font.m_data->m_fontStyle
                  && m_data->m_fontWeight == font.m_data->m_fontWeight
                  && static_cast<uint32>(m_data->m_fontPixelSize * 10) == static_cast<uint32>(font.m_data->m_fontPixelSize * 10) );
          if( _ret_equal != false ){
            unicode_char *p_f = m_data->m_fontFamily;
            unicode_char *p_cmp = font.m_data->m_fontFamily;
            if(  Nullptr != p_f
              && Nullptr != p_cmp ){

              while( L'\0' != *p_f ){

                if( *p_f != *p_cmp || L'\0' ==*p_cmp ){
                  _ret_equal = false;
                  break;
                }
                ++p_f;
                ++p_cmp;
              }
            }
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& ex ){
        //ex.what();
        //level
        abort();
      }
      return _ret_equal;
    }
    bool Font::operator != ( const Font & font ){
      return !operator ==( font );
    }

    const unicode_char Font::PrivateData::shared_default_theme[]
      = L"'normal 10px arial'";

    const unicode_char *Font::PrivateData::shared_font_styles[]
      = { L"normal ", L"italic ", L"oblique "};

    String Font::toString() const{
      String _ret_str;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_fontTheme == Font::FontTheme_Default ){
            _ret_str = String(Font::PrivateData::shared_default_theme);
          }
          else{
            OutStringStream _outter ;
            if( m_data->m_fontStyle <= Font::FontStyle_Oblique
              && m_data->m_fontStyle >= Font::FontStyle_Normal ){
                _outter << L"'";
                _outter <<  Font::PrivateData::shared_font_styles[ m_data->m_fontStyle ]
                << m_data->m_fontWeight << L' ' ;

                _outter << m_data->m_fontPixelSize<< L"px";

                _outter << L' ' <<  m_data->m_fontFamily;
                _outter << L"'";
                _ret_str = _outter.str();
            }
            else{
              throw std::out_of_range( "Memory Correpted" );
            }
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& ex ){
        ex.what();
      }
      return _ret_str;
    }

    String Font::PrivateData::_toString() const{
      String _ret_str;
      try{
        if( m_fontTheme == Font::FontTheme_Default ){
          _ret_str = shared_default_theme;
        }
        else{
          OutStringStream _outter ;
          if( m_fontStyle <= Font::FontStyle_Oblique
            && m_fontStyle >= Font::FontStyle_Normal ){
              _outter << L"'";
              _outter << shared_font_styles[ m_fontStyle ]
              << m_fontWeight << L' ' ;

              _outter << m_fontPixelSize<< L"px";

              _outter << L' ' <<  m_fontFamily;
              _outter << L"'";
              _ret_str = _outter.str();
          }
          else{
            throw std::out_of_range( "Memory Correpted" );
          }
        }
      }
      catch( const std::exception& ex ){
        ex.what();
      }
      return _ret_str;
    }

  }//namespace Render
}//namespace Magna
