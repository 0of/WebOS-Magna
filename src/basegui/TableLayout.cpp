#include "TableLayout.h"

#include "Layout_p.h"

#include "inner/InnerPrivateDataNullPointerException.h"
#include "inner/InnerIndexNotFoundException.h"
using namespace Magna::Inner;

#include "basedef/Size.h"
using namespace Magna::Core;

#include "ControllerAccessor.h"

namespace Magna{
  namespace GUI{

    struct TableLayoutElement{
      uint16 m_rowSpan;
      uint16 m_colSpan;
      uint16 m_rowAt  : 15 ;
      uint16 m_isAutoDeployed : 1;

      uint16 m_colAt;

      TableLayoutElement()
        :m_rowSpan(1)
        ,m_colSpan(1)
        ,m_isAutoDeployed( 0 )
        ,m_colAt(0)
        ,m_rowAt(0){

      }

      TableLayoutElement( uint16 rowSpan,  uint16 colSpan, uint16 row, uint16 col)
        :m_rowSpan(rowSpan)
        ,m_colSpan( colSpan )
        ,m_isAutoDeployed( 0 )
        ,m_rowAt(row)
        ,m_colAt(col){

      }

      TableLayoutElement( const TableLayoutElement& element )
        :m_rowSpan(element.m_rowSpan)
        ,m_colSpan(element.m_colSpan)
        ,m_isAutoDeployed( element.m_isAutoDeployed )
        ,m_rowAt(element.m_rowAt)
        ,m_colAt(element.m_colAt){

      }
    };
    
    class TableLayout::PrivateData{
      public:
        PrivateData()
          :m_rowCount( 0 )
          ,m_colCount( 0 )
          ,m_horizontalSpacing( 10 )
          ,m_verticalSpacing( 10 )
          ,m_autoDeployBreakPolicy( TableLayout::AutoDeployBreakPolicy_HorizontalBreak )
          ,m_eachAvgSize()
          ,m_autoDeloyedElementCount(0)
          ,m_elements(){

        }

        ~PrivateData(){

        }

        uint16 m_rowCount;
        uint16 m_colCount;

        uint32 m_autoDeloyedElementCount;

        uint32 m_horizontalSpacing;
        uint32 m_verticalSpacing;

        TableLayout::AutoDeployBreakPolicy m_autoDeployBreakPolicy;

        IntegerSize m_eachAvgSize;

        std::vector<TableLayoutElement> m_elements;
    };

    TableLayout::TableLayout()
      :Layout()
      ,m_data( new PrivateData ){

    }

    TableLayout::~TableLayout(){

    }

