#ifndef MRUNTIME_GLOBAL_H
#define MRUNTIME_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MRUNTIME_LIB
# define MRUNTIME_EXPORT Q_DECL_EXPORT
#else
# define MRUNTIME_EXPORT Q_DECL_IMPORT
#endif

#endif // MRUNTIME_GLOBAL_H
