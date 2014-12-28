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
  (G_TYPE_INSTANCE_GET_PRIVATE ((w), BRUSHLIB_TYPE_SURFACE, BrushLibSurfacePrivate))

typedef struct _BrushLibSurfacePrivate BrushLibSurfacePrivate;

struct _BrushLibSurfacePrivate
{
  guint32 id;
};


/* --- properties --- */
enum {
  PROP_0,

  PROP_COLOR,
};


/* --- signals --- */
enum {
  FULLSCREEN,

  LAST_SIGNAL
};


/* --- prototypes --- */
static guint surface_draw_dab_impl (BrushLibSurface *surface,
                                    const BrushLibPoint *point,
                                    const BrushLibColor *color,
                                    const BrushLibBrush *brush);


static guint           surface_signals[LAST_SIGNAL] = { 0, };


/* --- functions --- */

G_DEFINE_TYPE (BrushLibSurface, brushlib_surface, G_TYPE_OBJECT);

static void
surface_set_property (GObject       *object,
                      guint          prop_id,
                      const GValue  *value,
                      GParamSpec    *pspec)
{
  BrushLibSurface *surface;
  BrushLibSurfacePrivate *priv;

  surface = BRUSHLIB_SURFACE (object);
  priv = BRUSHLIB_SURFACE_GET_PRIVATE (surface);
}

static void
surface_get_property (GObject       *object,
                      guint          prop_id,
                      GValue        *value,
                      GParamSpec    *pspec)
{
  BrushLibSurface *surface;
  BrushLibSurfacePrivate *priv;

  surface = BRUSHLIB_SURFACE (object);
  priv = BRUSHLIB_SURFACE_GET_PRIVATE (surface);
}

static void
brushlib_surface_class_init (BrushLibSurfaceClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->set_property = surface_set_property;
  gobject_class->get_property = surface_get_property;

  klass->draw_dab = surface_draw_dab_impl;
  //klass->get_color = surface_get_color_impl;
  //klass->get_alpha = surface_get_alpha_impl;
  //klass->save_png = surface_save_png_impl;
  //klass->begin_atomic = surface_begin_atomic_impl;
  //klass->end_atomic = surface_end_atomic_impl;

  g_type_class_add_private (klass, sizeof (BrushLibSurfacePrivate));

  /* TODO: install properties */

  /* TODO: add signals */
}

static void
brushlib_surface_init (BrushLibSurface *surface)
{
  BrushLibSurfacePrivate *priv = BRUSHLIB_SURFACE_GET_PRIVATE (surface);

  priv->id = __id++;
}

guint
brushlib_surface_draw_dab (BrushLibSurface     *surface,
                           const BrushLibPoint *point,
                           const BrushLibColor *color,
                           const BrushLibBrush *brush)
{
  g_return_if_fail (BRUSHLIB_IS_SURFACE (surface));
  return BRUSHLIB_SURFACE_GET_CLASS(surface)->draw_dab(surface,
                                                       point,
                                                       color,
                                                       brush);
}

/* --- default implementation --- */
static guint
surface_draw_dab_impl (BrushLibSurface     *surface,
                       const BrushLibPoint *point,
                       const BrushLibColor *color,
                       const BrushLibBrush *brush)
{
  BrushLibSurfacePrivate *priv = BRUSHLIB_SURFACE_GET_PRIVATE (surface);
  g_print ("Default implementation for surface_draw_dab() id = %d\n", priv->id);
  return 0;
};
