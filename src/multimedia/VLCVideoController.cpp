#include "VLCVideoController.h"

#include "basegui/Controller_p.h"
#include "basegui/QtWidgetInitializer.h"
#include "basegui/WindowAccessor.h"

/*
#include "WidgetVideo.h"
#include "Media.h"
#include "MediaPlayer.h"
#include "Instance.h"
*/
#include "VLCVideoWidgetDelegator.h"

#include "QtWidgetInitReceptionist.h"

namespace Magna{
  namespace MultiMedia{

    class QtWidgetControllerImplementor : public ControllerImplementor
      ,public QtWidgetInitializer{
      public:
        QtWidgetControllerImplementor(VLCVideoController &);
        virtual~QtWidgetControllerImplementor();

      public:
        virtual void actInitialization( QtWidgetInitReceptionist & ) ;

      public:
        /*
        VlcInstance *m_instance;
        VlcMediaPlayer *m_player;
        VlcMedia *m_currentMedia;
        VlcWidgetVideo *m_videoWidget;
        */
        //VLCVideoWidgetDelegator m_widgetDelegator;
        VLCVideoWidgetDelegator *m_widgetDelegator;
        VLCVideoController &m_binding;

        QString m_srcPath;
        SpinMutex m_threadLock;
    };

    QtWidgetControllerImplementor::QtWidgetControllerImplementor(VLCVideoController &binding)
      :ControllerImplementor()
      ,QtWidgetInitializer()
      /*
      ,m_instance( Nullptr )
      ,m_player( Nullptr )
      ,m_currentMedia( Nullptr )
      ,m_videoWidget( Nullptr )
      */
      ,m_widgetDelegator( Nullptr )
      ,m_binding(binding)
      ,m_srcPath()
      ,m_threadLock(){

    }

    QtWidgetControllerImplementor::~QtWidgetControllerImplementor(){
      
    }


    void QtWidgetControllerImplementor::actInitialization( QtWidgetInitReceptionist & rec) {
      m_threadLock.acquires();
      /*
      m_instance = new VlcInstance( QStringList() );
      m_player = new VlcMediaPlayer( m_instance );

#ifdef _MSC_VER
      QString _URL = QString::fromUtf16( reinterpret_cast<const ushort *>( m_srcPath.c_str() ), m_srcPath.size() ); 
#else
      QString _URL = QString::fromStdWString( _current_URL );
#endif    
      m_currentMedia = new VlcMedia( _URL, !false, m_instance );

      m_player->open( m_currentMedia );
      m_videoWidget = new VlcWidgetVideo(  m_player );
      */
      if( !m_srcPath.isEmpty() ){

        m_widgetDelegator = new VLCVideoWidgetDelegator(m_srcPath);
        //m_widgetDelegator.loadVideoFromFile(_file_path);
      }
      else{
        m_widgetDelegator = new VLCVideoWidgetDelegator;
      }

      auto *_webkitview_widget = rec.queryBaseWidget( "magna-webkitview" );
      //m_widgetDelegator.attachVLCRenderContext( _webkitview_widget );
      m_widgetDelegator->attachVLCRenderContext( _webkitview_widget );

      //auto *_widget = m_widgetDelegator.getWidget();
      auto *_widget = m_widgetDelegator->getWidget();
      
      if( _widget != Nullptr ){

        const auto&_wrapper_size = m_binding.getSize();
        _widget->resize( _wrapper_size.getWidth(), _wrapper_size.getHeight() );

        auto *_layout = m_binding.getParentLayout();
        IntegerDyadCoordinate _to_wnd_pos;
        if( _layout != Nullptr ){
          _to_wnd_pos = _layout->toCoordOnManipulateDevice( m_binding.getPos() );
        }
        _widget->move( _to_wnd_pos.getX(), _to_wnd_pos.getY() );

        _widget->raise ();
        //m_widget->activateWindow();
        _widget->show();

        //m_widgetDelegator->play();
      }

      m_threadLock.releases();
    }

    class VLCVideoController::QtWidgetControllerRoot : public Controller::ControllerRoot{
      public:
        QtWidgetControllerRoot( VLCVideoController & );
        virtual ~QtWidgetControllerRoot();

