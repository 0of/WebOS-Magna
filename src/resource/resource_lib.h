#ifndef RESOURCE_LIB_H
#define RESOURCE_LIB_H

#ifdef _MSC_VER
#ifndef RESOURCE_LIB_EXPORT
#define RESOURCE_LIB_EXPORT  __declspec( dllexport )
#endif  /*  RESOURCE_LIB_EXPORT  */
#elif defined __GNUC__
#ifndef RESOURCE_LIB_EXPORT
#define RESOURCE_LIB_EXPORT
#endif  /*  RESOURCE_LIB_EXPORT  */
#endif

#endif  /*  RESOURCE_LIB_H  */
