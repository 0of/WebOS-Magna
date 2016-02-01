#ifndef IMAGERESOURCEHANDLER_H
#define IMAGERESOURCEHANDLER_H

#include "qt_glue_img_global.h"

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/SpinMutex.h"
using namespace Magna::Core;

#include "Image.h"
#include "Image_p.h"

#include <QtCore/QObject>
#include <QtGui/QImage>

#ifdef _MSC_VER
#include <hash_map>
#elif defined __GNUC__
#include <map>
//#include <ext/hash_map>
#endif
#include <random>

namespace Magna{
  namespace Glue{

#ifdef _MSC_VER
typedef std::hash_map<uint64, SharedPtr<Image::PrivateData> > ImageResourcesType;
#elif defined __GNUC__
typedef std::map<uint64, SharedPtr<Image::PrivateData> > ImageResourcesType;
//typedef __gnu_cxx::hash_map<uint64, SharedPtr<Image::PrivateData> > ImageResourcesType;
#endif

    class QT_GLUE_IMG_EXPORT ImageResourceHandler : public QObject{
      Q_OBJECT
      Q_DISABLE_COPY(ImageResourceHandler)

      public:
        static const unicode_char *const shared_Image_Res_Handler_node_name ;
        static ImageResourceHandler& getImageResourceHandler();

      __Constructor_Destructor protected:
        ImageResourceHandler();
        virtual ~ImageResourceHandler();

      public:
        void putImageResource( SharedPtr<Image::PrivateData> & res );
        void pullImageResource( const uint64& id );

      public slots:
        QImage getImageResource( const quint64& id );

      private:
        ImageResourcesType m_imgResources;

        SpinMutex m_mutex;
    };

  }//namespace Glue
}//namespace Magna

#endif  /*  IMAGERESOURCEHANDLER_H  */