    uint16 TableLayout::getHorizontalSpacing() const{
      uint16 _h_spacing = 0;
      try{
        if( !m_data.isNull() && !m_layout.isNull() ){
          _h_spacing = m_data->m_horizontalSpacing;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
      return _h_spacing;
    }

    uint16 TableLayout::getVerticalSpacing() const{
      uint16 _v_spacing = 0;
      try{
        if( !m_data.isNull() && !m_layout.isNull() ){
          _v_spacing = m_data->m_verticalSpacing;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
      return _v_spacing;
    }

    void TableLayout::setHorizontalSpacing( uint16 spacing ){
      try{
        if( !m_data.isNull() && !m_layout.isNull() ){
          m_data->m_horizontalSpacing = spacing;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
    }

    void TableLayout::setVerticalSpacing( uint16 spacing ){
      try{
        if( !m_data.isNull() && !m_layout.isNull() ){
          m_data->m_verticalSpacing = spacing;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex ){
        _ex.what();
      }
    }  

    void TableLayout::measure() {

      try{
        if( !m_data.isNull() && !m_layout.isNull() ){

          if( m_data->m_elements.size() == m_layout->m_controllers.size() ){
            Layout::measure();

            m_layout->m_realRect = IntegerRectRegion();
            //calculate the whole size
            //make sure won't numeric overflow
            IntegerSize _whole_size = IntegerSize( m_data->m_rowCount * ( m_data->m_eachAvgSize.getWidth() + m_data->m_horizontalSpacing ) + m_data->m_horizontalSpacing
              , m_data->m_colCount * ( m_data->m_eachAvgSize.getHeight() + m_data->m_verticalSpacing ) + m_data->m_verticalSpacing );

            m_layout->m_realRect = IntegerRectRegion( m_layout->m_layoutOffset, _whole_size.getWidth(), _whole_size.getHeight() );
        
          }
          else{
            throw std::runtime_error("Element Size Won't Match");
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

    void TableLayout::deploy() {
      try{
        if( !m_data.isNull() && !m_layout.isNull() ){

          Layout::deploy();

          if( m_data->m_elements.size() == m_layout->m_controllers.size() ){
            auto &_controllers = m_layout->m_controllers;
            auto &_layout_elements = m_data->m_elements;
            const auto &_parent_size = m_layout->m_windowAsParent ?
              m_layout->m_wnd->getSize() : m_layout->m_contr->getSize();

            //average width & height
            const auto & _avg_width = m_data->m_eachAvgSize.getWidth() + m_data->m_horizontalSpacing;
            const auto & _avg_height = m_data->m_eachAvgSize.getHeight() + m_data->m_verticalSpacing;

            //calculate containable column and row number
            auto _containable_row = 0;
            auto _containable_col = 0;
            if( m_data->m_autoDeloyedElementCount != 0 ){
              auto _break_policy = m_data->m_autoDeployBreakPolicy ;
              if( _break_policy == TableLayout::AutoDeployBreakPolicy_NoBreak ){
                _containable_row = m_data->m_rowCount;
                _containable_col = m_data->m_colCount;
              }
              else if( _break_policy == TableLayout::AutoDeployBreakPolicy_HorizontalBreak ){
                _containable_row =  (_parent_size.getWidth() - m_data->m_horizontalSpacing) / _avg_width;
                if( _containable_row == 0 ){
                  _containable_row = 1;
                }

                _containable_col =m_data->m_autoDeloyedElementCount / _containable_row + 1;
              }
              else if( _break_policy == TableLayout::AutoDeployBreakPolicy_VerticalBreak ){
                _containable_col = (_parent_size.getHeight() - m_data->m_verticalSpacing ) / _avg_height;
                if( _containable_col == 0 ){
                  _containable_col = 1;
                }

                _containable_row = m_data->m_autoDeloyedElementCount / _containable_col + 1;
              }
              else{
                throw InnerIndexNotFoundException();
              }
            }      
            
            //index traversal
            auto _auto_deploy_counter = 0;
            //offset
            const auto &_offset = m_layout->m_layoutOffset;

            for( auto _i = 0; _i != m_data->m_elements.size() ; ++_i, ++_auto_deploy_counter ){
              auto &_each_controller = _controllers[_i];

              if( !_each_controller.isNull() ){
                //get root
                auto &&_each_root  = ControllerAccessor::getRoot(_each_controller);
                if( !_each_root.isNull() ){

                  auto &_each_element = _layout_elements[_i];

                  //auto deployed
                  if( _each_element.m_isAutoDeployed ){
                    auto _break_policy = m_data->m_autoDeployBreakPolicy ;
                    if( _break_policy == TableLayout::AutoDeployBreakPolicy_HorizontalBreak ){
                      IntegerDyadCoordinate _ctrl_pos( (_i % _containable_row) * _avg_width + _offset.getX()
                        , (_i / _containable_row) * _avg_height + _offset.getY() );
                      _each_root->_pos_set( _ctrl_pos );
                    }
                    else if( _break_policy == TableLayout::AutoDeployBreakPolicy_VerticalBreak ){
                      IntegerDyadCoordinate _ctrl_pos( (_i / _containable_col) * _avg_width + _offset.getX()
                        , (_i % _containable_col) * _avg_height + _offset.getY() );
                      _each_root->_pos_set( _ctrl_pos );
                    }
                    //
                    
                  }
                  else{
                    IntegerDyadCoordinate _ctrl_pos( _each_element.m_rowAt * _avg_width + _offset.getX()
                      , _each_element.m_colAt * _avg_height + _offset.getY() );
                    _each_root->_pos_set( _ctrl_pos );
                  }
                  
                }
                else{
                  throw InnerPrivateDataNullPointerException();
                }        

              }
              else{
                throw InnerPrivateDataNullPointerException();
              }

            }
          }
          else{
            throw std::runtime_error("Element Size Won't Match");
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

    void TableLayout::addController( const SharedPtr<Controller>& controller, uint16 rowAt, uint16 colAt ){
      assert( rowAt < 1024 && colAt < 1024 );

      if( !controller.isNull() ){

        try{
          if( !m_data.isNull() ){
            //controller size
            const auto & _size = controller->getSize();
            auto &_avg_size = m_data->m_eachAvgSize;

            if( _size.getWidth() > _avg_size.getWidth() ){
              _avg_size.setWidth( _size.getWidth() );
            }

            if( _size.getHeight() > _avg_size.getHeight() ){
              _avg_size.setHeight( _size.getHeight() );
            }

            if( colAt >= m_data->m_colCount ){
              m_data->m_colCount = colAt + 1;
            }

            if( rowAt >= m_data->m_rowCount ){
              m_data->m_rowCount = rowAt + 1;
            }

            TableLayoutElement _gen_element(1, 1,rowAt, colAt) ;
            m_data->m_elements.push_back ( _gen_element );

            Layout::addChildController( controller );
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }

        catch( const InnerPrivateDataNullPointerException _ex ){
          _ex.what();
        }
      }
    }

    void TableLayout::addController( const SharedPtr<Controller>& controller, uint16 rowAt, uint16 colAt, uint16 rowSpan, uint16 colSpan ){
      assert( rowAt < 1024 && colAt < 1024 );
      //span couldn't be larger than 1024
      assert( rowSpan < 1024 && colSpan < 1024 );

      if( !controller.isNull() ){
        try{
          if( !m_data.isNull() ){
            //controller size
            const auto & _size = controller->getSize();
            auto &_avg_size = m_data->m_eachAvgSize;

            if( (_size.getWidth() / rowSpan)  > _avg_size.getWidth() ){
              _avg_size.setWidth( _size.getWidth() );
            }

            if((_size.getHeight() / colSpan ) > _avg_size.getHeight() ){
              _avg_size.setHeight( _size.getHeight() );
            }

            if( colAt >= m_data->m_colCount ){
              m_data->m_colCount = colAt + 1;
            }

            if( rowAt >= m_data->m_rowCount ){
              m_data->m_rowCount = rowAt + 1;
            }

            TableLayoutElement _gen_element(rowSpan, colSpan , rowAt, colAt) ;
            m_data->m_elements.push_back ( _gen_element );

            Layout::addChildController( controller );
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }

        catch( const InnerPrivateDataNullPointerException _ex ){
          _ex.what();
        }
      }
    }

    void TableLayout::addAutoDeployController( const SharedPtr<Controller>& controller ){
      if( !controller.isNull() ){      

        const auto & _size = controller->getSize();
        auto &_avg_size = m_data->m_eachAvgSize;

        if( _size.getWidth() > _avg_size.getWidth() ){
          _avg_size.setWidth( _size.getWidth() );
        }

        if( _size.getHeight() > _avg_size.getHeight() ){
          _avg_size.setHeight( _size.getHeight() );
        }

        TableLayoutElement _gen_element;
        _gen_element.m_isAutoDeployed = !false;
      
        m_data->m_elements.push_back ( _gen_element );

        ++(m_data->m_autoDeloyedElementCount);

        Layout::addChildController( controller );            
      }
    }

    void TableLayout::addAutoDeployControllers( const std::vector<SharedPtr<Controller> >& controllers, AutoDeployBreakPolicy policy ){    
      for(auto _iter = controllers.begin(); _iter != controllers.end(); ++_iter ){
        //controller size
        const auto & _size = (*_iter)->getSize();
        auto &_avg_size = m_data->m_eachAvgSize;

        if( _size.getWidth() > _avg_size.getWidth() ){
          _avg_size.setWidth( _size.getWidth() );
        }

        if( _size.getHeight() > _avg_size.getHeight() ){
          _avg_size.setHeight( _size.getHeight() );
        }

        TableLayoutElement _gen_element;
        _gen_element.m_isAutoDeployed = !false;

        m_data->m_elements.push_back ( _gen_element );

        Layout::addChildController( *_iter );
      }
      m_data->m_autoDeloyedElementCount += controllers.size();
      setAutoDeployBreakPolicy( policy );
    }

    void TableLayout::setAutoDeployBreakPolicy( AutoDeployBreakPolicy policy ){
      assert( policy <= TableLayout::AutoDeployBreakPolicy_VerticalBreak );

      try{
        if( !m_data.isNull() ){
          m_data->m_autoDeployBreakPolicy = policy;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException _ex ){
        _ex.what();
      }
    }
  
  }//namespace GUI
}//namespace Magna
