#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include "basegui_lib.h"

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"
#include "basedef/Trigger.h"
using namespace Magna::Core;

#include "qt_glue_img/Image.h"
using namespace Magna::Glue;

#include "Controller.h"

namespace Magna{
  namespace GUI{
    
    class BASEGUI_LIB_EXPORT ImageLabel : public Controller{
      __Constants public:
        enum ImagePolicy{
          ImagePolicy_NoMovement,
          ImagePolicy_ImageScaleToLabelSize,
          ImagePolicy_LabelExpandToImageSize      
        };

      __Constructor_Destructor public:
        ImageLabel();
        explicit ImageLabel( const Image& );
        explicit ImageLabel( const Image& , ImagePolicy );
        virtual ~ImageLabel();

      __Setter public:
        void setImage( const Image&);
        void setImagePolicy( ImagePolicy );

      __Getter public:
        Image getImage() const;
        ImagePolicy getImagePolicy() const;
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  IMAGELABEL_H  */
