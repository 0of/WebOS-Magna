#ifndef WINDOW_P_H
#define WINDOW_P_H

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"
#include "basedef/CompilerTimeAssert.h"
#include "basedef/SharedPtr.h"
#include "basedef/RunnableContext.h"
using namespace Magna::Core;

#include "render/RenderManager.h"
#include "render/RenderManager2D.h"
#include "render/Pen.h"
#include "render/FillBrush.h"
#include "render/Gradient.h"
#include "render/LinearGradient.h"
using namespace Magna::Render;

#include "Layout.h"

#include "Controller_p.h"
#include "Controller.h"

#include "WindowImplementor.h"
#include "WindowPropertySet.h"

#include "MouseEventArgs.h"
#include "MouseWheelEventArgs.h"
#include "KeyEventArgs.h"
#include "CommonEventArgs.h"
#include "MovedEventArgs.h"
#include "ResizedEventArgs.h"

#include "OSGUIBehaviourRequester.h"

#include <hash_map>
namespace Magna{  
   namespace GUI{   

     class BASEGUI_LIB_EXPORT EventDispacher{
     public:
       virtual void test(  Window::WindowRoot* ) = 0;
     };


     class BASEGUI_LIB_EXPORT Window::WindowRoot{
       friend class Window;
       friend class StateSwitcher<WindowPropertySet::StateValue>;
       __Trigger public:
        TRIGGER_DEF(OnceWindowClosed, const uint64& )

         //TRIGGER_DEF(OnceHidden, const String& )
         //TRIGGER_DEF(OnceShown, const String& )
         TRIGGER_DEF(OnceVisibilityChanged, const unicode_char *, bool)
         TRIGGER_DEF(OnceFocusChanged, const unicode_char *, bool)

        
         TRIGGER_DEF(OnceMoved,  const String&, const IntegerDyadCoordinate& )
         TRIGGER_DEF(OnceResized, const unicode_char *,  const IntegerSize&)
         TRIGGER_DEF(OnceControllerResized, const String&,  const IntegerSize&)
          /*
         TRIGGER_DEF(OnceRendered, ManipulateEngine& )

         //###
         //Unsolved Problem
         //When trigger vector to the global receiver, some parameters of the controller root have been revised
         //Can not find out how this happened
         TRIGGER_DEF(OnceControllersAttached, std::vector<SharedPtr<Controller::ControllerRoot> >&,RunnableContext *  )
         //###Solved
         //###Header file doesn't sync
         */

         TRIGGER_DEF(OnceControllersDetached, const std::vector<uint64>& )

         TRIGGER_DEF(OnceScrolled, const unicode_char *, uint32, uint32 )
        
       __Constructor_Destructor public:
 
        explicit WindowRoot( Window &bindingWindow );
        explicit WindowRoot( Window &bindingWindow, Window::WindowAttributes attributes  );
        ~WindowRoot();

      public:
        //use for derived class initializations
        void _impl_init( const SharedPtr<WindowImplementor>& impl );
        void _impl_set( const SharedPtr<WindowImplementor>& impl );
        SharedPtr<WindowImplementor> _impl_get();

        void _rect_set( const IntegerRectRegion& rect ){
          m_properties.m_mutex.acquires();
          m_properties.m_boundingRect = rect;
          m_properties.m_mutex.releases();
        }

        void _pos_set( const IntegerDyadCoordinate& coord ){
          m_properties.m_mutex.acquires();
          const auto &_pos_diff = coord - m_properties.m_boundingRect.getTopLeftCoord() ;
          m_properties.m_boundingRect.translatedBy( _pos_diff );
          m_properties.m_mutex.releases();
        }

        void _size_set( const IntegerSize& size){
          m_properties.m_mutex.acquires();
          m_properties.m_boundingRect.setSize( size );
          m_properties.m_mutex.releases();
        }

        void _x_set( sint32 x){
          m_properties.m_mutex.acquires();
          const auto &_x_diff = x - m_properties.m_boundingRect.getTopLeftCoord().getX() ;
          m_properties.m_boundingRect.translatedByX(_x_diff);
          m_properties.m_mutex.releases();
        }

        void _y_set( sint32 y){
          m_properties.m_mutex.acquires();
          const auto &_y_diff = y - m_properties.m_boundingRect.getTopLeftCoord().getY() ;
          m_properties.m_boundingRect.translatedByY( _y_diff );
          m_properties.m_mutex.releases();
        }

        void _width_set( uint32 w ){
          m_properties.m_mutex.acquires();
          m_properties.m_boundingRect.setWidth( w );
          m_properties.m_mutex.releases();
        }

        void _height_set( uint32 h){
          m_properties.m_mutex.acquires();
          m_properties.m_boundingRect.setHeight( h );
          m_properties.m_mutex.releases();
        }

        IntegerRectRegion _rect_get() const{
          IntegerRectRegion _ret_rect;
          m_properties.m_mutex.acquires();
          _ret_rect = m_properties.m_boundingRect;
          m_properties.m_mutex.releases();
          return _ret_rect;
        }

        sint32 _width_get() const{
          return m_properties.m_boundingRect.getWidth();
        }

        sint32 _height_get() const{
          return m_properties.m_boundingRect.getHeight();
        }

        IntegerSize _size_get() const{
          return m_properties.m_boundingRect.getSize();
        }

        IntegerDyadCoordinate _pos_get() const{
          return m_properties.m_boundingRect.getTopLeftCoord();
        }

        std::vector<SharedPtr<Controller::ControllerRoot> > _ctrls_get() const;    

        //use by manager
        String _createWindowNode();
        const unicode_char * _getPlainElementId() ;

        void _assignRuntimeId( const uint32& id);
        void _de_assignRuntimeId();

        //every focused window has one focused controller
        //when one controller acquire focus state it'll replace the current focused one
        void _controller_focus( Controller *_controller );
        void _controller_de_focus( Controller *_controller );

        void _dispatchEventMessage( AbstractedEventArgs &eventArgs );

        void _attachController( SharedPtr<Controller::ControllerRoot>& );
        void _detachController( SharedPtr<Controller::ControllerRoot>& );

        void _script_eval( const String& sc );

     private:
       //self initializations
       void _initPropertySet();
       void _stateChanged( const WindowPropertySet::StateValue& stateName, bool );

     public:
        //Window event process
        void windowClose( CloseEventArgs& eventArgs );
        void windowHidden( HideEventArgs& eventArgs );
        void windowShown( ShowEventArgs& eventArgs );

        void windowMoved( MovedEventArgs & eventArgs );
        void windowResized( ResizedEventArgs & eventArgs );

        void windowFocused( FocusEventArgs& eventArgs );

        //actions
        void windowRender();
        void renderController( Controller *contr );
        void partlyRenderController( Controller *contr, const IntegerRectRegion& dirtyRegion );
        
      __Data_Field public:
       WindowPropertySet m_properties;
       SharedPtr<WindowImplementor> m_impl;

       Window &m_binding;
       uint32 m_int_runtimeId;
       unicode_char *m_runtime_Id;

       RunnableContext *m_RunnableContext;
       OSGUIBehaviourRequester *m_requester;
     };
   }//GUI
}//Magna

#endif  /*  WINDOW_P_H  */
