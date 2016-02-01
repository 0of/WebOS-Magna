#ifndef MULTIMEDIA_LIB_H
#define MULTIMEDIA_LIB_H

#ifdef _MSC_VER
#ifndef MULTIMEDIA_LIB_EXPORT
#define MULTIMEDIA_LIB_EXPORT  __declspec( dllexport )
#endif  /*  MULTIMEDIA_LIB_EXPORT  */
#elif defined __GNUC__
#ifndef MULTIMEDIA_LIB_EXPORT
#define MULTIMEDIA_LIB_EXPORT
#endif  /*  MULTIMEDIA_LIB_EXPORT  */
#endif

#endif // MULTIMEDIA_LIB_H
