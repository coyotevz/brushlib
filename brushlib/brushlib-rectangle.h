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

#if !defined(__BRUSHLIB_H_INSIDE__) && !defined (BRUSHLIB_COMPILATION)
#error "Only <brushlib/brushlib.h> can be included directly."
#endif

#ifndef __BRUSHLIB_RECTANGLE_H__
#define __BRUSHLIB_RECTANGLE_H__

#include <glib-object.h>
#include <brushlib/brushlib-types.h>

G_BEGIN_DECLS

#define BRUSHLIB_TYPE_RECTANGLE                (brushlib_rectangle_get_type())
#define BRUSHLIB_VALUE_HOLDS_RECTANGLE(value)  (G_TYPE_CHECK_VALUE_TYPE((value), BRUSHLIB_TYPE_RECTANGLE))

GType              brushlib_rectangle_get_type (void) G_GNUC_CONST;
BrushLibRectangle *brushlib_rectangle_copy     (const BrushLibRectangle *rectangle);
void               brushlib_rectangle_free     (BrushLibRectangle       *rectangle);
void               brushlib_rectangle_expand   (BrushLibRectangle       *self,
                                                gint x, gint y);

G_END_DECLS

#endif /* __BRUSHLIB_RECTANGLE_H__ */

