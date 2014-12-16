#ifndef __GLIBCOMPAT_H__
#define __GLIBCOMPAT_H__

#include "brushlib-config.h"

#if BRUSHLIB_CONFIG_USE_GLIB

#include <glib.h>

#else // not BRUSHLIB_CONFIG_USE_GLIB

/* From $INCLUDEPATH/glib-2.0/glib/gmacros.h */
#ifdef  __cplusplus
# define G_BEGIN_DECLS  extern "C" {
# define G_END_DECLS    }
#else
# define G_BEGIN_DECLS
# define G_END_DECLS
#endif

#define	FALSE	(0)
#define	TRUE	(!FALSE)

typedef void * gpointer;

/* From $INCLUDEPATH/glib-2.0/glib/gtypes.h */
typedef char gchar;
typedef int gint;
typedef gint gboolean;

/* From $LIBPATH/glib-2.0/include/glibconfig.h */
typedef unsigned short guint16;

#endif /* BRUSHLIB_CONFIG_USE_GLIB */

#endif /* __GLIBCOMPAT_H__ */
