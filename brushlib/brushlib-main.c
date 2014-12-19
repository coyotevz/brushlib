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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#include "brushlib-main.h"
#include "brushlib-debug.h"
#include "brushlib-version.h"


/* version info */
const guint brushlib_major_version = BRUSHLIB_MAJOR_VERSION;
const guint brushlib_minor_version = BRUSHLIB_MINOR_VERSION;
const guint brushlib_micro_version = BRUSHLIB_MICRO_VERSION;


static gboolean brushlib_is_initialized = FALSE;
guint           brushlib_debug_flags    = 0; /* global debug flag */

static const GDebugKey brushlib_debug_keys[] = {
  { "main", BRUSHLIB_DEBUG_MAIN },
  { "brush", BRUSHLIB_DEBUG_BRUSH },
  { "surface", BRUSHLIB_DEBUG_SURFACE },
};

static gboolean
brushlib_arg_debug_cb (const char *key,
                       const char *value,
                       gpointer    user_data)
{
  brushlib_debug_flags |=
    g_parse_debug_string (value, brushlib_debug_keys, G_N_ELEMENTS (brushlib_debug_keys));

  return TRUE;
}

static GOptionEntry brushlib_args[] = {
  { "brushlib-debug", 0, 0, G_OPTION_ARG_CALLBACK, brushlib_arg_debug_cb,
    "BrushLib debugging flags to set", "FLAGS"},
  { NULL, },
};


/**
 * brushlib_get_option_group: (skip)
 *
 * Returns a #GOptionGroup for the command line arguments recognized by BrushLib.
 * You should add this groups to your #GOptionContext with
 * g_option_context_add_group(), if you are using g_option_context_parse() to
 * parse your commandline arguments.
 *
 * Return value: a GOptionGroup for the command line arguments
 *   recognized by BrushLib
 */
GOptionGroup *
brushlib_get_option_group (void)
{
  GOptionGroup *group;

  group = g_option_group_new ("brushlib",
                              "BrushLib Options",
                              "Show BrushLib Options",
                              NULL, NULL);

  g_option_group_add_entries (group, brushlib_args);

  return group;
}

static gboolean
brushlib_parse_args (guint   *argc,
                     gchar ***argv)
{
  GOptionContext *option_context;
  GOptionGroup   *brushlib_group;
  GError         *error = NULL;
  gboolean        ret = FALSE;

  if (brushlib_is_initialized)
    return TRUE;

  option_context = g_option_context_new (NULL);
  g_option_context_set_ignore_unknown_options (option_context, TRUE);
  g_option_context_set_help_enabled (option_context, FALSE);

  brushlib_group = brushlib_get_option_group ();
  g_option_context_set_main_group (option_context, brushlib_group);

  if (!g_option_context_parse (option_context, argc, argv, &error))
  {
    g_warning ("%s", error->message);
    g_error_free (error);
    ret = FALSE;
  }

  g_option_context_free (option_context);

  return ret;
}

void
ensure_max_threads (void)
{
#if _OPENMP
  const int max_threads = omp_get_max_threads ();
  if (max_threads > BRUSHLIB_MAX_THREADS)
    omp_set_num_threads (BRUSHLIB_MAX_THREADS);
#endif
}

void
brushlib_base_init (void)
{
  if (!brushlib_is_initialized)
  {
    brushlib_is_initialized = TRUE;

    //bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
    //bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");

    ensure_max_threads ();
  }
}

/**
 * brushlib_init:
 * @argc: The number of arguments in @argv
 * @argv: A pointer to an array of arguments
 *
 * It will initialize everything needed to operate with BrushLib and parses some
 * standard command line options.  @argc and @argv are adjusted accordingly so
 * your own code will never see those standard arguments.
 *
 * Return value: 1 on success, < 0 on failure.
 */
BrushLibInitError
brushlib_init (int    *argc,
               char ***argv)
{
  GError *error = NULL;

  if (brushlib_is_initialized)
    return BRUSHLIB_INIT_SUCCESS;

  brushlib_base_init ();

  if (brushlib_parse_args (argc, argv) == FALSE) {
    return BRUSHLIB_INIT_ERROR_INTERNAL;
  }

  return BRUSHLIB_INIT_SUCCESS;
}
