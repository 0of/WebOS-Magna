#ifndef LABEL_H
#define LABEL_H

#include "basegui_lib.h"

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"
#include "basedef/Trigger.h"
using namespace Magna::Core;

#include "render/RenderContants.h"
#include "render/ShadowAppearanceEffect.h"
#include "render/FillBrush.h"
using namespace Magna::Render;

#include "Controller.h"

namespace Magna{
  namespace GUI{
    
    class BASEGUI_LIB_EXPORT Label : public Controller{
      __Trigger public:
        TRIGGER_DEF(OnceTextChanged, const String&)

      __Constructor_Destructor public:
        Label();
        explicit Label( const String& text );
        explicit Label( const String& text,  TextAlignment );
        virtual ~Label();

      __Setter public:
        void setText( const String& text );
        void setTextFillBrush( const FillBrush& );
        void setVerticalTextSpacing( const uint32& );

        void setTextAlignment( TextAlignment alignment );
        void setTextEffect( const SharedPtr<AppearanceEffect>& );

      __Getter public:
        String getText() const;
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  LABEL_H  */