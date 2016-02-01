#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "basegui_lib.h"

#include "basedef/Size.h"
#include "basedef/DyadCoordinate.h"
#include "basedef/Trigger.h"
using namespace Magna::Core;

#include "render/Pen.h"
#include "render/FillBrush.h"
#include "render/Font.h"
#include "render/RenderableElement.h"
using namespace Magna::Render;

#include "KeyEventArgs.h"
#include "CommonEventArgs.h"
#include "MouseWheelEventArgs.h"
#include "MouseEventArgs.h"
#include "RenderEventArgs.h"
#include "HoverEventArgs.h"

#include "GUIDef.h"
#include "Layout.h"
#include "LayoutAttribute.h"
#include "GUIConstants.h"

#include "DelegatorCollection.h"
#include "EventDelegator.h"

#include <vector>

namespace Magna{
  namespace GUI{
    __Abstracted class Layout;
    /*  Each controller represents a element
     *  normally, a canvas.
     */
    //deprecated
    //class BASEGUI_LIB_EXPORT Controller : Uncopyable{
    class BASEGUI_LIB_EXPORT Controller : protected RenderableElement{
        friend class Window;
        friend class Layout;
        friend class ControllerAccessor;
        friend class WindowFrameController;
        friend class ScrollableController;

      __Trigger public:
        TRIGGER_DEF(OnceShown)
        TRIGGER_DEF(OnceHidden)
        TRIGGER_DEF(OnceEnabled, bool )
        TRIGGER_DEF(OnceFocussed)
        TRIGGER_DEF(OnceResized, const IntegerSize&)
        TRIGGER_DEF(OnceMoved, const IntegerDyadCoordinate&)
        TRIGGER_DEF(OnceBoundingRectChanged, const IntegerRectRegion& )

      __Constructor_Destructor public:
        Controller();
        explicit Controller( const String& element_name ) ;
        explicit Controller( RenderManager *manager ) ;
        virtual ~Controller();

        class MouseEventDelegatorCollection : public DelegatorCollection{
          __Constants public:
            enum {
              DelegatorCollectionType_Mouse = 2
            };
          __Constructor_Destructor public:
            MouseEventDelegatorCollection();
            MouseEventDelegatorCollection( const MouseEventDelegatorCollection& );
            ~MouseEventDelegatorCollection();

            MouseEventDelegatorCollection& operator = ( const MouseEventDelegatorCollection& );

            Delegator<Controller, MouseEventArgs> onMousePressed;
            Delegator<Controller, MouseEventArgs> onMousePressingMoved;
            Delegator<Controller, MouseEventArgs> onMouseReleased;

            Delegator<Controller, MouseEventArgs> onMouseHoverIn;
            Delegator<Controller, MouseEventArgs> onMouseHovered;
            Delegator<Controller, MouseEventArgs> onMouseHoverOut;

            Delegator<Controller, MouseEventArgs> onMouseClicked;
            Delegator<Controller, MouseEventArgs> onMouseDoubleClicked;

            Delegator<Controller, MouseWheelEventArgs> onMouseWheelUp;
            Delegator<Controller, MouseWheelEventArgs> onMouseWheelDown;
        };

        class KeyEventDelegatorCollection : public DelegatorCollection{
          __Constants public:
            enum {
              DelegatorCollectionType_Key = 3
            };
        __Constructor_Destructor public:
          KeyEventDelegatorCollection();
          KeyEventDelegatorCollection( const KeyEventDelegatorCollection& );
          ~KeyEventDelegatorCollection();

          KeyEventDelegatorCollection& operator = ( const KeyEventDelegatorCollection& );

          __Data_Field public:
          Delegator<Controller, KeyEventArgs> onKeyPressed;
          Delegator<Controller, KeyEventArgs> onKeyReleased;
        };

        class RenderEventDelegatorCollection : public DelegatorCollection{
          __Constants public:
          enum {
            DelegatorCollectionType_Render = 4
          };
          __Constructor_Destructor public:
            RenderEventDelegatorCollection();
            RenderEventDelegatorCollection( const RenderEventDelegatorCollection& );
            ~RenderEventDelegatorCollection();

