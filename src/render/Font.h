#ifndef FONT_H
#define FONT_H
/*
 * This file is part of core library of Magna framework
 * 
 * Copyright (c) 2013 by Magnus
 */
#ifdef _MSC_VER
#pragma warning(disable:4150)
#endif

#include "render_lib.h"

#include <cstdlib>
#include <cwchar>
#include <locale>

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/SharedPtr.h"
#include "basedef/String.h"
using namespace Magna::Core;

#include "Drawer.h"

namespace Magna{
  namespace Render{

    /*!    \brief
        The font defines the drawing style of text. \n×ÖÌå
     */
    /*!    \details
     *  
     *    A font has such properties:family, weight, style and pixel size.
     *    You can initialize one font with default constructor and also can 
     *    initialize with those properties which are listed above.
     *    
     *    \li Font family defines the family series of font. It can be set as a String
     *    parameter by calling setFontFamily(). The default family is Arial.
     *    
     *    \li Font weight value determines whether the text slim or bold and set with 
     *    setFontWeight(). Either set the FontWeight as normal way or put customized integer value
     *    which shall not higher than 1000 or lower than 0.
     *    
     *    \li Font style can be set by setFontStyle and its value should be 
     *    normal , italic, or oblique.
     *    
     *    \li Text size can use pixel as measuring unit. So you can set 
     *    font size with pixel value by calling setFontSize().
     * 
     *    \author  Magnus
     *    \version   1.0.0.0
     *    \date      
     */
    class RENDER_LIB_EXPORT Font{
      friend class Drawer< DrawerEngine::DrawerEngine_Canvas2D >;
      __Constants public:
        enum FontTheme{
          FontTheme_Default = 0x0000,
          FontTheme_Customized = 0x8000
        };
        enum FontWeight{
          FontWeight_Normal = 400,
          FontWeight_Bold = 700,
          FontWeight_Bolder = 800,
          FontWeight_Lighter = 300
        };
        enum FontStyle{
          FontStyle_Normal = 0,
          FontStyle_Italic = 1,
          FontStyle_Oblique = 2
        };
      __Definitions
        typedef uint32 FontWeightValue;
        //"italic small-caps bold 12px arial
      __Constructor_Destructor public:
        Font();
        explicit Font( const String& font_family
          , uint32 font_size
          , FontWeightValue font_weight = FontWeight_Normal
          , FontStyle font_style = FontStyle_Normal );
        Font( const Font& font );
        ~Font();

      __Setter public:
        void setFontFamily( const String&family );
        void setFontWeight( FontWeightValue value );
        void setFontStyle( FontStyle style );
        void setFontSize( uint32 pixelSize );

        //set Point Size /pt/

      __Getter public:
        String getFontFamily() const;

        FontWeightValue getFontWeight() const;
        FontStyle getFontStyle() const;
        uint32 getFontSize() const;

        String toString() const;

      __Overloaded_Methods public:
        Font & operator = ( const Font & font );
        bool operator == ( const Font & font );
        bool operator != ( const Font & font );

      __Data_Field private:
        class PrivateData;
        SharedPtr<PrivateData> m_data;

    };

  }//namespace Render
}//namespace Magna
#endif  /*  FONT_H  */
