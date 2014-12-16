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

  gfloat states[BRUSHLIB_BRUSH_STATES_COUNT]
}
