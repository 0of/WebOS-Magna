#ifndef APPLICATION_LIB_H
#define APPLICATION_LIB_H

#ifdef _MSC_VER
#ifndef APPLICATION_LIB_EXPORT
#define APPLICATION_LIB_EXPORT __declspec(dllexport)
#endif
#elif defined __GNUC__
#ifndef APPLICATION_LIB_EXPORT
#define APPLICATION_LIB_EXPORT
#endif
#endif

#endif  /*  APPLICATION_LIB_H  */
