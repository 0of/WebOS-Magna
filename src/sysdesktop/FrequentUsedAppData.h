#ifndef FREQUENTUSEDAPPDATA_H
#define FREQUENTUSEDAPPDATA_H

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class FrequentUsedAppData{
        public:
          FrequentUsedAppData( const String& a1, const String& a2, const Image& a3)
            :m_appName( a1 )
            ,m_appPath( a2 )
            ,m_appIcon( a3 ){
            m_appIcon.scale( 64, 64 );
          }

          FrequentUsedAppData( const FrequentUsedAppData& d )
            :m_appName( d.m_appName )
            ,m_appPath( d.m_appPath )
            ,m_appIcon( d.m_appIcon ){
            m_appIcon.scale( 64, 64 );  
          }

          String m_appName;
          String m_appPath;
          Image m_appIcon;
      };

    }
  }
}

#endif  /*  FREQUENTUSEDAPPDATA_H  */