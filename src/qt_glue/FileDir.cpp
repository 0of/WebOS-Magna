#include "FileDir.h"

#include <QDir>

namespace Magna{
  namespace Glue{
    
    std::vector<String> FileDir::getAbsPath( const String& dir, const String filter ){
      std::vector<String> _paths;
      if( !dir.empty() ){
#ifdef _MSC_VER
        const QString& _dir_p = QString::fromUtf16( reinterpret_cast<const ushort *>(dir.c_str()), dir.size() ) ;
#else
        const QString& _dir_p = QString::fromStdWString( dir ) ;
#endif
        QDir _dir( _dir_p );
#ifdef _MSC_VER
        const QString& _filter = QString::fromUtf16( reinterpret_cast<const ushort *>(filter.c_str()), filter.size() ) ;
#else
        const QString& _filter = QString::fromStdWString( filter ) ;
#endif
        QStringList filters = _filter.split(";");

        const auto &_list = _dir.entryInfoList( filters );

        
        for( auto _iter = _list.begin(); _iter != _list.end(); ++_iter ){
          const auto &_path = _iter->absoluteFilePath();
#ifdef _MSC_VER
          String _each = String( reinterpret_cast<const unicode_char *>( _path.utf16() ) ); 
#else
          String _each = String( _path.toStdWString() );
#endif
          _paths.push_back( _each );
        }        
      }
      return _paths;
    }

  }//namespace Glue
}//namespace Magna
