#include "RuntimeContainer.h"
#include "RuntimeScript.h"

#include "basegui/Window.h"
#include "basegui/WindowAccessor.h"
#include "basegui/GlobalPopOutWindowIntroducer.h"
using namespace Magna::GUI;

#include "application/ApplicationAccessor.h"
#include "application/ApplicationWindowManagerAccessor.h"
#include "ApplicationManager.h"
#include "ApplicationLoader.h"
#include "application/ApplicationIntroducer.h"
using namespace Magna::Application;

#include "ControllerManager.h"
#include "WindowManager.h"
using namespace Magna::Kernel;

#include "qt_glue_img/ImageResourceHandler.h"
using namespace Magna::Glue;

#include "SystemComObjectManager.h"
using namespace Magna::SystemComponent;

#include "multimedia/AudioOutObject.h"
using namespace Magna::MultiMedia;

#include "OSBehaviourNotifier.h"
#include "OSBehaviourNotifierHandler.h"
#include "GlobalEventReceiver.h"


#include <QFile>
#include <QTextStream>

namespace Magna{
  namespace Runtime{

    SpinMutex RuntimeContainer::shared_Load_mutex; 

    RuntimeContainer& RuntimeContainer::getRuntimeContainer(){
      static RuntimeContainer shared_container;
      return shared_container;
    }


    RuntimeContainer::RuntimeContainer()
      :QObject()
      ,m_webview( Nullptr )
      ,m_mainFrame( Nullptr )
      ,m_eventDispatcherNode()
      ,m_did_load( 0 ){

    
    }

    RuntimeContainer::~RuntimeContainer(){

    }


    void RuntimeContainer::initContainer ( ){
      m_webview =  new QWebView;
      m_webview->setProperty("magna", MAGNA_MAGIC_NUMBER);
      m_webview->setWindowFlags( Qt::FramelessWindowHint );

      //m_webview->load( QUrl("http://get.webgl.org/") );
      //if( m_webview->page() != Nullptr ){
      //  m_mainFrame = m_webview->page()->mainFrame();
      //}      

      loadHTMLFrame();  

      if( m_mainFrame != Nullptr ){
        m_mainFrame->addToJavaScriptWindowObject( EventDispatcherNode::shared_NodeName, &m_eventDispatcherNode );
        m_mainFrame->setScrollBarPolicy ( Qt::Horizontal, Qt::ScrollBarAlwaysOff);
        m_mainFrame->setScrollBarPolicy ( Qt::Vertical, Qt::ScrollBarAlwaysOff );
      }
      //load contents
      //for testing just load a HTML file

      //init app manager
      ApplicationManager &_app_manager = ApplicationManager::getApplicationManager();

      //init app loader
      ApplicationLoader & _app_loader = ApplicationLoader::obtainLoader();
      //push system application

      //init notifier handler
      //must be ahead of GlobalEventReceiver
      OSBehaviourNotifierHandler &_handler = OSBehaviourNotifierHandler::getOSBehaviourNotifierHandler();

      //init Global Event receiver
      GlobalEventReceiver &_receiver = GlobalEventReceiver::getGlobalEventReceiver();    

      //init Resource Handlers
      ImageResourceHandler &_img_res_handler = ImageResourceHandler::getImageResourceHandler();
      //add to webkit core
      if( m_mainFrame != Nullptr ){
#ifdef _MSC_VER
        QString _nodeName = QString::fromUtf16( reinterpret_cast<const ushort *>(ImageResourceHandler::shared_Image_Res_Handler_node_name) );
#else
        QString _nodeName = QString::fromWCharArray(ImageResourceHandler::shared_Image_Res_Handler_node_name );
#endif  
        m_mainFrame->addToJavaScriptWindowObject(_nodeName, &_img_res_handler );
      }

      //init window manager
      WindowManager &_manager = WindowManager::getWindowManager();
      //###
      //  _manager.OnceJSEval.connectAction( this, &RuntimeContainer::evalJavaScript );
      //  _manager.OnceJSRenderWindow.connectAction( this, &RuntimeContainer::evalJavaScriptRenderingWindow );
      //  _manager.OnceJSOpenNewWindow.connectAction( this, &RuntimeContainer::evalJavaScriptOpenNewWindow );
      //  _manager.OnceJSSetWindowVisible.connectAction( this, &RuntimeContainer::evalJavaScriptSetWindowVisible );
      //  _manager.OnceJSSetWindowHidden.connectAction( this, &RuntimeContainer::evalJavaScriptSetWindowHidden )
      ControllerManager &_controller_manager = ControllerManager::getControllerManager();

      //application objects
      ApplicationIntroducer &_app_intro = ApplicationIntroducer::getApplicationIntroducer();
      _app_intro.bindRequester( &_receiver );

      //system components
      SystemComObjectManager& _sysComObjManager = SystemComObjectManager::getSystemComObjectManager();

      //###
      auto& _obj =AudioOutObject::getAudioOutObject();


      m_webview->showFullScreen();
          
    }

