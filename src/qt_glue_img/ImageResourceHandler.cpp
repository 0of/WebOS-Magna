#include "ImageResourceHandler.h"

namespace Magna{
  namespace Glue{

    const unicode_char *const ImageResourceHandler::shared_Image_Res_Handler_node_name  = L"ImgResHandler";

    ImageResourceHandler& ImageResourceHandler::getImageResourceHandler(){
      static ImageResourceHandler img_handler;
      return img_handler;
    }

    ImageResourceHandler::ImageResourceHandler()
      :m_imgResources(){

    }

    ImageResourceHandler::~ImageResourceHandler(){

    }

    void ImageResourceHandler::putImageResource( SharedPtr<Image::PrivateData> & res ){
      if( !res.isNull() ){
        std::random_device _dev_gen;

        std::ranlux48_base _base64_ram( _dev_gen() );

        uint64 _id = 0;

        //ensure id unique
        //enter critical section
        m_mutex.acquires();
        while( [&]() -> bool{ _id = _base64_ram()
          ; return m_imgResources.count( _id )  != 0; }() ){}

        res->m_int_runtimeId = _id;

        m_imgResources.emplace( std::make_pair(_id,  res ) );

        m_mutex.releases();
      }
    }

    void ImageResourceHandler::pullImageResource( const uint64& id ){
      m_mutex.acquires();

      auto _found = m_imgResources.find( id );

      if( _found != m_imgResources.end() ){
        m_imgResources.erase( _found );
      }

      m_mutex.releases();
    }

    QImage ImageResourceHandler::getImageResource( const quint64& id ){
      QImage _ret_img;
      m_mutex.acquires();

      auto _found = m_imgResources.find( id );
      if( _found != m_imgResources.end() ){
        if( !_found->second.isNull() ){
          _ret_img = _found->second->m_qimageBody;
        }
      }

      m_mutex.releases();

      return _ret_img;
    }

  }//namespace Glue
}//namespace Magna
