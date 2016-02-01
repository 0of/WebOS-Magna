#ifndef LABELIMPLEMENTOR_H
#define LABELIMPLEMENTOR_H

#include <vector>

#include "basedef/RectRegion.h"
using namespace Magna::Core;

#include "render/RenderContants.h"
#include "render/AppearanceEffect.h"
#include "render/ShadowAppearanceEffect.h"
#include "render/FillBrush.h"
using namespace Magna::Render;

#include "ControllerImplementor.h"

namespace Magna{
  namespace GUI{
    class Label;
    class LabelImplementor : public ControllerImplementor{
      public:
        LabelImplementor( Label & bindingLabel );
        explicit LabelImplementor( Label & bindingLabel, const String& text, TextAlignment align );
        virtual ~LabelImplementor();

      __Override_Methods public:
        void rendering( RenderingEventArgs& eventArgs );

      public:
        void _remeasureText();

      public:
        String m_text;
        IntegerRectRegion m_textBoundingRect;
        uint32 m_avgHeight;
        uint32 m_vtextSpacing;
        TextAlignment m_alignment;
        SharedPtr<AppearanceEffect> m_effect;
        FillBrush m_textFillBrush;

        Label &m_bindingLabel;

        std::vector<String> m_lineBreakStrings;
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  LABELIMPLEMENTOR_H  */