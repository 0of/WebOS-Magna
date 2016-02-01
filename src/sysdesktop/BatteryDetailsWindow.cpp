#include "BatteryDetailsWindow.h"

#include "basedef/String.h"
using namespace Magna::Core;

#include "basegui/Label.h"
#include "basegui/ScrollableController.h"
#include "basegui/ImageLabel.h"
#include "basegui/LinearLayout.h"
using namespace Magna::GUI;

#include "DesktopWindow.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

       Image BatteryDetailsWindow::shared_full_status_icon = Image( DesktopWindow::getDesktopResDir() + L"plug_full.png");
       Image BatteryDetailsWindow::shared_charing_status_icon = Image( DesktopWindow::getDesktopResDir() + L"in_charge.png");
       Image BatteryDetailsWindow::shared_low_status_icon = Image( DesktopWindow::getDesktopResDir() + L"nearly_run_out.png");
       Image BatteryDetailsWindow::shared_medium_status_icon = Image( DesktopWindow::getDesktopResDir() + L"medium.png");
       Image BatteryDetailsWindow::shared_high_status_icon = Image( DesktopWindow::getDesktopResDir() + L"full.png");

      BatteryDetailsWindow::BatteryDetailsWindow()
        :Window()
        ,m_currentBatteryInfo( SystemInfo::getSystemInfo().getBatteryDeviceInfo() )
        ,m_infoLabel()
        ,m_currentSymb()
        ,m_currentStatusIcon(){
      
          OutStringStream _text_outer;
          _text_outer << L"电源状态：" << m_currentBatteryInfo.toBatteryStatusString()
            << L"\n电池状态：" << m_currentBatteryInfo.toBatteryPowerStatusString()
            << L"\n是否在充电："<< (m_currentBatteryInfo.isCharging() ? L"是" : L"否" )
            << L"\n是否在存在电池："<< (m_currentBatteryInfo.hasBattery() ? L"是" : L"无" )
            << L"\n剩余电量百分比："<< ( m_currentBatteryInfo.getBatteryPercentage() ) << L"%";

          //get the time
          uint32 _left_hour = m_currentBatteryInfo.getLeftUseTimeSec() / 3600 ;
          uint32 _left_min = (m_currentBatteryInfo.getLeftUseTimeSec() % 3600) / 60;
          if( _left_hour != 0 ){
            _text_outer << L"\n剩余时间：0时" << _left_min << L"分";
          }
          else{
            _text_outer << L"\n剩余时间：" << _left_hour << L"时" << _left_min << L"分";
          }

          m_infoLabel = new Label( _text_outer.str() );
          m_infoLabel->setSize( IntegerSize(186, 156 ) );
          m_infoLabel->setVerticalTextSpacing( 10 );
          Font f;
          f.setFontSize( 13 );
          m_infoLabel->setFont( f );

          if( m_currentBatteryInfo.isCharging() ){
            m_currentStatusIcon = shared_charing_status_icon;
          }
          else{
            if( m_currentBatteryInfo.getBatteryStatus() == BatteryDeviceInfo::BatteryStatus_AC ){
              m_currentStatusIcon = shared_full_status_icon;
            }
            else{
              switch( m_currentBatteryInfo.getBatteryPowerStatus() ){
                case BatteryDeviceInfo::BatteryPowerStatus_Low:
                  m_currentStatusIcon = shared_low_status_icon;
                  break;

                case BatteryDeviceInfo::BatteryPowerStatus_Medium:
                  m_currentStatusIcon = shared_medium_status_icon;
                  break;

                case BatteryDeviceInfo::BatteryPowerStatus_High:
                  m_currentStatusIcon = shared_high_status_icon;
                  break;

                default:
                  m_currentStatusIcon = shared_medium_status_icon;
                  break;
              }
            }
          }
          

          m_currentSymb = new ImageLabel( m_currentStatusIcon, ImageLabel::ImagePolicy_LabelExpandToImageSize );

          LinearLayout *layout = new LinearLayout;
          layout->addController( m_currentSymb );
          layout->addController( m_infoLabel );
          layout->setLayoutOffset( 6, 20 );


          auto &_desktop_rect = DesktopWindow::getDesktopRectRegion();
          auto &_desktop_top_left = _desktop_rect.getTopLeftCoord();
          auto &_size = _desktop_rect.getSize();
          //top 30px bottom 30px
          //left 20px right 20px
          IntegerDyadCoordinate _top_left ( _desktop_top_left.getX() + (_size.getWidth() >> 1 ) - ( 338 >> 1 ) 
            , _desktop_top_left.getY() +  (_size.getHeight() >> 1 ) - ( 236 >> 1 )  );

          setSize( IntegerSize( 318, 236 ) );
          setPos( _top_left );
          setCenterLayout( layout );
          setWindowTitle( L"系统电池信息" );
          setWindowIcon( Image( DesktopWindow::getDesktopResDir() + L"battery_config_wicon.png" ) );
      }

      BatteryDetailsWindow::~BatteryDetailsWindow(){

      }

    }
  }
}