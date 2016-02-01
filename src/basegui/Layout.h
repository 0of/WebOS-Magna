#ifndef LAYOUT_H
#define LAYOUT_H

#include "basegui_lib.h"
#include "basedef/SystemDef.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include "render/DyadCoordinateMapper.h"

/*  Magna GUI  */
#include "Controller.h"
#include "Window.h"

#include <vector>

namespace Magna{
  namespace GUI{
    class Controller;
    class Window;

    __Abstracted class BASEGUI_LIB_EXPORT Layout : public __Realizes DyadCoordinateMapper{
      friend class Controller;
      friend class ScrollableController;
      friend class Window;
      __Constants public:
        enum LayoutType{
          LayoutType_Absolute,
          LayoutType_Table
        };
      __Constructor_Destructor public:
        virtual ~Layout() ;
      __Constructor_Destructor protected:
        Layout();

      __Implemented_Methods public:
        virtual IntegerDyadCoordinate toCoordOnScreen( const IntegerDyadCoordinate& coord ) const ;
        virtual IntegerDyadCoordinate fromCoordOnScreen( const IntegerDyadCoordinate& coord ) const ;

        virtual IntegerDyadCoordinate toCoordUnderParentCoordSystem( const IntegerDyadCoordinate& coord ) const;
        virtual IntegerDyadCoordinate fromCoordUnderParentCoordSystem( const IntegerDyadCoordinate& coord ) const ;

        virtual IntegerDyadCoordinate toCoordOnManipulateDevice( const IntegerDyadCoordinate& coord ) const ;
        virtual IntegerDyadCoordinate fromCoordOnManipulateDevice( const IntegerDyadCoordinate& coord ) const ;

      protected:
        void addChildController( const SharedPtr<Controller>& controller ) ;

      __Getter public:
        inline LayoutType getType() const{ return m_type ; }

        Window * getAttachedWindow() const;
        bool getParent( Window *& _out_wind ) const;
        bool getParent( Controller *&_out_ctrl ) const;

        bool isWindowParent() const;

        IntegerRectRegion getMeasuredRect() const;
        IntegerDyadCoordinate getLayoutOffset() const;

      public:
        virtual SharedPtr<Controller> getControllerAt( const IntegerDyadCoordinate& pos ) const ;
        std::vector<SharedPtr<Controller> > getChildControllers() const;

        void removeChildController( const SharedPtr<Controller>& controller ) ;

        void setLayoutOffset( const IntegerDyadCoordinate& );
        void setLayoutOffset( sint32, sint32 );

      protected:
        virtual void measure() ;
        virtual void deploy() ;

      __Data_Field  protected:
        class PrivateLayout;
        friend class PrivateLayout;
        SharedPtr<PrivateLayout> m_layout;
        LayoutType m_type;
    };

  }//namespace GUI
}  //namespace Magna
#endif  /*  LAYOUT_H  */
