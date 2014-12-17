/* 
 * brushlib - The MyPaint Brush Library
 * Copyright (C) 2008 Martin Renold <martinxyz@gmx.ch>
 * Copyright (C) 2012 Jon Nordby <jononor@gmail.com>
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

#include "brushlib-rectangle.h"

void brushlib_rectangle_expand (BrushLibRectangle *self,
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
