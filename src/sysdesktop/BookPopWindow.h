#ifndef BOOKPOPWINDOW_H
#define BOOKPOPWINDOW_H

#include "basegui/PopOutWindow.h"
#include "basegui/Button.h"
#include "basegui/TableLayout.h"
#include "basegui/TextViewController.h"
using namespace Magna::GUI;

#include "BookReadWindow.h"
#include "PDFViewerWindow.h"

#include "FileInfoController.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class BookPopWindow : public PopOutWindow{
        enum ReadType{
          ReadType_Invalid = 0,
          ReadType_TXT = 1,
          ReadType_PDF = 2
        };

        public:
          BookPopWindow();
          virtual ~BookPopWindow();

        private:
          void readyToRead( FileInfoController & );

        private:
          SharedPtr<BookReadWindow> m_bookReadWindow;
          SharedPtr<PDFViewerWindow> m_pdfReadWindow;
          Image m_bookIcon;
          Image m_pdfBookIcon;
          //SharedPtr<TextViewController> m_textViewCtrl;
      };

    }
  }
}
#endif  /*  BOOKPOPWINDOW_H  */