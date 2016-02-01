#ifndef RUNTIMESCRIPT_H
#define RUNTIMESCRIPT_H

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"

#include <QWebView>

 namespace Magna{
   namespace Runtime{

    class RuntimeScript{
      public:
        static const uint32 shared_Webkit_version = 0x020203;

        static const assic_char *shared_JavaScript_standard ;

        //HTML frame
        //code set, language
        static const assic_char *shared_HTML_frame_begin;
        static const assic_char *shared_HTML_frame_end;

        static const assic_char *shared_HTML_frame_head_script_begin;
        static const assic_char *shared_HTML_frame_head_script_end;
        static const assic_char *shared_HTML_frame_body_script_begin;
        static const assic_char *shared_HTML_frame_body_script_end;
        
        //service provider names
        static const  assic_char *shared_JavaScript_Service_Provider_Window;
        static const  assic_char *shared_JavaScript_Service_Provider_Controller;

        //functionality names
        static const  assic_char *shared_JavaScript_Functionality_Window_Rubber_Band;


        //window services
        static const assic_char * shared_JavaScript_Service_open_new_window ;
        static const assic_char * shared_JavaScript_Service_set_window_visible ;
        static const assic_char * shared_JavaScript_Service_set_window_hidden  ;
        static const assic_char *shared_JavaScript_Service_set_window_size;
        static const assic_char * shared_JavaScript_Service_set_window_pos ;
        static const assic_char * shared_JavaScript_Service_close_window ;
        static const assic_char * shared_JavaScript_Service_window_focus_in ;
        static const assic_char * shared_JavaScript_Service_window_focus_out;

        //controller services
        static const assic_char * shared_JavaScript_Service_register_new_controller ;
        static const assic_char * shared_JavaScript_Service_register_protogenous_controller ;
        static const assic_char * shared_JavaScript_Service_unregister_controller ;
        static const assic_char * shared_JavaScript_Service_controller_resize ;
        static const assic_char * shared_JavaScript_Service_wrapper_resize ;
        static const assic_char * shared_JavaScript_Service_content_resize ;
        static const assic_char * shared_JavaScript_Service_controller_move ;

        //rubber band functionalities
        static const  assic_char *shared_JavaScript_Functionality_rubber_band_init;
        static const  assic_char *shared_JavaScript_Functionality_trigger_translate;
        static const  assic_char *shared_JavaScript_Functionality_trigger_stretch;

        //event listener
        static const assic_char * shared_JavaScript_Listener_script ;

        //listener manager service def
        static const assic_char * shared_JavaScript_Listener_Manager_Service_script;

        //window manager service def
        //[REF-Name] Window Rubber Band Functionality
        static const  assic_char *shared_kernel_JavaScript_Window_Manager_Service_script ;

        //Controller Manager service def
        static const  assic_char *shared_kernel_JavaScript_Controller_Manager_Service_script ;

        //rubber band functionality def
        //[REF-Name] Window Service Provider
        static const assic_char * shared_kernel_JavaScript_Window_Rubber_Band_Functionality_script;


        //global service provider and object def
        static const  assic_char *shared_kernel_JavaScript_Service_Provider_Object_init_script ;
        static const  assic_char *shared_kernel_JavaScript_Functionality_Object_init_script ;

        //Javascript code-lines
        //context retrieve script 
        static const  assic_char *shared_JavaScript_CodeLines_retrieve_context_pre;
        static const  assic_char *shared_JavaScript_CodeLines_retrieve_context_check;
        static const  assic_char *shared_JavaScript_CodeLines_retrieve_context_fin;
    };
  }
 }//namespace Magna

#endif /* RUNTIMESCRIPT_H  */