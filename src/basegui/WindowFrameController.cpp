#pragma warning(disable :4355)

#include "WindowFrameController.h"

#include "qt_glue/FontMetrics.h"
#include "qt_glue_img/Image.h"
using namespace Magna::Glue;

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "Controller_p.h"
#include "ControllerImplementor.h"
#include "ControllerAccessor.h"
#include "WindowAccessor.h"

#include "IFrame.h"
#include "DefaultIFrameImpl.h"
#include "Button.h"
#include "RelativeLayout.h"
#include "LinearLayout.h"

#include <cassert>
#include <cmath>

namespace Magna{
  namespace GUI{
  
    class WindowFrameControllerImpl : public ControllerImplementor{
    public:
      WindowFrameControllerImpl( WindowFrameController& binding)
        :ControllerImplementor()
        ,m_bindingFrameController( binding )
        ,m_frame(  new DefaultIFrameImpl )
        ,m_bingdingWindow( Nullptr )
        ,m_minWndButton( new Button(L"") )
        ,m_maxWndButton( new Button(L"") )
        ,m_exitWndButton( new Button(L"") )
        ,m_wrapController( new Controller ){
          
        String _res_dir = L"F:/projects/Qt_Project/[script_diagram]_WebOS/res/basegui/";
        Image _min_button_icon( _res_dir + L"magna_min_wnd.png" );
        Image _max_button_icon( _res_dir + L"magna_max_wnd.png" );
        Image _exit_button_icon( _res_dir + L"magna_exit_wnd.png" );  

        //takes 3/4 height of the frame
        const auto& _takes_height = (m_frame->getFrameHeight() >> 2) * 3;

        FillBrush _button_brush( Color( 106, 113, 198) );

        _min_button_icon.scale( _takes_height, _takes_height, Image::ImageTransformationMode_Smooth );
        _max_button_icon.scale( _takes_height, _takes_height, Image::ImageTransformationMode_Smooth );
        _exit_button_icon.scale( _takes_height, _takes_height, Image::ImageTransformationMode_Smooth );

        m_minWndButton->setSize( IntegerSize( _takes_height, _takes_height ) );
        m_maxWndButton->setSize( IntegerSize( _takes_height, _takes_height ) );
        m_exitWndButton->setSize( IntegerSize( _takes_height, _takes_height ) );

        m_minWndButton->setIcon( _min_button_icon );
        m_maxWndButton->setIcon( _max_button_icon );
        m_exitWndButton->setIcon( _exit_button_icon );

        m_minWndButton->setBrush( _button_brush );
        m_maxWndButton->setBrush( _button_brush );
        m_exitWndButton->setBrush( _button_brush );

        //connections
        m_exitWndButton->OnceClicked.connectAction( this, &WindowFrameControllerImpl::askCloseWindow );
        m_minWndButton->OnceClicked.connectAction( this, &WindowFrameControllerImpl::askHideWindow );

        LinearLayout *_wrap_layout = new LinearLayout;
        (*_wrap_layout) << m_minWndButton << m_maxWndButton << m_exitWndButton;

        m_wrapController->setSize( IntegerSize( _takes_height * 3 + 20, _takes_height ) );
        m_wrapController->setLayout( _wrap_layout );
        //m_wrapController->setBorderColor( Color( 156, 156, 156, 176 ) );
        //m_wrapController->setBorderStyle( GUIConstants::BorderStyle_Solid );
        //m_wrapController->setBorderWidth( 1 );

        RelativeLayout *_frameLayout = new RelativeLayout;

        //something wrong with rel
        _frameLayout->addController( m_wrapController, -0.05f, 0.0f );
        m_bindingFrameController.setLayout( _frameLayout );
        
      }

      WindowFrameControllerImpl( WindowFrameController& binding, IFrame *frame)
        :ControllerImplementor()
        ,m_bindingFrameController( binding )
        ,m_frame( frame )
        ,m_bingdingWindow( Nullptr )
        ,m_minWndButton( new Button(L"") )
        ,m_maxWndButton( new Button(L"") )
        ,m_exitWndButton( new Button(L"") )
        ,m_wrapController()
        ,m_hasPressed( false )
        ,m_dragOffset(){


      }

      virtual ~WindowFrameControllerImpl(){
        if( m_frame != Nullptr ){
          delete m_frame;
        }
      }

    public:
      void setIFrame( IFrame *frame ){
        if( m_frame != Nullptr ){
          delete m_frame;

          m_frame = frame;  
        }
        else{
          m_frame = new DefaultIFrameImpl;
        }        
      }

    public:
      void askCloseWindow();
      void askHideWindow();

    __Override_Methods public:
      virtual void rendering( RenderingEventArgs& eventArgs ){
        if( eventArgs.isAccepted() 
          && m_frame != Nullptr 
          && m_bingdingWindow != Nullptr ){
        
          const auto &_title = m_bingdingWindow->getWindowTitle();
          const auto &_titleSize = FontMetrics::measureSize( _title, Font() );
          const auto& _width = m_bingdingWindow->getWidth();

          //valid width
          if( _width > 0 ){
            m_frame->renderingFrame( m_bingdingWindow->getWindowTitle()
              , _titleSize
              , m_bingdingWindow->getWidth()
              , m_bingdingWindow->getWindowIcon()
              , eventArgs );
          }          
        }
      }

      virtual void mousePressed( MouseEventArgs& event ){
        if( event.isAccepted() ){
          m_hasPressed = !false;

          m_dragOffset = event.getTriggeredCoord();
        }
      }

