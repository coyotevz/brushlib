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

#ifndef __BRUSHLIB_DEBUG_H__
#define __BRUSHLIB_DEBUG_H__

#include <glib.h>
#include "brushlib-main.h"

G_BEGIN_DECLS

typedef enum {
  BRUSHLIB_DEBUG_MISC    = 1 << 0,
  BRUSHLIB_DEBUG_MAIN    = 1 << 1,
  BRUSHLIB_DEBUG_BRUSH   = 1 << 2,
  BRUSHLIB_DEBUG_SURFACE = 1 << 3,
} BrushLibDebugFlag;

extern guint brushlib_debug_flags;

G_END_DECLS

#endif /* __BRUSHLIB_DEBUG_H__ */

