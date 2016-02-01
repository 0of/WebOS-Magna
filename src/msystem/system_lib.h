#ifndef SYSTEM_LIB_H
#define SYSTEM_LIB_H

#ifdef _MSC_VER
#ifndef SYSTEM_LIB_EXPORT
# define SYSTEM_LIB_EXPORT __declspec( dllexport )
#endif
#elif defined __GNUC__
#ifndef SYSTEM_LIB_EXPORT
# define SYSTEM_LIB_EXPORT
#endif
#endif

#endif  /*  SYSTEM_LIB_H  */
