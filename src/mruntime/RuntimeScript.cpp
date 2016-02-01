#include "RuntimeScript.h"

#include "basegui/GUIDef.h"

namespace Magna{
  namespace Runtime{
    const assic_char * RuntimeScript::shared_JavaScript_standard = "ECMAScript 5";

    const assic_char *RuntimeScript::shared_HTML_frame_begin = "\
                               <!DOCTYPE html><html>";
                              
    const assic_char *RuntimeScript::shared_HTML_frame_end = "</html>";

    const assic_char *RuntimeScript::shared_HTML_frame_head_script_begin ="\
                                       <head><script type=\"text/javascript\">";

    const assic_char *RuntimeScript::shared_HTML_frame_head_script_end = "\
                                        </script></head>";

    const assic_char *RuntimeScript::shared_HTML_frame_body_script_begin = "\
                                         <body><script type=\"text/javascript\">";

    const assic_char *RuntimeScript::shared_HTML_frame_body_script_end = "\
                                       </script></body>";              


    const  assic_char *RuntimeScript::shared_JavaScript_Service_Provider_Window = "WindowManagerServiceProvider.";
    const  assic_char *RuntimeScript::shared_JavaScript_Service_Provider_Controller = "ControllerManagerServiceProvider.";
    const  assic_char *RuntimeScript::shared_JavaScript_Functionality_Window_Rubber_Band = "WindowRubberBandFunctionality.";

    const  assic_char *RuntimeScript::shared_JavaScript_Service_open_new_window = "openNewWindow";
    const  assic_char *RuntimeScript::shared_JavaScript_Service_set_window_visible = "setWindowVisible";
    const assic_char * RuntimeScript::shared_JavaScript_Service_set_window_hidden  = "setWindowInvisible";
    const  assic_char *RuntimeScript::shared_JavaScript_Service_set_window_size = "setWindowSize";
    const assic_char * RuntimeScript::shared_JavaScript_Service_set_window_pos  = "setWindowPos";
    const assic_char * RuntimeScript::shared_JavaScript_Service_close_window = "closeWindow";
    const assic_char * RuntimeScript::shared_JavaScript_Service_window_focus_in = "setWindowFocusIn";
    const assic_char * RuntimeScript::shared_JavaScript_Service_window_focus_out = "setWindowFocusOut";


    const assic_char * RuntimeScript::shared_JavaScript_Service_register_new_controller = "appendNewController";
    const assic_char *RuntimeScript::shared_JavaScript_Service_register_protogenous_controller = "appendProtogenousController";
    const assic_char *RuntimeScript::shared_JavaScript_Service_unregister_controller = "removeController";
    const assic_char * RuntimeScript::shared_JavaScript_Service_controller_resize  = "setControllerSize";
    const assic_char * RuntimeScript::shared_JavaScript_Service_controller_move = "setControllerPos";
    const assic_char * RuntimeScript::shared_JavaScript_Service_wrapper_resize = "setWrapperSize";
    const assic_char * RuntimeScript::shared_JavaScript_Service_content_resize = "setContentSize";

    const  assic_char *RuntimeScript::shared_JavaScript_Functionality_trigger_translate = "triggerTranslate";
    const  assic_char *RuntimeScript::shared_JavaScript_Functionality_trigger_stretch = "triggerStretch";
    const  assic_char *RuntimeScript::shared_JavaScript_Functionality_rubber_band_init = "initDesktopContext";

