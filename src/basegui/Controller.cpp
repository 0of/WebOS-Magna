#pragma warning(disable:4101)
#pragma warning(disable:4355)
#pragma warning(disable:4715)

#include "basedef/DyadCoordinate.h"

#include "Controller.h"

#include "Controller_p.h"
#include "Window_p.h"
#include "Layout_p.h"
#include "GUIConstantMapper.h"

#include "inner/InnerPrivateDataNullPointerException.h"
#include "inner/InnerIndexNotFoundException.h"
using namespace Inner;  

namespace Magna{
  namespace GUI{

        Controller::MouseEventDelegatorCollection::MouseEventDelegatorCollection()
          :DelegatorCollection( Controller::MouseEventDelegatorCollection::DelegatorCollectionType_Mouse )
          ,onMousePressed()
          ,onMousePressingMoved()
          ,onMouseReleased()
          ,onMouseHoverIn()
          ,onMouseHovered()
          ,onMouseHoverOut()
          ,onMouseClicked()
          ,onMouseDoubleClicked()
          ,onMouseWheelUp()
          ,onMouseWheelDown(){

      
        }

        Controller::MouseEventDelegatorCollection::MouseEventDelegatorCollection( const Controller::MouseEventDelegatorCollection& collection )
          :DelegatorCollection( collection ){
          ::memcpy( this,  &collection, sizeof( Controller::MouseEventDelegatorCollection ));
        }

        Controller::MouseEventDelegatorCollection::~MouseEventDelegatorCollection(){

        }

        Controller::MouseEventDelegatorCollection& Controller::MouseEventDelegatorCollection::operator = ( const MouseEventDelegatorCollection& collection ){
          ::memcpy( this,  &collection, sizeof( Controller::MouseEventDelegatorCollection ));
          return *this;
        }

        Controller::KeyEventDelegatorCollection::KeyEventDelegatorCollection()
          :DelegatorCollection( Controller::KeyEventDelegatorCollection::DelegatorCollectionType_Key )
          ,onKeyPressed()
          ,onKeyReleased(){

        }

        Controller::KeyEventDelegatorCollection::KeyEventDelegatorCollection( const Controller::KeyEventDelegatorCollection& collection )
          :DelegatorCollection( collection ){
          ::memcpy( this,  &collection, sizeof( Controller::KeyEventDelegatorCollection ));

        }  
    
        Controller::KeyEventDelegatorCollection::~KeyEventDelegatorCollection(){

        }

        Controller::KeyEventDelegatorCollection& Controller::KeyEventDelegatorCollection::operator = ( const Controller::KeyEventDelegatorCollection& collection ){
          ::memcpy( this,  &collection, sizeof( Controller::KeyEventDelegatorCollection ));
          return *this;
        }

        Controller::RenderEventDelegatorCollection::RenderEventDelegatorCollection()
          :DelegatorCollection( Controller::RenderEventDelegatorCollection::DelegatorCollectionType_Render ){

        }

        Controller::RenderEventDelegatorCollection::RenderEventDelegatorCollection( const Controller::RenderEventDelegatorCollection& collection )
          :DelegatorCollection( collection ){
          ::memcpy( this,  &collection, sizeof( Controller::RenderEventDelegatorCollection ));

        }  

        Controller::RenderEventDelegatorCollection::~RenderEventDelegatorCollection(){

        }

        Controller::RenderEventDelegatorCollection& Controller::RenderEventDelegatorCollection::operator = ( const RenderEventDelegatorCollection& collection ){
          ::memcpy( this,  &collection, sizeof( Controller::RenderEventDelegatorCollection ));
          return *this;
        }


        Controller::Controller()
          :RenderableElement()
          ,m_root( new Controller::ControllerRoot( *this ) ){

          m_root->_initProperties();

          m_manager = new RenderManager2D;
        }

        Controller::Controller( const String& element_name ) 
          :RenderableElement( element_name )
          ,m_root( new Controller::ControllerRoot( *this ) ){

          if( element_name != L"canvas" ){
            m_root->m_attributes |= Controller::ControllerRoot::Attribute_Protogenous;
          }
          
          m_root->_initProperties();

          m_manager = new RenderManager2D;
        }

