#ifndef BASEGUI_LIB_H
#define BASEGUI_LIB_H

#ifdef _MSC_VER
#ifndef BASEGUI_LIB_EXPORT
#define BASEGUI_LIB_EXPORT __declspec( dllexport )
#endif
#elif defined __GNUC__
#ifndef BASEGUI_LIB_EXPORT
#define BASEGUI_LIB_EXPORT
#endif
#endif

#endif  /*  BASEGUI_LIB_H  */
