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

#ifndef __BRUSHLIB_SURFACE_H__
#define __BRUSHLIB_SURFACE_H__

#if !defined(__BRUSHLIB_H_INSIDE__) && !defined (BRUSHLIB_COMPILATION)
#error "Only <brushlib/brushlib.h> can be included directly."
#endif

G_BEGIN_DECLS

typedef struct _BrushLibSurface BrushLibSurface;

typedef gint (*BrushLibDrawDabFunction) (BrushLibSurface *self,
                                         gfloat x, gfloat y,

/**
 * BrushLibSurface:
 *
 * Abstract surface type for BrushLib brush engine. The surface interface lets
 * th brush engine specify dabs to render, and to pick color.
 */
struct _BrushLibSurface {
     BrushLibSurfaceDrawDabFunction       draw_dab;
     BrushLibSurfaceGetColorFunction      get_color;
     BrushLibSurfaceBeginAtomicFunction   begin_static;
     BrushLibSurfaceEndAtomicFunction     end_atomic;
     BrushLibSurfaceDestroyFunction       destroy;
     BrushLibSurfactSavePng               save_png;
}

/**
 * brushlib_surface_draw_dab:
 *
 * Draw a dab onto the surface.
 */
gint    brushlib_surface_draw_dab     (BrushLibSurface *self,
                                       gfloat x, gfloat y,
                                       gfloat radius,
                                       gfloat color_r,
                                       gfloat color_g,
                                       gfloat color_b,
                                       gfloat opaque,
                                       gfloat hardness,
                                       gfloat alpha_eraser,
                                       gfloat aspet_ratio,
                                       gfloat angle,
                                       gfloat lock_alpha,
                                       gfloat colorize);

G_END_DECLS

#endif /* __BRUSHLIB_SURFACE_H__ */

