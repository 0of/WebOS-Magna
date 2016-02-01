#ifndef WINDOW_H
#define WINDOW_H

#include "basegui_lib.h"

#include "basedef/Trigger.h"
using namespace Magna::Core;

#include "render/ManipulateDevice.h"
using namespace Magna::Render;

#include "Layout.h"
#include "Controller.h"

#include "GUIDef.h"
#include "GUIConstants.h"

#include "CommonEventArgs.h"
#include "MovedEventArgs.h"
#include "ResizedEventArgs.h"

#include "EventDelegator.h"
#include "DelegatorCollection.h"

/*  STL  */
#include <vector>

namespace Magna{
  namespace GUI{
    __Abstracted class Layout;
    class Controller;
    class WindowFrameController;
    class BASEGUI_LIB_EXPORT Window : public ManipulateDevice{

      friend class Layout;
      friend class Controller;
      friend class ScrollableController;
      friend class WindowAccessor;

    __Trigger public:
      TRIGGER_DEF(OnceClosed)
      TRIGGER_DEF(OnceHidden)
      TRIGGER_DEF(OnceShown)

    __Definitions
      typedef uint32 WindowAttributes;

    __Constants public:
      enum WindowAttribute{
        WindowAttribute_SizeFixed = 0x00000001,
        WindowAttribute_PositionFixed = 0x00000002,
        WindowAttribute_NoBackground = 0x00000004,
        WindowAttribute_NoWindowFrame = 0x00000008,
        WindowAttribute_NoBorder = 0x00000010,
      };

    __Constructor_Destructor public:
      Window() ;
      Window( WindowAttributes init_attr ) ;
      virtual ~Window();

      class  WindowDelegatorCollection : public DelegatorCollection{
        __Constructor_Destructor public:
          enum {
            DelegatorCollectionType_Window = 1
          };
          WindowDelegatorCollection();
          WindowDelegatorCollection( const WindowDelegatorCollection& );
          ~WindowDelegatorCollection();

          WindowDelegatorCollection& operator = ( const WindowDelegatorCollection& );

        __Data_Field public:
          Delegator<Window, ShowEventArgs> onShow;
          Delegator<Window, CloseEventArgs> onClose;
          Delegator<Window, HideEventArgs> onHide;
          Delegator<Window, MovedEventArgs> onMoved;
          Delegator<Window, ResizedEventArgs> onResized;
      };


    __Setter public:
      void setWindowAttribute( WindowAttribute attr, bool on = true );
      void turnOnWindowAttributes( WindowAttributes attrs );

      void setWindowTitle( const String& );
      void setWindowIcon( const Image& );

    __Getter public:
      String getWindowTitle() const;
      Image getWindowIcon() const;

      SharedPtr<Layout> getCenterLayout() const;

      std::vector<SharedPtr<Controller> > getControllers() const;

      WindowDelegatorCollection & getWindowDelegatorCollection();
      const WindowDelegatorCollection & getWindowDelegatorCollection() const;

      void addDelegatorCollection( const DelegatorCollection& collection );

    public:
      //window style
      void setBackgroundFillBrush( const FillBrush& brush );
      void setBorderStyle( GUIConstants::BorderStyle );
      void setBorderWidth( uint32 );
      void setBorderColor( const Color& color );
      //animations

      void setCenterLayout( Layout *Layout );
      void setWindowFrame( WindowFrameController *frameController );

      void update();
      void close();

      void setPos( const IntegerDyadCoordinate& coord );
      void setPos( sint32 x, sint32 y );
      void setSize( const IntegerSize& size );
      void setSize( uint32 w, uint32 h );

      void setVisible( bool );
      void setFocus( bool );

      void setRectRegion( const IntegerRectRegion& rect );

      IntegerSize getSize() const;
      IntegerRectRegion getBoundingRectRegion() const;
      IntegerDyadCoordinate getPos() const;
      IntegerDyadCoordinate getContentPos() const;

      sint32 getWidth() const;
      sint32 getHeight() const;

      bool isVisible() const;
      bool isHidden() const;

      bool isFocused() const;

      bool isRunning() const;

    public:
      class WindowRoot;
      friend class WindowRoot;

    protected:
      SharedPtr<WindowRoot> m_wndRoot;

    };
  }//namespace GUI
}  //namespace Magna

#endif  /*  WINDOW_H  */