    //#
    /*
    const  assic_char *RuntimeScript::shared_kernel_JavaScript_Window_Manager_Service_script  = "\
      var Magna_WindowManagerService = function (_frameBody){\
        \
        this.m_frameBody = _frameBody;\
        \
        Magna_WindowManagerService.prototype.openNewWindow = function(_gen_Id, _styleString,_width,_height){\
        var _gen_element = document.createElement('canvas');\
        _gen_element.id = _gen_Id;\
        _gen_element.width=_width;\
        _gen_element.height=_height;\
        _gen_element.style.cssText = _styleString;\
        _gen_element.setAttribute('tabindex',0 );\
        _gen_element.focus();\
        \
        Object.defineProperty( _gen_element,'pro_is_hover_on', {\
        set : function(_isOn){\
        Magna_ListenerManagerService._switchHoverEvent( this,_isOn );\
        },enumerable: true,configurable: true} );\
        \
        _gen_element.pro_is_hover_on = false;\
        Magna_ListenerManagerService._registers( _gen_element );\
        this.m_frameBody.appendChild( _gen_element );\
        };\
        \
        Magna_WindowManagerService.prototype.setWindowVisible = function(_id){\
        var _found_canvas = document.getElementById( _id );\
        if( _found_canvas != null ){\
          _found_canvas.style.visibility = 'visible';\
        }};\
        \
        Magna_WindowManagerService.prototype.setWindowInvisible = function(_id){\
        var _found_canvas = document.getElementById( _id );\
       if( _found_canvas != null ){\
        _found_canvas.style.visibility = 'hidden';\
       }};\
       \
       Magna_WindowManagerService.prototype.setWindowSize = function(_id, width, height){\
      var _found_canvas = document.getElementById( _id );\
      if( _found_canvas != null ){\
               _found_canvas.width = width;\
               _found_canvas.height = height;\
      }};\
      \
      Magna_WindowManagerService.prototype.setWindowPos = function(_id, x, y){\
            var _found_canvas = document.getElementById( _id );\
            if( _found_canvas != null ){\
               _found_canvas.style.left = x;\
               _found_canvas.style.top = y;\
            }};\
      };";
     
     _gen_element.onmousedown = function(e){\
     \
     var left_diff = e.pageX - _gen_element.offsetLeft;\
     var right_diff = e.pageX - _gen_element.offsetLeft - _gen_element.offsetWidth;\
     \
     var top_diff = e.pageY - _gen_element.offsetTop;\
     var bottom_diff =  e.pageY - _gen_element.offsetTop- _gen_element.offsetHeight;\
     \
     var hor_src = 0;\
     var ver_src = 0;\
     \
     if( left_diff < _gen_element.clientLeft && left_diff > -1 ){\
     hor_src = 1;\
     }\
     else if( right_diff < 1 && right_diff > (-_gen_element.clientLeft)){\
     hor_src = 2;\
     }\
     else{}\
     \
     if( top_diff < _gen_element.clientTop && top_diff > -1 ){\
     ver_src = 1;\
     }\
     else if(bottom_diff < 1 && bottom_diff >(-_gen_element.clientTop)){\
     ver_src = 2;\
     }\
     else{}\
     \
     if( hor_src != 0 || ver_src != 0 ){\
     WindowRubberBandFunctionality.triggerStretch( _gen_Id ,hor_src, ver_src, e.pageX, e.pageY );\
     }\
     };\
      */

    const  assic_char *RuntimeScript::shared_kernel_JavaScript_Window_Manager_Service_script  = "\
      var Magna_WindowManagerService = function (_frameBody){\
        \
        this.m_frameBody = _frameBody;\
        \
        Magna_WindowManagerService.prototype.openNewWindow = function(_gen_Id, _styleString){\
        var _gen_element = document.createElement(\"div\");\
        _gen_element.id = _gen_Id;\
        _gen_element.style.cssText = _styleString;\
        \
        this.m_frameBody.appendChild( _gen_element );\
        };\
        \
        Magna_WindowManagerService.prototype.closeWindow = function(_Id){\
        var _found_element = document.getElementById(_Id);\
        \
        this.m_frameBody.removeChild( _found_element );\
        };\
        \
        Magna_WindowManagerService.prototype.setWindowVisible = function(_id){\
        var _found_window = document.getElementById( _id );\
        if( _found_window != null ){\
          _found_window.style.visibility = 'visible';\
        }};\
        \
        Magna_WindowManagerService.prototype.setWindowInvisible = function(_id){\
        var _found_window = document.getElementById( _id );\
        if( _found_window != null ){\
          _found_window.style.visibility = 'hidden';\
        }};\
        \
        Magna_WindowManagerService.prototype.setWindowFocusIn = function(_id){\
        var _found_window = document.getElementById( _id );\
        if( _found_window != null ){\
        _found_window.style.zIndex = 100;\
        }};\
        \
        Magna_WindowManagerService.prototype.setWindowFocusOut = function(_id){\
        var _found_window = document.getElementById( _id );\
        if( _found_window != null ){\
        _found_window.style.zIndex = 0;\
        }};\
       \
        Magna_WindowManagerService.prototype.setWindowRect = function(_id, x, y, width, height){\
        \
         var _found_window = document.getElementById( _id );\
         if( _found_window != null ){\
           _found_window.style.left = x + 'px';\
           _found_window.style.top = y + 'px';\
           _found_window.style.width = width+ 'px';\
           _found_window.style.height = height+ 'px';\
         }};\
       \
         Magna_WindowManagerService.prototype.setWindowSize = function(_id,width, height){\
         \
           var _found_window = document.getElementById( _id );\
           if( _found_window != null ){\
             _found_window.style.width = width+ 'px';\
             _found_window.style.height = height+ 'px';\
           }\
         };\
         Magna_WindowManagerService.prototype.setWindowPos = function(_id, x, y){\
           var _found_window = document.getElementById( _id );\
           if( _found_window != null ){\
             _found_window.style.left = x + 'px';\
             _found_window.style.top = y + 'px';\
           }\
         }};";

