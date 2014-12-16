/*
 * BrushLib - Brush Toolkit
 *
 * Copyright (C) 2014 Augusto Roccasalva <augusto@rioplomo.com.ar>
 *
 * $Id
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the 
 *  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 *  Boston, MA  02111-1307  USA
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>

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
brushlib_arg_debug_cb(const char *key,
                 const char *value,
                 gpointer    user_data)
{
  brushlib_debug_flags |=
    g_parse_debug_string(value, brushlib_debug_keys, G_N_ELEMENTS(brushlib_debug_keys));

  return TRUE;
}

static GOptionEntry brushlib_args[] = {
  { "brushlib-debug", 0, 0, G_OPTION_ARG_CALLBACK, brushlib_arg_debug_cb,
    "BrushLib debugging flags to set", "FLAGS"},
  { NULL, },
};


/**
 * buik_get_option_group:
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
brushlib_get_option_group(void)
{
  GOptionGroup *group;

  group = g_option_group_new("brushlib",
                             "BrushLib Options",
                             "Show BrushLib Options",
                             NULL, NULL);

  g_option_group_add_entries(group, brushlib_args);

  return group;
}

static gboolean
brushlib_parse_args(guint   *argc,
               gchar ***argv)
{
  GOptionContext *option_context;
  GOptionGroup   *brushlib_group;
  GError         *error = NULL;
  gboolean        ret = FALSE;

  if (brushlib_is_initialized)
    return TRUE;

  option_context = g_option_context_new(NULL);
  g_option_context_set_ignore_unknown_options(option_context, TRUE);
  g_option_context_set_help_enabled(option_context, FALSE);

  brushlib_group = brushlib_get_option_group();
  g_option_context_set_main_group(option_context, brushlib_group);

  if (!g_option_context_parse(option_context, argc, argv, &error))
  {
    g_warning("%s", error->message);
    g_error_free(error);
    ret = FALSE;
  }

  g_option_context_free(option_context);

  return ret;
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
brushlib_init(int    *argc,
         char ***argv)
{
  GError *error;

  if (brushlib_parse_args(argc, argv) == FALSE) {
    return BRUSHLIB_INIT_ERROR_INTERNAL;
  }

  return BRUSHLIB_INIT_SUCCESS;
}
