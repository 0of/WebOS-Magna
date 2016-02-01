#ifndef FONT_P_H
#define FONT_P_H

#include "../Font.h"

#include "basedef/Comparer.h"
#include "basedef/String.h"
using namespace Magna::Core;

#include <cstring>
#include <cassert>

namespace Magna{
  namespace Render{
    class Font::PrivateData{
      __Constants public:
        static const unicode_char shared_default_theme[];
        static const unicode_char *shared_font_styles[];

      __Constructor_Destructor public:
        PrivateData() : m_fontTheme( Font::FontTheme_Default )
          ,m_fontWeight( Font::FontWeight_Normal )
          ,m_fontStyle( Font::FontStyle_Normal )
          ,m_fontPixelSize( 10 )
          ,m_fontFamily( Nullptr ){
          const unicode_char *defaultFamily = L"arial";
          size_t len = ::wcslen( defaultFamily );
          m_fontFamily = new unicode_char[ ++len ];
          ::memcpy( m_fontFamily, defaultFamily, len * sizeof( unicode_char ) );
        }

        PrivateData(const String& font_family
          , uint32 font_size
          , Font::FontWeightValue font_weight
          , Font::FontStyle font_style )
          :m_fontTheme( Font::FontTheme_Customized )
          ,m_fontWeight( font_weight - (font_weight % 100) )
          ,m_fontStyle( font_style )
          ,m_fontPixelSize( font_size )
          ,m_fontFamily( Nullptr ){

          assert(  font_size < 5120 );
          assert( font_weight < 1000 && font_weight > 0 );

          size_t rawLen = font_family.size();
          m_fontFamily = new unicode_char[ ++rawLen ];
          ::memcpy( m_fontFamily,  font_family.c_str(), rawLen * sizeof( unicode_char )  );
        }

      public:
        String _toString() const;

      __Data_Field public:
        Font::FontTheme m_fontTheme;
        Font::FontWeightValue m_fontWeight;
        Font::FontStyle m_fontStyle;
        uint32 m_fontPixelSize;
        unicode_char *m_fontFamily;

    };
  }//namespace Render
}//namespace Magna

#endif  /*  FONT_P_H  */
