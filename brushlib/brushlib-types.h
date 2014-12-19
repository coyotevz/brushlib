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

#ifndef __BRUSHLIB_TYPES_H__
#define __BRUSHLIB_TYPES_H__

#include <glib-object.h>

G_BEGIN_DECLS

/* Forward declarations to avoid header catch */
typedef struct _BrushLibSurface     BrushLibSurface;
typedef struct _BrushLibRectangle   BrushLibRectangle;
typedef struct _BrushLibPoint       BrushLibPoint;
typedef struct _BrushLibColor       BrushLibColor;
typedef struct _BrushLibBrush       BrushLibBrush;


/**
 * BrushLibPoint:
 * @x: x coordinate
 * @y: y coordinate
 * @radius: radius of point
 *
 * Point with radius representation.
 */
struct _BrushLibPoint
{
  gint   x;
  gint   y;
  gfloat radius;
};

/**
 * BrushLibRectangle:
 * @x: x origin component
 * @y: y origin component
 * @width: width of rectangle
 * @height: height of rectangle
 *
 * Rectangle representation.
 */
struct _BrushLibRectangle
{
  gint x;
  gint y;
  gint width;
  gint height;
};

G_END_DECLS

#endif /* __BRUSHLIB_TYPES_H__ */