    void RuntimeContainer::evalJavaScript( const QString& sc){
      if( m_mainFrame != Nullptr ){
        //no need return values
        m_mainFrame->evaluateJavaScript ( sc );
      }
    }

    void RuntimeContainer::evalJavaScript( const String& sc){
      if( m_mainFrame != Nullptr ){
        //no need return values
        
#ifdef _MSC_VER
        const QString& _sc = QString::fromUtf16( reinterpret_cast<const ushort *>(sc.c_str()), sc.size() ) ;
#else
        const QString& _sc = QString::fromStdWString(sc ) ;
#endif
        m_mainFrame->evaluateJavaScript ( _sc );
      }
    }
    /*
    void RuntimeContainer::evalJavaScript( const std::string& sc){
      if( m_mainFrame != Nullptr ){
        //no need return values
        m_mainFrame->evaluateJavaScript ( QString::fromStdString( sc ) );
      }
    }

    void RuntimeContainer::evalJavaScriptRenderingWindow( const assic_char* element_id, const std::string& content ){
      if( m_mainFrame != Nullptr ){
        //no need return values
        QString _script ( RuntimeScript::shared_JavaScript_CodeLines_retrieve_context_pre );
        _script.append( element_id )
          .append( RuntimeScript::shared_JavaScript_CodeLines_retrieve_context_check )
          .append( QString::fromStdString( content ) )
          .append( RuntimeScript::shared_JavaScript_CodeLines_retrieve_context_fin );  
        m_mainFrame->evaluateJavaScript ( _script );
      }
    }

    void RuntimeContainer::evalJavaScriptOpenNewWindow( const std::string& para ){
  

      if( m_mainFrame != Nullptr ){
        QString _new_wnd_sr( RuntimeScript::shared_JavaScript_Service_Provider_Window );      
        _new_wnd_sr.append( RuntimeScript::shared_JavaScript_Service_open_new_window )
          .append( "(" )
          .append( QString::fromStdString( para ) )
          .append( ");");
        m_mainFrame->evaluateJavaScript ( _new_wnd_sr );
      }
    }



    void RuntimeContainer::evalJavaScriptSetWindowVisible( const std::string& id ){
      if( m_mainFrame != Nullptr ){
        QString _new_wnd_sr = RuntimeScript::shared_JavaScript_Service_Provider_Window ;
        _new_wnd_sr += ( RuntimeScript::shared_JavaScript_Service_set_window_visible + '(' + QString::fromStdString( id ) + ')' );

        m_mainFrame->evaluateJavaScript ( _new_wnd_sr );
      }
    }

    void RuntimeContainer::evalJavaScriptSetWindowHidden( const std::string& id ){
      if( m_mainFrame != Nullptr ){
        QString _new_wnd_sr = RuntimeScript::shared_JavaScript_Service_Provider_Window ;
        _new_wnd_sr += ( RuntimeScript::shared_JavaScript_Service_set_window_hidde + '(' + QString::fromStdString( id ) + ')' );

        m_mainFrame->evaluateJavaScript ( _new_wnd_sr );
      }
    }
    */

    void RuntimeContainer::loadApplication( const String& path ){
      ApplicationLoader & _app_loader = ApplicationLoader::obtainLoader();
      
      auto _app_block = _app_loader.loads( path );
      if( _app_block != Nullptr ){      
        ApplicationManager &_app_manager = ApplicationManager::getApplicationManager();

        //fetch main window
        //### Unsolved Problem
        //### Application Mutex
        const SharedPtr<Window>& _main_wnd = (_app_block->getApplication()->getMainWindow());
        if( !_main_wnd.isNull() ){
          WindowManager &_wnd_manager = WindowManager::getWindowManager();
          //get application private data
          auto &&_app_data = ApplicationAccessor::accessApplication( _app_block->getApplication() );
          _app_data->m_appPath = path;

          //connect global event receiver
          GlobalEventReceiver &_receiver = GlobalEventReceiver::getGlobalEventReceiver();  
          _app_data->m_eventHandler.bindRequester( &_receiver );

          //_wnd_manager.startWindow(WindowAccessor::getRoot( _main_wnd ) ,  _app_data->m_loop ) ;
          _wnd_manager.startWindow(WindowAccessor::getRoot( _main_wnd ) ) ;
        }

        //fetch the services?

        _app_manager.pushAppTaskBlock( _app_block );
      }
    }

