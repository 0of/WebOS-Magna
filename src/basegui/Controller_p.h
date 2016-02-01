#ifndef CONTROLLER_P_H
#define CONTROLLER_P_H

#include "basegui_lib.h"

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"
#include "basedef/CompilerTimeAssert.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include "ControllerImplementor.h"
#include "Controller.h"
#include "LayoutAttribute.h"
#include "StateSwitcher.h"

namespace Magna{
   namespace GUI{

    class BASEGUI_LIB_EXPORT Controller::ControllerRoot{
      friend class WindowRoot;
      friend class ControllerRoot;

      public:
        TRIGGER_DEF( OnceRun )

      __Constants public:
        enum StateValue{
          State_Show = 0x00000001,
          State_Focus = 0x00000002,
          State_Enabled = 0x00000004,
        };

        enum ControllerAttribute{
          Attribute_MouseHovered  =  0x00001000,
          Attribute_Protogenous = 0x00010000
        };
        typedef uint32 ControllerAttributes;

      __Data_Field public:
        uint64 m_int_runtimeId;

        Delegator<ControllerImplementor, const StateValue& > m_disposeStateChangedDelegator;

        //binding controller
        Controller & m_binding;
        SharedPtr<ControllerImplementor> m_impl;

        //render property
        FillBrush m_brush;
        Pen m_pen;
        Font m_font;
        float m_opacity;
        //

        //style
        GUIConstants::BorderStyle m_borderStyle;
        uint32 m_borderWidth;
        Color m_borderColor;

        ControllerAttributes m_attributes;
        ImplStateSwitcher<StateValue, MultiplexedSwitcherMode> m_stateSwitcher;

        SharedPtr<Layout> m_centreLayout;
        Layout * m_parentLayout;
        IntegerDyadCoordinate m_offsetCoord;
        IntegerRectRegion m_realBoundingRect;


        //delegator collections
        Controller::MouseEventDelegatorCollection *m_mouseEventDelegatorCollections;
        Controller::KeyEventDelegatorCollection m_keyEventDelegatorCollections;
        Controller::RenderEventDelegatorCollection m_renderEventDelegatorCollections;

        LayoutAttribute m_layoutAttr;

    __Constructor_Destructor public:
      explicit ControllerRoot( Controller &bindingController );
      virtual~ControllerRoot();

    //inner events
    public:
      virtual void onWindowBound();
      virtual void onControllerRun();
      virtual void onWindowUnbound();
      virtual void onControllerFinished();
      virtual void onLayoutMeasured();
      virtual void onLayoutDeployed();

    public:
      void _impl_init( const SharedPtr<ControllerImplementor> & impl );
      void _impl_set( const SharedPtr<ControllerImplementor> & impl );
      SharedPtr<ControllerImplementor> _impl_get() const;

      std::vector<SharedPtr<Controller::ControllerRoot> > _ctrls_get() const;
      String _createControllerNode() const;

      RenderManager * _render_manager_get() const;

      void _assignRuntimeId( const uint64& id);
      void _de_assignRuntimeId();
      const unicode_char * _runtime_elementId_get() const;

      void _dispatchEventMessage( AbstractedEventArgs &eventArgs );

      typedef Delegator<ControllerImplementor, const ControllerRoot::StateValue& > DisposeStateChangedDelegator;

      void _dispose_state_changed_delegator_init( const Delegator<ControllerImplementor, const StateValue& >& delegator );
      Delegator<ControllerImplementor, const StateValue& > _dispose_state_changed_delegator_get() const;

      void _offset_coord_update();
      //real rect
      void _real_rect_set( const IntegerRectRegion& rect );
      IntegerRectRegion _real_rect_get() const;

      void _border_init( GUIConstants::BorderStyle style, uint32 width,  const Color& color );

      GUIConstants::BorderStyle _border_style_get(){
        m_binding.m_mutex.acquires();
        GUIConstants::BorderStyle _style = m_borderStyle;
        m_binding.m_mutex.releases();
        return _style;
      }

      void _brush_init( const FillBrush& brush ){
        m_brush = brush;
      }
      void _font_init( const Font& f ){
        m_font = f;
      }

      void _rect_set( const IntegerRectRegion& rect ){
        m_binding.m_mutex.acquires();
        m_binding.m_renderableRect = rect;
        m_binding.m_mutex.releases();
      }

      void _pos_set( const IntegerDyadCoordinate& coord ){
        m_binding.m_mutex.acquires();
        //old position
        auto _old_pos = m_binding.m_renderableRect.getTopLeftCoord();
        m_binding.m_renderableRect.translatedBy( coord - _old_pos/* get the offset difference */ );
        m_binding.m_mutex.releases();
      }

      void _size_set( const IntegerSize& size){
        m_binding.m_mutex.acquires();
        m_binding.m_renderableRect.setSize( size );
        m_binding.m_mutex.releases();
      }

      void _x_set( sint32 x){
        m_binding.m_mutex.acquires();
        //old position - x
        auto &_old_x = m_binding.m_renderableRect.getTopLeftCoord().getX();
        m_binding.m_renderableRect.translatedByX( x - _old_x  );
        m_binding.m_mutex.releases();
      }

      void _y_set( sint32 y){
        m_binding.m_mutex.acquires();
        //old position - y
        auto &_old_y = m_binding.m_renderableRect.getTopLeftCoord().getY();
        m_binding.m_renderableRect.translatedByY( y - _old_y  );
        m_binding.m_renderableRect.setTopLeftCoordY( y );
        m_binding.m_mutex.releases();
      }

      void _width_set( uint32 w ){
        m_binding.m_mutex.acquires();
        m_binding.m_renderableRect.setWidth( w );
        m_binding.m_mutex.releases();
      }

      void _height_set( uint32 h){
        m_binding.m_mutex.acquires();
        m_binding.m_renderableRect.setHeight( h );
        m_binding.m_mutex.releases();
      }

      const IntegerRectRegion& _rect_get() const{
        return m_binding.m_renderableRect;
      }

      IntegerSize _size_get() const{
        return m_binding.m_renderableRect.getSize();
      }

      IntegerDyadCoordinate _pos_get() const{
        return m_binding.m_renderableRect.getTopLeftCoord();
      }

      void _initProperties();
      void _disposeStateChanged( const StateValue& value, bool );

      /*  dispatch methods  */public:
        void mousePressed( MouseEventArgs& event );
        void mousePressingMoved( MouseEventArgs& event );
        void mouseReleased( MouseEventArgs& event );
        void hoverIn( HoverEventArgs& event );
        void hovered( HoverEventArgs& event );
        void hoverOut( HoverEventArgs& event );

        void mouseWheelUp( MouseWheelEventArgs& event );
        void mouseWheelDown( MouseWheelEventArgs& event );
        void mouseClicked( MouseEventArgs& event );
        void mouseDoubleClicked( MouseEventArgs& event );

        void keyPressed( KeyEventArgs& eventArgs );
        void keyReleased(KeyEventArgs& eventArgs );

        void rendering( RenderingEventArgs& eventArgs );
        void renderChildren();

        void focusIn( FocusEventArgs&eventArgs );
        void focusOut( FocusEventArgs&eventArgs );

        void moved( MovedEventArgs&eventArgs );
        void resized( ResizedEventArgs&eventArgs );
    };

   }//GUI
}//Magna

#endif  /*  CONTROLLER_P_H  */
