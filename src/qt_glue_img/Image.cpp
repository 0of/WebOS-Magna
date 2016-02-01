#include "Image.h"
#include "Image_p.h"

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "ImageResourceHandler.h"

namespace Magna{
  namespace Glue{

    Image::Image()
      :m_data(){


    }

      Image::Image( const byte*data, uint32 width, uint32 height, ImageFormat  format)
      :m_data( new PrivateData() ){

        QImage::Format _format;
        if( format == Image::ImageFormat_RGB24Bits ){
          _format = QImage::Format_RGB888 ;
        }
        else if( format == Image::ImageFormat_ARGB32Bits ){
          _format = QImage::Format_ARGB32;
        }

        m_data->m_qimageBody = QImage( static_cast<const byte*>(data), width, height, _format );

        if( !m_data.isNull()  && !m_data->m_qimageBody.isNull() ){
          auto &_res_handler = ImageResourceHandler::getImageResourceHandler();
          _res_handler.putImageResource( m_data );
        }
    }

    Image::Image( const String& path )
      :m_data( new PrivateData( path ) ){

      if( !m_data.isNull()  && !m_data->m_qimageBody.isNull() ){
        auto &_res_handler = ImageResourceHandler::getImageResourceHandler();
        _res_handler.putImageResource( m_data );
      }
    }

    Image::Image( const Image& img )
      :m_data( img.m_data ){

    }

    Image::~Image(){

    }

    bool  Image::loadFromRawData ( const byte * data, uint32 width, uint32 height, ImageFormat format ){
      bool _loaded = false;

      if( !m_data.isNull()){
        if( m_data.hasReferences() ){
          PrivateData *_regen = new PrivateData( m_data->m_qimageBody );
          m_data = SharedPtr<PrivateData>( _regen );
        }

      }
      else{
        m_data = new PrivateData();
      }

      QImage::Format _format;
      if( format == Image::ImageFormat_RGB24Bits ){
        _format = QImage::Format_RGB888 ;
      }
      else if( format == Image::ImageFormat_ARGB32Bits ){
        _format = QImage::Format_ARGB32_Premultiplied;
      }

      auto _image = QImage( static_cast<const byte*>(data), width, height, _format );

      m_data->m_qimageBody = _image;
      if( !_image.isNull() ){
        _loaded = !false;
      }

      if( _loaded && m_data->m_int_runtimeId == 0 ){
        auto &_res_handler = ImageResourceHandler::getImageResourceHandler();
        _res_handler.putImageResource( m_data );
      }
      return _loaded;
    }

    byte *Image::getBytes(){
      byte *_byte = Nullptr;

      if( !m_data.isNull()){
        if(  m_data->m_int_runtimeId != 0 ){
          if( m_data.hasReferences() ){
            PrivateData *_regen = new PrivateData( m_data->m_qimageBody );
            m_data = SharedPtr<PrivateData>( _regen );

            auto &_res_handler = ImageResourceHandler::getImageResourceHandler();
            _res_handler.putImageResource( m_data );
          }
          _byte = m_data->m_qimageBody.bits();
        }
      }

      return _byte;
    }

    const byte *Image::getBytes() const{
      const byte *_byte = Nullptr;
      if( !m_data.isNull()){
        _byte = m_data->m_qimageBody.bits();
      }
      return _byte;
    }

    byte *Image::getLineAt( uint32 line ){
      byte *_byte = Nullptr;

      if( !m_data.isNull()){

        if(  m_data->m_int_runtimeId != 0 ){
          if( m_data.hasReferences() ){
            PrivateData *_regen = new PrivateData( m_data->m_qimageBody );
            m_data = SharedPtr<PrivateData>( _regen );

            auto &_res_handler = ImageResourceHandler::getImageResourceHandler();
            _res_handler.putImageResource( m_data );
          }
          _byte = m_data->m_qimageBody.scanLine(line);
        }
      }
      return _byte;
    }


    const byte *Image::getLineAt( uint32 line ) const{
      const byte *_byte = Nullptr;
      if( !m_data.isNull()){
        _byte = m_data->m_qimageBody.scanLine(line);
      }
      return _byte;
    }

