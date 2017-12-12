#ifndef QMYJSON_GLOBAL_H
#define QMYJSON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QMYJSON_LIBRARY)
#  define QMYJSONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QMYJSONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QMYJSON_GLOBAL_H
