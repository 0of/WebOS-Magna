#include "ImageLabelImplementor.h"

#include "ImageLabel.h"

namespace Magna{
  namespace GUI{
    
    ImageLabelImplementor::ImageLabelImplementor( ImageLabel & bindingLabel )
      :ControllerImplementor()
      ,m_bindingLabel( bindingLabel )
      ,m_image()
      ,m_originalImage()
      ,m_imagePolicy( ImageLabel::ImagePolicy_NoMovement ){

    }

    ImageLabelImplementor::ImageLabelImplementor( ImageLabel & bindingLabel, const Image& img )
      :ControllerImplementor()
      ,m_bindingLabel( bindingLabel )
      ,m_image(img)
      ,m_imagePolicy( ImageLabel::ImagePolicy_NoMovement )
      ,m_originalImage(img){

      
    }

    ImageLabelImplementor::~ImageLabelImplementor(){

    }

    void ImageLabelImplementor::rendering( RenderingEventArgs& eventArgs ){
      if( eventArgs.isAccepted() ){
        auto *_2d_manager = eventArgs.getRenderManager2D();
        if( _2d_manager != Nullptr ){
          Canvas2DDrawer _drawer;
          if( _2d_manager->retrieveDrawer( _drawer ) != false ){
            //normal state
            _drawer.clearRectRegion( eventArgs.getRenderingRectRegion() );

            _drawer.drawImage( IntegerDyadCoordinate( 0, 0),  m_image );

            _2d_manager->pullbackDrawer( _drawer );
          }
        }
      }
    }

    void ImageLabelImplementor::resized( ResizedEventArgs&eventArgs){

      if( eventArgs.isAccepted() ){

        if( m_imagePolicy == ImageLabel::ImagePolicy_ImageScaleToLabelSize ){
          m_image = m_originalImage;
          m_image.scale( eventArgs.getNewSize() );
        }
      
      }
    }

  }//namespace GUI
}//namespace Magna