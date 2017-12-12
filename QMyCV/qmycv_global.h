#ifndef QMYCV_GLOBAL_H
#define QMYCV_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QMYCV_LIBRARY)
#  define QMYCVSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QMYCVSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QMYCV_GLOBAL_H
