#ifndef TOOLBARIMPLEMENTOR_H
#define TOOLBARIMPLEMENTOR_H

#include <vector>

#include "basedef/RectRegion.h"
using namespace Magna::Core;

#include "ControllerImplementor.h"
#include "ToolBarElement.h"

namespace Magna{
  namespace GUI{
    
    class ToolBar;
    class ToolBarImplementor : public ControllerImplementor{

      __Constructor_Destructor public:
        ToolBarImplementor( ToolBar& toolBar );
        virtual ~ToolBarImplementor();

      public:
        virtual void mousePressed( MouseEventArgs& event );
        virtual void mouseReleased( MouseEventArgs& event );

        virtual void rendering( RenderingEventArgs& eventArgs );

      public:
        void _updateRenderArguments();

      __Data_Field public:
        FillBrush m_pressedBrush;
        Pen m_borderPen;

        std::vector<ToolBarElement> m_elements;
        
        uint32 m_renderElementIndex : 30;
        uint32 m_renderElementHovered : 1;
        uint32 m_renderElementPressed : 1;
        

        IntegerRectRegion m_realRect;
        uint32 m_startRenderIndex;
        uint32 m_endRenderIndex;

        //contains text ,spacing & element size
        IntegerSize m_eachElementSize;

        //element side length 
        uint32 m_elmentSideLen;

        ToolBar& m_toolBar; 

        uint32 m_orientation;
        uint32 m_textHangingPolicy;

        uint32 m_spacing;
        uint32 m_logicalVerticalSpacing;
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  TOOLBARIMPLEMENTOR_H  */