#ifndef LINEARGRADIENT_H
#define LINEARGRADIENT_H

#include "basedef/DyadCoordinate.h"

#include "Gradient.h"

using namespace Magna;
using namespace Magna::Core;

namespace Magna{  
   namespace Render{
     class RENDER_LIB_EXPORT LinearGradient : public __Generalizes Gradient{
       __Constructor_Destructor public:
        LinearGradient()  ;
        explicit LinearGradient( sint32 xStart, sint32 yStart, sint32 xEnd, sint32 yEnd );
        explicit LinearGradient( const IntegerDyadCoordinate& start, const IntegerDyadCoordinate& end );

        virtual ~LinearGradient() ;
        
      __Setter public:
        inline void setStart( const IntegerDyadCoordinate& start ){
          m_startCoord = start;
        }
      __Overloaded_Methods 
        void setStart( sint32 xStart, sint32 yStart ){
          m_startCoord.setCoordinate( xStart, yStart );
        }
  
        void setEnd( const IntegerDyadCoordinate& end ){
          m_endCoord = end;
        }
      __Overloaded_Methods
        void setEnd( sint32 xEnd, sint32 yEnd  ){
          m_endCoord.setCoordinate( xEnd, yEnd );
        }
      __Getter public:
        inline const IntegerDyadCoordinate & getStart() const {
          return m_startCoord;
        }
        inline const IntegerDyadCoordinate & getEnd() const {
          return m_endCoord;
        }
        
        __Override_Methods protected:
        virtual String _toString( const IntegerDyadCoordinate& ) const;

      __Data_Field private:
        IntegerDyadCoordinate m_startCoord;
        IntegerDyadCoordinate m_endCoord;
     };
   }//Render
}//Magna

#endif  /*  LINEARGRADIENT_H  */