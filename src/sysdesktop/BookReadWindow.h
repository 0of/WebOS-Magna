#ifndef BOOKREADWINDOW_H
#define BOOKREADWINDOW_H

#include "basegui/Window.h"
#include "basegui/Button.h"
#include "basegui/LinearLayout.h"
#include "basegui/TextViewController.h"
#include "PDFViewerController.h"

using namespace Magna::GUI;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class BookReadWindow : public Window{
        public:
          BookReadWindow();
          virtual ~BookReadWindow();

        public:
          SharedPtr<TextViewController> m_textViewCtrl;
      };

    }
  }
}

#endif  /*  BOOKREADWINDOW_H  */