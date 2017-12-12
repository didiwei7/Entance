#ifndef SOCKET_GLOBAL_H
#define SOCKET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QMYSOCKET_LIBRARY)
#  define SOCKETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SOCKETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SOCKET_GLOBAL_H