    //#
    /*
    const assic_char * RuntimeScript::shared_JavaScript_Listener_Manager_Service_script ="\
        var Magna_ListenerManagerService = Magna_ListenerManagerService ||{\
        \
        _registers : function(_element){\
        \
        _element.addEventListener('mousedown', function(event){\
        \
                Magna_MousePressed_EListener(_element, event) }, false );\
        \
        _element.addEventListener('keydown', function(event){\
        \
                Magna_keyPressed_EListener(_element, event) }, false );\
        },\
        \
      _switchHoverEvent : function(_element,_isOn){\
      }  };";                                                
    */
    const assic_char * RuntimeScript::shared_JavaScript_Listener_Manager_Service_script ="\
        var Magna_ControllerEventListenerRegisterService = Magna_ControllerEventListenerRegisterService ||{\
        \
        _registers : function(_element){\
        \
        _element.addEventListener('mousedown', function(event){\
                Magna_MousePressed_EListener(_element, event) }, false );\
        \
        _element.addEventListener('mouseup', function(event){\
        Magna_MouseReleased_EListener(_element, event) }, false );\
        \
        _element.addEventListener('keydown', function(event){\
                Magna_keyPressed_EListener(_element, event) }, false );\
        \
        _element.addEventListener('mouseover', function(){\
        Magna_HoverIn_EListener(_element) }, false );\
        \
        _element.addEventListener('mousemove', function(){\
        Magna_MouseMove_EListener(_element) }, false );\
        \
        _element.addEventListener('mouseout', function(){\
        Magna_HoverOut_EListener(_element) }, false );\
        },\
        \
      _switchHoverEvent : function(_element,_isOn){\
      }  };";  

