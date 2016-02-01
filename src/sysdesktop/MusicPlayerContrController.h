#ifndef MUSICPLAYERCONTRCONTROLLER_H
#define MUSICPLAYERCONTRCONTROLLER_H

#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include "glue_img/Image.h"
using namespace Magna::Glue;

#include "basegui/Controller.h"
#include "basegui/Button.h"
#include "basegui/LinearLayout.h"
#include "basegui/ButtonGroup.h"
using namespace Magna::GUI;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class VolumeAvgAdjustController : public Controller{
        public:
          VolumeAvgAdjustController();
          virtual ~VolumeAvgAdjustController();
      };

      class MusicPlayerContrController : public Controller{
      public:
        MusicPlayerContrController( uint32 width );
        virtual ~MusicPlayerContrController();

        public:
          SharedPtr<Button> m_startPauseButton;
          SharedPtr<Button> m_stopButton;

          SharedPtr<Button> m_playPreButton;
          SharedPtr<Button> m_playNextButton;

          SharedPtr<VolumeAvgAdjustController> m_adjustCtrl;
      };
    }
  }
}//namespace Magna

#endif  /*  MUSICPLAYERCONTRCONTROLLER_H  */