#ifndef TEXTLINEEDITORIMPLEMENTOR_H
#define TEXTLINEEDITORIMPLEMENTOR_H

#include "basedef/RectRegion.h"
using namespace Magna::Core;

#include "Controller_p.h"

#include "ControllerImplementor.h"
#include "TextLineEditor.h"

#include "qt_glue_img/Image.h"
using namespace Magna::Glue;

namespace Magna{
  namespace GUI{
    
    class TextLineEditorImplementor : public ControllerImplementor{
      __Constructor_Destructor public:
        explicit TextLineEditorImplementor( TextLineEditor &bindingEditor );
        explicit TextLineEditorImplementor( TextLineEditor &bindingEditor, const String hint );
        explicit TextLineEditorImplementor( TextLineEditor &bindingEditor, const String hint, const String text );
        virtual ~TextLineEditorImplementor();

      __Override_Methods public:
        virtual void mousePressed( MouseEventArgs& event );
        virtual void mouseReleased( MouseEventArgs& event );

        virtual void rendering( RenderingEventArgs& eventArgs );

      public:
        void _remeasureText();
        void _measureHintText();
        void _updateCursorPos();

      __Data_Field public:
        std::wstring m_text;
        String m_hintText;
        Image m_leadingIcon;
      
        IntegerDyadCoordinate m_startCoord;

        uint32 m_oldCurPos;
        uint32 m_currCurPos;
        uint32 m_curCoordLogicalX;

        IntegerRectRegion m_textBoundingRect;
        IntegerRectRegion m_hintTextBoundingRect;

        TextLineEditor &m_bindingEditor;
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  TEXTLINEEDITORIMPLEMENTOR_H  */
