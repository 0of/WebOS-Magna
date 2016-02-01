#include "Layout.h"

#include <algorithm>

#include "Layout_p.h"
#include "Controller_p.h"
#include "Window_p.h"

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

namespace Magna{  
   namespace GUI{
    

     Layout::Layout()
       :m_layout( new PrivateLayout ){

     }

     Layout::~Layout() {
  
     }

     void Layout::setLayoutOffset( const IntegerDyadCoordinate& offset){
       try{
         if( !m_layout.isNull() ){
           m_layout->m_layoutOffset = offset;
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& _ex){
         _ex.what();
       }
     }

     void Layout::setLayoutOffset( sint32 xOffset, sint32 yOffset){
       try{
         if( !m_layout.isNull() ){
           m_layout->m_layoutOffset = IntegerDyadCoordinate( xOffset, yOffset );
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& _ex){
         _ex.what();
       }
     }

     IntegerDyadCoordinate Layout::getLayoutOffset() const{
       IntegerDyadCoordinate _ret_offset;
       try{
         if( !m_layout.isNull() ){
          _ret_offset = m_layout->m_layoutOffset ;
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& _ex){
         _ex.what();
       }
       return _ret_offset;
     }

     void Layout::measure() {
       //measure its children
       auto _child_iter = m_layout->m_controllers.begin();
       for( ;_child_iter != m_layout->m_controllers.end(); ++_child_iter ){
         if( !_child_iter->isNull() ){
           auto &_ctrl_root = (*_child_iter)->m_root;
           if( !_ctrl_root.isNull() ){
             _ctrl_root->onLayoutMeasured();
           }

           auto _child_layout = _ctrl_root->m_centreLayout;
           if( !_child_layout.isNull() ){
             _child_layout->measure();          
           }
         }
       }
     }

     void Layout::deploy() {
       auto _child_iter = m_layout->m_controllers.begin();
       for( ;_child_iter != m_layout->m_controllers.end(); ++_child_iter ){
         if( !_child_iter->isNull() ){
           auto &_ctrl_root = (*_child_iter)->m_root;
           if( !_ctrl_root.isNull() ){
             _ctrl_root->onLayoutDeployed();
           }

           auto &&_child_layout = (*_child_iter)->getLayout();
           if( !_child_layout.isNull() ){
             _child_layout->deploy();          
           }
         }
       }
     }

     IntegerRectRegion Layout::getMeasuredRect() const{
       IntegerRectRegion _ret_rect;
       try{
         if( !m_layout.isNull() ){
          _ret_rect = m_layout->m_realRect;
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& _ex){
         _ex.what();
       }
       return _ret_rect;
     }

     SharedPtr<Controller> Layout::getControllerAt( const IntegerDyadCoordinate& pos ) const {
       SharedPtr<Controller> _ret_ctrl;
       try{
         if( !m_layout.isNull() ){
           auto _rev_iter = m_layout->m_controllers.rbegin();
           for( ; _rev_iter !=  m_layout->m_controllers.rend(); ++_rev_iter ){
             if( !_rev_iter->isNull() ){
               auto _each_rect = (*_rev_iter)->getBoundingRectRegion();

               if ( _each_rect.contains( pos ) ){
                 _ret_ctrl = (*_rev_iter);
                 break;
               }        
             }
             else{
               //In common these lines won't be ran at
               throw InnerPrivateDataNullPointerException();
             }
           }
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& _ex){
         _ex.what();
       }
       return _ret_ctrl;
     }

     bool Layout::getParent( Window *& _out_wind ) const{
       bool _is_parent_wind = false;
       try{
         if( !m_layout.isNull() ){
           _is_parent_wind = m_layout->m_windowAsParent;
          if( _is_parent_wind ){
            _out_wind = m_layout->m_wnd;
          }
         }
         else{
            throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& _ex){
         _ex.what();
       }
       return _is_parent_wind;
     }

     bool Layout::getParent( Controller *&_out_ctrl ) const{
       bool _is_parent_ctrl = false;
       try{
         if( !m_layout.isNull() ){
           _is_parent_ctrl = !m_layout->m_windowAsParent;
           if( _is_parent_ctrl ){
             _out_ctrl = m_layout->m_contr;
           }
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& _ex){
         _ex.what();
       }
       return _is_parent_ctrl;
     }

     bool Layout::isWindowParent() const{
       bool _is_parent_wnd = false;
       try{
         if( !m_layout.isNull() ){
           _is_parent_wnd = m_layout->m_windowAsParent;    
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& _ex){
         _ex.what();
       }
       return _is_parent_wnd;
     }

     IntegerDyadCoordinate Layout::toCoordOnScreen( const IntegerDyadCoordinate& coord ) const {
       return IntegerDyadCoordinate( 0, 0);
     }

     IntegerDyadCoordinate Layout::fromCoordOnScreen( const IntegerDyadCoordinate& coord ) const {
       return IntegerDyadCoordinate( 0, 0);
     }

     IntegerDyadCoordinate Layout::toCoordUnderParentCoordSystem( const IntegerDyadCoordinate& coord ) const {
       IntegerDyadCoordinate _ret_coord;
       try{
         if( !m_layout.isNull() ){
           m_layout->m_mutex.acquires();

           if( m_layout->m_contr != Nullptr ){
             _ret_coord =  m_layout->m_contr->getPos().translatesTo( coord ); 
           }
           else{
             _ret_coord =  m_layout->m_wnd->getContentPos().translatesTo( coord );
           }

           m_layout->m_mutex.releases();
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& _ex){
         _ex.what();
       }
       return _ret_coord;
     }

     IntegerDyadCoordinate Layout::fromCoordUnderParentCoordSystem( const IntegerDyadCoordinate& coord ) const {
       IntegerDyadCoordinate _ret_coord;
       try{
         if( !m_layout.isNull() ){
           m_layout->m_mutex.acquires();

           if( m_layout->m_contr != Nullptr ){
             _ret_coord =  coord - m_layout->m_contr->getPos() ;
           }
           else{
             _ret_coord = coord - m_layout->m_wnd->getContentPos() ;
           }

           m_layout->m_mutex.releases();
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& _ex){
         _ex.what();
       }
       return _ret_coord;
     }

     IntegerDyadCoordinate Layout::toCoordOnManipulateDevice( const IntegerDyadCoordinate& coord ) const {
       IntegerDyadCoordinate _ret_coord;
       try{
         if( !m_layout.isNull() ){
           m_layout->m_mutex.acquires();

           //not window as the parent
           if( m_layout->m_contr != Nullptr){
             if( m_layout->m_contr->getParentLayout() != Nullptr ){
               _ret_coord = m_layout->m_contr->getParentLayout()->toCoordOnManipulateDevice( coord );
             }  
             else{
               throw InnerPrivateDataNullPointerException();
             }
           }
           else{
             if( m_layout->m_wnd != Nullptr ){
               _ret_coord = m_layout->m_wnd->getContentPos().translatesTo( coord );
             }
             else{
               throw InnerPrivateDataNullPointerException();
             }
           }

           m_layout->m_mutex.releases();
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& _ex){
         _ex.what();
       }
       return _ret_coord;
     }

     IntegerDyadCoordinate Layout::fromCoordOnManipulateDevice( const IntegerDyadCoordinate& coord ) const {
       IntegerDyadCoordinate _ret_coord;
       try{
         if( !m_layout.isNull() ){
           m_layout->m_mutex.acquires();

           //not window as the parent
           if( m_layout->m_contr != Nullptr){
             if( m_layout->m_contr->getParentLayout() != Nullptr ){
               _ret_coord = coord - m_layout->m_contr->getParentLayout()->fromCoordOnManipulateDevice( coord );
             }  
             else{
               throw InnerPrivateDataNullPointerException();
             }
           }
           else{
             if( m_layout->m_wnd != Nullptr ){
               _ret_coord = coord - m_layout->m_wnd->getContentPos() ;
             }
             else{
               throw InnerPrivateDataNullPointerException();
             }
           }

           m_layout->m_mutex.releases();
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& _ex){
         _ex.what();
       }
       return _ret_coord;
     }

     void Layout::addChildController( const SharedPtr<Controller>& controller ) {
       try{
         if( !m_layout.isNull() ){
           //passing argument shall not be Nullptr
           if( !controller.isNull() ){
             m_layout->m_mutex.acquires();

             bool _exsited = false;
             auto _iter = m_layout->m_controllers.begin();
             for( ; _iter != m_layout->m_controllers.end(); [&](){
               if( (*_iter++) == controller ){
                 _exsited = !false;
               }
             }()){}

             if( !_exsited ){
               m_layout->m_controllers.push_back( controller );
               //assign controller parent layout
               auto _root =  controller->m_root;
               if( !_root.isNull() ){
                 _root->m_parentLayout = this;
               }

               if( m_layout->m_hasBound ){
                 //bind the window to added controller
                 auto && _controller_layout = controller->getLayout();
                 if( !_controller_layout.isNull() && !_controller_layout->m_layout.isNull() ){
                   _controller_layout->m_layout->bindWindow( m_layout->m_wnd );
                 }

                 auto &_wnd_root = m_layout->m_wnd->m_wndRoot;
                 if( !_wnd_root.isNull() ){
                   _wnd_root->_attachController(_root);
                 }
                 
               }
             }            
             m_layout->m_mutex.releases();
           }
        
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }
     }

     Window * Layout::getAttachedWindow() const{
       Window *_ret_window = Nullptr;
       try{
          if( !m_layout.isNull() ){
            if( m_layout->m_hasBound ){
              _ret_window = m_layout->m_wnd;
            }        
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }
       return _ret_window;
     }

     std::vector<SharedPtr<Controller> > Layout::getChildControllers() const{
       std::vector<SharedPtr<Controller> > _ret_controllers;
       try{
          if( !m_layout.isNull() ){
            _ret_controllers = m_layout->m_controllers;
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }
       return _ret_controllers;
     }

     void Layout::removeChildController( const SharedPtr<Controller>& controller ) {

       class _comparer{
         public:
           _comparer( decltype( controller )& _init )
             :m_cmp( _init ){}

           inline bool operator() ( const SharedPtr<Controller>& _cmp){
             return m_cmp == _cmp;
           }

         private:
           decltype( controller ) &m_cmp;
       };

       try{
         if( !m_layout.isNull() ){
           m_layout->m_mutex.acquires();
           auto _iter = std::find_if( m_layout->m_controllers.begin(), m_layout->m_controllers.end(), _comparer(controller));
      
           if( _iter != m_layout->m_controllers.end() ){
             //found the controller
             auto &ctrl_root = (*_iter)->m_root;
            
             if(  m_layout->m_wnd != Nullptr
               && !ctrl_root.isNull() 
               && ctrl_root->m_int_runtimeId != 0 ){

               auto &_wnd_root = m_layout->m_wnd->m_wndRoot;
               if( !_wnd_root.isNull() ){

                  //window is running
                 if(_wnd_root->m_int_runtimeId != 0 ){
                   //unbind window
                   auto &_ctrl_layout = ctrl_root->m_centreLayout;
                   if( !_ctrl_layout.isNull() ){
                     auto &_layout = _ctrl_layout->m_layout;
                     if( !_layout.isNull() ){
                       _layout->unbindWindow();
                     }
                   }
                  _wnd_root->_detachController( ctrl_root );             

                   measure();  
                   deploy();
                 }
                 //
               }

             }
             //check the window & controller

             //remove from the vector
             m_layout->m_controllers.erase( _iter );
           }
           //found the controller
           m_layout->m_mutex.releases();
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const InnerPrivateDataNullPointerException& ex ){
         ex.what();
         abort();
       }
     }

  

   }//GUI
}//Magna
