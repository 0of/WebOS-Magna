#include "ButtonGroup.h"

#include <random>

#include "Controller_p.h"
#include "ButtonImplementor.h"

namespace Magna{
  namespace GUI{

    ButtonGroup::ButtonGroup()
      :m_buttons()
      ,m_currentToggledButtonIndex(0)
      ,m_isExclusive( false ){

    }

    ButtonGroup::~ButtonGroup(){

      for( auto _iter = m_buttons.begin(); _iter != m_buttons.end(); ++_iter ){
        removeButton( _iter->second );
      }

    }

    void ButtonGroup::removeButtonAt( uint32 index){
      auto _found = m_buttons.find( index );

      if( _found != m_buttons.end() ){
        auto & button = _found->second;
        if( !button.isNull() ){
          auto &_root = button->m_root;
          if( !_root.isNull() ){

            auto _impl = _root->_impl_get();
            if( !_impl.isNull() ){

              auto _impl_ptr = _impl.operator->();

              ButtonImplementor *_button_impl_ptr = reinterpret_cast<ButtonImplementor *>(_impl_ptr);

              if( _button_impl_ptr->m_bindingGroup == this
                && _button_impl_ptr->m_groupIndex == index ){

                  //Buttons::iterator _erase_at = (m_buttons.begin() + _button_impl_ptr->m_groupIndex);
                  m_buttons.erase( _found );

                  _button_impl_ptr->m_bindingGroup = Nullptr;
                  _button_impl_ptr->m_groupIndex = 0;
              }
            }
          }
        }
      }

    }

    uint32 ButtonGroup::addButton( const SharedPtr<Button>& button ){
      uint32 _added_index = 0;
      if( !button.isNull() ){
        auto &_root = button->m_root;
        if( !_root.isNull() ){

          auto _impl = _root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = _impl.operator->();

            ButtonImplementor *_button_impl_ptr = reinterpret_cast<ButtonImplementor *>(_impl_ptr);

            if( _button_impl_ptr->m_bindingGroup == Nullptr ){

              std::random_device _dev_gen;

              std::default_random_engine _base32_ram( _dev_gen() );

              uint32 _index = 0;
              while( [&]() -> bool{ _index = _base32_ram()
                ; return _index == 0 || m_buttons.count( _index )  != 0;  }() ){}

              _added_index = _index;
              m_buttons.emplace( std::make_pair( _index, button )  );

              _button_impl_ptr->m_bindingGroup = this;
              _button_impl_ptr->m_groupIndex = _added_index;
            }
          }
        }
      }
      return _added_index;
    }

    void ButtonGroup::removeButton( const SharedPtr<Button>& button){
      if( !button.isNull() ){
        auto &_root = button->m_root;
        if( !_root.isNull() ){

          auto _impl = _root->_impl_get();
          if( !_impl.isNull() ){

            auto _impl_ptr = _impl.operator->();

            ButtonImplementor *_button_impl_ptr = reinterpret_cast<ButtonImplementor *>(_impl_ptr);

            if( _button_impl_ptr->m_bindingGroup == this
              && _button_impl_ptr->m_groupIndex != 0 ){

              auto _found = m_buttons.find(  _button_impl_ptr->m_groupIndex  );
              if( _found != m_buttons.end() ){
                m_buttons.erase( _found );
              }

              _button_impl_ptr->m_bindingGroup = Nullptr;
              _button_impl_ptr->m_groupIndex = 0;
            }
          }
        }
      }
    }

    void ButtonGroup::setButtonToggled( uint32 index ){
      if( m_currentToggledButtonIndex != index ){
        auto _found = m_buttons.find(  index  );
        if( _found != m_buttons.end() ){

          if( m_isExclusive ){

            if( m_currentToggledButtonIndex != 0  ){

              auto _current_button = m_buttons.find(  m_currentToggledButtonIndex  );
              if( _current_button != m_buttons.end() ){
                auto &_curr_toggled_button = _current_button->second;

                if( !_curr_toggled_button.isNull() ){
                  _curr_toggled_button->setToggled( false );
                }
              }
            }
            m_currentToggledButtonIndex = index;

          }
          OnceButtonToggled.triggers( index );
        }
      }
    }

    void ButtonGroup::setButtonUntoggled( uint32 index ){
      auto _found = m_buttons.find(  index  );
      if( _found != m_buttons.end() ){
        m_currentToggledButtonIndex = 0;

        OnceButtonUntoggled.triggers( index );
      }
    }

  }//namespace GUI
}//namespace Magna
