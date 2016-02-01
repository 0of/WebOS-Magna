#ifndef RENDER_LIB_H
#define RENDER_LIB_H

#ifdef _MSC_VER
#ifndef RENDER_LIB_EXPORT
#define RENDER_LIB_EXPORT _declspec( dllexport )
#endif  /*  RENDER_EXPORT  */
#elif defined __GNUC__
#ifndef RENDER_LIB_EXPORT
#define RENDER_LIB_EXPORT
#endif
#endif

#endif  /*  RENDER_LIB_H  */
