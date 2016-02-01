#include "OSStartApplicationBehaviourNotifier.h"

#include "qt_glue/FileDialog.h"
using namespace Magna::Glue;

#include "RuntimeContainer.h"

namespace Magna{
  namespace Runtime{

    OSStartApplicationBehaviourNotifier:: OSStartApplicationBehaviourNotifier( bool dialog,const String& a1 , RunnableContext * r)
      :OSBehaviourNotifier()
      ,m_needDialog( dialog )
      ,m_appPath( a1 )
      ,m_parent( r ){

    }

    OSStartApplicationBehaviourNotifier:: ~OSStartApplicationBehaviourNotifier(){

    }

    void OSStartApplicationBehaviourNotifier::notifyOS(){
      String _path;
      if( m_needDialog != 0 ){
        _path = FileDialog::getFilePath(L"访问Magna应用程序",m_appPath, L"Magna App (*.dll)");
      }
      else{
        _path = m_appPath;
      }

      if( !_path.empty() ){
        RuntimeContainer &_container = RuntimeContainer::getRuntimeContainer();
        _container.loadApplication( _path );
      }
      
    }

  }
}
