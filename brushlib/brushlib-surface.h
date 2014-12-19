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

#if !defined (__BRUSHLIB_H_INSIDE__) && !defined (BRUSHLIB_COMPILATION)
#error "Only <brushlib/brushlib.h> can be included directly."
#endif

#ifndef __BRUSHLIB_SURFACE_H__
#define __BRUSHLIB_SURFACE_H__

#include <glib-object.h>
#include <brushlib/brushlib-types.h>

G_BEGIN_DECLS

#define BRUSHLIB_TYPE_SURFACE \
  (brushlib_surface_get_type ())
#define BRUSHLIB_SURFACE (obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), BRUSHLIB_TYPE_SURFACE, BrushLibSurface))
#define BRUSHLIB_SURFACE_CLASS (klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), BRUSHLIB_TYPE_SURFACE, BrushLibSurfaceClass))
#define BRUSHLIB_IS_SURFACE (obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), BRUSHLIB_TYPE_SURFACE))
#define BRUSHLIB_IS_SURFACE_CLASS (klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), BRUSHLIB_TYPE_SURAFCE))
#define BRUSHLIB_SURFACE_GET_CLASS (obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), BRUSHLIB_TYPE_SURFACE, BrushLibSurfaceClass))


/* BrushLibSurface alias is defined in brushlib-types.h */
typedef struct _BrushLibSurfaceClass    BrushLibSurfaceClass;

/**
 * BrushLibSurface:
 *
 * Abstract surface type for BrushLib brush engine.  The surface interface lets
 * the brush engine specify dabs to render, and to pick color.
 */
struct _BrushLibSurface
{
  /*< private >*/
  GObject parent_instance;

  /*< public >*/
  guint32 flags;
};

/**
 * BrushLibSurfaceClass:
 */
struct _BrushLibSurfaceClass
{
  /*< private >*/
  GObjectClass parent_class;

  /* basic methods */
  guint   (* draw_dab)          (BrushLibSurface         *surface,
                                 const BrushLibPoint     *point,
                                 const BrushLibColor     *color,
                                 const BrushLibBrush     *brush);
  void    (* get_color)         (const BrushLibSurface   *surface,
                                 const BrushLibPoint     *point,
                                 BrushLibColor           *color);
  gfloat  (* get_alpha)         (const BrushLibSurface   *surface,
                                 const BrushLibPoint     *point);
  void    (* save_png)          (const BrushLibSurface   *surface,
                                 const char              *path,
                                 const BrushLibRectangle *rectangle);

  void    (* begin_atomic)      (BrushLibSurface         *surface);
  void    (* end_atomic)        (BrushLibSurface         *surface);
};

GType             brushlib_surface_get_type     (void) G_GNUC_CONST;
BrushLibSurface * brushlib_surface_new          (GType type,
                                                 const char *first_property_name,
                                                 ...);

guint             brushlib_surface_draw_dab     (BrushLibSurface         *surface,
                                                 const BrushLibPoint     *point,
                                                 const BrushLibColor     *color,
                                                 const BrushLibBrush     *brush);
void              brushlib_surface_get_color    (const BrushLibSurface   *surface,
                                                 const BrushLibPoint     *point,
                                                 BrushLibColor           *color);
gfloat            brushlib_surface_get_alpha    (const BrushLibSurface   *surface,
                                                 const BrushLibPoint     *point);
void              brushlib_surface_save_png     (const BrushLibSurface   *surface,
                                                 const char              *path,
                                                 const BrushLibRectangle *rectangle);
void              brushlib_surface_begin_atomic (BrushLibSurface         *surface);
void              brushlib_surface_end_atomic   (BrushLibSurface         *surface);

G_END_DECLS

#endif /* __BRUSHLIB_SURFACE_H__ */

