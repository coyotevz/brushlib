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

#ifndef __BRUSHLIB_MAIN_H__
#define __BRUSHLIB_MAIN_H__

#include <glib.h>

G_BEGIN_DECLS

/**
 * BrushLibInitError:
 * @BRUSHLIB_INIT_SUCCESS: Initialization successful
 * @BRUSHLIB_INIT_ERROR_INTERNAL: Internal error
 *
 * Error conditions returned by brushlib_init()
 */

typedef enum {
  BRUSHLIB_INIT_SUCCESS        =  1,
  BRUSHLIB_INIT_ERROR_INTERNAL = -1,
} BrushLibInitError;


/* Initialization */
BrushLibInitError     brushlib_init             (int            *argc,
                                                 char         ***argv) G_GNUC_WARN_UNUSED_RESULT;
BrushLibInitError     brushlib_init_with_args   (int            *argc,
                                                 char         ***argv,
                                                 const char     *parameter_string,
                                                 GOptionEntry   *entries,
                                                 const char     *translation_domain,
                                                 GError        **error) G_GNUC_WARN_UNUSED_RESULT;

GOptionGroup *        brushlib_get_option_group (void);

G_END_DECLS

#endif /* __BRUSHLIB_MAIN_H__ */

