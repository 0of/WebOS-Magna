#ifndef MOVEDEVENTARGS_H
#define MOVEDEVENTARGS_H

#include "basegui_lib.h"

#include "basedef/AbstractedEventArgs.h"
#include "basedef/DyadCoordinate.h"
using namespace Magna::Core;

#include "EventArgConstants.h"

namespace Magna{  
  namespace GUI{
    class BASEGUI_LIB_EXPORT MovedEventArgs : public __Generalizes AbstractedEventArgs{
      __Constructor_Destructor public:
        explicit MovedEventArgs( const IntegerDyadCoordinate& oldCoord,  const IntegerDyadCoordinate& newCoord )
          :AbstractedEventArgs( GUIEventConstants::GUIEvent_Moved, false )
          ,m_oldCoord( oldCoord )
          ,m_newCoord( newCoord ){

        }

        MovedEventArgs( const MovedEventArgs& args )
          :AbstractedEventArgs( args )
          ,m_oldCoord( args.m_oldCoord )
          ,m_newCoord( args.m_newCoord ){
          
        }
          
        virtual ~MovedEventArgs(){}
      
      __Getter public:
        inline const IntegerDyadCoordinate& getOldCoord() const{ return m_oldCoord; }
        inline const IntegerDyadCoordinate& getNewCoord() const{ return m_newCoord; }

      __Overloaded_Methods public:
        MovedEventArgs & operator = ( const MovedEventArgs& args ){
          m_oldCoord = args.m_oldCoord;
          m_newCoord = args.m_newCoord;
          return *this;
        }

        bool operator == ( const MovedEventArgs& args ){
          return ( ( m_oldCoord == args.m_newCoord )
            && ( m_newCoord == args.m_newCoord ) );
        }

        bool operator != ( const MovedEventArgs& args ){
          return !operator==( args );
        }

      __Data_Field private:
        IntegerDyadCoordinate m_oldCoord;
        IntegerDyadCoordinate m_newCoord;

    };
  }//GUI
}//Magna
#endif  /*  MOVEDEVENTARGS_H  */