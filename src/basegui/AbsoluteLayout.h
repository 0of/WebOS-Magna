#ifndef ABSOLUTELAYOUT_H
#define ABSOLUTELAYOUT_H

#include "basegui_lib.h"

#include "basedef/DyadCoordinate.h"
using namespace Magna::Core;

#include "Layout.h"
 
namespace Magna{
  namespace GUI{
    
    class BASEGUI_LIB_EXPORT AbsoluteLayout : public __Generalizes Layout{
      __Constructor_Destructor public:
        AbsoluteLayout();
        virtual ~AbsoluteLayout();

      __Override_Methods public:
        virtual SharedPtr<Controller> getControllerAt( const IntegerDyadCoordinate& pos ) const ;

      __Override_Methods protected:
        virtual void measure() ;
        virtual void deploy();

      public:
        AbsoluteLayout & addController( const SharedPtr<Controller>& controller );
        AbsoluteLayout & addController( SharedPtr<Controller>& controller, const LayoutAttribute & attr );

    };


  }//namespace GUI
}//namespace Magna

#endif  /*  ABSOLUTELAYOUT_H  */