    void RuntimeContainer::loadHTMLFrame(){
      //effect use for temp
      QString _effect = "var Magna_Canvas_Effect_Snow = function(){\
                var ctx = null;\
                var W = 0;\
                var H = 0;\
                \
                var mp = 12;\
                var particles = [];\
                var angle = 1;\
                var weight = 3;\
                var speed = 5;\
                \
                var bkstyle = [];\
                var pcolor = \"rgba(233,243,210,0.9)\";\
                var timer2 = null;\
                var timer = null;\
                bkstyle.push({ color : 'rgba(233,243,210,0.9)', ang : 4,\
                s : 2 });\
                bkstyle.push({ color : 'rgba(124,182,210,0.9)', ang :3,\
                s : 7 });\
                bkstyle.push({ color : 'rgba(205,97,191,0.9)', ang :6,\
                s : 4 });\
                bkstyle.push({ color : 'rgba(19,177,3,0.9)', ang :1,\
                s : 5 });\
                \
                bkstyle.push({ color : 'rgba(25, 4,235,0.9)', ang :7,\
                s : 6 });\
                \
                bkstyle.push({ color : 'rgba(225, 101,91,0.9)', ang :5,\
                s : 7 });\
                for(var i = 0; i < mp; i++)\
                {\
                particles.push({\
                x: Math.random()*W,\
                y: Math.random()*H,\
                r: Math.random()*30+3,\
                d: Math.random()*mp\
                })\
                }\
                \
                Magna_Canvas_Effect_Snow.prototype.resetCanvas = function( id ){\
                var _canvas = document.getElementById(id);\
                if( _canvas != null ){\
                ctx = _canvas.getContext('2d');\
                if ( ctx != null ){\
                \
                W = _canvas.width;\
                H = _canvas.height;\
                \
                for(var i = 0; i < mp; i++)\
                {\
                particles[i]=({\
                x: Math.random()*W,\
                \
                y: Math.random()*H,\
                \
                r: Math.random()*30+3,\
                \
                d: Math.random()*mp\
                });\
                }\
                }\
                }\
                };\
                Magna_Canvas_Effect_Snow.prototype.draw = function()\
                {\
                \
                ctx.clearRect(0, 0, W, H);\
                \
                ctx.fillStyle = pcolor;\
                \
                ctx.beginPath();\
                for(var i = 0; i < mp; i++)\
                {\
                var p = particles[i];\
                ctx.moveTo(p.x, p.y);\
                ctx.arc(p.x, p.y, p.r, 0, Math.PI*2, true);\
                }\
                ctx.fill();\
                \
                for(var i = 0; i < mp; i++)\
                {\
                var p = particles[i];\
                \
                p.y += Math.cos(angle) + weight + p.r/2;\
                p.x += Math.sin(angle) * speed;\
                \
                if(p.x > W || p.x < 0 || p.y > H) {\
                \
                if (i%3 > 0) {\
                particles[i] = {x: Math.random()*W, y: -10, r: p.r, d: p.d};\
                } else {\
                particles[i] = {x: 0, y: Math.random()*H, r: p.r, d: p.d};\
                }\
                }\
                }\
                \
                };\
                \
                Magna_Canvas_Effect_Snow.prototype.changeStyle= function(){\
                if( ctx != null ){\
                var a= parseInt(Math.random() * 5 );\
                \
                pcolor = bkstyle[a].color;\
                \
                speed =  bkstyle[a].s;\
                angle = bkstyle[a].ang;\
                \
                }\
                };\
                \
                Magna_Canvas_Effect_Snow.prototype.start= function(){\
                if( ctx != null ){\
                var v= parseInt(Math.random() * 5);\
                pcolor = bkstyle[v].color;\
                \
                speed =  bkstyle[v].s;\
                angle = bkstyle[v].ang;\
                \
                timer = setInterval(this.draw,30);\
                timer2 = setTimeout(this.changeStyle, 10000 );\
                }\
                };\
                \
                Magna_Canvas_Effect_Snow.prototype.stop= function(){\
                if( ctx != null ){\
                clearInterval(timer);\
                clearTimeout(timer2)\
                }\
                };\
                };\
                var Magna_Canvas_snow_effect  = new  Magna_Canvas_Effect_Snow;";


      QString _html_str( RuntimeScript::shared_HTML_frame_begin );
      //head script
      _html_str.append( RuntimeScript::shared_HTML_frame_head_script_begin )
        .append( RuntimeScript::shared_kernel_JavaScript_Window_Manager_Service_script)
        .append( RuntimeScript::shared_JavaScript_Listener_script )
        .append(RuntimeScript::shared_JavaScript_Listener_Manager_Service_script)
        .append( RuntimeScript::shared_kernel_JavaScript_Controller_Manager_Service_script )
        .append( RuntimeScript::shared_kernel_JavaScript_Window_Rubber_Band_Functionality_script )
        .append( RuntimeScript::shared_HTML_frame_head_script_end);

      //body script
      _html_str.append( RuntimeScript::shared_HTML_frame_body_script_begin )
        .append(  RuntimeScript::shared_kernel_JavaScript_Service_Provider_Object_init_script )
        .append(  RuntimeScript::shared_kernel_JavaScript_Functionality_Object_init_script )
        .append( _effect )
        .append( RuntimeScript::shared_HTML_frame_body_script_end );

      //end
      _html_str.append( RuntimeScript::shared_HTML_frame_end );

      m_webview->setHtml( _html_str );

      if( m_webview->page() != Nullptr ){
        m_mainFrame = m_webview->page()->mainFrame();
      }  

      //### dynamic append script node
      //### 
      /*
      if( m_webview->page() != Nullptr ){
        m_mainFrame = m_webview->page()->mainFrame();
      }  
      
      if( m_mainFrame != Nullptr ){
        auto &_head_element = m_mainFrame->findFirstElement( "HEAD" );
        //check Nullptr or not
        if( !_head_element.isNull() ){
          auto & _script_element = _head_element.firstChild ();

          QString _script (RuntimeScript::shared_kernel_JavaScript_Window_Manager_Service_script);
          _script.append( RuntimeScript::shared_JavaScript_Listener_script )
          .append(RuntimeScript::shared_JavaScript_Listener_Manager_Service_script);

          _script_element.setPlainText( _script );
        }

        auto & _body_element = m_mainFrame->findFirstElement( "BODY" );
        if( !_body_element.isNull() ){
          auto & _script_element = _body_element.firstChild ();
          QString _script = RuntimeScript::shared_kernel_JavaScript_Service_Provider_Object_init_script;      

          _script_element.setPlainText( _script );
        }
      }
      */
      //Debug 
      //output the script to HTML File
      //Depends on Qt Framework
      /*
      QFile _out_file( "gen_file.html" );
      if( _out_file.open( QIODevice::WriteOnly ) ){
        //  
      }
      QTextStream _out_stream ( &_out_file );
      _out_stream << m_mainFrame->toHtml();
      _out_file.close();
      */
    }

