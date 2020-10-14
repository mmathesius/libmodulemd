/*
 * This file is part of libmodulemd
 * Copyright (C) 2020 Red Hat, Inc.
 *
 * Fedora-License-Identifier: MIT
 * SPDX-2.0-License-Identifier: MIT
 * SPDX-3.0-License-Identifier: MIT
 *
 * This program is free software.
 * For more information on the license, see COPYING.
 * For more information on free software, see <https://www.gnu.org/philosophy/free-sw.en.html>.
 */

#include "modulemd-packager.h"


/* TODO: delete this comment block duplicated from modulemd-packager.h
 * modulemd_packager_read_file:
 * @path: (in): The path to a YAML document containing a module packager
 * definition.
 * @strict: (in): Whether the parser should return failure if it encounters an
 * unknown mapping key or if it should ignore it.
 * @module_name: (in) (nullable): An optional module name to override the
 * document on disk. Mostly useful in cases where the name is being
 * auto-detected from git.
 * @module_stream: (in) (nullable): An optional module stream name to override
 * the document on disk. Mostly useful in cases where the name is being
 * auto-detected from git.
 * @error: (out): A #GError that will return the reason for a failed read.
 *
 * Create a #ModulemdModuleIndex object from a YAML file.
 *
 * Returns: (transfer full): A newly-allocated #ModulemdModuleIndex object if
 * the YAML file was valid and contained exactly one
 * `document: modulemd-packager` subdocument. NULL if the document fails
 * validation or multiple documents are encountered and sets @error
 * appropriately. See #ModulemdModuleIndex for functions to read in
 * multiple-subdocument YAML.
 *
 * Since: 2.10
 */
ModulemdModuleIndex *
modulemd_packager_read_file (const gchar *path,
                             gboolean strict,
                             const gchar *module_name,
                             const gchar *module_stream,
                             GError **error)
{
  /* TODO: implement */
  return NULL;
}


/* TODO: delete this comment block duplicated from modulemd-packager.h
 * modulemd_packager_read_string:
 * @yaml_string: (in): A YAML document string containing a module packager
 * definition.
 * @strict: (in): Whether the parser should return failure if it encounters an
 * unknown mapping key or if it should ignore it.
 * @module_name: (in) (nullable): An optional module name to override the
 * document on disk. Mostly useful in cases where the name is being
 * auto-detected from git.
 * @module_stream: (in) (nullable): An optional module stream name to override
 * the document on disk. Mostly useful in cases where the name is being
 * auto-detected from git.
 * @error: (out): A #GError that will return the reason for a failed read.
 *
 * Create a #ModulemdModuleIndex object from a YAML string.
 *
 * Returns: (transfer full): A newly-allocated #ModulemdModuleIndex object if
 * the YAML string was valid and contained exactly one
 * `document: modulemd-packager` subdocument. NULL if the document fails
 * validation or multiple documents are encountered and sets @error
 * appropriately. See #ModulemdModuleIndex for functions to read in
 * multiple-subdocument YAML.
 *
 * Since: 2.10
 */
ModulemdModuleIndex *
modulemd_packager_read_string (const gchar *yaml_string,
                               gboolean strict,
                               const gchar *module_name,
                               const gchar *module_stream,
                               GError **error)
{
  /* TODO: implement */
  return NULL;
}


/* TODO: delete this comment block duplicated from modulemd-packager.h
 * modulemd_packager_read_stream: (skip)
 * @stream: (in): A YAML document as a FILE * containing a module packager
 * definition.
 * @strict: (in): Whether the parser should return failure if it encounters an
 * unknown mapping key or if it should ignore it.
 * @module_name: (in) (nullable): An optional module name to override the
 * document on disk. Mostly useful in cases where the name is being
 * auto-detected from git.
 * @module_stream: (in) (nullable): An optional module stream name to override
 * the document on disk. Mostly useful in cases where the name is being
 * auto-detected from git.
 * @error: (out): A #GError that will return the reason for a failed read.
 *
 * Create a #ModulemdModuleIndex object from a YAML file.
 *
 * Returns: (transfer full): A newly-allocated #ModulemdModuleIndex object if
 * the YAML file was valid and contained exactly one
 * `document: modulemd-packager` subdocument. NULL if the document fails
 * validation or multiple documents are encountered and sets NULL appropriately.
 * See #ModulemdModuleIndex for functions to read in multiple-subdocument YAML.
 *
 * Since: 2.10
 */
ModulemdModuleIndex *
modulemd_packager_read_stream (FILE *stream,
                               gboolean strict,
                               const gchar *module_name,
                               const gchar *module_stream,
                               GError **error)
{
  /* TODO: implement */
  return NULL;
}


G_END_DECLS
