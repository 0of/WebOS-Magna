#ifndef LINEARLAYOUR_H
#define LINEARLAYOUR_H

#include "basegui_lib.h"

#include "Layout.h"

namespace Magna{
  namespace GUI{
    
    class BASEGUI_LIB_EXPORT LinearLayout : public __Generalizes Layout{
      __Constants public:
        enum LinearLayoutOrientation{
          LinearLayoutOrientation_Horizontal,
          LinearLayoutOrientation_Vertical
        };

      __Constructor_Destructor public:
        LinearLayout();
        LinearLayout( LinearLayoutOrientation );
        virtual ~LinearLayout();

      __Override_Methods protected:
        virtual void measure() ;
        virtual void deploy() ;

      public:
        void addController( const SharedPtr<Controller>& controller );
        void insertController( uint32 index, const SharedPtr<Controller>& controller );
  
      __Setter public:
        void setOrientation( LinearLayoutOrientation );
        void setSpacing( uint32 spacing );

      __Getter public:
        inline LinearLayoutOrientation getOrientation() const{
          return m_orientation;
        }
        inline uint32 getSpacing() const{
          return m_spacing;
        }
         
      __Overloaded_Methods public:
        LinearLayout& operator << ( const SharedPtr<Controller>& controller );

      __Data_Field private:
        LinearLayoutOrientation m_orientation;
        uint32 m_spacing;
    };



  }//namespace GUI
}//namespace Magna

#endif  /*  LINEARLAYOUR_H  */