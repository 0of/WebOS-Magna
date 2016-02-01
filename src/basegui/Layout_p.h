#ifndef LAYOUT_P_H
#define LAYOUT_P_H

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/SpinMutex.h"
using namespace Magna::Core;

#include "Layout.h"

/*  STL  */
#include <vector>

namespace Magna{  
   namespace GUI{

     class Layout::PrivateLayout{
        
       __Constructor_Destructor public:
        PrivateLayout();
        ~PrivateLayout();

      public:
        void bindWindow( Window *binder );
        void unbindWindow();

        void assignParent( Window *wnd );
        void assignParent( Controller *controller );

      __Data_Field public:

        std::vector<SharedPtr<Controller> > m_controllers;
        IntegerRectRegion m_realRect;
        IntegerDyadCoordinate m_layoutOffset;

        SpinMutex m_mutex;

        //this value won't be Nullptr when binded
        //no matter parent is a window or a controller
        Window *m_wnd;
        
        Controller *m_contr;

        uint32 m_hasBound : 1;
        uint32 m_windowAsParent : 1;
        uint32 m_flags : 30;

     };
   }//GUI
}//Magna
#endif  /*  LAYOUT_P_H  */