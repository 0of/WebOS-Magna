#ifndef MOUSEEVENTARGSACCESSOR_H
#define MOUSEEVENTARGSACCESSOR_H

#include "MouseEventArgs.h"

namespace Magna{
  namespace GUI{
    
    class MouseEventArgsAccessor{
      public:
        inline static IntegerDyadCoordinate & getMouseEventArgsCoord( MouseEventArgs& args ){
          return args.m_eventPos;
        }

    };

  }//namespace GUI
}//namespace Magna
#endif  /*  MOUSEEVENTARGSACCESSOR_H  */