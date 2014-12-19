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

#ifndef __BRUSHLIB_BRUSH_H__
#define __BRUSHLIB_BRUSH_H__

#if !defined (__BRUSHLIB_H_INSIDE__) && !defined (BRUSHLIB_COMPILATION)
#error "Only <brushlib/brushlib.h> can be included directly."
#endif

#include <glib-object.h>
#include <brushlib/brushlib-types.h>

G_BEGIN_DECLS

#define BRUSHLIB_TYPE_BRUSH \
  (brushlib_brush_get_type ())
#define BRUSHLIB_BRUSH(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), BRUSHLIB_TYPE_BRUSH, BrushLibBrush))
#define BRUSHLIB_BRUSH_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), BRUSHLIB_TYPE_BRUSH, BrushLibClass))
#define BRUSHLIB_BRUSH_GET_CLASS(obj) \
  (G_TYPE_INStANCE_GET_CLASS ((obj), BRUSHLIB_TYPE_SURFACE, BrushLibSurfaceClass))


/* BrushLibBrush alias is defined in brushlib-types.h */
typedef struct _BrushLibBrushClass BrushLibBrushClass;


typedef struct _BrushLibBrush
{
  /*< private >*/
  GObject parent_instance;

  /*< public >*/
  guint32 flags;
};

typedef struct _BrushLibBrushClass
{
  /*< private >*/
  GObjectClass parent_class;

  /* basic methods */
  void      (* test_method)       (BrushLibBrush *brush);
};


GType   brushlib_brush_get_type     (void) G_GNUC_CONST;
void    brushlib_brush_test_method  (BrushLibBrush *brush);

G_END_DECLS

#endif /* __BRUSHLIB_BRUSH_H__ */

