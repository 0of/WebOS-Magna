#include "FrequentUsedAppPopWindow.h"

#include "DesktopWindow.h"
#include "application/Application.h"
using namespace Magna::Application;

#include "DesktopWindow.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      AppInfoController::AppInfoController( const FrequentUsedAppData& d)
        :Controller()
        ,m_data( d )
        ,m_appEntryButton( new Button(L"") )
        ,m_appNameLabel( new Label( d.m_appName ) ){

        m_appEntryButton->setIcon( d.m_appIcon );
        m_appEntryButton->setSize( IntegerSize( 64, 64) );
        m_appNameLabel->setSize( IntegerSize( 64, 36 ) );

        LinearLayout *layout = new LinearLayout( LinearLayout::LinearLayoutOrientation_Vertical );

        layout->addController( m_appEntryButton );
        layout->addController( m_appNameLabel );

        setSize( IntegerSize( 64, 100 ) );
        setLayout(layout);
      }

      AppInfoController::~AppInfoController(){

      }

      FrequentUsedAppPopWindow::FrequentUsedAppPopWindow()
        :PopOutWindow(Window::WindowAttribute_NoWindowFrame)
        ,m_centerLayout()
        ,m_appButtons()
        ,m_appCommonIcon( DesktopWindow::getDesktopResDir() + L"app_demo_ex.png"){
        //m_centerLayout->setAutoDeployBreakPolicy(  TableLayout::AutoDeployBreakPolicy_HorizontalBreak );

        //init data , read from file
        //this for demo
        /*
        FrequentUsedAppData _data( L"Demo"
          , L"F:/projects/Qt_Project/[script_diagram]_WebOS/AppTest/Debug/AppTest.dll"
          , Image( DesktopWindow::getDesktopResDir() + L"app_demo.png" ));
        AppInfoController *ctrl = new AppInfoController( _data );
        std::vector<SharedPtr<Controller> > _pre;
        _pre.push_back( ctrl );
        m_appButtons.push_back( ctrl );

        TableLayout *layout = new TableLayout;
        setCenterLayout( layout );

        //m_centerLayout = 
        layout->addAutoDeployControllers( _pre );
        

        auto &_userRect = DesktopWindow::getUserRectRegion();
        uint32 _take_width = (_userRect.getWidth() >> 1);
        uint32 _take_height = (_userRect.getHeight() >> 1);

        auto &_desktop_rect = DesktopWindow::getDesktopRectRegion();
        auto &_desktop_top_left = _desktop_rect.getTopLeftCoord();
        auto &_size = _desktop_rect.getSize();
        //top 30px bottom 30px
        //left 20px right 20px
        IntegerDyadCoordinate _top_left ( _desktop_top_left.getX() + (_size.getWidth() >> 1 ) - ( _take_width >> 1 ) 
          , _desktop_top_left.getY() +  (_size.getHeight() >> 1 ) - ( _take_height >> 1 )  );

        m_wndRoot->_pos_set( _top_left );
        m_wndRoot->_size_set( IntegerSize( _take_width,_take_height ));
        */

        auto &_userRect = DesktopWindow::getUserRectRegion();
        uint32 _take_width = (_userRect.getWidth() - 80);
        uint32 _take_height = (_userRect.getHeight()  - 100 );

        auto &_desktop_rect = DesktopWindow::getDesktopRectRegion();
        auto &_desktop_top_left = _desktop_rect.getTopLeftCoord();
        auto &_size = _desktop_rect.getSize();
        //top 30px bottom 30px
        //left 20px right 20px
        IntegerDyadCoordinate _top_left ( _desktop_top_left.getX() + (_size.getWidth() >> 1 ) - ( _take_width >> 1 ) 
          , _desktop_top_left.getY() +  (_size.getHeight() >> 1 ) - ( _take_height >> 1 )  );

        m_wndRoot->_pos_set( _top_left );
        m_wndRoot->_size_set( IntegerSize( _take_width,_take_height ));

      //  FrequentUsedAppData _data( L"Demo"
      //    , L"F:/projects/Qt_Project/[script_diagram]_WebOS/AppTest/Debug/AppTest.dll"
      //    , Image( DesktopWindow::getDesktopResDir() + L"app_demo.png" ));
      //  AppInfoController *ctrl = new AppInfoController( _data );

        m_appCommonIcon.scale( 84, 112, Image::ImageTransformationMode_Smooth );

        String _list[] = {
          L"AppTest_2"
        };

        TableLayout *layout = new TableLayout;
        layout->setHorizontalSpacing( 18  );
        layout->setLayoutOffset( 24, 24 );

        std::vector< SharedPtr<Controller> > _ctrls;

        for( auto _iter = 0; _iter != (sizeof( _list ) / sizeof( _list[0] )) ; ++_iter ){
          FileInfoController*each = new FileInfoController( m_appCommonIcon, _list[_iter], _iter );

          _ctrls.push_back(each);
          each->OnceAboutToEnter.connectAction( this, &FrequentUsedAppPopWindow::processAboutToRun );
        }
        layout->addAutoDeployControllers(_ctrls);
        
        setCenterLayout( layout );

        setBackgroundFillBrush( FillBrush( DesktopWindow::getPopWindowBG() ) );

        setBorderStyle( GUIConstants::BorderStyle_None );    
      }

      void FrequentUsedAppPopWindow::processAboutToRun( const String& path){
        MagnaApplication::introducesApplication( path );
      }


      FrequentUsedAppPopWindow::~FrequentUsedAppPopWindow(){

      }

      void FrequentUsedAppPopWindow::addFrequentUsedApp( const FrequentUsedAppData& d){

        bool _found_existed = false;
        for( auto _iter = m_appButtons.begin(); _iter != m_appButtons.end(); ++_iter ){

          if( !_iter->isNull() ){
            if( ((*_iter)->m_data).m_appPath == d.m_appPath ){
              _found_existed = !false;
              break;
            }
          }
        }

        if( !_found_existed ){
          AppInfoController *ctrl =new AppInfoController( d );
          m_centerLayout->addAutoDeployController( ctrl );
        }

      }


    }
  }
}