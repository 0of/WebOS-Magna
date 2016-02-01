#include "ProgressBar.h"

#include "render/LinearGradient.h"
using namespace Magna::Render;

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "Controller_p.h"
#include "ProgressBarImplementor.h"

namespace Magna{
  namespace GUI{
    
    ProgressBar::ProgressBar()
      :Controller(){

      m_root->_size_set( IntegerSize(160, 20 ) );

      /*
      LinearGradient *_linearGradient = new LinearGradient( 0, 0, 160, 20 );
      _linearGradient->setColorAt( Color( 224, 224, 224 ), 0.0 );
      _linearGradient->setColorAt( Color( 176, 176, 176 ), 1.0 );
      m_root->m_brush = FillBrush( _linearGradient );
      */
      m_root->_impl_init( new ProgressBarImplementor( *this ) );

    }

    ProgressBar::ProgressBar( sint32 init_val )
      :Controller(){

      m_root->_size_set( IntegerSize(160, 20 ) );

      /*
      LinearGradient *_linearGradient = new LinearGradient( 0, 0, 160, 20 );
      _linearGradient->setColorAt( Color( 224, 224, 224 ), 0.0 );
      _linearGradient->setColorAt( Color( 176, 176, 176 ), 1.0 );
      m_root->m_brush = FillBrush( _linearGradient );
      */
      m_root->_impl_init( new ProgressBarImplementor( *this, init_val ) );

    }

    ProgressBar::ProgressBar( float percentage )
      :Controller(){

      m_root->_size_set( IntegerSize(160, 20 ) );

      LinearGradient *_linearGradient = new LinearGradient( 0, 0, 160, 20 );
      _linearGradient->setColorAt( Color( 224, 224, 224 ), 0.0 );
      _linearGradient->setColorAt( Color( 176, 176, 176 ), 1.0 );
      m_root->m_brush = FillBrush( _linearGradient );

      m_root->_impl_init( new ProgressBarImplementor( *this, percentage * 100 ) );

    }

    ProgressBar::~ProgressBar(){

    }

    void  ProgressBar::setMaximum ( sint32 maximum ){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = reinterpret_cast<ProgressBarImplementor *>(_impl.operator->() );
            
            _impl_ptr->m_max  = maximum;

            if( _impl_ptr->m_max < _impl_ptr->m_min ){
              _impl_ptr->m_max += _impl_ptr->m_min;
              _impl_ptr->m_min = _impl_ptr->m_max - _impl_ptr->m_min;
              _impl_ptr->m_max -= _impl_ptr->m_min;
            }
            
            _impl_ptr->m_value =  _impl_ptr->m_min;
            _impl_ptr->m_text = String( L"0%");
            _impl_ptr->m_barBoundingRect = IntegerRectRegion();

            _impl_ptr->_remeasureText();
            //update
            update();
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
    }

    void  ProgressBar::setMinimum ( sint32 minimum ){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = reinterpret_cast<ProgressBarImplementor *>(_impl.operator->() );

            _impl_ptr->m_min = minimum;

            if( _impl_ptr->m_max < _impl_ptr->m_min ){
              _impl_ptr->m_max += _impl_ptr->m_min;
              _impl_ptr->m_min = _impl_ptr->m_max - _impl_ptr->m_min;
              _impl_ptr->m_max -= _impl_ptr->m_min;
            }

            _impl_ptr->m_value =  _impl_ptr->m_min;
            _impl_ptr->m_text = String( L"0%");
            _impl_ptr->m_barBoundingRect = IntegerRectRegion();

            _impl_ptr->_remeasureText();
            //update
            update();
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
    }

    void  ProgressBar::setRange ( sint32 minimum, sint32 maximum ){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = reinterpret_cast<ProgressBarImplementor *>(_impl.operator->() );
      
            if( maximum <  minimum ){
              maximum += minimum;
              minimum = maximum - minimum;
              maximum -= minimum;
            }

            _impl_ptr->m_min = minimum;
            _impl_ptr->m_max = maximum;

            _impl_ptr->m_value =  _impl_ptr->m_min;
            _impl_ptr->m_text = String( L"0%");
            _impl_ptr->m_barBoundingRect = IntegerRectRegion();

            _impl_ptr->_remeasureText();
            //update
            update();
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
    }

    void ProgressBar::setPercentage( float per ){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = reinterpret_cast<ProgressBarImplementor *>(_impl.operator->() );
          
            _impl_ptr->_setProgressValue( (_impl_ptr->m_max - _impl_ptr->m_min) * per );
            _impl_ptr->_remeasureText();
            //update
            update();

            OnceValueChanged.triggers( _impl_ptr->m_value );
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
    }

    void  ProgressBar::setValue ( sint32 value ){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = reinterpret_cast<ProgressBarImplementor *>(_impl.operator->() );

            _impl_ptr->_setProgressValue( value );
            _impl_ptr->_remeasureText();
            //update
            update();

            OnceValueChanged.triggers( _impl_ptr->m_value );
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
    }

    sint32 ProgressBar::getValue() const{
      sint32 _ret_val = 0;
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            auto _impl_ptr = reinterpret_cast<ProgressBarImplementor *>(_impl.operator->() );
            _ret_val = _impl_ptr->m_value;
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      return _ret_val;
    }

    float ProgressBar::getPercentage() const{
      float _percentage = 0.0;
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            auto _impl_ptr = reinterpret_cast<ProgressBarImplementor *>(_impl.operator->() );
            _percentage =  (static_cast<float>( (_impl_ptr->m_value - _impl_ptr->m_min) ) 
              / static_cast<float>( (_impl_ptr->m_value - _impl_ptr->m_min ) ) );
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      return _percentage;
    }
        
    sint32  ProgressBar::getMaximum () const{
      sint32 _max = 0;
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            auto _impl_ptr = reinterpret_cast<ProgressBarImplementor *>(_impl.operator->() );
            _max =  _impl_ptr->m_max;
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      return _max;
    }

    sint32  ProgressBar::getMinimum () const{
      sint32 _min = 0;
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            auto _impl_ptr = reinterpret_cast<ProgressBarImplementor *>(_impl.operator->() );
            _min =  _impl_ptr->m_min;
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      return _min;
    }

    void  ProgressBar::reset(){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            auto _impl_ptr = reinterpret_cast<ProgressBarImplementor *>(_impl.operator->() );
            _impl_ptr->m_min  =  _impl_ptr->m_min;

            _impl_ptr->m_text = String( L"0%");
            _impl_ptr->m_barBoundingRect.setSize( IntegerSize( 0, 0 ) );

            update();

            OnceValueChanged.triggers( _impl_ptr->m_value );
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
    }

    void ProgressBar::setTextVisible( bool visible ){
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            auto _impl_ptr = reinterpret_cast<ProgressBarImplementor *>(_impl.operator->() );
            
            if( _impl_ptr->m_textVisible != static_cast<uint32>(visible) ){
              _impl_ptr->m_textVisible = visible;

              update();
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
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
    }

    bool  ProgressBar::isTextVisible () const{
      bool _visible = !false;
      try{
        if( !m_root.isNull() ){
          auto && _impl = m_root->_impl_get();
          if( !_impl.isNull() ){
            auto _impl_ptr = reinterpret_cast<ProgressBarImplementor *>(_impl.operator->() );

            _visible = static_cast<bool>(_impl_ptr->m_textVisible);  
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
      }
      return _visible;
    }

  }//namespace GUI
}//namespace Magna