    const assic_char * RuntimeScript::shared_JavaScript_Listener_script = "\
      var Magna_HoverIn_EListener = function(element){\
        DispatcherNode.dispatchHoverIn(element.id)\
      };\
      var Magna_HoverOut_EListener = function(element){\
        DispatcherNode.dispatchHoverOut(element.id)\
      };\
      var Magna_keyPressed_EListener = function(element){\
        var _trigger_id = element.id;\
        \
        eventArgs = eventArgs || event;\
        var _keyCode = eventArgs.keyCode || eventArgs.which || eventArgs.charCode;\
        var _modifiers = 0;\
        if( eventArgs.ctrlKey ){\
          _modifiers |= 0x00040000;\
        }\
        if( eventArgs.shiftKey ){\
          _modifiers |= 0x00020000;\
        }\
        if( eventArgs.altKey ){\
          _modifiers |= 0x00080000;\
        }\
        DispatcherNode.dispatchKeyPressed(_trigger_id, _keyCode, _modifiers );\
      };\
      \
      var Magna_MousePressed_EListener = function(element,eventArgs){\
      element.setAttribute('ispressed',1);\
        var _trigger_id = element.id;\
        \
        eventArgs = eventArgs || event;\
        var _trigger_button = eventArgs.button;\
        var _modifiers = 0;\
        if( eventArgs.ctrlKey ){\
          _modifiers |= 0x00040000;\
        }\
        if( eventArgs.shiftKey ){\
          _modifiers |= 0x00020000;\
        }\
        if( eventArgs.altKey ){\
          _modifiers |= 0x00080000;\
        }\
        DispatcherNode.dispatchMousePressed(_trigger_id, eventArgs.clientX, eventArgs.clientY, _trigger_button, _modifiers );\
      };\
      \
      var Magna_MouseMove_EListener = function(element,eventArgs){\
      if( parseInt(element.getAttribute('ispressed')) != 0 ){\
          var _trigger_id = element.id;\
          eventArgs = eventArgs || event;\
          var _trigger_button = eventArgs.button;\
          var _modifiers = 0;\
          if( eventArgs.ctrlKey ){\
            _modifiers |= 0x00040000;\
          }\
          if( eventArgs.shiftKey ){\
            _modifiers |= 0x00020000;\
          }\
          if( eventArgs.altKey ){\
            _modifiers |= 0x00080000;\
          }\
          DispatcherNode.dispatchMousePressingMoved(_trigger_id, eventArgs.clientX, eventArgs.clientY, _trigger_button, _modifiers );\
        }\
      };\
        \
      var Magna_MouseReleased_EListener = function(element,eventArgs){\
        element.setAttribute('ispressed',0);\
        var _trigger_id = element.id;\
        \
        eventArgs = eventArgs || event;\
        var _trigger_button = eventArgs.button;\
        var _modifiers = 0;\
        if( eventArgs.ctrlKey ){\
          _modifiers |= 0x00040000;\
        }\
        if( eventArgs.shiftKey ){\
          _modifiers |= 0x00020000;\
        }\
        if( eventArgs.altKey ){\
          _modifiers |= 0x00080000;\
        }\
        DispatcherNode.dispatchMouseReleased(_trigger_id, eventArgs.clientX, eventArgs.clientY, _trigger_button, _modifiers );\
      };";

#ifdef MAGNA_DIV_CANVAS_WRAPPER
      const  assic_char *RuntimeScript::shared_kernel_JavaScript_Controller_Manager_Service_script = "\
          var Magna_ControllerManagerService = function (){\
            Magna_ControllerManagerService.prototype.appendNewController = function(_gen_Id, _parent_Id, _styleString, width, height){\
            var _gen_element_wrapper = document.createElement(\"div\");\
            var _gen_element = document.createElement(\"canvas\");\
            \
            _gen_element.id = _gen_Id;\
            _gen_element.width = width;\
            _gen_element.height = height;\
            \
            _gen_element_wrapper.id=(_gen_Id+'w');\
            _gen_element_wrapper.style.cssText = _styleString;\
            _gen_element.setAttribute('tabindex',0 );\
            _gen_element.setAttribute('ispressed', 0);\
            _gen_element.focus();\
              Object.defineProperty( _gen_element,\"pro_is_hover_on\", {\
                set : function(_isOn){\
                  Magna_ControllerEventListenerRegisterService._switchHoverEvent( this,_isOn );\
                },enumerable: true,configurable: true} );\
            \
            _gen_element.pro_is_hover_on = false;\
            Magna_ControllerEventListenerRegisterService._registers( _gen_element );\
            \
            _gen_element_wrapper.appendChild(_gen_element);  \
            var _parent_ = document.getElementById( _parent_Id );\
            if( _parent_ != null ){\
              _parent_.appendChild( _gen_element_wrapper );\
              \
            }};\
            Magna_ControllerManagerService.prototype.appendProtogenousController = function(_gen_Id, _parent_Id, _styleString, element_type, init_f ){\
            var _gen_element_wrapper = document.createElement(\"div\");\
            var _gen_element = document.createElement(element_type);\
            _gen_element.id = _gen_Id;\
            \
            _gen_element.style.cssText = _styleString;\
            _gen_element_wrapper.id=(_gen_Id+'w');\
            _gen_element_wrapper.style.cssText = _styleString;\
            _gen_element.setAttribute('tabindex',0 );\
            _gen_element.focus();\
            init_f(_gen_element);\
            alert(0);\
            \
              Object.defineProperty( _gen_element,\"pro_is_hover_on\", {\
                set : function(_isOn){\
                  Magna_ControllerEventListenerRegisterService._switchHoverEvent( this,_isOn );\
                },enumerable: true,configurable: true} );\
            _gen_element.pro_is_hover_on = false;\
            Magna_ControllerEventListenerRegisterService._registers( _gen_element );\
            _gen_element_wrapper.appendChild(_gen_element);  \
            var _parent_ = document.getElementById( _parent_Id );\
            if( _parent_ != null ){\
            _parent_.appendChild( _gen_element_wrapper );\
            alert(0);\
            \
            }};\
          Magna_ControllerManagerService.prototype.setControllerVisible = function(_id){\
            var _found_ = document.getElementById( _id );\
            if( _found_ != null ){\
              _found_.style.visibility = 'visible';\
            }};\
          Magna_ControllerManagerService.prototype.setControllerInvisible = function(_id){\
            var _found_ = document.getElementById( _id );\
            if( _found_ != null ){\
              _found_.style.visibility = 'hidden';\
            }};\
            Magna_ControllerManagerService.prototype.setControllerSize = function(_id, width, height){\
            var _found_ = document.getElementById( _id );\
            var _found_wrapper = document.getElementById( (_id + 'w') );\
            if( _found_ != null && _found_wrapper != null){\
            _found_.width=width;\
            _found_.height=height;\
            _found_wrapper.style.width = width + 'px';\
            _found_wrapper.style.height = height + 'px';\
            }};\
            Magna_ControllerManagerService.prototype.removeController = function(_id){\
            var _wrap_id =  _id + 'w';\
            var _found_ = document.getElementById( _wrap_id);\
            if( _found_ != null ){\
            _found_.parentNode.removeChild(_found_);\
            }};\
            Magna_ControllerManagerService.prototype.setWrapperSize = function(_id, width, height){\
            var _wrap_id =  _id + 'w';\
            var _found_ = document.getElementById( _wrap_id);\
            if( _found_ != null ){\
            _found_.style.width = width + 'px';\
            _found_.style.height = height + 'px';\
            }};\
            Magna_ControllerManagerService.prototype.setContentSize = function(_id, width, height){\
            var _found_ = document.getElementById( _id);\
            if( _found_ != null ){\
            _found_.width = width;\
            _found_.height = height;\
            }};\
          Magna_ControllerManagerService.prototype.setControllerPos = function(_id, x, y){\
            var _found_ = document.getElementById( _id );\
            if( _found_ != null ){\
              _found_.style.left = x + 'px';\
              _found_.style.top = y + 'px';\
            }};};";
#else
    const  assic_char *RuntimeScript::shared_kernel_JavaScript_Controller_Manager_Service_script = "\
          var Magna_ControllerManagerService = function (){\
            Magna_ControllerManagerService.prototype.appendNewController = function(_parent_Id, _gen_Id, _styleString, width, height){\
            var _gen_element = document.createElement(\"canvas\");\
            \
            _gen_element.id = _gen_Id;\
            _gen_element.width = width;\
            _gen_element.height = height;\
            _gen_element.style.cssText = _styleString;\
            _gen_element.setAttribute('tabindex',0 );\
            _gen_element.focus();\
              Object.defineProperty( _gen_element,\"pro_is_hover_on\", {\
                set : function(_isOn){\
                  Magna_ControllerEventListenerRegisterService._switchHoverEvent( this,_isOn );\
                },enumerable: true,configurable: true} );\
            \
            _gen_element.pro_is_hover_on = false;\
            Magna_ControllerEventListenerRegisterService._registers( _gen_element );\
            var _window_ = document.getElementById( _parent_Id );\
            if( _window_ != null ){\
              _window_.appendChild( _gen_element );\
            }};\
            Magna_ControllerManagerService.prototype.appendProtogenousController = function(_win_Id, _gen_Id, element_type, type, _styleString){\
            var _gen_element = document.createElement(element_type);\
            _gen_element.id = _win_Id;\
            _gen_element.type=type;\
            _gen_element.style.cssText = _styleString;\
              Object.defineProperty( _gen_element,\"pro_is_hover_on\", {\
                set : function(_isOn){\
                  Magna_ControllerEventListenerRegisterService._switchHoverEvent( this,_isOn );\
                },enumerable: true,configurable: true} );\
            _gen_element.pro_is_hover_on = false;\
            Magna_ControllerEventListenerRegisterService._registers( _gen_element );\
            var _window_ = document.getElementById( _win_Id );\
            if( _window_ != null ){\
              _window_.appendChild( _gen_element );\
            }};\
          Magna_ControllerManagerService.prototype.setControllerVisible = function(_id){\
            var _found_ = document.getElementById( _id );\
            if( _found_ != null ){\
              _found_.style.visibility = 'visible';\
            }};\
          Magna_ControllerManagerService.prototype.setWindowInvisible = function(_id){\
            var _found_ = document.getElementById( _id );\
            if( _found_ != null ){\
              _found_.style.visibility = 'hidden';\
            }};\
          Magna_ControllerManagerService.prototype.setWindowSize = function(_id, width, height){\
            var _found_ = document.getElementById( _id );\
            if( _found_ != null ){\
              _found_.style.width = width;\
              _found_.style.height = height;\
            }};\
          Magna_ControllerManagerService.prototype.setWindowPos = function(_id, x, y){\
            var _found_ = document.getElementById( _id );\
            if( _found_ != null ){\
              _found_.style.left = x;\
              _found_.style.top = y;\
            }};};";
#endif  
    