        Controller::Controller( const SharedPtr<ControllerRoot>&  _inner_init ) 
          :RenderableElement()
          ,m_root( _inner_init ){
  
          assert( !_inner_init.isNull() );
          m_root->_initProperties();

          m_manager = new RenderManager2D;
        }

        Controller::~Controller(){

        }

        Controller::MouseEventDelegatorCollection & Controller::getMouseEventDelegatorCollection(){
          try{
            if( !m_root.isNull() && m_root->m_mouseEventDelegatorCollections != Nullptr ){
              auto &_collection = *m_root->m_mouseEventDelegatorCollections;

              if( _collection.isShared() ){
                Controller::MouseEventDelegatorCollection *_gen_collection 
                  = new Controller::MouseEventDelegatorCollection( _collection );

                m_root->m_mouseEventDelegatorCollections = _gen_collection;

              }
              return (*m_root->m_mouseEventDelegatorCollections);
            }
            else{
              throw InnerPrivateDataNullPointerException();
            }
          }
          catch( const InnerPrivateDataNullPointerException& _null_ptr_ex ){

          }
        }

        const Controller::MouseEventDelegatorCollection & Controller::getMouseEventDelegatorCollection() const{
          try{
            if( !m_root.isNull() && m_root->m_mouseEventDelegatorCollections != Nullptr ){
              return (*m_root->m_mouseEventDelegatorCollections);
            }
            else{
              throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _null_ptr_ex ){

      }
    }

    Controller::KeyEventDelegatorCollection & Controller::getKeyEventDelegatorCollection(){
      try{
        if( !m_root.isNull() ){
          return m_root->m_keyEventDelegatorCollections;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _null_ptr_ex ){

      }
    }

    const Controller::KeyEventDelegatorCollection & Controller::getKeyEventDelegatorCollection() const{
      try{
        if( !m_root.isNull() ){
          return m_root->m_keyEventDelegatorCollections;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _null_ptr_ex ){

      }
    }

    Controller::RenderEventDelegatorCollection & Controller::getRenderEventDelegatorCollection(){
      try{
        if( !m_root.isNull() ){
          return m_root->m_renderEventDelegatorCollections;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _null_ptr_ex ){

      }
    }

    const Controller::RenderEventDelegatorCollection & Controller::getRenderEventDelegatorCollection() const{
      try{
        if( !m_root.isNull() ){
          return m_root->m_renderEventDelegatorCollections;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _null_ptr_ex ){

      }
    }

    void Controller::addDelegatorCollection( const DelegatorCollection& collection ){
      try{
        if( !m_root.isNull() ){
          switch( collection.getType() ){
          case MouseEventDelegatorCollection::DelegatorCollectionType_Mouse:
            if( m_root->m_mouseEventDelegatorCollections != Nullptr ){
              if( !m_root->m_mouseEventDelegatorCollections->isShared() ){
                delete m_root->m_mouseEventDelegatorCollections;
              }
              m_root->m_mouseEventDelegatorCollections 
                = new MouseEventDelegatorCollection( *(reinterpret_cast<const MouseEventDelegatorCollection * >( &collection)) );
            }
            break;

          case KeyEventDelegatorCollection::DelegatorCollectionType_Key:
            m_root->m_keyEventDelegatorCollections = *(reinterpret_cast<const KeyEventDelegatorCollection * >( &collection)) ;
            break;

          case RenderEventDelegatorCollection::DelegatorCollectionType_Render:
            m_root->m_renderEventDelegatorCollections =  *(reinterpret_cast<const RenderEventDelegatorCollection * >( &collection)) ;
            break;

          default:
            throw InnerIndexNotFoundException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){

      }  
    }

    bool Controller::isFocussed() const{
      return m_root->m_stateSwitcher.isStateOn( ControllerRoot::State_Focus );
    }

    bool Controller::isEnabled() const{
      return m_root->m_stateSwitcher.isStateOn( ControllerRoot::State_Enabled );
    }
    bool Controller::isShown() const{
      return m_root->m_stateSwitcher.isStateOn( ControllerRoot::State_Show );
    }
    bool Controller::isHidden() const{
      return !m_root->m_stateSwitcher.isStateOn( ControllerRoot::State_Show );
    }

    bool Controller::isEqualTo( Controller *cmper ){
      //bool _ret_equ = cmper != Nullptr 
      //    && m_private != Nullptr 
      //    && cmper->m_private != Nullptr
      //    && m_root->m_runtime_ID != 0
      //    && m_root->m_runtime_ID 
      //      == cmper->m_root->m_runtime_ID;
      //return _ret_equ;  
      return true;
    }
  

    IntegerSize Controller::getSize() const{
      IntegerSize _ret_size;
      m_mutex.acquires();
      _ret_size = m_renderableRect.getSize();
      m_mutex.releases();
      return _ret_size;
    }

    IntegerRectRegion Controller::getBoundingRectRegion() const{
      IntegerRectRegion _ret_rect;
      m_mutex.acquires();
      _ret_rect = m_renderableRect;
      m_mutex.releases();
      return _ret_rect;
    }

    IntegerDyadCoordinate Controller::getPos() const{
      IntegerDyadCoordinate _ret_pos;
      m_mutex.acquires();
      _ret_pos = m_renderableRect.getTopLeftCoord();
      m_mutex.releases();
      return _ret_pos;
    }
    
    sint32 Controller::getHeight() const{
      sint32 _ret_height = 0;
      m_mutex.acquires();
      _ret_height = m_renderableRect.getHeight();
      m_mutex.releases();
      return _ret_height;
    }

    sint32 Controller::getWidth() const{
      sint32 _ret_width = 0;
      m_mutex.acquires();
      _ret_width = m_renderableRect.getWidth();
      m_mutex.releases();
      return _ret_width;
    }

    SharedPtr<Layout> Controller::getLayout() const{
      SharedPtr<Layout> _ret_layout ;
      try{
        if( !m_root.isNull() ){
          _ret_layout = m_root->m_centreLayout;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& ex ){
        abort();
      }
      return _ret_layout;
    }

    Layout *Controller::getParentLayout() const{
      Layout *_ret_layout = Nullptr;
      try{
        if( !m_root.isNull() ){
          _ret_layout = m_root->m_parentLayout;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& ex ){
        abort();
      }
      return _ret_layout;
    }

    LayoutAttribute Controller::getLayoutAttribute() const{
      LayoutAttribute _ret_layout_Attr ;
      try{
        if( !m_root.isNull() ){
          _ret_layout_Attr =  m_root->m_layoutAttr;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& ex ){
        abort();
      }
      return _ret_layout_Attr;
    }


    void Controller::setBorderStyle( GUIConstants::BorderStyle style ){
      try{
        if( !m_root.isNull() ){
          //not running controller
          if( m_root->m_int_runtimeId == 0 ){
            m_root->m_borderStyle = style;
          }
          

        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& ex ){
        abort();
      }
    }

    void Controller::setBorderWidth( uint32 width ){
      try{
        if( !m_root.isNull() ){
          //not running controller
          if( m_root->m_int_runtimeId == 0 ){
            m_root->m_borderWidth = width;
          }


        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& ex ){
        abort();
      }
    }

    void Controller::setBorderColor( const Color& color ){
      try{
        if( !m_root.isNull() ){
          //not running controller
          if( m_root->m_int_runtimeId == 0 ){
            m_root->m_borderColor = color;
          }


        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& ex ){
        abort();
      }
    }

    void Controller::setLayout( const SharedPtr<Layout>& layout ){
      if( !layout.isNull()){
        try{
          if( !m_root.isNull() && !layout->m_layout.isNull() ){
            m_root->m_centreLayout = layout;

            m_root->m_centreLayout ->m_layout->assignParent( this );
            //need to notify all the children controller

            if( m_root->m_centreLayout->getAttachedWindow() != Nullptr ){
              m_root->m_centreLayout ->measure();

              m_root->m_centreLayout ->deploy();

              update();
            }
          }
        }
        catch( const std::exception& ex ){
          abort();
        }
      }
    }

    void Controller::setLayoutAttribute( const LayoutAttribute& attr ){
      try{
        if( !m_root.isNull() ){      
          if( m_root->m_layoutAttr != attr ){
            m_root->m_layoutAttr = attr;
            //re-layout
            Layout *_parent_Layout = m_root->m_parentLayout;
            if(  _parent_Layout != Nullptr ){
              _parent_Layout->measure();
              _parent_Layout->deploy();
            }
            //
          }

        }
      }
      catch( const std::exception& ex ){
        abort();
      }
    }

    void Controller::setPos( const IntegerDyadCoordinate& pos ){
      try{
        if( !m_root.isNull() 
          && m_root->_pos_get() != pos ){
          bool _event_occur_cond = !false;
          Layout *_parent_Layout = m_root->m_parentLayout;
          if(  _parent_Layout != Nullptr ){
            if( _parent_Layout->getType() != Layout::LayoutType_Absolute ){
              _event_occur_cond = false;        
            }
          }

          if( _event_occur_cond != false ){
            MovedEventArgs eventArgs( m_root->_pos_get(), pos );
            m_root->moved( eventArgs );    
          }
        }
      }
      catch( const std::exception& ex ){
        abort();
      }
    }

    void Controller::setSize( const IntegerSize& size ){
      try{
        if( !m_root.isNull() 
          && m_root->_size_get() != size ){
          bool _event_occur_cond = !false;
          Layout *_parent_Layout = m_root->m_parentLayout;
          if(  _parent_Layout != Nullptr ){
            const LayoutAttribute& attr = m_root->m_layoutAttr;
            if( attr.m_hint != LayoutAttribute::LayoutHint_Specific ){
              _event_occur_cond = false;              
            }                      
          }

          if( _event_occur_cond != false ){
            ResizedEventArgs eventArgs( m_root->_size_get(), size );
            m_root->resized( eventArgs );      
          }

        }
      }
      catch( const std::exception& ex ){
        abort();
      }
    }

    void Controller::setBoundingRectRegion( const IntegerRectRegion& rect ){
      try{
          if( !m_root.isNull() ){

          //if the top left coordinate of the bounding rect has changed
          //do as setPos does
          if( m_root->_pos_get() != rect.getTopLeftCoord() ){
            Layout *_parent_Layout = m_root->m_parentLayout;
            if(  _parent_Layout != Nullptr ){
              if( _parent_Layout->getType() != Layout::LayoutType_Absolute ){
                m_root->_pos_set( rect.getTopLeftCoord());
                //re-render
                //
              }
            }
            else{        
              m_root->_pos_set( rect.getTopLeftCoord());
            }
          }

          //size changed do setSize
          const IntegerSize& _given_rect_size = rect.getSize();
          if( m_root->_size_get() != _given_rect_size ){
            const LayoutAttribute& attr = m_root->m_layoutAttr;
            if( attr.m_hint != LayoutAttribute::LayoutHint_Specific ){
              m_root->_size_set( _given_rect_size );

              //get current layout
              SharedPtr<Layout> _layout = m_root->m_centreLayout;
              if( !_layout.isNull() ){
                _layout->measure();
                _layout->deploy();
              }
              //re-render
              ///
              ///Resize Event
              ///emit trigger
              //OnceResized.triggers( size );
            }                      
          }
          else{
            //only set the pos values
            m_root->_size_set( _given_rect_size );
          }
        }
          
        else{

        }
      }
      catch( const std::exception& ex ){
        abort();
      }
    }

    void Controller::setFocus(){
      try{
        if( !m_root.isNull() ){
          FocusEventArgs _focus_in_arg( GUIEventConstants::GUIEvent_FocusIn );
          m_root->focusIn( _focus_in_arg );
        }
      }
      catch( const std::exception& ex ){
        abort();
      }
    }

    void Controller::show(){
      try{
        if( !m_root.isNull() ){
          ImplStateSwitcher<ControllerRoot::StateValue, MultiplexedSwitcherMode> &_stateSwitcher
            = m_root->m_stateSwitcher;

            _stateSwitcher.switches( ControllerRoot::State_Show );
            _stateSwitcher.switches( ControllerRoot::State_Focus );

            //re-render
        }
      }
      catch( const std::exception& ex ){
        abort();
      }
    }
    void Controller::hide(){
      try{
        if( !m_root.isNull() ){
            ImplStateSwitcher<ControllerRoot::StateValue, MultiplexedSwitcherMode> &_stateSwitcher
              = m_root->m_stateSwitcher;

        }
      }
      catch( const std::exception& ex ){
        abort();
      }
    }

    //
    void Controller::enable(){
      try{
        if( !m_root.isNull() ){
            ImplStateSwitcher<ControllerRoot::StateValue, MultiplexedSwitcherMode> &_stateSwitcher
              = m_root->m_stateSwitcher;

          _stateSwitcher.switches( ControllerRoot::State_Enabled );

        }
      }
      catch( const std::exception& ex ){
        abort();
      }
    }

    void Controller::disable(){

    }

    void Controller::update(){
      try{
        if( !m_root.isNull() ){
          auto * _parent_layout = m_root->m_parentLayout;

          if( _parent_layout != Nullptr ){
            auto * _base_wnd = _parent_layout->getAttachedWindow();

            if( _base_wnd != Nullptr ){            
              auto &_wnd_root = _base_wnd->m_wndRoot;
              if( !_wnd_root.isNull() ){
                _wnd_root->renderController( this );
              }
              else{
                throw InnerPrivateDataNullPointerException();
              }
            }
            //base window is Nullptr
            //do nothing
          }
        }
      }
      catch( const std::exception& ex ){
        abort();
      }
    }    

    void Controller::update(const IntegerRectRegion& dirtyRect){
      try{
        if( !m_root.isNull() ){
          auto * _parent_layout = m_root->m_parentLayout;

          if( _parent_layout != Nullptr ){
            auto * _base_wnd = _parent_layout->getAttachedWindow();

            if( _base_wnd != Nullptr ){            
              auto &_wnd_root = _base_wnd->m_wndRoot;
              if( !_wnd_root.isNull() ){
                _wnd_root->partlyRenderController( this, dirtyRect );
              }
              else{
                throw InnerPrivateDataNullPointerException();
              }
            }
            //base window is Nullptr
            //do nothing
          }
        }
      }
      catch( const std::exception& ex ){
        abort();
      }
    }


    FillBrush Controller::getBrush(){
      FillBrush _ret_brush;
      try{
        if( !m_root.isNull() ){
          _ret_brush = m_root->m_brush ;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      return _ret_brush;
    }

    Pen Controller::getPen(){
      Pen _ret_pen;
      try{
        if( !m_root.isNull() ){
          _ret_pen = m_root->m_pen ;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      return _ret_pen;
    }

    Font Controller::getFont(){
      Font _ret_font;
      try{
        if( !m_root.isNull() ){
          _ret_font = m_root->m_font ;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      return _ret_font;
    }

    float Controller::getOpacity(){
      float _ret_opacity;
      try{
        if( !m_root.isNull() ){
          _ret_opacity = m_root->m_opacity ;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      return _ret_opacity;
    }

    void Controller::setBrush( const FillBrush& brush ){
      try{
        if( !m_root.isNull() ){
          m_root->m_brush = brush;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
    }
    void Controller::setPen( const Pen& pen ){
      try{
        if( !m_root.isNull() ){
          m_root->m_pen = pen ;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
    }

    void Controller::setFont( const Font& font ){
      try{
        if( !m_root.isNull() ){
          m_root->m_font = font;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
    }

    void Controller::setOpacity( float opacity ){
      assert( !Comparer<float>::isLowerThanZero( opacity ) 
        && !Comparer<float>::isHigherThan( opacity, 1.0 )  );
      try{
        if( !m_root.isNull() ){
          m_root->m_opacity = opacity;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
    }

    std::vector<SharedPtr<Controller> > Controller::getControllers(){
      std::vector<SharedPtr<Controller> > _ret_controllers;
      try{
        if( !m_root.isNull() ){
          auto &_layout  = m_root->m_centreLayout;
          if( !_layout.isNull() ){
            std::vector<SharedPtr<Controller> > _controllers ( std::move( _layout->getChildControllers() ) );
            _ret_controllers.insert( _ret_controllers.end(), _controllers.begin(), _controllers.end() );

            auto _iter = _controllers.begin();
            for( ; _iter != _controllers.end(); [&](){
              auto &_each = (*_iter++);
                if( ! _each.isNull() ){      
                  decltype(_each->getControllers()) _each_controllers ( std::move(_each->getControllers()) );
                  _ret_controllers.insert( _ret_controllers.end(), _each_controllers.begin(), _each_controllers.end() );
                }      
            }()){}        
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      return _ret_controllers;
    }

    String Controller::toStyleString() const {
      OutStringStream _outter;
    
      if( !m_root.isNull() && m_root->m_parentLayout != Nullptr ){
#ifdef MAGNA_DIV_CANVAS_WRAPPER
        auto *_attached_wind = m_root->m_parentLayout->getAttachedWindow();
        if( _attached_wind != Nullptr ){

          IntegerDyadCoordinate _mapped_pos;
          if( m_root->m_parentLayout->isWindowParent() ){
            const auto& _y_diff = _attached_wind->getContentPos().getY()  - _attached_wind->getPos().getY() ;
            _mapped_pos = m_renderableRect.getTopLeftCoord().translatedByY( _y_diff ) ;        
          }
          else{
            _mapped_pos = m_renderableRect.getTopLeftCoord();
          }

          //wrapper style
          _outter << L" 'overflow: hidden;display: inline-block;position: absolute; -webkit-tap-highlight-color: rgba(0, 0, 0, 0);"
            << L"left:" << _mapped_pos.getX() << L"px; top:" << _mapped_pos.getY() 
            //border style
            <<L"px; border-style:" << GUIConstantMapper::BorderStyleMapper[ m_root->m_borderStyle ]
          <<L";border-width: " << m_root->m_borderWidth 
            <<L"px;border-color: " 
            << m_root->m_borderColor.toString( Color::ColorStringFormat_Numeric_RGB, Color::ColorStringQualifier_NumberSign)
            << L";'";
        }
        
#else
        auto &_mapped_pos = m_root->m_parentLayout->toCoordOnManipulateDevice( m_renderableRect.getTopLeftCoord() );
        _outter << L" 'position: absolute; "
          << L"left:" << _mapped_pos.getX() << L"px; top:" << _mapped_pos.getY() 
          //border style
          <<L"px; border-style:" << GUIConstantMapper::BorderStyleMapper[ m_root->m_borderStyle ]
        <<L";border-width: " << m_root->m_borderWidth 
          <<L"px;border-color: " 
          << m_root->m_borderColor.toString( Color::ColorStringFormat_Numeric_RGB, Color::ColorStringQualifier_NumberSign)
          << L";',"
          //width & height
          << m_renderableRect.getWidth()
          << L","
          <<m_renderableRect.getHeight();      
#endif            
      }  
      return _outter.str();
    }

    String Controller::toScriptString () const {
      String _ret_str;
      if( m_manager != Nullptr ){
        //_ret_str = m_manager->getManipulator().str();
      }
      return _ret_str;
    }

    String Controller::toElementString () const {
      assert( m_elementId != Nullptr );

      OutStringStream _ret_str(m_elementId);
        _ret_str << m_elementId
        << L",";
#ifdef MAGNA_DIV_CANVAS_WRAPPER
      Window *_wnd_parent = Nullptr;
      Controller *_ctrl_parent = Nullptr;
      String _id_str;
      if( !m_root.isNull() && m_root->m_parentLayout != Nullptr ){
        if( m_root->m_parentLayout->getParent( _wnd_parent ) 
          && _wnd_parent != Nullptr ){
          //parent id
          if( !(_wnd_parent->m_wndRoot.isNull()) ){
            _id_str.append( _wnd_parent->m_wndRoot->m_runtime_Id);  
          }        
        }
        else if( m_root->m_parentLayout->getParent( _ctrl_parent ) 
          && _ctrl_parent != Nullptr  ){
            _id_str.append( _ctrl_parent->m_elementId );
            auto _insert_it = _id_str.end() - 1;
            _id_str.insert( _insert_it , L'w' );        
        }
        else{
          //throw exception
        }      
        _ret_str << _id_str
          << L",";  
      }
#endif
      _ret_str << toStyleString();

      if( (m_root->m_attributes & Controller::ControllerRoot::Attribute_Protogenous) != 0 ) {
        _ret_str << L","
          << m_elementTagName
          << L","
          << toProtogenousInitString();
      }
      else{
        //width & height
        _ret_str << L"," 
          << m_renderableRect.getWidth()
          << L","
          <<m_renderableRect.getHeight();    
      }

      return _ret_str.str();
    }

    String Controller::toProtogenousInitString( const String& start 
      , const String& , const String& element ) const{
      return String();
    }

    //////////////////////////////////////////////////////////////////////////
    //no need implementations
  
  }//namespace GUI
}//namespace Magna
