#ifndef SCROLLABLECONTROLLER_H
#define SCROLLABLECONTROLLER_H

#include "basegui_lib.h"

#include "Controller.h"
#include "ScrollEventArgs.h"

namespace Magna{
  namespace GUI{
    
    class BASEGUI_LIB_EXPORT ScrollableController : public Controller{
      __Trigger public:
        TRIGGER_DEF(OnceScrolled, uint32 , uint32 )

      __Constants public:
        enum ScrollBarPolicy{
          ScrollBarPolicy_AlwaysShow,
          ScrollBarPolicy_AlwaysOff,
          ScrollBarPolicy_OnlyShowHorizontalBar,
          ScrollBarPolicy_OnlyShowVerticalBar
        };

      __Constructor_Destructor public:
        ScrollableController();
        virtual ~ScrollableController();

      __Implemented_Methods public:
        virtual String toElementString () const ;
        virtual String toStyleString() const ;

      public:
        void scrollTo( sint32 x, sint32 y );
        void scrollToX( sint32 x );
        void scrollToY( sint32 y );

      __Getter public:
        IntegerSize getScrollSize() const;
        sint32 getScrollHeight() const;
        sint32 getScrollWidth() const;      

      __Setter public:
        void setScrollBarPolicy( ScrollBarPolicy );
        void setScrollSize( const IntegerSize& );
        virtual void setSize( const IntegerSize& );

      __Data_Field protected:
        class ScrollableControllerRoot;
        SharedPtr<ScrollableControllerRoot> m_sroot;
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  SCROLLABLECONTROLLER_H  */