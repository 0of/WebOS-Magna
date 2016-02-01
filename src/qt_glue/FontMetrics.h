#ifndef FONTMETRICS_H
#define FONTMETRICS_H

#include "qt_glue_lib.h"

#include "basedef/BaseTypes.h"
#include "basedef/Size.h"
#include "basedef/String.h"
using namespace Magna::Core;

#include "render/Font.h"
using namespace Magna::Render;

namespace Magna{
  namespace Glue{
    
    class QT_GLUE_LIB_EXPORT FontMetrics{
      __Constructor_Destructor public:
        FontMetrics();
        explicit FontMetrics( const Font& f );
        explicit FontMetrics( const String& text );
        explicit FontMetrics( const String& text, const Font& f );
        ~FontMetrics();

      __Setter public:
        void setMetricsText( const String& text );
        void setMetricsFont( const Font& f );

      __Getter public:
        const String& getMetricsText() const;
        const Font& getMetricsFont() const;

      public:
        sint32 measureHeight() const;
        sint32 measureWidth() const;
        IntegerSize measureSize() const;

      public:
        static IntegerSize measureSize( const String& text, const Font& f  );

      __Data_Field private:
      
        String m_text;
        Font m_font;
    };

  }//namespace Glue
}//namespace Magna

#endif  /*  FONTMETRICS_H  */