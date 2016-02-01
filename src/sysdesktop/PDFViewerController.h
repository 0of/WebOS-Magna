#ifndef PDFVIEWERCONTROLLER_H
#define PDFVIEWERCONTROLLER_H

#include "basegui/Button.h"
#include "basegui/ButtonGroup.h"
#include "basegui/Window_p.h"
#include "basegui/LinearLayout.h"
#include "basegui/ScrollableController.h"
using namespace Magna::GUI;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class PDFViewerController : public ScrollableController{
        public:
          PDFViewerController();
          explicit PDFViewerController( const String& );
          virtual ~PDFViewerController();

        public:
          void loadPDFDocument( const String& );
          void jumpToPageAt( uint32 );

          uint32 getPageNumbers() const;
      };

    }
  }
}//namespace Magna

#endif  /*  PDFVIEWERCONTROLLER_H  */