      public:
        virtual void onLayoutDeployed();
        virtual void onWindowBound();
        //virtual void onWindowUnbound();

      private:
        void processAttachedWindowShow();
        void processAttachedWindowHide();
        void processAttachedWindowClose();

      public:
        SharedPtr<QtWidgetControllerImplementor> m_qtwImplementor;
    };

    VLCVideoController::QtWidgetControllerRoot::QtWidgetControllerRoot( VLCVideoController & binding)
      :ControllerRoot( binding )
      ,m_qtwImplementor( new QtWidgetControllerImplementor( binding ) ){

      _impl_init( m_qtwImplementor );

    }

    VLCVideoController::QtWidgetControllerRoot::~QtWidgetControllerRoot(){

    }

    void VLCVideoController::QtWidgetControllerRoot::onLayoutDeployed(){

      if( m_parentLayout != Nullptr && !m_qtwImplementor.isNull() && m_qtwImplementor->m_widgetDelegator != Nullptr ){

        auto *_widget = m_qtwImplementor->m_widgetDelegator->getWidget();
        if( _widget != Nullptr ){
          const auto &_wrapper_size = _size_get();
          _widget->resize( _wrapper_size.getWidth(), _wrapper_size.getHeight() );
    
          const auto &_to_wnd_pos = m_parentLayout->toCoordOnManipulateDevice( _pos_get() );
          _widget->move( _to_wnd_pos.getX(), _to_wnd_pos.getY() );
        }
      }
    }

    void VLCVideoController::QtWidgetControllerRoot::onWindowBound(){

      if( m_parentLayout != Nullptr && !m_qtwImplementor.isNull() ){

        auto *_wnd = m_parentLayout->getAttachedWindow();
        if( _wnd != Nullptr ){
          auto &&_wnd_root = WindowAccessor::getRoot( _wnd );
          if( !_wnd_root.isNull() && _wnd_root->m_int_runtimeId != 0 
            && _wnd_root->m_requester != Nullptr ){

            //bind to attached window
            _wnd->OnceHidden.connectAction( this
                , &VLCVideoController::QtWidgetControllerRoot::processAttachedWindowShow );

            _wnd->OnceHidden.connectAction( this
              , &VLCVideoController::QtWidgetControllerRoot::processAttachedWindowHide );

            _wnd->OnceClosed.connectAction( this
              , &VLCVideoController::QtWidgetControllerRoot::processAttachedWindowClose );

            _wnd_root->m_requester->requestQtWidgetInit( m_qtwImplementor.operator->() );
          }
        }
      }
    }
    //void onWindowUnbound();

    void VLCVideoController::QtWidgetControllerRoot::processAttachedWindowShow(){
      if( !m_qtwImplementor.isNull() ){
        if(  m_qtwImplementor->m_widgetDelegator != Nullptr ){
          auto *_widget = m_qtwImplementor->m_widgetDelegator->getWidget();
          if(  _widget != Nullptr){
            _widget->show();
          }    
        }
        //auto *_widget = m_qtwImplementor->m_widgetDelegator.getWidget();
        //if( _widget != Nullptr ){
        //  _widget->show();
        //}
      }
    }

    void VLCVideoController::QtWidgetControllerRoot::processAttachedWindowHide(){

      if( !m_qtwImplementor.isNull() ){
        //auto *_widget = m_qtwImplementor->m_widgetDelegator.getWidget();
        if(  m_qtwImplementor->m_widgetDelegator != Nullptr ){
          auto *_widget = m_qtwImplementor->m_widgetDelegator->getWidget();
          if(  _widget != Nullptr){
            _widget->hide();
          }    
        }
      }
    }

    void VLCVideoController::QtWidgetControllerRoot::processAttachedWindowClose(){
      if( !m_qtwImplementor.isNull() ){
        if(  m_qtwImplementor->m_widgetDelegator != Nullptr ){
          m_qtwImplementor->m_widgetDelegator->stop();  
        }

        /*
        auto *_widget = m_qtwImplementor->m_widgetDelegator.getWidget();
        if( _widget != Nullptr ){
          m_qtwImplementor->m_threadLock.accquires();
          m_qtwImplementor->m_widgetDelegator.stop();
          m_qtwImplementor->m_threadLock.releases();
        }
        */
      }
    }

