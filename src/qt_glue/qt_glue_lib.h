#ifndef QT_GLUE_H
#define QT_GLUE_H

#ifdef _MSC_VER
#ifndef QT_GLUE_LIB_EXPORT
# define QT_GLUE_LIB_EXPORT __declspec( dllexport )
#endif
#elif defined __GNUC__
#ifndef QT_GLUE_LIB_EXPORT
# define QT_GLUE_LIB_EXPORT
#endif
#endif

#endif // QT_GLUE_H