    sint32 Image::getHeight() const{
      sint32 _height = -1;
      if( !m_data.isNull()){
        _height = m_data->m_qimageBody.height();
      }
      return _height;
    }

    sint32 Image::getWidth() const{
      sint32 _width = -1;
      if( !m_data.isNull()){
        _width = m_data->m_qimageBody.width();
      }
      return _width;
    }

    IntegerSize Image::getSize() const{
      IntegerSize _size( -1, -1 );

      if( !m_data.isNull()){
        const QSize &_img_size = m_data->m_qimageBody.size();
        _size = IntegerSize( _img_size.width(), _img_size.height() );
      }

      return _size;
    }

    RGBColor Image::getPixelAt( uint32 x, uint32 y ){
      RGBColor _color = 0xFF000000;
      if( !m_data.isNull()){
        QRgb _rgb = m_data->m_qimageBody.pixel( x, y) ;
        _color = static_cast<RGBColor>( _rgb );
      }

      return _color;
    }

    bool  Image::isGrayScale () const{
      bool _ret_gray_scale = false;

      if( !m_data.isNull()){
        _ret_gray_scale = m_data->m_qimageBody.isGrayscale();
      }
      return _ret_gray_scale;
    }

    bool  Image::isNull () const{
      return   m_data.isNull() || m_data->m_qimageBody.isNull();
    }

    bool  Image::load ( const String & fileName ){
      bool _loaded = false;

        if( !m_data.isNull()){
          if( m_data.hasReferences() ){
            PrivateData *_regen = new PrivateData( m_data->m_qimageBody );
            m_data = SharedPtr<PrivateData>( _regen );
          }
        }
        else{
          m_data = new PrivateData();
        }

#ifdef _MSC_VER
        _loaded = m_data->m_qimageBody.load( QString::fromUtf16( reinterpret_cast<const ushort *>(fileName.c_str()), fileName.size() ) );
#else
        _loaded = m_data->m_qimageBody.load( QString::fromStdWString( fileName ) );
#endif
        if( _loaded ){
          m_data->m_loadPath = fileName;

          if( m_data->m_int_runtimeId == 0 ){
            auto &_res_handler = ImageResourceHandler::getImageResourceHandler();
            _res_handler.putImageResource( m_data );
          }
        }

      return _loaded;
    }

    bool  Image::loadFromRawData ( const byte * data, uint32 len ){
      bool _loaded = false;

      if( !m_data.isNull()){
        if( m_data.hasReferences() ){
          PrivateData *_regen = new PrivateData( m_data->m_qimageBody );
          m_data = SharedPtr<PrivateData>( _regen );
        }

      }
      else{
        m_data = new PrivateData();
      }
      _loaded = m_data->m_qimageBody.loadFromData( data, len );

      if( _loaded && m_data->m_int_runtimeId == 0 ){
        auto &_res_handler = ImageResourceHandler::getImageResourceHandler();
        _res_handler.putImageResource( m_data );
      }
      return _loaded;
    }

    void  Image::mirrored ( bool horizontal , bool vertical ) {
      if( !m_data.isNull()){

        if( m_data->m_int_runtimeId != 0 ){
          if( m_data.hasReferences() ){
            PrivateData *_regen = new PrivateData( m_data->m_qimageBody );
            m_data = SharedPtr<PrivateData>( _regen );

            auto &_res_handler = ImageResourceHandler::getImageResourceHandler();
            _res_handler.putImageResource( m_data );
          }
          m_data->m_qimageBody = m_data->m_qimageBody.mirrored( horizontal, vertical );
        }

      }
    }

    void Image::fill( RGBColor color ){
      if( !m_data.isNull()){

        if( m_data->m_int_runtimeId != 0 ){
          if( m_data.hasReferences() ){
            PrivateData *_regen = new PrivateData( m_data->m_qimageBody );
            m_data = SharedPtr<PrivateData>( _regen );

            auto &_res_handler = ImageResourceHandler::getImageResourceHandler();
            _res_handler.putImageResource( m_data );
          }
          m_data->m_qimageBody.fill( color );
        }

      }
    }

