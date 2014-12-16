/*
 * BrushLib - Brush Toolkit
 *
 * Copyright (C) 2014 Augusto Roccasalva <augusto@rioplomo.com.ar>
 *
 * $Id
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the 
 *  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 *  Boston, MA  02111-1307  USA
 */

#if !defined(__BRUSHLIB_H_INSIDE__) && !defined (BRUSHLIB_COMPILATION)
#error "Only <brushlib/brushlib.h> can be included directly."
#endif

#ifndef __BRUSHLIB_MAIN_H__
#define __BRUSHLIB_MAIN_H__

#include <glib.h>

G_BEGIN_DECLS

/**
 * BrushLibInitError:
 * @BRUSHLIB_INIT_SUCCESS: Initialization successful
 * @BRUSHLIB_INIT_ERROR_INTERNAL: Internal error
 *
 * Error conditions returned by brushlib_init()
 */

typedef enum {
  BRUSHLIB_INIT_SUCCESS        =  1,
  BRUSHLIB_INIT_ERROR_INTERNAL = -1,
} BrushLibInitError;


/* Initialization */
BrushLibInitError    brushlib_init  (int    *argc,
                           char ***argv);
GOptionGroup *  brushlib_get_option_group(void);

G_END_DECLS

#endif /* __BRUSHLIB_MAIN_H__ */

