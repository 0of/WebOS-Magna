#ifndef HOVEREVENTARGS_H
#define HOVEREVENTARGS_H

#pragma once
#pragma warning(disable:4800)

#include "basegui_lib.h"

#include "basedef/DyadCoordinate.h"
#include "basedef/AbstractedEventArgs.h"
using namespace Magna::Core;

#include "EventArgConstants.h"

namespace Magna{
  namespace GUI{
     
    class BASEGUI_LIB_EXPORT HoverEventArgs : public AbstractedEventArgs{
      public:
        explicit HoverEventArgs( GUIEventConstants::EventType hoverEventType )
          :AbstractedEventArgs( hoverEventType )
          ,m_oldCoord()
          ,m_newCoord(){            

        }
        //hovered event
        explicit HoverEventArgs( const IntegerDyadCoordinate& oldPos,  const IntegerDyadCoordinate& newPos )
          :AbstractedEventArgs( GUIEventConstants::GUIEvent_MouseHovered )
          ,m_oldCoord( oldPos )
          ,m_newCoord( newPos ){
            
        }

        virtual ~HoverEventArgs(){

        }

      __Checker public:
        inline bool isHoverIn() const{
          return m_type == GUIEventConstants::GUIEvent_MouseHoverIn;
        }
        inline bool isHoverOut() const{
          return m_type == GUIEventConstants::GUIEvent_MouseHoverOut;
        }

      __Getter public:
        inline const IntegerDyadCoordinate& getOldCoord() const{ return m_oldCoord; }
        inline const IntegerDyadCoordinate& getNewCoord() const{ return m_newCoord; }

      __Overloaded_Methods public:
        HoverEventArgs & operator = ( const HoverEventArgs& args ){
          m_oldCoord = args.m_oldCoord;
          m_newCoord = args.m_newCoord;
          return *this;
        }

        bool operator == ( const HoverEventArgs& args ){
          return ( ( m_oldCoord == args.m_newCoord )
            && ( m_newCoord == args.m_newCoord ) );
        }

        bool operator != ( const HoverEventArgs& args ){
          return !operator==( args );
        }

      __Data_Field private:
        IntegerDyadCoordinate m_oldCoord;
        IntegerDyadCoordinate m_newCoord;

    };

  }//namespace GUI
}//namespace Magna

#endif  /*  HOVEREVENTARGS_H  */