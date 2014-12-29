/* 
 * BrushLib - The MyPaint Brush Library
 *
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

#if !defined (__BRUSHLIB_H_INSIDE__) && !defined (BRUSHLIB_COMPILATION)
#error "Only <brushlib/brushlib.h> can be included directly."
#endif

#ifndef __BRUSHLIB_MATRIX_H__
#define __BRUSHLIB_MATRIX_H__

#include <glib-gobject.h>
#include <brushlib/brushlib-types.h>

G_BEGIN_DECLS

#define BRUSHLIB_TYPE_MATRIX                (brushlib_matrix_get_type ())
#define BRUSHLIB_VALUE_HOLDS_MATRIX(value)  (G_TYPE_CHECK_VALUE_TYPE ((value), BRUSHLIB_TYPE_MATRIX))

GType           brushlib_matrix_get_type        (void) G_GNUC_CONST;
BrushLibMatrix *brushlib_matrix_copy            (const BrushLibMatrix *matrix);
void            brushlib_matrix_free            (BrushLibMatrix       *matrix);

void            brushlib_matrix_init            (BrushLibMatrix       *matrix,
                                                 double xx, double yx,
                                                 double xy, double yy,
                                                 double x0, double y0);
void            brushlib_matrix_init_identity   (BrushLibMatrix       *matrix);
void            brushlib_matrix_init_translate  (BrushLibMatrix       *matrix,
                                                 double tx, double ty);
void            brushlib_matrix_init_scale      (BrushLibMatrix       *matrix,
                                                 double sx, double sy);
void            brushlib_matrix_init_rotate     (BrushLibMatrix       *matrix,
                                                 double radians);

void            brushlib_matrix_translate       (BrushLibMatrix       *matrix,
                                                 double tx, double ty);
void            brushlib_matrix_scale           (BrushLibMatrix       *matrix,
                                                 double sx, double sy);
void            brushlib_matrix_rotate          (BrushLibMatrix       *matrix,
                                                 double radians);

void            brushlib_matrix_invert          (BrushLibMatrix       *matrix);
void            brushlib_matrix_multiply        (BrushLibMatrix       *matrix);
void            brushlib_matrix_transform_distance (const BrushLibMatrix *matrix,
                                                    double dx, double dy);
void            brushlib_matrix_transform_point (const BrushLibMatrix *matrix,
                                                 double *x, double *y);

G_END_DECLS

#endif /* __BRUSHLIB_MATRIX_H__ */

