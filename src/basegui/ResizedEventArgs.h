#ifndef RESIZEDEVENTARGS_H
#define RESIZEDEVENTARGS_H

#include "basegui_lib.h"

#include "basedef/AbstractedEventArgs.h"
#include "basedef/Size.h"
using namespace Magna::Core;

#include "EventArgConstants.h"

namespace Magna{
  namespace GUI{

    class BASEGUI_LIB_EXPORT ResizedEventArgs : public __Generalizes AbstractedEventArgs{
      __Constructor_Destructor public:
    
        explicit ResizedEventArgs( const IntegerSize& oldSize,  const IntegerSize& newSize )
          :AbstractedEventArgs( GUIEventConstants::GUIEvent_Moved, false )
          ,m_oldSize( oldSize )
          ,m_newSize( newSize ){

        }

        ResizedEventArgs( const ResizedEventArgs& args )
          :AbstractedEventArgs( args )
          ,m_oldSize( args.m_oldSize )
          ,m_newSize( args.m_newSize ){
          
        }
          
        virtual ~ResizedEventArgs(){}
      
      __Getter public:
        inline const IntegerSize& getOldSize() const{ return m_oldSize; }
        inline const IntegerSize& getNewSize() const{ return m_newSize; }

      __Overloaded_Methods public:
        ResizedEventArgs & operator = ( const ResizedEventArgs& args ){
          m_oldSize = args.m_oldSize;
          m_newSize = args.m_newSize;
          return *this;
        }

        bool operator == ( const ResizedEventArgs& args ){
          return ( ( m_oldSize == args.m_newSize )
            && ( m_newSize == args.m_newSize ) );
        }

        bool operator != ( const ResizedEventArgs& args ){
          return !operator==( args );
        }

      __Data_Field private:
        IntegerSize m_oldSize;
        IntegerSize m_newSize;

        
    };
    
  }//namespace GUI
}//namespace Magna

#endif  /*  RESIZEDEVENTARGS_H  */