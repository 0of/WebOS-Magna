#ifndef MULTIMEDIA_GLOBAL_H
#define MULTIMEDIA_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MULTIMEDIA_LIB
# define MULTIMEDIA_EXPORT Q_DECL_EXPORT
#else
# define MULTIMEDIA_EXPORT Q_DECL_IMPORT
#endif

#endif // MULTIMEDIA_GLOBAL_H
