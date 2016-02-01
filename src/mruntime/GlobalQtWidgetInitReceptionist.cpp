#include "GlobalQtWidgetInitReceptionist.h"

#include "RuntimeContainer.h"

namespace Magna{
  namespace Runtime{

    GlobalQtWidgetInitReceptionist &GlobalQtWidgetInitReceptionist::getGlobalQtWidgetInitReceptionist(){
      static GlobalQtWidgetInitReceptionist _rec;
      return _rec;
    }

    void GlobalQtWidgetInitReceptionist::appendWidgetAsChild( QWidget * w ) {
      if( w != Nullptr ){
        RuntimeContainer &_c = RuntimeContainer::getRuntimeContainer();
        w->setParent( _c.getWebView() );
      }
    }

    QWidget *GlobalQtWidgetInitReceptionist::queryBaseWidget( const QString& query) {
      QWidget * _ret_widget = Nullptr;
      if( query == "magna-webkitview"){
        RuntimeContainer &_c = RuntimeContainer::getRuntimeContainer();
        _ret_widget =  _c.getWebView() ;
      }
      return _ret_widget;
    }

  }
}