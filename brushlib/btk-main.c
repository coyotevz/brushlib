/*
 * Btk - Brush Toolkit
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

#include "btk-main.h"
#include "btk-version.h"


/* version info */
const guint btk_major_version = BTK_MAJOR_VERSION;
const guint btk_minor_version = BTK_MINOR_VERSION;
const guint btk_micro_version = BTK_MICRO_VERSION;


static gboolean btk_is_initialized = FALSE;


/**
 * buik_get_option_group:
 *
 * Returns a #GOptionGroup for the command line arguments recognized by Btk.
 * You should add this groups to your #GOptionContext with
 * g_option_context_add_group(), if you are using g_option_context_parse() to
 * parse your commandline arguments.
 *
 * Return value: a GOptionGroup for the command line arguments
 *   recognized by Btk
 */
GOptionGroup *
btk_get_option_group(void)
{
  GOptionGroup *group;

  group = g_option_group_new("btk",
                             "Btk Options",
                             "Show Btk Options",
                             NULL, NULL);

  g_option_group_set_parse_hooks(group, btk_pre_parse_hook, btk_post_parse_hook);
  g_option_group_add_entries(group, btk_args);

  return group;
}

static gboolean
btk_parse_args(int   *argc,
               char **argv)
{
  GOptionContext *option_context;
  GOptionGroup   *btk_group;
  GError         *error = NULL;
  gboolean        ret = FALSE;

  if (btk_is_initialized)
    return TRUE;

  option_context = g_option_context_new(NULL);
  g_option_context_set_ignore_unknown_options(option_context, TRUE);
  g_option_context_set_help_enabled(option_context, FALSE);

  btk_group = btk_get_option_group();
  g_option_context_set_main_group(option_context, btk_group);

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
 * btk_init:
 * @argc: The number of arguments in @argv
 * @argv: A pointer to an array of arguments
 *
 * It will initialize everything needed to operate with Btk and parses some
 * standard command line options.  @argc and @argv are adjusted accordingly so
 * your own code will never see those standard arguments.
 *
 * Return value: 1 on success, < 0 on failure.
 */
BtkInitError
btk_init(int   *argc,
         char **argv)
{
  GError *error;

  if (argc && *argc > 0 && *argv)
    g_set_prgname ((*argv)[0]);

  if (btk_parse_args(argc, argv) == FALSE) {
    return BTK_INIT_ERROR_INTERNAL;
  }

  return BTK_INIT_SUCCESS;
}
