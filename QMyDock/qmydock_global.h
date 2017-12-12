#ifndef QMYDOCK_GLOBAL_H
#define QMYDOCK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QMYDOCK_LIBRARY)
#  define QMYDOCKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QMYDOCKSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QMYDOCK_GLOBAL_H
