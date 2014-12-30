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

#include "brushlib-main.h"
#include "brushlib-matrix.h"

#if _XOPEN_SOURCE >= 600 || defined (_ISOC99_SOURCE)
#define ISFINITE(x) isfinite (x)
#else
#define ISFINITE(x) ((x) * (x) >= 0.) /* check for NaNs */
#endif

/* --- prototypes --- */
static void     matrix_scalar_multiply     (BrushLibMatrix *matrix,
                                            gdouble scalar);
static gboolean matrix_is_invertible       (const BrushLibMatrix *matrix) G_GNUC_UNUSED;
static gdouble  matrix_compute_determinant (const BrushLibMatrix *matrix);
static void     matrix_compute_adjoint     (BrushLibMatrix *matrix);
static void     matrix_get_affine          (const BrushLibMatrix *matrix,
                                            gdouble *xx, gdouble *yx,
                                            gdouble *xy, gdouble *yy,
                                            gdouble *x0, gdouble *y0);

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

BrushLibStatus
brushlib_matrix_invert (BrushLibMatrix *matrix)
{
  gdouble det;

  /* Simple scaling|translation matrices are quite common... */
  if (matrix->xy == 0. && matrix->yx == 0.) {
    matrix->x0 = -matrix->x0;
    matrix->y0 = -matrix->y0;

    if (matrix->xx != 1.) {
      if (matrix->xx == 0.)
        return BRUSHLIB_STATUS_INVALID_MATRIX;
      matrix->xx = 1. / matrix->xx;
      matrix->x0 *= matrix->xx;
    }

    if (matrix->yy != 1.) {
      if (matrix->yy == 0.)
        return BRUSHLIB_STATUS_INVALID_MATRIX;
      matrix->yy = 1. / matrix->yy;
      matrix->y0 *= matrix->yy;
    }

    return BRUSHLIB_STATUS_SUCCESS;
  }

  /* inv (A) = 1/det (A) * adj (A) */
  det = matrix_compute_determinant (matrix);

  if (!ISFINITE (det))
    return BRUSHLIB_STATUS_INVALID_MATRIX;
  if (det == 0)
    return BRUSHLIB_STATUS_INVALID_MATRIX;

  matrix_compute_adjoint (matrix);
  matrix_scalar_multiply (matrix, 1 / det);

  return BRUSHLIB_STATUS_SUCCESS;
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

void
brushlib_matrix_transform_distance (const BrushLibMatrix *matrix,
                                    gdouble *dx, gdouble *dy)
{
  gdouble new_x, new_y;

  new_x = (matrix->xx * *dx + matrix->xy * *dy);
  new_y = (matrix->xy * *dx + matrix->yy * *dy);

  *dx = new_x;
  *dy = new_y;
}

void
brushlib_matrix_transform_point (const BrushLibMatrix *matrix,
                                 gdouble *x, gdouble *y)
{
  brushlib_matrix_transform_distance (matrix, x, y);

  *x += matrix->x0;
  *y += matrix->y0;
}

static void
matrix_scalar_multiply (BrushLibMatrix *matrix,
                        gdouble scalar)
{
  matrix->xx *= scalar;
  matrix->yx *= scalar;

  matrix->xy *= scalar;
  matrix->yy *= scalar;

  matrix->x0 *= scalar;
  matrix->y0 *= scalar;
}

static gboolean
matrix_is_invertible (const BrushLibMatrix *matrix)
{
  gdouble det;
  det = matrix_compute_determinant (matrix);
  return ISFINITE (det) && det != 0;
} G_GNUC_UNUSED

static gdouble
matrix_compute_determinant (const BrushLibMatrix *matrix)
{
  gdouble a, b, c, d;

  a = matrix->xx; b = matrix->yx;
  c = matrix->xy; d = matrix->yy;

  return a*d - b*c;
}

/* This function isn't a correct adjoint in that the implicit 1 in the
   homogeneous result should actually be ad-bc instead. But, since this adjoint
   is only used in the computation of the inverse, which divides by
   det(A)=ab-cd anyway, everything woks out in the end. */
static void
matrix_compute_adjoint (BrushLibMatrix *matrix)
{
  gdouble a, b, c, d, tx, ty;

  /* adj (A) = transpose (C:cofactor (A,i,j)) */
  matrix_get_affine (matrix,
                     &a, &b,
                     &c, &d,
                     &tx, &ty);

  brushlib_matrix_init (matrix,
                        d, -b,
                        -c, a,
                        c*ty - d*tx, b*tx - a*ty);
}

static void
matrix_get_affine (const BrushLibMatrix *matrix,
                   gdouble *xx, gdouble *yx,
                   gdouble *xy, gdouble *yy,
                   gdouble *x0, gdouble *y0)
{
  *xx = matrix->xx;
  *yx = matrix->yx;

  *xy = matrix->xy;
  *yy = matrix->yy;

  if (x0)
    *x0 = matrix->x0;
  if (y0)
    *y0 = matrix->y0;
}