    VLCVideoController::VLCVideoController()
      :Controller( new QtWidgetControllerRoot( *this ) )
      ,m_qtwRoot( Nullptr ) {

      m_qtwRoot = reinterpret_cast<QtWidgetControllerRoot *>(m_root.operator->()); 
    }

    VLCVideoController::VLCVideoController( const String& path )
      :Controller( new QtWidgetControllerRoot( *this ) )
      ,m_qtwRoot( Nullptr ) {

      m_qtwRoot = reinterpret_cast<QtWidgetControllerRoot *>(m_root.operator->()); 
      if( !m_qtwRoot->m_qtwImplementor.isNull() ){

#ifdef _MSC_VER
        QString _file_path = QString::fromUtf16( reinterpret_cast<const ushort *>( path.c_str() ), path.size() ); 
#else
        QString _file_path = QString::fromStdWString( path );
#endif  
        m_qtwRoot->m_qtwImplementor->m_srcPath = _file_path;

      }
      
    }

    VLCVideoController::~VLCVideoController(){

    }

    void VLCVideoController::play(){
      if( m_qtwRoot != Nullptr && !m_qtwRoot->m_qtwImplementor.isNull() ){      
        auto &_impl = *(m_qtwRoot->m_qtwImplementor);

        if( _impl.m_widgetDelegator != Nullptr ){
          _impl.m_widgetDelegator->play();
        }
        //_impl.m_threadLock.accquires();
        //_impl.m_widgetDelegator.play();
        //_impl.m_threadLock.releases();
        
      }
    }

    void VLCVideoController::pause(){
      if( m_qtwRoot != Nullptr && !m_qtwRoot->m_qtwImplementor.isNull() ){

        //m_qtwRoot->m_qtwImplementor->m_threadLock.accquires();
        if( m_qtwRoot->m_qtwImplementor->m_widgetDelegator != Nullptr ){
          m_qtwRoot->m_qtwImplementor->m_widgetDelegator->play();
        }
        ///m_qtwRoot->m_qtwImplementor->m_widgetDelegator.pause();
        //m_qtwRoot->m_qtwImplementor->m_threadLock.releases();
        
      }
    }

    void VLCVideoController::stop(){
      if( m_qtwRoot != Nullptr && !m_qtwRoot->m_qtwImplementor.isNull() ){

        if( m_qtwRoot->m_qtwImplementor->m_widgetDelegator != Nullptr ){
          m_qtwRoot->m_qtwImplementor->m_widgetDelegator->stop();
        }

        //m_qtwRoot->m_qtwImplementor->m_threadLock.accquires();
        //m_qtwRoot->m_qtwImplementor->m_widgetDelegator.stop();
        //m_qtwRoot->m_qtwImplementor->m_threadLock.releases();

      }
    }

    void VLCVideoController::setVideoSource( const String& p ){
      /*
      if( m_qtwRoot != Nullptr && !m_qtwRoot->m_qtwImplementor.isNull() ){

        auto *_player = m_qtwRoot->m_qtwImplementor->m_player;
        if( _player != Nullptr ){
          m_qtwRoot->m_qtwImplementor->m_threadLock.accquires();
          _player->play();
          m_qtwRoot->m_qtwImplementor->m_threadLock.releases();
        }
      }
      */
      if( m_qtwRoot != Nullptr && !m_qtwRoot->m_qtwImplementor.isNull() ){
#ifdef _MSC_VER
        QString _file_path = QString::fromUtf16( reinterpret_cast<const ushort *>( p.c_str() ), p.size() ); 
#else
        QString _file_path = QString::fromStdWString( p );
#endif  
        m_qtwRoot->m_qtwImplementor->m_srcPath = _file_path;

        if( m_qtwRoot->m_qtwImplementor->m_widgetDelegator != Nullptr ){
          m_qtwRoot->m_qtwImplementor->m_threadLock.acquires();
          m_qtwRoot->m_qtwImplementor->m_widgetDelegator->loadVideoFromFile( _file_path );
          m_qtwRoot->m_qtwImplementor->m_threadLock.releases();
        }
      }

    }
  }
}
