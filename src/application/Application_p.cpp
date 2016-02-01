#include "Application.h"
#include "Application_p.h"

namespace Magna{
  namespace Application{
    
    MagnaApplication::PrivateData::PrivateData(const String& appName)
      :m_appName( appName )
      ,m_appPath()
      ,m_eventHandler()
      ,m_wndManager(){

    }

    MagnaApplication::PrivateData::~PrivateData(){

    }

    /*
    MagnaApplication::PrivateData::PrivateData(const assic_char* appName)
      :m_loop()
      ,m_eventHandler()
      ,m_wndManager( m_eventHandler )    
      ,m_appName( Nullptr ){

      size_t _size = ::strlen( appName );
      m_appName = new assic_char[ ++_size ];
      ::memcpy( m_appName, appName, _size );

    }

    MagnaApplication::PrivateData::~PrivateData(){
      if( m_appName != Nullptr ){
        delete [] m_appName;
      }
    }
    */
    //ApplicationWindowManager::PrivateData &MagnaApplication::PrivateData::getAppWindowManagerData(){
    //  return *m_wndManager.m_data;
    //}

  }//namespace Application
}//namespace Magna