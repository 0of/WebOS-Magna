#ifndef VLCVIDEOCONTROLLER_H
#define VLCVIDEOCONTROLLER_H

#include "multimedia_lib.h"

#include "basedef/String.h"
using namespace Magna::Core;

#include "basegui/Controller.h"
using namespace Magna::GUI;

namespace Magna{
  namespace MultiMedia{

    class  MULTIMEDIA_LIB_EXPORT VLCVideoController : public Controller{
      public:
        VLCVideoController();
        explicit VLCVideoController( const String& );
        virtual ~VLCVideoController();

      public:
        void play();
        void pause();
        void stop();
        void setVideoSource( const String& );

      private:
        class QtWidgetControllerRoot;
        QtWidgetControllerRoot *m_qtwRoot;
    };
  }
}//namespace Magna

#endif  /*  VLCVIDEOCONTROLLER_H  */
