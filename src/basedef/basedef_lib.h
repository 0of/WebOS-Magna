#ifndef BASEDEF_LIB_H
#define BASEDEF_LIB_H

#ifdef _MSC_VER
#ifndef BASEDEF_LIB_EXPORT
#define BASEDEF_LIB_EXPORT
#elif defined __GNUC__
#ifndef BASEDEF_LIB_EXPORT
#define BASEDEF_LIB_EXPORT
#endif
#endif

#endif