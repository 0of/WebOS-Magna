#ifndef IMAGELABELIMPLEMENTOR_H
#define IMAGELABELIMPLEMENTOR_H

#include "basedef/RectRegion.h"
using namespace Magna::Core;

#include "qt_glue_img/Image.h"
using namespace Magna::Glue;

#include "ControllerImplementor.h"

namespace Magna{
  namespace GUI{

    class ImageLabel;
    class ImageLabelImplementor : public ControllerImplementor{
      __Constructor_Destructor public:
        explicit ImageLabelImplementor( ImageLabel & bindingLabel );
        explicit ImageLabelImplementor( ImageLabel & bindingLabel, const Image& img);
        virtual ~ImageLabelImplementor();

      __Override_Methods public:
        virtual void rendering( RenderingEventArgs& eventArgs );
        virtual void resized( ResizedEventArgs&eventArgs);

      public:
        Image m_originalImage;
        Image m_image;
        uint32 m_imagePolicy;

        ImageLabel &m_bindingLabel;
    };
  }//namespace GUI
}//namespace Magna

#endif  /*  IMAGELABELIMPLEMENTOR_H  */
