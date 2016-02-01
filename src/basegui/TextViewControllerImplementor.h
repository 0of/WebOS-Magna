#ifndef TEXTVIEWCONTROLLERIMPLEMENTOR_H
#define TEXTVIEWCONTROLLERIMPLEMENTOR_H

#include <vector>

#include "basedef/RectRegion.h"
#include "basedef/String.h"
using namespace Magna::Core;

#include "ControllerImplementor.h"

namespace Magna{
  namespace GUI{
    class TextViewController;
    class TextViewControllerImplementor : public ControllerImplementor{
    public:
      TextViewControllerImplementor( TextViewController & binding );
      explicit TextViewControllerImplementor( TextViewController & binding, const String& text );
      virtual ~TextViewControllerImplementor();

      __Override_Methods public:
      void rendering( RenderingEventArgs& eventArgs );

    public:
      void _remeasureText();

    public:

      String m_text;

      IntegerRectRegion m_textBoundingRect;
      uint32 m_avgHeight;
      uint32 m_vtextSpacing;

      TextViewController &m_binding;

      std::vector<String> m_lineBreakStrings;
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  TEXTVIEWCONTROLLERIMPLEMENTOR_H  */