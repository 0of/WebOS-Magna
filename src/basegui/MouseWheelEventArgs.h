#ifndef MOUSEWHEELEVENTARGS_H
#define MOUSEWHEELEVENTARGS_H

#pragma once
#pragma warning( disable:4800 )

#include "basegui_lib.h"

#include "basedef/DyadCoordinate.h"
#include "basedef/AbstractedEventArgs.h"

#include "render/DyadCoordinateMapper.h"
using namespace Magna::Render;

#include "EventArgConstants.h"

namespace Magna{  
   namespace GUI{
     class BASEGUI_LIB_EXPORT MouseWheelEventArgs : public __Generalizes AbstractedEventArgs{
       __Constructor_Destructor public:
        typedef uint32 KeyModifiers;
        MouseWheelEventArgs( GUIEventConstants::EventType type, sint32 delta, const IntegerDyadCoordinate& eventPos
          , KeyModifiers modifiers )
          :AbstractedEventArgs( static_cast<uint16>(type) )
          ,m_delta( delta ), m_eventPos( eventPos ), m_modifiers( modifiers ){}
        virtual ~MouseWheelEventArgs(){}

      __Checker public:
        inline bool isCausedWithAltModifier() const { return static_cast<bool>( m_modifiers & KeyEventArgConstants::KeyModifier_Alt) ;}
        inline bool isCausedWithCtrlModifier() const { return static_cast<bool>( m_modifiers & KeyEventArgConstants::KeyModifier_Control) ;}
        inline bool isCausedWithShiftModifier() const { return static_cast<bool>( m_modifiers & KeyEventArgConstants::KeyModifier_Shift) ;}

      __Getter public:
        inline const IntegerDyadCoordinate & getTriggeredCoord() const{ return m_eventPos; }
        inline sint32 getDelta(){ return m_delta; }

      __Overloaded_Methods public:
        MouseWheelEventArgs & operator = ( const MouseWheelEventArgs& args );

        bool operator == ( const MouseWheelEventArgs& args );
        bool operator != ( const MouseWheelEventArgs& args );

      __Data_Field private:
        sint32 m_delta;
        KeyModifiers m_modifiers;
        IntegerDyadCoordinate m_eventPos;

     };
   }//GUI
}//Magna

#endif  /*  MOUSEWHEELEVENTARGS_H  */
