#ifndef APPLICATIONENTRY_H
#define APPLICATIONENTRY_H

#include "basedef/SystemDef.h"

#include "application_lib.h"

#ifdef __cplusplus
  extern "C"{
#endif  /*  __cplusplus  */
  //External Entry Def
  APPLICATION_LIB_EXPORT  void  MAGNA_CDECL _magna_entry()  ;

  //cplusplus env
  #define _magna_obtain \
    _magna_nop();\
    extern "C" APPLICATION_LIB_EXPORT MagnaApplication *MAGNA_CDECL _magna_obtain_app(){\
      return MagnaApplication::shared_Obtain_Application();\
    }  
  
  #define _magna_app_name_def(s) \
    extern "C"APPLICATION_LIB_EXPORT String _magna_obtain_app_name(){\
      return s;};

  #define _magna_app_icon_path_def(s) \
    extern "C"APPLICATION_LIB_EXPORT String _magna_obtain_app_icon_path(){\
    return s;};

#ifdef __cplusplus
  }
#endif  /*  __cplusplus  */

  //WIN32 DLL Main
#ifdef _WINDOWS_
  BOOL APIENTRY DllMain( HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
    )
  {
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
    }
    return TRUE;
  }
#endif  /*  _WINDOWS_  */

#define _magna_main() _magna_obtain \
  void _magna_entry()

#define _Main() _magna_main()

#define APP_NAME_SET(name) _magna_app_name_def(name)

#define APP_ICON_PATH_SET(path) _magna_app_icon_path_def(path)

#endif  /*  APPLICATIONENTRY_H  */
//uint32 _magna_entry(){
//  method body
//}


