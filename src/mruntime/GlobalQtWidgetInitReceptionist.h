#ifndef GLOBALQTWIDGETINITRECEPTIONIST_H
#define GLOBALQTWIDGETINITRECEPTIONIST_H

#include "multimedia/QtWidgetInitReceptionist.h"
using namespace Magna::GUI;

#include <QtGui/QWidget>

namespace Magna{
  namespace Runtime{

    class GlobalQtWidgetInitReceptionist : public QtWidgetInitReceptionist{
    public:
      static GlobalQtWidgetInitReceptionist &getGlobalQtWidgetInitReceptionist();

      virtual void appendWidgetAsChild( QWidget * ) ;
      virtual QWidget *queryBaseWidget( const QString& ) ;
    };
  }
}

#endif  /*  GLOBALQTWIDGETINITRECEPTIONIST_H  */
