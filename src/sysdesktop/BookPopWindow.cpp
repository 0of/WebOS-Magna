#include "BookPopWindow.h"

#include "basegui/Window_p.h"
#include "basegui/LinearLayout.h"
using namespace Magna::GUI;

#include "DesktopWindow.h"
#include "basegui/Label.h"

#include "glue/FileDir.h"

#include "DesktopApplication.h"
#include "DesktopWindow.h"

#include "application/WindowIntroducer.h"
using namespace Magna::Application;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      BookPopWindow::BookPopWindow()
        :PopOutWindow( WindowAttribute_NoWindowFrame )
        ,m_bookReadWindow( new BookReadWindow )
        ,m_bookIcon( DesktopWindow::getDesktopResDir() + L"TXT-icon.png")
        ,m_pdfBookIcon( DesktopWindow::getDesktopResDir() + L"PDF-icon.png" )
        ,m_pdfReadWindow( new PDFViewerWindow ){

        m_bookIcon.scale( 84, 112, Image::ImageTransformationMode_Smooth );
        m_pdfBookIcon.scale( 84, 112, Image::ImageTransformationMode_Smooth );
        

        auto &_userRect = DesktopWindow::getUserRectRegion();
        uint32 _take_width = (_userRect.getWidth()  - 80);
        uint32 _take_height = (_userRect.getHeight()  - 100  );

        auto &_desktop_rect = DesktopWindow::getDesktopRectRegion();
        auto &_desktop_top_left = _desktop_rect.getTopLeftCoord();
        auto &_size = _desktop_rect.getSize();
        //top 30px bottom 30px
        //left 20px right 20px
        IntegerDyadCoordinate _top_left ( _desktop_top_left.getX() + (_size.getWidth() >> 1 ) - ( _take_width >> 1 ) 
          , _desktop_top_left.getY() +  (_size.getHeight() >> 1 ) - ( _take_height >> 1 )  );

        m_wndRoot->_pos_set( _top_left );
        m_wndRoot->_size_set( IntegerSize( _take_width,_take_height ));

        auto &_filePaths = FileDir::getAbsPath( DesktopApplication::shared_usr_dir + L"book/", L"*.txt;*.pdf" );

        TableLayout *layout = new TableLayout;
        layout->setHorizontalSpacing( 18 );
        layout->setLayoutOffset( 24, 24 );
        std::vector< SharedPtr<Controller > > _ctrls;

        for( auto _iter = 0; _iter != _filePaths.size(); ++_iter ){
          //check whether PDF or TXT
          const auto &_each_path = _filePaths.at( _iter );
          auto _find = _each_path.find_last_of( L'.');
          //std::tol
          auto &_ext_name = _each_path.substr( _find );
          auto _found_pos = _ext_name.find( L"pdf" );
          FileInfoController*each = Nullptr;
          if( _found_pos != String::npos ){
            each = new FileInfoController( m_pdfBookIcon, _filePaths.at(_iter), _iter, BookPopWindow::ReadType_PDF );
          }
          else{
            each = new FileInfoController( m_bookIcon, _filePaths.at(_iter), _iter, BookPopWindow::ReadType_TXT );
          }
          
          _ctrls.push_back( each );
          //layout->addController( each );
          each->OnceAboutToEnterByInfo.connectAction( this, &BookPopWindow::readyToRead );
        }

        layout->addAutoDeployControllers( _ctrls );
        setCenterLayout(layout);

        setBackgroundFillBrush( FillBrush( DesktopWindow::getPopWindowBG() ) );
        setBorderStyle( GUIConstants::BorderStyle_None );
      }

      BookPopWindow::~BookPopWindow(){

      }

      void BookPopWindow::readyToRead( FileInfoController & info ){
        if( info.m_type == BookPopWindow::ReadType_TXT ){
          if( !m_bookReadWindow->isRunning() ){
            WindowIntroducer::introduceWindow(*DesktopApplication::pInstance, m_bookReadWindow);    
          }
          if( !m_bookReadWindow->m_textViewCtrl.isNull() ){
            m_bookReadWindow->m_textViewCtrl->loadFromFile( info.m_path );
          }      
        }
        else if(  info.m_type == BookPopWindow::ReadType_PDF ){
          if( !m_bookReadWindow->isRunning() ){
            WindowIntroducer::introduceWindow(*DesktopApplication::pInstance, m_pdfReadWindow);    
          }
          if( !m_pdfReadWindow->m_pdfViewer.isNull() ){
            m_pdfReadWindow->m_pdfViewer->loadPDFDocument( info.m_path );
          }
          
        }
        
      }

    }
  }
}
