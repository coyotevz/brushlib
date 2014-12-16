#if !defined(__BRUSHLIB_H_INSIDE__) && !defined (BRUSHLIB_COMPILATION)
#error "Only <brushlib/brushlib.h> can be included directly."
#endif

/* brushlib - The MyPaint Brush Library
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


#ifndef __BRUSHLIB_BRUSH_H__
#define __BRUSHLIB_BRUSH_H__

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _BrushLibBrush BrushLibBrush;

#define BRUSHLIB_TYPE_BRUSH                 (brushlib_brush_get_type())
#define BRUSHLIB_VALUE_HOLDS_BRUSH(value)   (G_TYPE_CHECK_VALUE_TYPE ((value), BRUSHLIB_TYPE_BRUSH))


GType brushlib_brush_get_type(void);


BrushLibBrush *brushlib_brush_new        (void);
void           brushlib_brush_unref      (BrushLibBrush   *self);
void           brushlib_brush_ref        (BrushLibBrush   *self);
void           brushlib_brush_reset      (BrushLibBrush   *self);
void           brushlib_brush_new_stroke (BrushLibBrush   *self);
gint           brushlib_bruhs_stroke_to  (BrushLibBrush   *self,
                                          BrushLibSurface *surface,
                                          gfloat           x,
                                          gfloat           y,
                                          gfloat           pressure,
                                          gfloat           xtilt,
                                          gfloat           ytitl,
                                          gdouble          dtime);

void           brushlib_brush_set_base_value    (BrushLibBrush *self,
                                                 BrushSettings  id,
                                                 gfloat         value);
gfloat         brushlib_brush_get_base_value    (BrushLibBrush *self,
                                                 BrushSettings  id);
gboolean       brushlib_brush_is_constant       (BrushLibBrush *self,
                                                 BrushSettings  id);
gint           brushlib_brush_get_inputs_used_n (BrushLibBrush *self,
                                                 BrushSettings  id);
void           brushlib_brush_set_mapping_n     (BrushLibBrush *self,
                                                 BrushSettings  id,
                                                 BrushInput     input,
                                                 gint           n);
gint           brushlib_brush_get_mapping_n     (BrushLibBrush *self,
                                                 BrushSettings  id,
                                                 BrushInput     input);
void           brushlib_brush_set_mapping_point (BrushLibBrush *self,
                                                 BrushSettings  id,
                                                 BrushInput     input,
                                                 gint           index,
                                                 gfloat         x,
                                                 gfloat         y);
void           brushlib_brush_get_mapping_point (BrushLibBrush *self,
                                                 BrushSettings  id,
                                                 BrushInput     input,
                                                 gint           index,
                                                 gfloat        *x,
                                                 gfloat        *y);
void           brushlib_brush_get_state         (BrushLibBrush *self,
                                                 BrushState     i,
                                                 gfloat         value);
gfloat         brushlib_brush_get_state         (BrushLibBrush *self,
                                                 BrushState     i);
gdouble        brushlib_brush_get_stroke_time   (BrushLibBrush *self);
void           brushlib_brush_set_print_inputs  (BrushLibBrush *self,
                                                 gboolean       enabled);
void           brushlib_brush_from_defaults     (BrushLibBrush *self);
gboolean       brushlib_brush_from_string       (BrushLibBrush *self,
                                                 const gchar   *string);

G_END_DECLS

#endif /* __BRUSHLIB_BRUSH_H__ */
