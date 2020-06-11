#ifndef APPLIB_GLOBAL_H
#define APPLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(APPLIB_LIBRARY)
#  define APPLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define APPLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // APPLIB_GLOBAL_H