    const assic_char * RuntimeScript::shared_kernel_JavaScript_Window_Rubber_Band_Functionality_script = "var Magna_WindowRubberBand = function(){\
      Magna_WindowRubberBand.RubberBandViewFactory = function(){\
        var _gen_div = document.createElement('div');\
        if( _gen_div != null ){\
          _gen_div.style.cssText = 'border:5px solid white;position: absolute; left: 0px; top: 0px; width: 20px; height: 20px; zindex=900;';\
          document.body.appendChild( _gen_div );\
        }\
        return _gen_div;\
      };\
      \
      var stretch_horizontal_src_enum = {\
        NotSet : 0,\
        Left : 1,\
        Right : 2\
      };\
      \
      var stretch_vertical_src_enum = {\
        NotSet : 0,\
        Top : 1,\
        Bottom : 2\
      };\
      \
      var m_rubber_band_view = Magna_WindowRubberBand.RubberBandViewFactory();\
      \
      var m_is_on_translate = false;\
      var m_is_on_stretch = false;\
      \
      var m_is_stretch_h_src = stretch_horizontal_src_enum.NotSet;\
      var m_is_stretch_v_src = stretch_vertical_src_enum.NotSet;\
      \
      var m_init_off_x = 0;\
      var m_init_off_y = 0;\
      \
      var m_diff_x = 0;\
      var m_diff_y = 0;\
      \
      var m_trigger_wid = null;\
      \
      var m_is_drag_started = false;\
      \
      var WindowRubberBandBehaviour = function(){\
        WindowRubberBandBehaviour.prototype.onTranslating = function(eventArg){\
          m_rubber_band_view.style.left =eventArg.pageX- m_init_off_x +'px';\
          m_rubber_band_view.style.top = eventArg.pageY- m_init_off_y +'px';\
          \
        };\
        \
        WindowRubberBandBehaviour.prototype.onTranslateStarted = function(x,y){\
          m_init_off_x = x - m_rubber_band_view.offsetLeft;\
          m_init_off_y = y - m_rubber_band_view.offsetTop;\
        };\
        \
        WindowRubberBandBehaviour.prototype.onTranslateEnd = function(eventArg){\
          m_is_on_translate = false;\
          \
          m_init_off_x = 0;\
          m_init_off_y = 0;\
          alert(0);\
          WindowManagerServiceProvide.setWindowPos(m_trigger_wid, m_rubber_band_view.style.left, m_rubber_band_view.style.top );\
          DispatcherNode.dispatchWindowMoved(m_trigger_wid, eventArg.pageX, eventArg.pageY );\
          \
        };\
        WindowRubberBandBehaviour.prototype.onStretchEnd = function(eventArg){\
          m_is_on_stretch = false;\
          \
          m_init_off_x = 0;\
          m_init_off_y = 0;\
          \
          m_diff_x = 0;\
          m_diff_y = 0;\
          \
          m_is_stretch_h_src = stretch_horizontal_src_enum.NotSet;\
          m_is_stretch_v_src = stretch_vertical_src_enum.NotSet;\
          \
          var _left = m_rubber_band_view.offsetLeft + m_rubber_band_view.clientLeft;\
          var _top = m_rubber_band_view.offsetTop + m_rubber_band_view.clientTop;\
          var _width = m_rubber_band_view.clientWidth - m_rubber_band_view.clientLeft * 4;\
          var _height = m_rubber_band_view.clientHeight -m_rubber_band_view.clientTop * 4;\
          \
          var _wnd_ = document.getElementById( m_trigger_wid );\
          if( _wnd_ != null ){\
            WindowManagerServiceProvide.setWindowSize(m_trigger_wid, _width, _height );\
            DispatcherNode.dispatchWindowResized(m_trigger_wid, _width, _height );\
            if( _left != _wnd_.offsetLeft\
            || _top != _wnd_.offsetTop ){\
              WindowManagerServiceProvide.setWindowPos(m_trigger_wid, _left, _top);\
              DispatcherNode.dispatchWindowMoved(m_trigger_wid,_left,_top);\
            }\
          }\
        };\
        \
        WindowRubberBandBehaviour.prototype.onStretchStarted = function(x,y){\
          m_init_off_x = x - parseInt(m_rubber_band_view.offsetLeft);\
          m_init_off_y = y - parseInt(m_rubber_band_view.offsetTop);\
          \
          m_diff_x = x;\
          m_diff_y =  y;\
        };\
        \
        WindowRubberBandBehaviour.prototype.onStretching = function(eventArg){\
        \
          if( m_is_stretch_h_src == stretch_horizontal_src_enum.Left ){\
          \
            if( m_rubber_band_view.offsetLeft + m_rubber_band_view.offsetWidth  - eventArg.pageX > 20 ){\
            \
              m_rubber_band_view.style.left = eventArg.clientX - m_init_off_x + 'px';\
              m_rubber_band_view.style.width = (parseInt(m_rubber_band_view.style.width) - eventArg.clientX + m_diff_x) + 'px';\
              \
              m_diff_x = eventArg.pageX;\
            }\
          }\
          else if( m_is_stretch_h_src == stretch_horizontal_src_enum.Right ){\
          \
            if( eventArg.pageX - m_rubber_band_view.offsetLeft > 20 ){\
              m_rubber_band_view.style.width = (parseInt(m_rubber_band_view.style.width) + eventArg.clientX - m_diff_x) + 'px';\
              m_diff_x = eventArg.pageX;\
            }\
          }\
          else{\
          }\
          if( m_is_stretch_v_src == stretch_vertical_src_enum.Top){\
            if( m_rubber_band_view.offsetTop + m_rubber_band_view.offsetHeight - eventArg.pageY > 20 ){\
              m_rubber_band_view.style.top = eventArg.clientY - m_init_off_y + 'px';\
              m_rubber_band_view.style.height = (parseInt(m_rubber_band_view.style.height) - eventArg.pageY + m_diff_y) + 'px';\
              \
              m_diff_y = eventArg.pageY;\
            }\
          }\
          else if( m_is_stretch_v_src == stretch_vertical_src_enum.Bottom ){\
            if( eventArg.pageY - m_rubber_band_view.offsetTop > 20 ){\
              m_rubber_band_view.style.height = (parseInt(m_rubber_band_view.style.height) + eventArg.pageY - m_diff_y) + 'px';\
              m_diff_y = eventArg.pageY;\
            }\
          }\
          else{\
          }\
          \
        };\
      };\
      var m_rubber_band_behaviour = new WindowRubberBandBehaviour();\
      \
      WindowRubberBandBehaviour.prototype.initDesktopContext  = function(id){\
      var _desktop_wnd = document.getElementById(id);\
        if(_desktop_wnd!=null){\
            _desktop_wnd.addEventListener('mousemove', function(eventArg){\
            if( m_is_drag_started != false ){\
              if( m_is_on_translate != false ){\
              alert(0);\
                m_rubber_band_behaviour.onTranslating( eventArg );\
              }\
              else if( m_is_on_stretch != false ){\
                m_rubber_band_behaviour.onStretching(eventArg);\
              }\
              else{}\
            }\
          }, false);\
          \
          _desktop_wnd.addEventListener('mouseup', function(eventArg){\
            if( m_is_on_translate != false ){\
               m_rubber_band_behaviour.onTranslateEnd(eventArg);\
            }\
            else if( m_is_on_stretch != false ){\
               m_rubber_band_behaviour.onStretchEnd(eventArg);\
            }\
            else{}\
            m_is_drag_started = false;\
            \
            m_trigger_wid = null;\
            m_rubber_band_view.style.visibility = 'hidden';\
            \
          }, false );\
        }\
      };\
      \
      Magna_WindowRubberBand.prototype.triggerTranslate = function( wid, x, y , tran_x, tran_y ){\
        var _wnd_ = document.getElementById( wid );\
        \
        if( _wnd_ != null ){\
          m_is_on_stretch = !false;\
          m_trigger_wid = wid;\
          \
          m_rubber_band_view.style.visibility = 'visible';\
          m_rubber_band_view.style.top = _wnd_.offsetTop - m_rubber_band_view.clientTop + tran_x + 'px';\
          m_rubber_band_view.style.left = _wnd_.offsetLeft - m_rubber_band_view.clientLeft + tran_y + 'px' ;\
          m_rubber_band_view.style.width = _wnd_.offsetWidth + 'px';\
          m_rubber_band_view.style.height = _wnd_.offsetHeight + 'px';\
          \
          m_is_drag_started = true;\
          \
          m_rubber_band_behaviour.onTranslateStarted(x, y);\
        }\
      };\
      \
      Magna_WindowRubberBand.prototype.triggerStretch = function( wid, is_h_src, is_v_src, x, y ){\
        var _wnd_ = document.getElementById( wid );\
        if( _wnd_ != null ){\
          m_is_on_stretch = !false;\
          m_trigger_wid = wid;\
          \
          m_is_stretch_h_src = is_h_src;\
          m_is_stretch_v_src = is_v_src;\
          \
          m_rubber_band_view.style.visibility = 'visible';\
          m_rubber_band_view.style.top = _wnd_.offsetTop - m_rubber_band_view.clientTop + 'px';\
          m_rubber_band_view.style.left = _wnd_.offsetLeft - m_rubber_band_view.clientLeft + 'px' ;\
          m_rubber_band_view.style.width = _wnd_.offsetWidth + 'px';\
          m_rubber_band_view.style.height = _wnd_.offsetHeight + 'px';\
          \
          m_is_drag_started = true;\
          m_rubber_band_behaviour.onStretchStarted(x, y);\
        }\
      };\
    };";
    
    
    const assic_char * RuntimeScript::shared_kernel_JavaScript_Service_Provider_Object_init_script = "\
        var WindowManagerServiceProvider=new Magna_WindowManagerService( document.body );\
        var ControllerManagerServiceProvider=new Magna_ControllerManagerService();";

    const  assic_char *RuntimeScript::shared_kernel_JavaScript_Functionality_Object_init_script  = "\
         var WindowRubberBandFunctionality = new Magna_WindowRubberBand();";

        
    const assic_char * RuntimeScript::shared_JavaScript_CodeLines_retrieve_context_pre = "var _found_element=document.getElementById(";
    
    const assic_char * RuntimeScript::shared_JavaScript_CodeLines_retrieve_context_check = "\
      );if(_found_element!=null){var context=_found_element.getContext(\"2d\");";

    const  assic_char *RuntimeScript::shared_JavaScript_CodeLines_retrieve_context_fin = "}";
    
  }
}//namespace Magna