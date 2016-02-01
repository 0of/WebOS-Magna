#include "TimeObject.h"

#include <QTime>

namespace Magna{
  namespace Glue{
    
    class Time::PrivateData{
      public:
        PrivateData()
          :m_timeObj(){

        }

        PrivateData( uint32 h, uint32 m, uint32 s, uint32 ms )
          :m_timeObj( h, m, s, ms ){

        }

        QTime m_timeObj;
    };

    Time::Time()
      :m_data(){

    }
    
    Time::Time( uint32 h, uint32 m, uint32 s, uint32 ms )
      :m_data( new PrivateData( h, m, s, ms )){

    }

    Time::Time( const Time& t )
      :m_data( t.m_data ){

    }

    Time::~Time(){

    }

    uint32  Time::getHour () const{
      uint32 _hour = 0;
      if( !m_data.isNull() ){
        _hour = m_data->m_timeObj.hour();
      }
      return _hour;
    }

    uint32  Time::getMinute () const{
      uint32 _min = 0;
      if( !m_data.isNull() ){
        _min = m_data->m_timeObj.minute();
      }
      return _min;
    }

    uint32  Time::getMsec () const{
      uint32 _msec = 0;
      if( !m_data.isNull() ){
        _msec = m_data->m_timeObj.msec();
      }
      return _msec;
    }

    uint32  Time::getSecond () const{
      uint32 _sec = 0;
      if( !m_data.isNull() ){
        _sec = m_data->m_timeObj.second();
      }
      return _sec;
    }

    bool  Time::isValid () const{
      return ( !m_data.isNull() && m_data->m_timeObj.isValid() );
    }

    String Time::toString ( const String & format ) const{
      String _ret_str;
      if( !m_data.isNull() ){
#ifdef _MSC_VER
        QString &_format = QString::fromUtf16( reinterpret_cast<const ushort *>( format.c_str() ), format.size() );
        QString &_str = m_data->m_timeObj.toString( _format );
        _ret_str = String( reinterpret_cast<const unicode_char *>( _str.utf16() ) );
#else
        QString _format = QString::fromStdWString( format );
        const QString &_str = m_data->m_timeObj.toString( _format );
        _ret_str = _str.toStdWString();
#endif
      }
      return _ret_str;
    }

    Time Time::currentTime() {
      Time _time;
      _time.m_data = new PrivateData;
      const auto &_qtime = QTime::currentTime();
      _time.m_data->m_timeObj = _qtime;

      return _time;
    }

    void Time::currentTime( Time & t ) {
      if( t.m_data.isNull() ){
        t.m_data = new PrivateData;
      }
      t.m_data->m_timeObj = QTime::currentTime();
    }
  
  }//namespace Glue
}//namespace Magna
