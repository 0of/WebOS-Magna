#ifndef WINDOWFRAMECONTROLLER_H
#define WINDOWFRAMECONTROLLER_H

#include "basegui_lib.h"

#include "basedef/Trigger.h"
using namespace Magna::Core;

#include "Controller.h"
#include "IFrame.h"
#include "RenderEventArgs.h"

namespace Magna{
  namespace GUI{
    class Window;
    class BASEGUI_LIB_EXPORT WindowFrameController : public Controller{
      friend class Window;
      __Constructor_Destructor public:
        WindowFrameController();
        explicit WindowFrameController( IFrame *iframe );
        virtual ~WindowFrameController();

      __Checker public:
        bool hasBound() const;
        bool isDefaultFrame() const;

        __Setter public:
        void setFrameImplementor( IFrame *iframe );

        __Setter protected:
        void setBindingWindow( Window *wind );

        __Override_Methods private:
        virtual String toStyleString() const ;

    };
  }//namespace GUI
}//namespace Magna

#endif  /*  WINDOWFRAMECONTROLLER_H  */