            RenderEventDelegatorCollection& operator = ( const RenderEventDelegatorCollection& );
          __Data_Field public:
          Delegator<Controller, RenderingEventArgs> onRendering;
        };
        /*
        class CommonEventDelegatorCollection : public DelegatorCollection{
          __Constants public:
          enum {
            DelegatorCollectionType_Render = 4
          };
          __Constructor_Destructor public:
            CommonEventDelegatorCollection();
            CommonEventDelegatorCollection( const CommonEventDelegatorCollection& );
            ~CommonEventDelegatorCollection();

            CommonEventDelegatorCollection& operator = ( const CommonEventDelegatorCollection& );

          __Data_Field public:
            Delegator<Controller, RenderingEventArgs> onRendering;
        };
        };    */

      __Checker public:
        bool isFocussed() const;
        bool isEnabled() const;
        bool isShown() const;
        bool isHidden() const;

        bool isEqualTo( Controller *cmper );

      __Getter public:
        //#deprecated

        IntegerSize getSize() const;
        sint32 getHeight() const;
        sint32 getWidth() const;
        IntegerRectRegion getBoundingRectRegion() const;
        IntegerDyadCoordinate getPos() const;

        std::vector<SharedPtr<Controller> > getControllers();

        SharedPtr<Layout> getLayout() const;

        Layout *getParentLayout() const;

        LayoutAttribute getLayoutAttribute() const;


        MouseEventDelegatorCollection & getMouseEventDelegatorCollection();
        const MouseEventDelegatorCollection & getMouseEventDelegatorCollection() const;

        KeyEventDelegatorCollection & getKeyEventDelegatorCollection();
        const KeyEventDelegatorCollection & getKeyEventDelegatorCollection() const;

        RenderEventDelegatorCollection & getRenderEventDelegatorCollection();
        const RenderEventDelegatorCollection & getRenderEventDelegatorCollection() const;

        void addDelegatorCollection( const DelegatorCollection& collection );

        //render property
        FillBrush getBrush();
        Pen getPen();
        Font getFont();
        float getOpacity();

      __Setter public:

        void setBorderStyle( GUIConstants::BorderStyle );
        void setBorderWidth( uint32 );
        void setBorderColor( const Color& color );

        void setLayout( const SharedPtr<Layout>& layout );
        void setLayoutAttribute( const LayoutAttribute& attr );

        void setPos( const IntegerDyadCoordinate& pos );
        virtual void setSize( const IntegerSize& size );
        //void setSize( sint32 width, sint32 height );
        void setBoundingRectRegion( const IntegerRectRegion& rect );

        //render property
        void setBrush( const FillBrush& brush );
        void setPen( const Pen& pen );
        void setFont( const Font& font );
        void setOpacity( float opacity );

        //state
        void setFocus();

      public:
        void show();
        void hide();
        void enable();
        void disable();

        void update();
        void update(const IntegerRectRegion&);
      __Override_Methods public:
        //////////////////////////////////////////////////////////////////////////
        //virtual void processMessage( const SharedPtr<Message>& );
        //virtual void processEvent( const SharedPtr<AbstractedEventArgs>& );

      __Override_Methods private:
        virtual String toStyleString() const ;
        virtual String toScriptString () const ;
        virtual String toElementString () const ;

        virtual String toProtogenousInitString( const String& start = L"function(element){"
          , const String& end = L"}", const String& element = L"element") const ;

        //not support
        virtual String toIntermediaCode () const { return  L""; };
        virtual void initFromString( const String& str ) {};

      __Overloaded_Methods public:
        //void * operator new ( size_t size );
        //void operator delete( void *pController );

      __Overloaded_Methods private:
         bool operator == ( const Controller& controller );
         bool operator != ( const Controller& controller );

      public:
        class ControllerRoot;
        friend class ControllerRoot;

      __Data_Field protected:
        SharedPtr<ControllerRoot> m_root;

      protected:
        explicit Controller( const SharedPtr<ControllerRoot>&  ) ;
    };
  }//namespace GUI
}  //namespace Magna

#endif  /*  CONTROLLER_H  */
