#include "ImageLabel.h"

#include <stdexcept>
#include <typeinfo>

#include "inner/InnerPrivateDataNullPointerException.h"
#include "inner/InnerIndexNotFoundException.h"
using namespace Magna::Inner;

#include "Controller_p.h"
#include "ImageLabelImplementor.h"

namespace Magna{
  namespace GUI{
    
    ImageLabel::ImageLabel()
      :Controller(){

      if( !m_root.isNull() ){
        m_root->_size_set( IntegerSize( 20, 20 ) );

        ImageLabelImplementor *_impl = new ImageLabelImplementor( *this );
        m_root->_impl_init( SharedPtr<ControllerImplementor>( _impl ) );
      }    

    }

    ImageLabel::ImageLabel( const Image& img)
      :Controller(){

      if( !m_root.isNull() ){
        const auto &_img_size = img.getSize();

        m_root->_size_set( _img_size != IntegerSize(-1,-1) ? _img_size :  IntegerSize(20, 20 ) );
      
        ImageLabelImplementor *_impl = new ImageLabelImplementor( *this, img );
        m_root->_impl_init( SharedPtr<ControllerImplementor>( _impl ) );      
      }  
    }

    ImageLabel::ImageLabel( const Image& img, ImagePolicy policy )
      :Controller(){

      if( !m_root.isNull() ){
        const auto &_img_size = img.getSize();

        m_root->_size_set( _img_size != IntegerSize(-1,-1) ? _img_size :  IntegerSize(20, 20 ) );

        if( policy < ImageLabel::ImagePolicy_NoMovement 
          && policy > ImageLabel::ImagePolicy_LabelExpandToImageSize ){
          policy = ImageLabel::ImagePolicy_NoMovement ;
        }
            
        ImageLabelImplementor *_impl = new ImageLabelImplementor( *this, img );
        m_root->_impl_init( SharedPtr<ControllerImplementor>( _impl ) );      
      }  

    }

    ImageLabel::~ImageLabel(){

    }

    void ImageLabel::setImage( const Image& img ){
      try{
        if( !m_root.isNull() ){
          auto&& _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ImageLabelImplementor & _label_impl = dynamic_cast< ImageLabelImplementor &>(*_impl );
            _label_impl.m_originalImage = img;
            _label_impl.m_image = img;
            //
            if( _label_impl.m_imagePolicy == ImageLabel::ImagePolicy_ImageScaleToLabelSize ){
              _label_impl.m_image = _label_impl.m_originalImage;
              _label_impl.m_image.scale( m_root->_size_get() );
            }
            else if( _label_impl.m_imagePolicy == ImageLabel::ImagePolicy_LabelExpandToImageSize ){
              const auto &_image_size = _label_impl.m_image.getSize();
              if( _image_size.getWidth() > 0
                && _image_size.getHeight() > 0 ){
                  setSize( _image_size );
              }
            }

            //update
            update();
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      catch( const std::bad_cast& _ex ){
        _ex.what();
      }
    }

    Image ImageLabel::getImage() const{
      Image *_ret_img_p = Nullptr;
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ImageLabelImplementor & _label_impl = dynamic_cast< ImageLabelImplementor &>(*_impl );
            _ret_img_p = &_label_impl.m_image;
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      catch( const std::bad_cast& _ex ){
        _ex.what();
      }
      return _ret_img_p != Nullptr ? *_ret_img_p : Image();
    }

    void ImageLabel::setImagePolicy( ImagePolicy policy ){

      try{
        if( policy < ImageLabel::ImagePolicy_NoMovement 
          && policy > ImageLabel::ImagePolicy_LabelExpandToImageSize ){
          throw InnerIndexNotFoundException();
        }

        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ImageLabelImplementor & _label_impl = dynamic_cast< ImageLabelImplementor &>(*_impl );
            
            if( _label_impl.m_imagePolicy != policy ){

              if( policy == ImageLabel::ImagePolicy_ImageScaleToLabelSize ){
                _label_impl.m_image = _label_impl.m_originalImage;
                _label_impl.m_image.scale( m_root->_size_get() );
              }
              else if( policy == ImageLabel::ImagePolicy_LabelExpandToImageSize ){
                const auto &_image_size = _label_impl.m_image.getSize();
                if( _image_size.getWidth() > 0
                  && _image_size.getHeight() > 0 ){
                  setSize( _image_size );
                }
              }

            }
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      catch( const InnerIndexNotFoundException& _ex ){
        _ex.what();
      }
      catch( const std::bad_cast& _ex ){
        _ex.what();
      }
    }

    ImageLabel::ImagePolicy ImageLabel::getImagePolicy() const{
      ImageLabel::ImagePolicy _ret_policy = ImagePolicy_NoMovement;
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            ImageLabelImplementor & _label_impl = dynamic_cast< ImageLabelImplementor &>(*_impl );
            _ret_policy = static_cast<ImageLabel::ImagePolicy>(_label_impl.m_imagePolicy);
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      catch( const std::bad_cast& _ex ){
        _ex.what();
      }
      return _ret_policy;
    }


  }//namespace GUI
}//namespace Magna