    void RuntimeContainer::loadDesktopPage(){
      auto &_loader = ApplicationLoader::obtainLoader();

      //system components
      SystemComObjectManager& _sysComObjManager = SystemComObjectManager::getSystemComObjectManager();

      auto _app_block = _loader.loadDesktopApplication( _sysComObjManager.getDesktopObject() );

      if( _app_block != Nullptr ){      
        ApplicationManager &_app_manager = ApplicationManager::getApplicationManager();

        const SharedPtr<Window>& _main_wnd = (_app_block->getApplication()->getMainWindow());
        if( !_main_wnd.isNull() ){
          WindowManager &_wnd_manager = WindowManager::getWindowManager();
          //get application private data
          auto &&_app_data = ApplicationAccessor::accessApplication( _app_block->getApplication() );
          
          //connect global event receiver
          GlobalEventReceiver &_receiver = GlobalEventReceiver::getGlobalEventReceiver();  
          _app_data->m_eventHandler.bindRequester( &_receiver );
    
          _wnd_manager.startDesktopWindow(WindowAccessor::getRoot( _main_wnd ) ) ;

          //in GUI lib global manager
          auto &_introducer = GlobalPopOutWindowIntroducer::getGlobalPopOutWindowIntroducer();
          //###
          //puts the global receiver as the requester, NOT the application's handler
          _introducer.init( _app_block->getApplication() , &_receiver );
        }

        //fetch the services?
        _app_manager.pushAppTaskBlock( _app_block ); 
      }
    }

  }
}//namespace Magna
