#include "DesktopInfo.h"

#include <QApplication>
#include <QVariant>
#include <QWidget>
#include <QDesktopWidget>

namespace Magna{
  namespace Glue{
    
    DesktopInfo& DesktopInfo::getDesktopInfo(){
      static DesktopInfo _info;
      return _info;
    }
      
    DesktopInfo::DesktopInfo(){

    }

    DesktopInfo::~DesktopInfo(){

    }


    sint32  DesktopInfo::screenCount () const{
      sint32 _ret_count = -1;
      auto *_desktop_widget = QApplication::desktop();
      if( _desktop_widget != Nullptr ){
        _ret_count = _desktop_widget->screenCount();
      }
      return _ret_count;
    }

    sint32  DesktopInfo::getPrimaryScreenIndex () const{
      sint32 _ret_index = -1;
      auto *_desktop_widget = QApplication::desktop();
      if( _desktop_widget != Nullptr ){
        _ret_index = _desktop_widget->primaryScreen();
      }
      return _ret_index;
    }

    IntegerRectRegion DesktopInfo::getScreenBoundingRect( sint32 screenIndex ) const{
      IntegerRectRegion _ret_rect;
      auto *_desktop_widget = QApplication::desktop();
      if( _desktop_widget != Nullptr ){
        auto &_qt_rect = _desktop_widget->screenGeometry( screenIndex );
        _ret_rect = IntegerRectRegion( IntegerDyadCoordinate( _qt_rect.topLeft().x(), _qt_rect.topLeft().y() )
          , _qt_rect.width(), _qt_rect.height() );
      }
      return _ret_rect;
    }

    IntegerRectRegion DesktopInfo::getMagnaOSScreenBoundingRect() const{
      IntegerRectRegion _ret_rect;
      auto *_desktop_widget = QApplication::desktop();
      if( _desktop_widget != Nullptr ){
        QWidget *_magna_widget = Nullptr;

        //get magna widget
        {
          const auto &_widgets = QApplication::allWidgets();
          for( auto _each_widget = _widgets.begin(); _each_widget != _widgets.end(); ++_each_widget ){
            const auto &_magna_id = (*_each_widget)->property("magna");
            if( _magna_id.isValid() 
              && QVariant::Int  == _magna_id.type()
              && MAGNA_MAGIC_NUMBER == _magna_id.toInt() ){                
                _magna_widget = (*_each_widget);
                break;      
            }      
          }
        }
        
        if( _magna_widget != Nullptr ){
          auto &_qt_rect = _desktop_widget->screenGeometry( _magna_widget );
          _ret_rect = IntegerRectRegion( IntegerDyadCoordinate( _qt_rect.topLeft().x(), _qt_rect.topLeft().y() )
            , _qt_rect.width(), _qt_rect.height() );
        }    
      }
      return _ret_rect;
    }

  }//namespace Glue
}//namespace Magna
