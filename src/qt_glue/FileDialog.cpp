#include "FileDialog.h"

#include <QFileDialog>
#include <QString>

namespace Magna{
  namespace Glue{

    String FileDialog::getFilePath( const String& title, const String& startDir, const String& filter ){
#ifdef _MSC_VER
      QString _title = QString::fromUtf16( reinterpret_cast<const ushort *>(  title.c_str() ),  title.size() ) ;
      QString _dir = QString::fromUtf16( reinterpret_cast<const ushort *>(  startDir.c_str() ),  startDir.size() ) ;
      QString _filter = QString::fromUtf16( reinterpret_cast<const ushort *>(  filter.c_str() ),  filter.size() ) ;
#else
      QString _title = QString::fromStdWString(title ) ;
      QString _dir = QString::fromStdWString( startDir ) ;
      QString _filter = QString::fromStdWString( filter ) ;
#endif
      QString _filePath = QFileDialog::getOpenFileName( Nullptr, _title, _dir, _filter );


      String filePath = String( reinterpret_cast<const unicode_char *>( _filePath.utf16() ) , _filePath.size() );
      return filePath;
    }

  }
}
