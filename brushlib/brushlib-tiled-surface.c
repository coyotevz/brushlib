/*
 * BrushLib - The MyPaint Brush Library
 *
 * Copyright (C) 2007-2014 Martin Renold <martinxyz@gmx.ch> et. al.
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

#include "brushlib-tiled-surface.h"

static guint32 __id = 0;

#define BRUSHLIB_TILED_SURFACE_GET_PRIVATE(w) \
  (G_TYPE_INSTANCE_GET_PRIVATE ((w), BRUSHLIB_TYPE_TILED_SURFACE, BrushLibTiledSurfacePrivate))

typedef struct _BrushLibTiledSurfacePrivate BrushLibTiledSurfacePrivate;

struct _BrushLibTiledSurfacePrivate
{
  guint32 id;
};


/* --- functions --- */

G_DEFINE_TYPE (BrushLibTiledSurface, brushlib_tiled_surface, BRUSHLIB_TYPE_SURFACE);

static void
tiled_surface_set_property  (GObject       *object,
                             guint          prop_id,
                             const GValue  *value,
                             GParamSpec    *pspec)
{
  BrushLibTiledSurface *tsurface;
  BrushLibTiledSurfacePrivate *priv;

  tsurface = BRUSHLIB_TILED_SURFACE (object);
  priv = BRUSHLIB_TILED_SURFACE_GET_PRIVATE (tsurface);
}

static void
tiled_surface_get_property  (GObject       *object,
                             guint          prop_id,
                             GValue        *value,
                             GParamSpec    *pspec)
{
  BrushLibTiledSurface *tsurface;
  BrushLibTiledSurfacePrivate *priv;

  tsurface = BRUSHLIB_TILED_SURFACE (object);
  priv = BRUSHLIB_TILED_SURFACE_GET_PRIVATE (tsurface);
}

static gfloat
tiled_surface_get_alpha (const BrushLibSurface *surface,
                         const BrushLibPoint   *point)
{
  return 0.00;
}

static void
brushlib_tiled_surface_class_init (BrushLibTiledSurfaceClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  BrushLibSurfaceClass *surface_class = BRUSHLIB_SURFACE_CLASS (klass);

  gobject_class->set_property = tiled_surface_set_property;
  gobject_class->get_property = tiled_surface_get_property;

  surface_class->get_alpha = tiled_surface_get_alpha;

  g_type_class_add_private (klass, sizeof (BrushLibTiledSurfacePrivate));
}

static void
brushlib_tiled_surface_init (BrushLibTiledSurface *tsurface)
{
  BrushLibTiledSurfacePrivate *priv = BRUSHLIB_TILED_SURFACE_GET_PRIVATE (tsurface);
  priv->id = __id++;
}
