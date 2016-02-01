#ifndef MOUSEEVENTARGS_H
#define MOUSEEVENTARGS_H

#pragma once
#pragma warning(disable:4800)

#include "basegui_lib.h"

#include "basedef/DyadCoordinate.h"
#include "basedef/AbstractedEventArgs.h"
using namespace Magna::Core;

#include "render/DyadCoordinateMapper.h"
using namespace Magna::Render;

#include "EventArgConstants.h"

namespace Magna{  
   namespace GUI{
     class BASEGUI_LIB_EXPORT MouseEventArgs : public AbstractedEventArgs{
       friend class MouseEventArgsAccessor;
      __Constructor_Destructor public:
        typedef uint32 MouseButtons;
        typedef uint32 KeyModifiers;
         MouseEventArgs( GUIEventConstants::EventType mouseEventType
                    , MouseButtons buttons
                     ,  const IntegerDyadCoordinate& pos
                     , KeyModifiers modifiers
                    );

        MouseEventArgs( const MouseEventArgs& args );
         virtual ~MouseEventArgs();
       __Getter public:
         inline const IntegerDyadCoordinate & getTriggeredCoord() const{ return m_eventPos; }    
        inline MouseButtons getCausedButtons() const { return m_buttons; }
        inline KeyModifiers getKeyModifiers() const { return m_modifiers; }
        
      __Checker public:
        inline bool isCausedByLeftButton() const { return static_cast<bool>(m_buttons & MouseEventArgConstants::MouseButton_LeftButton); }
        inline bool isCausedByRightButton() const { return static_cast<bool>(m_buttons & MouseEventArgConstants::MouseButton_RightButton); }
        inline bool isCausedWithAltModifier() const { return static_cast<bool>( m_modifiers & KeyEventArgConstants::KeyModifier_Alt) ;}
        inline bool isCausedWithCtrlModifier() const { return static_cast<bool>( m_modifiers & KeyEventArgConstants::KeyModifier_Control) ;}
        inline bool isCausedWithShiftModifier() const { return static_cast<bool>( m_modifiers & KeyEventArgConstants::KeyModifier_Shift) ;}

      __Overloaded_Methods public:
        MouseEventArgs & operator = ( const MouseEventArgs& args );

        bool operator == ( const MouseEventArgs& args );
        bool operator != ( const MouseEventArgs& args );

      __Data_Field private:
        MouseButtons m_buttons;
        KeyModifiers m_modifiers;
        IntegerDyadCoordinate m_eventPos;
     };
   }//GUI
}//Magna
#endif  /*  MOUSEEVENTARGS_H  */
