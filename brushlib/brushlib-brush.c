/* BrushLib - The MyPaint Brush Library
 *
 * Copyright (C) 2007-2011 Martin Renold <martinxyz@gmx.ch>
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "brushlib-brush.h"

static guint32 __id = 0;

#define BRUSHLIB_BRUSH_GET_PRIVATE(w) \
  (G_TYPE_INSTANCE_GET_PRIVATE ((w), BRUSHLIB_TYPE_BRUSH, BrushLibBrushPrivate))

typedef struct _BrushLibBrushPrivate BrushLibBrushPrivate;

struct _BrushLibBrushPrivate {
  guint32 id;
};

G_DEFINE_TYPE (BrushLibBrush, brushlib_brush, G_TYPE_OBJECT);

static void
brushlib_brush_set_property (GObject      *object,
                             guint         prop_id,
                             const GValue *value,
                             GParamSpec   *pspec)
{
  BrushLibBrush *brush;
  BrushLibBrushPrivate *priv;

  brush = BRUSHLIB_BRUSH (object);
  priv = BRUSHLIB_BURSH_GET_PRIVATE (brush);
}

static void
brushlib_brush_get_property (GObject    *object,
                             guint       prop_id,
                             GValue     *value,
                             GParamSpec *pspec)
{
  BrushLibBrush *brush;
  BrushLibBrushPrivate *priv;

  brush = BRUSHLIB_BRUSH (object);
  priv = BRUSHLIB_BURSH_GET_PRIVATE (brush);
}

static void
brushlib_brush_class_init (BrushLibBrushClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->set_property = brushlib_brush_set_property;
  gobject_class->get_property = brushlib_brush_get_property;

  brushlib_brush_parent_class = g_type_class_peek_parent (klass);

  g_type_class_add_private (klass, sizeof (BrushLibBrushPrivate));

  /* TODO: install properties */
  /* TODO: add signals */
}

static void
brushlib_brush_init (BrushLibBrush *brush)
{
  BrushLibBrushPrivate *priv = BRUSHLIB_BRUSH_GET_PRIVATE (brush);
}