    void Image::fill( Color color ){
      if( !m_data.isNull()){

        if( m_data->m_int_runtimeId != 0 ){
          if( m_data.hasReferences() ){
            PrivateData *_regen = new PrivateData( m_data->m_qimageBody );
            m_data = SharedPtr<PrivateData>( _regen );

            auto &_res_handler = ImageResourceHandler::getImageResourceHandler();
            _res_handler.putImageResource( m_data );
          }
          m_data->m_qimageBody.fill( color.toRGBColor() );
        }

      }
    }

    String Image::getLoadPath() const{
      String _ret_path;
      if( !m_data.isNull()){
        _ret_path = m_data->m_loadPath;
      }
      return _ret_path;
    }

    void Image::scale( const IntegerSize& size, ImageTransformationMode mode){
      if( !m_data.isNull()){

        if( m_data->m_int_runtimeId != 0
          && ( m_data->m_qimageBody.width() != size.getWidth()
              || m_data->m_qimageBody.height() != size.getHeight() ) ){

          if( m_data.hasReferences() ){
            PrivateData *_regen = new PrivateData( m_data->m_qimageBody );
            m_data = SharedPtr<PrivateData>( _regen );

            auto &_res_handler = ImageResourceHandler::getImageResourceHandler();
            _res_handler.putImageResource( m_data );
          }
          m_data->m_qimageBody = m_data->m_qimageBody.scaled( size.getWidth(), size.getHeight()
            , Qt::IgnoreAspectRatio
            , static_cast<Qt::TransformationMode>(mode) );
        }

      }
    }

    void Image::scale( uint32 width, uint32 height, ImageTransformationMode mode ){
      if( !m_data.isNull()){

        if( m_data->m_int_runtimeId != 0
          && ( m_data->m_qimageBody.width() != width
              || m_data->m_qimageBody.height() != height) ){

          if( m_data.hasReferences() ){
            PrivateData *_regen = new PrivateData( m_data->m_qimageBody );
            m_data = SharedPtr<PrivateData>( _regen );

            auto &_res_handler = ImageResourceHandler::getImageResourceHandler();
            _res_handler.putImageResource( m_data );
          }
          m_data->m_qimageBody = m_data->m_qimageBody.scaled( width, height
            , Qt::IgnoreAspectRatio
            , static_cast<Qt::TransformationMode>(mode) );
        }

      }
    }

    void Image::swap( Image& img ){
      SharedPtr<PrivateData> _swap( m_data );
      m_data = img.m_data;
      img.m_data = _swap;
    }

    bool  Image::save ( const String & fileName ) const{
      bool _ret_save_ok = false;

      if( !m_data.isNull() ){
#ifdef _MSC_VER
        QString _q_file_path = QString::fromUtf16( reinterpret_cast<const ushort *>(fileName.c_str()), fileName.size() );
#else
        QString _q_file_path = QString::fromStdWString( fileName );
#endif

        _ret_save_ok = m_data->m_qimageBody.save( _q_file_path );
      }

      return _ret_save_ok;
    }

    bool  Image::operator!= ( const Image & image ) const{
      bool _ret_equ = false;
      if( m_data.isNull()  && image.m_data.isNull() ){

      }
      else if( !m_data.isNull()  && !image.m_data.isNull()  ){
        _ret_equ = ( m_data->m_int_runtimeId != image.m_data->m_int_runtimeId );
      }
      else{
        _ret_equ = !false;
      }
      return _ret_equ;
    }

    Image &  Image::operator= ( const Image & image ){
      m_data = image.m_data;
      return *this;
    }

    bool  Image::operator== ( const Image & image ) const{
      bool _ret_equ = false;
      if( m_data.isNull()  && image.m_data.isNull() ){
        _ret_equ = !false;
      }
      else if( !m_data.isNull()  && !image.m_data.isNull()  ){
        _ret_equ = ( m_data->m_int_runtimeId == image.m_data->m_int_runtimeId );
      }
      else{

      }
      return _ret_equ;
    }

  }//namespace Glue
}//namespace Magna
