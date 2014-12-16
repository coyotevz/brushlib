/* brushlib - The MyPaint Brush Library
 * Copyright (C) 2007-2011 Martin Renold <martinxyz@gmx.ch>
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "brushlib-brush.h"

#ifdef HAVE_JSON_C
// Allow the C99 define from json.h
#undef TRUE
#undef FALSE
#include <json.h>
#endif /* HAVE_JSON_C */


/**
 * BrushLibBrush:
 *
 * The BrushLib brush engine class.
 */
struct _BrushLibBrush {
  gboolean print_inputs;  // debug menu
  // for stroke splitting (undo/redo)
  gdouble stroke_total_painting_time;
  gdouble stroke_current_idling_time;

  // the states (get_state, set_state, reset) that change diring a stroke
  gfloat states[BRUSHLIB_BRUSH_STATES_COUNT];
  RngDouble *rng;

  // Those mapping describe how to calculate the current value for each
  // setting.  Most of settings will be constant (eg. only their base_value is
  // used).
  Mapping *settings[BRUSHLIB_BRUSH_SETTINGS_COUNT];

  // the current value of all settings (calculated using the current state)
  gfloat settings_value[BRUSHLIB_BRUSH_SETTINGS_COUNT];

  gfloat speed_mapping_gamma[2];
  gfloat speed_mapping_m[2];
  gfloat speed_mapping_q[2];

  gboolean reset_requested;
#ifdef HAVE_JSON_C
  json_object *brush_json;
#endif
  int refcount;
};

GType
brushlib_get_type(void)
{
  static GType type = 0;

  if (!type) {
    type = g_boxed_type_register_static("BrushLibBrush",
                                        (GBoxedCopyFunc) brushlib_brush_ref,
                                        (GBoxedFreeFunc) brushlib_brush_unref);
  }

  return type;
}

/**
 * brushlib_brush_new:
 *
 * Create a new BrushLib brush engine instance.
 * Initial reference count is 1.
 */
BrushLibBrush *
brushlib_brush_new(void)
{
  BrushLibBrush *self = (BrushLibBrush *)malloc(size_of(BrushLibBrush))
