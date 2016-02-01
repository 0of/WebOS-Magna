#ifndef PDFVIEWERWINDOW_H
#define PDFVIEWERWINDOW_H

#include "basegui/Window.h"
using namespace Magna::GUI;

#include "PDFViewerController.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class PDFViewerWindow : public Window{
        public:
          PDFViewerWindow();
          PDFViewerWindow( const String& path );
          virtual ~PDFViewerWindow();
        public:
          SharedPtr<PDFViewerController> m_pdfViewer;
      };

    }
  }
}//namespace Magna

#endif  /*  PDFVIEWERWINDOW_H  */