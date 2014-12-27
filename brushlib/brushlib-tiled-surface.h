/*
 * BrushLib - The MyPaint Brush Library
 *
 * Copyright (C) 2007-2014 Martin Renold <martinxyz@gmx.ch> et. al.
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

#ifndef __BRUSHLIB_TILED_SURFACE_H__
#define __BRUSHLIB_TILED_SURFACE_H__

#if !defined(__BRUSHLIB_H_INSIDE__) && !defined (BRUSHLIB_COMPILATION)
#error "Only <brushlib/brushlib.h> can be included directly."
#endif

#include <glib-object.h>
#include <brushlib/brushlib-types.h>
#include <brushlib/brushlib-surface.h>

G_BEGIN_DECLS

#define BRUSHLIB_TYPE_TILED_SURFACE \
  (brushlib_surface_get_type ())
#define BRUSHLIB_TILED_SURFACE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), BRUSHLIB_TYPE_TILED_SURFACE, BrushLibTiledSurface))
#define BRUSHLIB_TILED_SURFACE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), BRUSHLIB_TYPE_TILED_SURFACE, BrushLibTiledSurfaceClass))
#define BRUSHLIB_IS_TILED_SURFACE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), BRUSHLIB_TYPE_TILED_SURFACE))
#define BRUSHLIB_IS_TILED_SURFACE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), BRUSHLIB_TYPE_TILED_SURFACE))
#define BRUSHLIB_TILED_SURFACE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), BRUSHLIB_TYPE_TILED_SURFACE, BrushLibTiledSurfaceClass))

/* BrushLibTiledSurface alias is defined in brushlib-types.h */
typedef struct _BrushLibTiledSurfaceClass  BrushLibTiledSurfaceClass;

/**
 * BurshLibTiledSurface:
 *
 * TODO: Write docs.
 */
struct _BrushLibTiledSurface
{
  /*< private >*/
  BrushLibSurface parent_instance;

  /*< public >*/
  guint32 flags;
};

/**
 * BrushLibTiledSurfaceClass:
 */
struct _BrushLibTiledSurfaceClass
{
  /*< private >*/
  BrushLibSurfaceClass parent_class;

  /* methods */
  void  (* set_symmetry_state)      (BrushLibTiledSurface *tsurface,
                                     const gboolean        active,
                                     const gint            center_x);
  void  (* tile_request_start)      (BrushLibTiledSurface *tsurface,
                                   /*TileRequest           request*/);
  void  (* tile_request_end)        (BrushLibTiledSurface *tsurface,
                                   /*TileRequest           request*/);
};

GType                  brushlib_tiled_surface_get_type           (void) G_GNUC_CONST;
BrushLibTiledSurface * brushlib_tiled_surface_new                (void);
void                   brushlib_tiled_surface_set_symmetry_state (BrushLibTiledSurface *tsurface,
                                                                  const gboolean        active,
                                                                  const gint            center_x);
void                   brushlib_tiled_surface_tile_request_start (BrushLibTiledSurface *tsurface,
                                                                /*TileRequest           request*/);
void                   brushlib_tiled_surface_tile_request_end   (BrushLibTiledSurface *tsurface,
                                                                /*TileRequest           request*/);

G_END_DECLS

#endif /* __BRUSHLIB_TILED_SURFACE_H__ */

