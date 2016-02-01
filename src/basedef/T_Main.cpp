#include "SystemDef.h"

#ifdef MAGNA_WINDOWS
#include <windows.h>

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
#endif  /*_MSV_VER  */
