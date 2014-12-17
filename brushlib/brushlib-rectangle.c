/* 
 * BrushLib - The MyPaint Brush Library
 *
 * Copyright (C) 2008 Martin Renold <martinxyz@gmx.ch>
 * Copyright (C) 2012 Jon Nordby <jononor@gmail.com>
 * Copyright (C) 2014 Augusto Roccasalva <augusto@rioplomo.com.ar>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is he.hreby granted, provided that the above
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
#include <string.h>

#include "brushlib-private.h"
#include "brushlib-rectangle.h"

/**
 * brushlib_rectangle_copy:
 * @rectangle: a #BrushLibRectangle
 *
 * Makes a copy of the rectangle structure. The result must be freed using
 * brushlib_rectangle_free().
 *
 * Return value: an allocated copy of @rectangle.
 */
BrushLibRectangle *
brushlib_rectangle_copy(const BrushLibRectangle *rectangle)
{
  BrushLibRectangle *new_rectangle;

  g_return_val_if_fail (rectangle != NULL, NULL);

  new_rectangle = g_slice_new (BrushLibRectangle);
  *new_rectangle = *rectangle;

  return new_rectangle;
}

/**
 * brushlib_rectangle_free:
 * @rectangle: a #BrushLibRectangle
 *
 * Frees a rectangle structure created with brushlib_rectangle_copy().
 */
void
brushlib_rectangle_free(BrushLibRectangle *rectangle)
{
  g_return_if_fail (rectangle != NULL);
  g_slice_free(BrushLibRectangle, rectangle);
}

GType
brushlib_rectangle_get_type(void)
{
  static GType type = 0;

  if (!type) {
    type = g_boxed_type_register_static(I_("BrushLibRectangle"),
                                        (GBoxedCopyFunc) brushlib_rectangle_copy,
                                        (GBoxedFreeFunc) brushlib_rectangle_free);
  }

  return type;
}

void
brushlib_rectangle_expand (BrushLibRectangle *self,
                           gint x, gint y)
{
  if (self->width == 0)
  {
    self->width = 1;
    self->height = 1;
    self->x = x;
    self->y = y;
  } else {
    if (x < self->x)
    {
      self->width += self->x - x;
      self->x = x;
    } else
    if (x >= self->x + self->width)
    {
      self->width = x - self->x + 1;
    }

    if (y < self->y)
    {
      self->height += self->y - y;
      self->y = y;
    } else
    if (y >= self->y + self->height)
    {
      self->height = y - self->y + 1;
    }
  }
}
