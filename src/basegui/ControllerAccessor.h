#ifndef CONTROLLERACCESSOR_H
#define CONTROLLERACCESSOR_H

#include "Controller.h"
#include "Controller_p.h"

namespace Magna{
  namespace GUI{

    class ControllerAccessor{
      public:
        inline static SharedPtr<Controller::ControllerRoot> getRoot( Controller * ctrl ){
          SharedPtr<Controller::ControllerRoot> _ret_root;
          if( ctrl != Nullptr ){
            _ret_root = ctrl->m_root;
          }
          return _ret_root;
        }

        inline static SharedPtr<Controller::ControllerRoot> getRoot( const SharedPtr<Controller> & ctrl ){
          SharedPtr<Controller::ControllerRoot> _ret_root;
          if( !ctrl.isNull() ){
            _ret_root = ctrl->m_root;
          }
          return _ret_root;
        }
    };
  }//namespace GUI
}  //namespace Magna

#endif  /*  CONTROLLERACCESSOR_H  */
