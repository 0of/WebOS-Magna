#include "MusicPlayerContrController.h"

#include "render/LinearGradient.h"
using namespace Magna::GUI;

#include "basegui/ControllerImplementor.h"
#include "basegui/Controller_p.h"
#include "basegui/AbsoluteLayout.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class IconSet{
      public:
        static IconSet shared_icon_set;

        static const String getAudioPlayResDir(){
          static String _dir = L"/res/sysdesktop/audioplayer/";
          return _dir;
        }

        IconSet()
          :m_maxVol( getAudioPlayResDir() + L"Volume-high.png" )
          ,m_avgVol( getAudioPlayResDir() + L"Volume-medium.png" )
          ,m_minVol( getAudioPlayResDir() + L"Volume-low.png" )
          ,m_muted( getAudioPlayResDir() + L"Volume-mute.png"  )
          ,m_playIcon( getAudioPlayResDir() + L"play.png"  )
          ,m_pauseIcon( getAudioPlayResDir() + L"pause.png"  )
          ,m_stopIcon( getAudioPlayResDir() + L"3.png" )
          ,m_nextIcon(  getAudioPlayResDir() + L"1.png" )
          ,m_preIcon( getAudioPlayResDir() + L"2.png"){

            m_maxVol.scale( 48, 48 );
            m_avgVol.scale( 48, 48 );
            m_minVol.scale( 48, 48 );
            m_muted.scale( 48, 48 );
        }

        ~IconSet(){

        }

        Image m_maxVol;
        Image m_avgVol;
        Image m_minVol;
        Image m_muted;

        Image m_playIcon;
        Image m_pauseIcon;
        Image m_stopIcon;
        Image m_nextIcon;
        Image m_preIcon;
      };

      IconSet IconSet::shared_icon_set = IconSet();

      class VolumeAvgAdjustControllerImpl : public ControllerImplementor{
      public:
        VolumeAvgAdjustControllerImpl( VolumeAvgAdjustController& binding );
        virtual ~VolumeAvgAdjustControllerImpl();

        virtual void mousePressed( MouseEventArgs& event );
        virtual void mouseReleased( MouseEventArgs& event );

        virtual void rendering( RenderingEventArgs& eventArgs );

      public:

        //not a proper way
        uint32 m_state;
        IntegerDyadCoordinate m_pressedPos;
        Image m_icon;

        VolumeAvgAdjustController& m_binding; 
      };      

      VolumeAvgAdjustControllerImpl::VolumeAvgAdjustControllerImpl( VolumeAvgAdjustController& binding )
        :ControllerImplementor()
        ,m_pressedPos()
        ,m_state( 1 )
        ,m_icon( IconSet::shared_icon_set.m_avgVol )
        ,m_binding( binding ){

      }

      VolumeAvgAdjustControllerImpl::~VolumeAvgAdjustControllerImpl(){

      }
      
       void VolumeAvgAdjustControllerImpl::mousePressed( MouseEventArgs& event ){
         if( event.isAccepted() ){
           m_pressedPos = event.getTriggeredCoord();
         }
       }

       void VolumeAvgAdjustControllerImpl::mouseReleased( MouseEventArgs& event ){
         if( event.isAccepted() ){
           uint32 _state = 0;
           Image _icon;
           if( m_pressedPos.getX() > 40 ){
             _state = 0;
             _icon = IconSet::shared_icon_set.m_maxVol;
           }
           else if( m_pressedPos.getX() <= 40 && m_pressedPos.getX() > 26 ){
             _state = 1;
             _icon = IconSet::shared_icon_set.m_avgVol; 
           }
           else if( m_pressedPos.getX() <= 26 && m_pressedPos.getX() > 14 ){
             _state = 2;
             _icon = IconSet::shared_icon_set.m_minVol;
           }
           else{
             _state = 3;
              _icon = IconSet::shared_icon_set.m_muted;
           }

           if( m_state != _state ){
             m_icon = _icon;
             m_binding.update();
           }
         }
       }

       void VolumeAvgAdjustControllerImpl::rendering( RenderingEventArgs& eventArgs ){
         if( eventArgs.isAccepted() ){
           auto *_2d_manager = eventArgs.getRenderManager2D();
           if( _2d_manager != Nullptr ){
             Canvas2DDrawer _drawer;
             if( _2d_manager->retrieveDrawer( _drawer ) != false ){
               _drawer.drawImage( IntegerDyadCoordinate( 0, 0 ), m_icon );

               _2d_manager->pullbackDrawer( _drawer );
             }
           }
         }
       }


      VolumeAvgAdjustController::VolumeAvgAdjustController()
        :Controller(){

        VolumeAvgAdjustControllerImpl *impl = new VolumeAvgAdjustControllerImpl( *this );
        m_root->_impl_init( impl );

        //size fixed
        m_root->_size_set( IntegerSize( 48, 48 ) );
      }

      VolumeAvgAdjustController::~VolumeAvgAdjustController(){

      }

      //////////////////////////////////////////////////////////////////////////

      MusicPlayerContrController::MusicPlayerContrController( uint32 width )
        :Controller()
        ,m_startPauseButton( new Button(L"") )
        ,m_stopButton( new Button(L"") )
        ,m_playPreButton( new Button(L"") )
        ,m_playNextButton( new Button( L"") )
        ,m_adjustCtrl( new VolumeAvgAdjustController() ){

        AbsoluteLayout *layout = new AbsoluteLayout;

        //default height  160
        setSize( IntegerSize( width , 160 ) );

        m_startPauseButton->setSize( IntegerSize( 128, 128 ) );
        m_stopButton->setSize( IntegerSize( 64, 64 ) );
        m_playPreButton->setSize( IntegerSize( 64, 64 ) );
        m_playNextButton->setSize( IntegerSize( 64, 64 ) );

        m_startPauseButton->setPressedBrush( FillBrush() );
        m_stopButton->setPressedBrush( FillBrush() );
        m_playPreButton->setPressedBrush( FillBrush() );
        m_playNextButton->setPressedBrush( FillBrush() );

        m_startPauseButton->setIcon( IconSet::shared_icon_set.m_playIcon );
        m_startPauseButton->setPressedIcon( IconSet::shared_icon_set.m_pauseIcon );

        m_stopButton->setIcon( IconSet::shared_icon_set.m_stopIcon );
        m_playPreButton->setIcon( IconSet::shared_icon_set.m_preIcon );
        m_playNextButton->setIcon( IconSet::shared_icon_set.m_nextIcon );

        //deploy
        m_stopButton->setPos( IntegerDyadCoordinate( 6, 90 ) );
        m_startPauseButton->setPos( IntegerDyadCoordinate( 48, 16 ) );
        m_playPreButton->setPos( IntegerDyadCoordinate( 188 , 36 ) );
        m_playNextButton->setPos( IntegerDyadCoordinate( 152, 86 ) );

        m_adjustCtrl->setPos( IntegerDyadCoordinate( width - 52, 56 ) );

        layout->addController( m_stopButton );
        layout->addController( m_startPauseButton );
        layout->addController( m_playPreButton );
        layout->addController( m_playNextButton );
        layout->addController( m_adjustCtrl );

        setLayout(layout);

      }

      MusicPlayerContrController::~MusicPlayerContrController(){

      }
    }
  }
}

