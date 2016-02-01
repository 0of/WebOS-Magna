#include "Date.h"

#include <QtCore/QDate>

namespace Magna{
  namespace Glue{

    class Date::PrivateData{
      public:
        PrivateData()
          :m_date(){

        }

        explicit PrivateData( uint32 y, uint32 m, uint32 d )
          :m_date( y, m, d ){

        }

        QDate m_date;
    };


    Date::Date ()
      :m_data( new PrivateData ){

    }

    Date::Date ( uint32 y, uint32 m, uint32 d )
      :m_data( new PrivateData( y, m, d ) ){

    }

    Date::Date( const Date& d)
      :m_data( d.m_data ){

    }

    Date::~Date(){

    }

    uint32 Date::getDay () const{
      uint32 _ret_day = 0;
      if( !m_data.isNull() ){
        _ret_day = m_data->m_date.day();
      }
      return _ret_day;
    }

    uint32  Date::getDayOfWeek () const{
      uint32 _ret_day = 0;
      if( !m_data.isNull() ){
        _ret_day = m_data->m_date.dayOfWeek();
      }
      return _ret_day;
    }

    uint32  Date::getDayOfYear () const{
      uint32 _ret_day = 0;
      if( !m_data.isNull() ){
        _ret_day = m_data->m_date.dayOfYear();
      }
      return _ret_day;
    }

    uint32  Date::getDaysNumberInMonth () const{
      uint32 _ret_day = 0;
      if( !m_data.isNull() ){
        _ret_day = m_data->m_date.daysInMonth();
      }
      return _ret_day;
    }

    uint32  Date::getDaysNumberInYear () const{
      uint32 _ret_day = 0;
      if( !m_data.isNull() ){
        _ret_day = m_data->m_date.daysInYear();
      }
      return _ret_day;
    }

    uint32  Date::getWeekNumber () const{
      uint32 _ret_week = 0;
      if( !m_data.isNull() ){
        _ret_week = m_data->m_date.weekNumber();
      }
      return _ret_week;
    }

    uint32  Date::getYear () const{
      uint32 _ret_year = 0;
      if( !m_data.isNull() ){
        _ret_year = m_data->m_date.year();
      }
      return _ret_year;
    }

    uint32  Date::getMonth () const{
      uint32 _ret_mon = 0;
      if( !m_data.isNull() ){
        _ret_mon = m_data->m_date.month();
      }
      return _ret_mon;
    }

    bool  Date::isValid () const{
      return !m_data.isNull() && m_data->m_date.isValid();
    }

    bool  Date::setDate ( uint32 year, uint32 month, uint32 day ){
      bool _ret_ok = false;
      if( m_data.isNull() ){
        m_data = new PrivateData;
      }
      _ret_ok = m_data->m_date.setDate( year, month, day );
      return _ret_ok;
    }

    String  Date::toString ( const String & format ) const{
      String _ret_str;
      if( !m_data.isNull() ){
#ifdef _MSC_VER
        QString &_format = QString::fromUtf16( reinterpret_cast<const ushort *>( format.c_str() ) , format.size() );
        QString &_str = m_data->m_date.toString( _format );
        _ret_str = String( reinterpret_cast<const unicode_char *>( _str.utf16() ) );
#else
        const QString &_format = QString::fromStdWString( format );
        const QString &_str = m_data->m_date.toString( _format );
        _ret_str = _str.toStdWString();
#endif
      }
      return _ret_str;
    }

    Date Date::currentDate (){
      Date _date;
      _date.m_data = new PrivateData;
      _date.m_data->m_date = QDate::currentDate();
      return _date;
    }

    void Date::currentDate ( Date& d ){
      if( d.m_data.isNull() ){
        d.m_data = new PrivateData;
      }
      d.m_data->m_date = QDate::currentDate();
    }

  }//namespace Glue
}//namespace Magna
