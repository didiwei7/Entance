#ifndef QMYXML_GLOBAL_H
#define QMYXML_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QMYXML_LIBRARY)
#  define QMYXMLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QMYXMLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QMYXML_GLOBAL_H
