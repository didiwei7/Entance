#ifndef QMYMUSIC_GLOBAL_H
#define QMYMUSIC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QMYMUSIC_LIBRARY)
#  define QMYMUSICSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QMYMUSICSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QMYMUSIC_GLOBAL_H
