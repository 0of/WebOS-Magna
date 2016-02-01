#ifndef QTWIDGETINITRECEPTIONIST_H
#define QTWIDGETINITRECEPTIONIST_H

#include "multimedia_lib.h"

#include <QtGui/QWidget>

namespace Magna{
  namespace GUI{

    class MULTIMEDIA_LIB_EXPORT QtWidgetInitReceptionist{
    public:
      virtual void appendWidgetAsChild( QWidget * ) = 0;
      virtual QWidget *queryBaseWidget( const QString& ) = 0;
    };
  }
}

#endif  /*  QTWIDGETINITRECEPTIONIST_H  */
