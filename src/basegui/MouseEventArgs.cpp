#include "MouseEventArgs.h"
#include "EventArgConstants.h"

#include <cstring>

#include "basedef/CompilerTimeAssert.h"
namespace Magna{  
   namespace GUI{
      
     MouseEventArgs::MouseEventArgs( GUIEventConstants::EventType mouseEventType
                            , MouseButtons buttons
                             ,  const IntegerDyadCoordinate& pos
                             , KeyModifiers modifiers)
                             :AbstractedEventArgs( static_cast<uint16>(mouseEventType) ),  m_buttons( buttons ), m_eventPos( pos ), m_modifiers( modifiers ){
        
    
     }

     MouseEventArgs:: ~MouseEventArgs(){

     }

     MouseEventArgs::MouseEventArgs( const MouseEventArgs& args )
       :AbstractedEventArgs( args.m_type )
        ,m_buttons( args.m_buttons ), m_eventPos( args.m_eventPos )
       , m_modifiers( args.m_modifiers ){

     }

     MouseEventArgs &  MouseEventArgs::operator = ( const MouseEventArgs& args ){
       ::memcpy( this, &args, sizeof( MouseEventArgs ) );
       return *this;
     }

     bool MouseEventArgs::operator == ( const MouseEventArgs& args ){
       return m_buttons == args.m_buttons && m_eventPos == args.m_eventPos
         && m_modifiers == args.m_modifiers ;
     }
     bool MouseEventArgs::operator != ( const MouseEventArgs& args ){
       return !operator ==( args );
     }
   }//GUI
}//Magna
