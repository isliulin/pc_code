#ifndef SCRIPTLIB_GLOBAL_H
#define SCRIPTLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SCRIPTLIB_LIBRARY)
#  define SCRIPTLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SCRIPTLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SCRIPTLIB_GLOBAL_H
