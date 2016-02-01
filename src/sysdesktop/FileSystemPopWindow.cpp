#include "FileSystemPopWindow.h"

#include "basegui/Window_p.h"

#include "system/SystemInfo.h"

#include "DesktopWindow.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      FileSystemPopWindow::FileSystemPopWindow()
        :PopOutWindow( WindowAttribute_NoWindowFrame )
        ,m_fileSystemInfos()
        ,m_usageResults()
        ,m_fileSystemButtons()
        ,m_centerLayout(){


        auto &_sys_info = SystemInfo::getSystemInfo();
        auto &_fs_infos = _sys_info.getFileSystemInfos();

        std::vector<SharedPtr<Controller> > _controllers;

        for( auto _i = 0; _i != _fs_infos.size() - 3 ; ++_i ){
          auto &_each_info = _fs_infos[_i];
          //query usage
          auto &_query_usage = _sys_info.queryFileSystemUsage( _each_info );
          String _label_name = _each_info.getSystemTypeName();
          _label_name.append( L"  " + _each_info.getTypeName() )
                .append( L"  " + _each_info.getDirPath() );

          OutStringStream _usage_info_stream;
          _usage_info_stream<< L"共:";
          auto _total_bytes = _query_usage.getTotal();
          auto _total_gbytes = (_total_bytes >> 20);
          if( _total_gbytes != 0 ){
            _usage_info_stream << _total_gbytes
              << L"(GB)\n已使用:";
            _usage_info_stream << (static_cast<float>(_query_usage.getUsed()) / (1 << 20))
              <<  L"(GB)";
          }
          else{
            _usage_info_stream << (_total_bytes >> 10)
              << L"(MB)\n已使用:";
            _usage_info_stream << (static_cast<float>(_query_usage.getUsed()) / (1 << 10))
              <<  L"(MB)";
          }
      

          m_usageResults.push_back( _query_usage ); 

          SharedPtr<FileSystemButton> _buttons = new FileSystemButton( _fs_infos[_i].getDirPath()
            , _fs_infos[_i].getType()
            ,   _label_name
            , static_cast<float>( _query_usage.getUsedPercentage() )
            ,  _usage_info_stream.str() );

          //_buttons->once

          _controllers.push_back( _buttons );
          m_fileSystemButtons.push_back( _buttons );
        }
        m_fileSystemInfos = _fs_infos;

        //calculate the window
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
        
        TableLayout *_center_layout =  new TableLayout;
        _center_layout->setLayoutOffset( 40, 24 );
        _center_layout->setHorizontalSpacing( 18 );
        _center_layout->setVerticalSpacing( 24 );
        _center_layout->addAutoDeployControllers( _controllers, TableLayout::AutoDeployBreakPolicy_HorizontalBreak );
        
        setCenterLayout( _center_layout );

        setBackgroundFillBrush( FillBrush( DesktopWindow::getPopWindowBG() ) );
        setBorderStyle( GUIConstants::BorderStyle_None );
      }

      FileSystemPopWindow::~FileSystemPopWindow(){

      }

      void FileSystemPopWindow::updateFileSystemUsage(){

      }

    }
  }
}//namespace Magna