#ifndef POPOUTWINDOW_H
#define POPOUTWINDOW_H

#include "basegui_lib.h"

#include "Window.h"

namespace Magna{
  namespace GUI{
    
    class BASEGUI_LIB_EXPORT PopOutWindow : public Window{
      __Constructor_Destructor public:
        PopOutWindow();
        explicit PopOutWindow( WindowAttributes );
        explicit PopOutWindow( const IntegerDyadCoordinate& global_coord );
        virtual ~PopOutWindow();

      public:
        void popOutAt( const IntegerDyadCoordinate& global_coord );
        void popOutAtCenter();
        //
        void popOut();
        //void modalPopOut();

        void popIn();
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  POPOUTWINDOW_H  */