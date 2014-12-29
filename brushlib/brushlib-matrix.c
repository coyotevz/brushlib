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

#include <float.h>

#include "brushlib-matrix.h"

BrushLibMatrix *
brushlib_matrix_copy (const BrushLibMatrix *matrix)
{
  g_return_val_if_fail (matrix != NULL, NULL);
  return g_slice_dup (BrushLibMatrix, matrix);
}

void
brushlib_matrix_free (BrushLibMatrix *matrix)
{
  g_return_if_fail (matrix != NULL);
  g_slice_free (BrushLibMatrix, matrix);
}

G_DEFINE_BOXED_TYPE (BrushLibMatrix, brushlib_matrix,
                     brushlib_matrix_copy,
                     brushlib_matrix_free)

void
brushlib_matrix_init (BrushLibMatrix *matrix,
                      gdouble xx, gdouble yx,
                      gdouble xy, gdouble yy,
                      gdouble x0, gdouble y0)
{
  matrix->xx = xx; matrix->yx = yx;
  matrix->xy = xy; matrix->yy = yy;
  matrix->x0 = x0; matrix->y0 = y0;
}

void
brushlib_matrix_init_identity (BrushLibMatrix *matrix)
{
  brushlib_matrix_init (matrix,
                        1, 0,
                        0, 1,
                        0, 0);
}

void
brushlib_matrix_init_translate (BrushLibMatrix *matrix,
                                gdouble tx, gdouble ty)
{
  brushlib_matrix_init (matrix,
                        1, 0,
                        0, 1,
                        tx, ty);
}

void
brushlib_matrix_init_scale (BrushLibMatrix *matrix,
                            gdouble sx, gdouble sy)
{
  brushlib_matrix_init (matrix,
                        sx, 0,
                        0, sy,
                        0,  0);
}

void
brushlib_matrix_init_rotate (BrushLibMatrix *matrix,
                            gdouble radians)
{
  gdouble s;
  gdouble c;

  s = sin (radians);
  c = cos (radians);

  brushlib_matrix_init (matrix,
                        c, s,
                        -s, c,
                        0, 0);
}

void
brushlib_matrix_translate (BrushLibMatrix *matrix,
                           gdouble tx, gdouble ty)
{
  BrushLibMatrix tmp;
  brushlib_matrix_init_translate (&tmp, tx, ty);
  brushlib_matrix_multiply (matrix, &tmp, matrix);
}

void
brushlib_matrix_scale (BrushLibMatrix *matrix,
                       gdouble sx, gdouble sy)
{
  BrushLibMatrix tmp;
  brushlib_matrix_init_scale (&tmp, sx, sy);
  brushlib_matrix_multiply (matrix, &tmp, matrix);
}

void
brushlib_matrix_rotate (BrushLibMatrix *matrix,
                        gdouble radians)
{
  BrushLibMatrix tmp;
  brushlib_matrix_init_rotate (&tmp, radians);
  brushlib_matrix_multiply (matrix, &tmp, matrix);
}

void
brushlib_matrix_multiply (BrushLibMatrix       *result,
                          const BrushLibMatrix *a,
                          const BrushLibMatrix *b)
{
  BrushLibMatrix r;

  r.xx = a->xx * b->xx + a->yx * b->xy;
  r.yx = a->xx * b->yx + a->yx * b->yy;

  r.xy = a->xy * b->xx + a->yy * b->xy;
  r.yy = a->xy * b->yx + a->yy * b->yy;

  r.x0 = a->x0 * b->xx + a->y0 * b->xy + b->x0;
  r.y0 = a->x0 * b->yx + a->y0 * b->yy + b->y0;

  *result = r;
}
