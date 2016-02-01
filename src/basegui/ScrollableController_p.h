#ifndef SCROLLABLECONTROLLER_P_H
#define SCROLLABLECONTROLLER_P_H

#include "ScrollableController.h"
#include "Controller_p.h"

namespace Magna{
  namespace GUI{

    class ScrollableController::ScrollableControllerRoot : public Controller::ControllerRoot{

      __Constructor_Destructor public:
        ScrollableControllerRoot( ScrollableController & binding )
          :ControllerRoot( binding )
          ,m_scrollableController( binding )
          ,m_scrollX()
          ,m_scrollY()
          ,m_speed()
          ,m_policy( ScrollableController::ScrollBarPolicy_AlwaysShow )
          ,m_scrollSize(){

        }

      public:
        virtual void onLayoutMeasured();

        void scrolled( ScrollEventArgs& eventArgs );

      __Data_Field public:
        uint32 m_scrollX;
        uint32 m_scrollY;
        uint32 m_speed;

        ScrollableController::ScrollBarPolicy m_policy;
        IntegerSize m_scrollSize;

        ScrollableController &m_scrollableController;
    };

  }//namespace GUI
}//namespace Magna

#endif