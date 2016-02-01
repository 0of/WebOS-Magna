#ifndef RADIALGRADIENT_H
#define RADIALGRADIENT_H

#include "basedef/DyadCoordinate.h"

#include "Gradient.h"

using namespace Magna;
using namespace Magna::Core;

namespace Magna{  
   namespace Render{
     class RENDER_LIB_EXPORT RadialGradient : public __Generalizes Gradient{
        __Constructor_Destructor public:
        RadialGradient();
        explicit RadialGradient( const IntegerDyadCoordinate& center, float centerRadius
          ,  const IntegerDyadCoordinate& focus, float focusRadius);
        explicit RadialGradient( sint32 xCenter, sint32 yCenter, float centerRadius
          ,  sint32 xFocus, sint32 yFocus, float focusRadius);
        virtual ~RadialGradient();

      __Setter public:
        void setCenter( const IntegerDyadCoordinate& center ){
          m_center = center;
        }
        void setCenter( sint32 xCenter, sint32 yCenter){
          m_center.setCoordinate( xCenter, yCenter ); 
        }
        void setFocus( const IntegerDyadCoordinate& focus ){
          m_focus = focus;
        }
        void setFocus(  sint32 xFocus, sint32 yFocus ){
          m_focus.setCoordinate( xFocus, yFocus );
        }
        void setCenterRadius( float r ){
          m_centerRadius = r;
        }
        void setFocusRadius( float r ){
          m_focusRadius = r;
        }

      __Getter public:
        inline const IntegerDyadCoordinate& getCenter() const{
          return m_center;
        }
        inline const IntegerDyadCoordinate& getFocus() const{
          return m_focus;
        }
        inline float getCenterRadius() const{
          return m_centerRadius;
        }
        inline float getFocusRadius() const{
          return m_focusRadius;
        }

      __Override_Methods protected:
        virtual String _toString( const IntegerDyadCoordinate& ) const;

      __Data_Field private:
        IntegerDyadCoordinate m_center;
        IntegerDyadCoordinate m_focus;
        float m_centerRadius;
        float m_focusRadius;
     };
   }//Render
}//Magna
#endif  /*  RADIALGRADIENT_H  */