      virtual void mousePressingMoved( MouseEventArgs& event ){
        if( event.isAccepted() ){
          if( m_hasPressed != false ){
            m_hasPressed = false;

            IntegerDyadCoordinate _trigger_coord = m_dragOffset;
            m_dragOffset = (event.getTriggeredCoord() - _trigger_coord);

            if( m_dragOffset.manhattanLength() >= 1 ){
              auto &&_wnd_root = WindowAccessor::getRoot( m_bingdingWindow );
              if( !(_wnd_root.isNull()) ){
                if( _wnd_root->m_requester != Nullptr 
                  && _wnd_root->m_int_runtimeId != 0 ){
                  _wnd_root->m_requester->requestDraggableWindowMove( _wnd_root->m_runtime_Id 
                    , _trigger_coord , m_dragOffset );

                  m_dragOffset = IntegerDyadCoordinate();
                }
              }
            }      
          }      
        }
      }


    __Data_Field public:
      IFrame *m_frame;
      Window *m_bingdingWindow;

      SharedPtr<Button> m_minWndButton;
      SharedPtr<Button> m_maxWndButton;
      SharedPtr<Button> m_exitWndButton;
      SharedPtr<Controller> m_wrapController;

      IntegerDyadCoordinate m_dragOffset;
      uint32 m_hasPressed;

      WindowFrameController& m_bindingFrameController;
    };


    void WindowFrameControllerImpl::askCloseWindow(){
      if( m_bingdingWindow != Nullptr ){
        m_bingdingWindow->close();
      }
    }

    void WindowFrameControllerImpl::askHideWindow(){
      if( m_bingdingWindow != Nullptr ){
        m_bingdingWindow->setVisible(false);
      }
    }
    
    String WindowFrameController::toStyleString() const {

      OutStringStream _outter;
      //m_mutex.acquires();
      try{
        if( !m_root.isNull() ){

          auto &&_impl = m_root->_impl_get();
          auto * raw_impl = _impl.operator->();

          auto *_wnd_frame_cont_impl = reinterpret_cast<WindowFrameControllerImpl *>( raw_impl );
          if( _wnd_frame_cont_impl != Nullptr ){
            
            if( _wnd_frame_cont_impl->m_bingdingWindow != Nullptr ){
              auto &&_wnd_root = WindowAccessor::getRoot( _wnd_frame_cont_impl->m_bingdingWindow );
              if( !(_wnd_root.isNull()) ){

                _outter << L" 'overflow: hidden;display: inline-block; position: absolute; outline:none;"
                  << L"left:"<< L"0px; top:0px;'" 
                  << L","
                  << m_renderableRect.getWidth()
                  << L","
                  <<m_renderableRect.getHeight();
              }
              else{
                throw InnerPrivateDataNullPointerException();
              }        
            }
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
      
      return _outter.str();
    }

    
    WindowFrameController::WindowFrameController()
      :Controller(){
      
      auto &&_root = ControllerAccessor::getRoot( this );
      if( !_root.isNull() ){
        WindowFrameControllerImpl *_default_frame_impl =  new WindowFrameControllerImpl( *this );

        if( _default_frame_impl->m_frame != Nullptr ){
          _root->_impl_init( SharedPtr<ControllerImplementor>(_default_frame_impl ) );
          _root->_height_set( _default_frame_impl->m_frame->getFrameHeight() );
        }
      
      }  

    }

    WindowFrameController::WindowFrameController( IFrame *iframe )
      :Controller(){

      auto &&_root = ControllerAccessor::getRoot( this );
      if( !_root.isNull() ){
        WindowFrameControllerImpl *_default_frame_impl =  new WindowFrameControllerImpl( *this, iframe );

        if( _default_frame_impl->m_frame != Nullptr ){



          _root->_impl_init( SharedPtr<ControllerImplementor>(_default_frame_impl ) );
          _root->_height_set( _default_frame_impl->m_frame->getFrameHeight() );
        }

      }  
    }

    WindowFrameController::~WindowFrameController(){

    }

    bool WindowFrameController::hasBound() const{
      bool _ret_bound = false;
      try{
        if( !m_root.isNull() ){

          auto &&_impl = m_root->_impl_get();
          auto * raw_impl = _impl.operator->();

          auto *_wnd_frame_cont_impl = reinterpret_cast<WindowFrameControllerImpl *>( raw_impl );
          if( _wnd_frame_cont_impl != Nullptr ){
            _ret_bound = (_wnd_frame_cont_impl->m_bingdingWindow != Nullptr);
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
      return _ret_bound;
    }

    void WindowFrameController::setFrameImplementor( IFrame *iframe ){
      try{
        if( !m_root.isNull() ){

          auto &&_impl = m_root->_impl_get();
          auto * raw_impl = _impl.operator->();

          auto *_wnd_frame_cont_impl = reinterpret_cast<WindowFrameControllerImpl *>( raw_impl );
          if( _wnd_frame_cont_impl != Nullptr ){
            _wnd_frame_cont_impl->setIFrame( iframe );

            setSize( IntegerSize( m_root->_size_get().getWidth(), _wnd_frame_cont_impl->m_frame->getFrameHeight() ) );      
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
    }

    void WindowFrameController::setBindingWindow( Window *wind ){
      assert( wind != Nullptr );
      
      try{
        if( !m_root.isNull() ){
          auto &&_impl = m_root->_impl_get();
          auto * raw_impl = _impl.operator->();

          auto *_wnd_frame_cont_impl = reinterpret_cast<WindowFrameControllerImpl *>( raw_impl );
          auto &_binding_wnd = _wnd_frame_cont_impl->m_bingdingWindow;

          if( wind != _binding_wnd
            && _binding_wnd != Nullptr ){
            _binding_wnd->setWindowFrame( Nullptr );
          }
          _binding_wnd = wind;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }

    }

  }//namespace GUI
}//namespace Magna
