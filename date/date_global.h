#ifndef DATE_GLOBAL_H
#define DATE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DATE_LIBRARY)
#  define DATESHARED_EXPORT Q_DECL_EXPORT
#else
#  define DATESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DATE_GLOBAL_H


// DATESHARED_EXPORT
