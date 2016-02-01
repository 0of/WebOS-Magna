#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "basedef/Trigger.h"
using namespace Magna::Core;

#include "Controller.h"

#include "ToolBarElement.h"

namespace Magna{
  namespace GUI{

    class ToolBar : public Controller{
      __Trigger public:
        TRIGGER_DEF(OnceElementTriggeredWithIndex, uint32 )
        TRIGGER_DEF(OnceElementTriggered, const ToolBarElement & )

      __Constants public:
        enum TextHangingPolicy{
          TextHangingPolicy_NoText,
          TextHangingPolicy_Left,
          TextHangingPolicy_Right,
          TextHangingPolicy_Top,
          TextHangingPolicy_Bottom
        };

        enum ToolBarOrientation{
          ToolBarOrientation_Horizontal,
          ToolBarOrientation_Vertical
        };

      __Constructor_Destructor public:
        ToolBar();
        virtual ~ToolBar();

      __Setter public:
        void setTextHangingPolicy( TextHangingPolicy );
        void setOrientation( ToolBarOrientation );
        void setSpacing( uint32 );

      __Getter public:
        TextHangingPolicy getTextHangingPolicy() const;
        uint32 getSpacing();
        ToolBarOrientation getOrientation() const;
        std::vector<ToolBarElement> getElements() const;

      public:
        void addElement( const ToolBarElement& elment );
        void insertElement( const ToolBarElement& elment,  uint32 index );
        void clearElement();
    };

  }//namespace GUI
}//namespace Magna

#endif  /*TOOLBAR_H  */