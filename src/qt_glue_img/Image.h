#ifndef IMAGE_H
#define IMAGE_H

#include "qt_glue_img.h"

#include <cstdlib>
#include <cwchar>
#include <locale>

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"
#include "basedef/Color.h"
#include "basedef/Size.h"
#include "basedef/SharedPtr.h"
#include "basedef/String.h"
using namespace Magna::Core;

namespace Magna{
  namespace Glue{
    
    class QT_GLUE_LIB_EXPORT Image{
        friend class ImageResourceHandler;
        friend class ImageResourceHandlerHelper;

      __Constants public:
        enum ImageTransformationMode{
          ImageTransformationMode_Fast = 0
          ,ImageTransformationMode_Smooth = 1
        };

        enum ImageFormat{
          ImageFormat_Invalid,
          ImageFormat_Mono,
          ImageFormat_RGB24Bits,
          ImageFormat_ARGB32Bits
        };

      __Constructor_Destructor public:
        Image();
        explicit Image( const byte*, uint32 width, uint32 height, ImageFormat );
        explicit Image( const String& path );
        Image( const Image& img );
        ~Image();

      __Getter public:
        byte *getBytes();
        const byte *getBytes() const;

        byte *getLineAt( uint32 line );
        const byte *getLineAt( uint32 line ) const;

        sint32 getHeight() const;
        sint32 getWidth() const;
        IntegerSize getSize() const;

        RGBColor getPixelAt( uint32 x, uint32 y );        

      __Checker public:

        bool  isGrayScale () const;
        bool  isNull () const;

      public:
        bool  load ( const String & fileName );
        bool  loadFromRawData ( const byte * data, uint32 width, uint32 height, ImageFormat );
        bool  loadFromRawData ( const byte * data, uint32 len );

        void  mirrored ( bool horizontal = false, bool vertical = true ) ;

        void fill( RGBColor color );
        void fill( Color color );

        void scale( const IntegerSize& size, ImageTransformationMode = ImageTransformationMode_Fast );
        void scale( uint32 width, uint32 height, ImageTransformationMode = ImageTransformationMode_Fast );

        void swap( Image& img );

        bool  save ( const String & fileName ) const;

        String getLoadPath() const;

      __Overloaded_Methods public:
        bool  operator!= ( const Image & image ) const;
        Image &  operator= ( const Image & image );
        bool  operator== ( const Image & image ) const;

      public:
        class PrivateData;
      __Data_Field private:
        SharedPtr<PrivateData> m_data;
    };

  }//namespace Glue
}//namespace Magna

#endif  /*  IMAGE_H  */