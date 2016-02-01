#ifndef CONTROLLERIMPLEMENTOR_H
#define CONTROLLERIMPLEMENTOR_H

#include "basegui_lib.h"

#include "MouseEventArgs.h"
#include "MouseWheelEventArgs.h"
#include "KeyEventArgs.h"
#include "CommonEventArgs.h"
#include "ResizedEventArgs.h"
#include "MovedEventArgs.h"
#include "RenderEventArgs.h"
#include "HoverEventArgs.h"

namespace Magna{
   namespace GUI{

     class BASEGUI_LIB_EXPORT ControllerImplementor{
      public:
         ControllerImplementor() {}
         virtual~ControllerImplementor() {}
       public:
         virtual void mousePressed( MouseEventArgs& event ){}
         virtual void mousePressingMoved( MouseEventArgs& event ){}
         virtual void mouseReleased( MouseEventArgs& event ){}
         virtual void hoverIn( HoverEventArgs& event ){}
         virtual void hovered( HoverEventArgs& event ){}
         virtual void hoverOut( HoverEventArgs& event ){}
         virtual void mouseWheelUp( MouseWheelEventArgs& event ){}
         virtual void mouseWheelDown( MouseWheelEventArgs& event ){}
         virtual void mouseClicked( MouseEventArgs& event ){}
         virtual void mouseDoubleClicked( MouseEventArgs& event ){}

         virtual void keyPressed( KeyEventArgs& eventArgs ){}
         virtual void keyReleased(KeyEventArgs& eventArgs ){}

         virtual void rendering( RenderingEventArgs& eventArgs ){}

        virtual void focusIn( FocusEventArgs&eventArgs ){}
        virtual void focusOut( FocusEventArgs&eventArgs ){}

        virtual void resized( ResizedEventArgs&eventArgs ){}
        virtual void moved( MovedEventArgs&eventArgs ){}
      };

   }//GUI
}//Magna

#endif  /*  CONTROLLERIMPLEMENTOR_H  */
