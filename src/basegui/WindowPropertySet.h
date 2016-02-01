#ifndef WINDOWPROPERTYSET_H
#define WINDOWPROPERTYSET_H

#include "basedef/RectRegion.h"
#include "basedef/Size.h"
#include "basedef/Trigger.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include "render/RenderManager.h"
#include "render/RenderManager2D.h"
using namespace Magna::Render;

#include "StateSwitcher.h"
#include "WindowFrameController.h"

#include "GUIEventIndexer.h"
#include "CommonEventArgs.h"
#include "MouseEventArgs.h"
#include "KeyEventArgs.h"
#include "MouseWheelEventArgs.h"

#include "Layout.h"
#include "Window.h"

namespace Magna{  
   namespace GUI{

     struct WindowPropertySet{
       __Constants
         enum StateValue{
           State_Show = 0x00000001,
           State_Focus = 0x00000002,
           State_Enabled  =  0x00000004
       };
       WindowPropertySet()
         : m_title( L"New Window")
         ,m_icon()
         ,m_scaledIcon()
         ,m_focusController( Nullptr )
         ,m_windowAttributes( 0 )
        ,m_frameController()
        ,m_frameLayout()
        ,m_centreLayout()
        ,m_borderWidth(1)
        ,m_borderStyle( GUIConstants::BorderStyle_Solid )
        ,m_borderColor( Color( 0, 0, 0 ) ){}
      ~WindowPropertySet(){
        
      }
       String m_title;
       Image m_icon;
       Image m_scaledIcon;

       GUIConstants::BorderStyle m_borderStyle;
       uint32 m_borderWidth;
       Color m_borderColor;

       SharedPtr<Layout> m_centreLayout;
       SharedPtr<Layout> m_frameLayout;
       SharedPtr<WindowFrameController> m_frameController;

       Controller *m_focusController;

       FillBrush m_backgroundBrush;

       SpinMutex m_mutex;

       IntegerRectRegion m_boundingRect;

       Window::WindowAttributes m_windowAttributes;

       Window::WindowDelegatorCollection m_delegatorCollection;
       ImplStateSwitcher<StateValue, MultiplexedSwitcherMode> m_stateSwitcher;
     };

   }//GUI
}//Magna
#endif  /*  WINDOWPROPERTYSET_H  */