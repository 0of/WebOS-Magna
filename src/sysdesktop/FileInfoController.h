#ifndef FILEINFOCONTROLLER_H
#define FILEINFOCONTROLLER_H

#include "render/ShadowAppearanceEffect.h"
#include "render/FillBrush.h"
#include "render/Font.h"
using namespace Magna::Render;

#include "basegui/Button.h"
#include "basegui/LinearLayout.h"
#include "basegui/WebFrameController.h"
#include "basegui/Label.h"
using namespace Magna::GUI;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class FileInfoController : public Controller{
      public:
        TRIGGER_DEF(OnceAboutToEnter, const String&)
          TRIGGER_DEF(OnceAboutToEnterByInfo, FileInfoController &)
      public:
        explicit FileInfoController( const Image& icon, const String& path, uint32 s, uint32 type = 0 );
        virtual ~FileInfoController();

      private:
        void processButtonClicked();

      public:
        SharedPtr<Button> m_fileEntry;
        SharedPtr<Label> m_nameLabel;
        String m_path;
        uint32 m_seq;
        uint32 m_type;

      };

      
    }
  }
}
#endif  /*  FILEINFOCONTROLLER_H  */