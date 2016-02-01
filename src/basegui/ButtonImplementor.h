#ifndef BUTTONIMPLEMENTOR_H
#define BUTTONIMPLEMENTOR_H

#include "basedef/RectRegion.h"
using namespace Magna::Core;

#include "ControllerImplementor.h"
#include "ButtonGroup.h"

namespace Magna{
  namespace GUI{

    //### 
    //Cached Pixels
    //text or image will excess the bounding rect
    //webkit will recover the pixel of the difference region 
    //later will manipulate on the pixel by c++ code
    // 
    class Button;
    class ButtonImplementor : public ControllerImplementor{
      __Constructor_Destructor public:
        ButtonImplementor( Button &bindingButton );
        virtual ~ButtonImplementor();

      __Override_Methods public:

        virtual void mousePressed( MouseEventArgs& event );
        virtual void mouseReleased( MouseEventArgs& event );

        //virtual void mouseClicked( MouseEventArgs& event );
  
        virtual void rendering( RenderingEventArgs& eventArgs );
        virtual void hoverIn( HoverEventArgs& event );
        virtual void hoverOut( HoverEventArgs& event );

      public:
        void _remeasureText();

      __Data_Field public:
        uint16  m_checkable : 4;
        uint16 m_toggleable : 4;
        uint16  m_isReleased : 2;
        uint16  m_isHovered : 2;
        uint16 m_isPressed : 2;
        uint16 m_hasHoverParaSet : 2;
        //states
        bool m_checked;
        bool m_toggled;

        uint32 m_data;

        ButtonGroup *m_bindingGroup;
        uint32 m_groupIndex;


        String m_text;

        IntegerRectRegion m_textBoundingRect;

        Button &m_bindingButton;

        Image m_icon;
        Image m_hoverIcon;
        Image m_pressedIcon;

        //pressed Brush
        FillBrush m_pressedBrush;
        FillBrush m_hoveredBrush;

        FillBrush m_fontBrush;

        SpinMutex m_mutex;

    };
  }//namespace GUI
}//namespace Magna

#endif  /*  BUTTONIMPLEMENTOR_H  */