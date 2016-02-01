#ifndef QTWIDGETINITIALIZER_H
#define QTWIDGETINITIALIZER_H

#include "basegui_lib.h"

namespace Magna{
  namespace GUI{
    class QtWidgetInitReceptionist;
    class BASEGUI_LIB_EXPORT QtWidgetInitializer {
    public:
      virtual void actInitialization( QtWidgetInitReceptionist & ) = 0;
    };
  }
}

#endif  /*  QTWIDGETINITIALIZER_H  */