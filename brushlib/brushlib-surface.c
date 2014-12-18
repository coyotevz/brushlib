/* 
 * BrushLib - The MyPaint Brush Library
 *
 * Copyright (C) 2008 Martin Renold <martinxyz@gmx.ch>
 * Copyright (C) 2012 Jon Nordby <jononor@gmail.com>
 * Copyright (C) 2014 Augusto Roccasalva <augusto@rioplomo.com.ar>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "brushlib-surface.h"

static guint32 __id = 0;

#define BRUSHLIB_SURFACE_GET_PRIVATE(w) \
  (G_TYPE_INSTANCE_GET_PRIVATE((w), BRUSHLIB_TYPE_SURFACE, BrushLibSurfacePrivate))

struct _BrushLibSurfacePrivate
{
  guint32 id;
};


/* --- functions --- */
GType
brushlib_surface_get_type(void)
{
  static GType surface_type = 0;
  if (G_UNLIKELY(surface_type == 0))
  {
    const GTypeInfo surface_info = {
      sizeof(BrushLibSurfaceClass), /* class_size */
      NULL, /* base_init */
      NULL, /* base_finalize */
      NULL, /* class_init */
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof(BrushLibSurface), /* isntance_size */
      0, /* n_preallocs */
      NULL, /* instance_init */
      NULL, /* value_table */
    };

    surface_type = g_type_register_static(G_TYPE_OBJECT, "BrushLibSurface",
                                          &surface_info, 0/*G_TYPE_FLAGS_ABSTRACT*/);
  }

  return surface_type;
}
