#ifndef IMAGE_P_H
#define IMAGE_P_H

#include "Image.h"

#include <QtGui/QImage>

namespace Magna{
  namespace Glue{

    class Image::PrivateData{
      public:
        PrivateData()
          :m_qimageBody()
          ,m_int_runtimeId( 0 )
          ,m_loadPath(){

        }

        explicit PrivateData( const String& path )
#ifdef _MSC_VER
          :m_qimageBody( QString::fromUtf16( reinterpret_cast<const ushort *>(path.c_str()), path.size() ) )
#else
          :m_qimageBody( QString::fromStdWString( path ) )
#endif
          ,m_int_runtimeId( 0 )
          ,m_loadPath(){

          if( !m_qimageBody.isNull() ){
            m_loadPath = path;
          }
        }

        explicit PrivateData( const QImage& img )
          :m_qimageBody( img )
          ,m_int_runtimeId( 0 )
          ,m_loadPath(){

        }

        ~PrivateData(){

        }



      public:
        uint64 m_int_runtimeId;
        QImage m_qimageBody;

        String m_loadPath;
    };

  }//namespace Glue
}//namespace Magna

#endif  /*  IMAGE_P_H  */
