#include "PDFViewerWindow.h"

#include "DesktopWindow.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      PDFViewerWindow::PDFViewerWindow()
        :Window()
        ,m_pdfViewer( new PDFViewerController ){

        //init property
        Image _icon = Image( DesktopWindow::getDesktopResDir() + L"PDF-Reader-icon.png" );
        setWindowIcon( _icon );
        setWindowTitle( L"Magna ¼òÂªµÄPDFÔÄ¶ÁÆ÷");

        LinearLayout *layout = new LinearLayout;
        layout ->addController(m_pdfViewer);

        setCenterLayout(layout);

        setSize( 800, 600 );
      }

      PDFViewerWindow::PDFViewerWindow( const String& path )  
        :Window()
        ,m_pdfViewer( new PDFViewerController( path ) ){

        //init property
        Image _icon = Image( DesktopWindow::getDesktopResDir() + L"PDF-Reader-icon.png" );
        setWindowIcon( _icon );
        setWindowTitle( L"Magna ¼òÂªµÄPDFÔÄ¶ÁÆ÷");

        LinearLayout *layout = new LinearLayout;
        layout ->addController(m_pdfViewer);

        setCenterLayout(layout);

        setSize( 800, 600 );
      }

      PDFViewerWindow::~PDFViewerWindow(){

      }

    }
  }
}

