/*
 * This file is part of libmodulemd
 * Copyright (C) 2018 Red Hat, Inc.
 *
 * Fedora-License-Identifier: MIT
 * SPDX-2.0-License-Identifier: MIT
 * SPDX-3.0-License-Identifier: MIT
 *
 * This program is free software.
 * For more information on the license, see COPYING.
 * For more information on free software, see <https://www.gnu.org/philosophy/free-sw.en.html>.
 */

#pragma once

#include <glib-object.h>
#include <yaml.h>

#include "modulemd-configurations.h"

/**
 * SECTION: modulemd-configurations-private
 * @title: Modulemd.Configurations (Private)
 * @stability: Private
 * @short_description: #ModulemdConfigurations methods that should be used only
 * by internal consumers.
 */

/**
 * modulemd_configurations_parse_yaml:
 * @parser: (inout): A libyaml parser object positioned at a sequence entry for
 * a Configurations object.
 * @strict: (in): Whether the parser should return failure if it encounters an
 * unknown mapping key or if it should ignore it.
 * @error: (out): A #GError that will return the reason for a parsing or
 * validation error.
 *
 * Returns: (transfer full): A newly-allocated #ModulemdConfigurations object
 * read from the YAML. NULL if a parse or validation error occurred and sets
 * @error appropriately.
 *
 * Since: 2.0
 */
ModulemdConfigurations *
modulemd_configurations_parse_yaml (yaml_parser_t *parser,
                                  gboolean strict,
                                  GError **error);


/**
 * modulemd_configurations_emit_yaml:
 * @self: This #ModulemdConfigurations object.
 * @emitter: (inout): A libyaml emitter object positioned where a configurations instance
 * belongs in the YAML document.
 * @error: (out): A #GError that will return the reason for an emission or
 * validation error.
 *
 * Returns: TRUE if the configurations object was emitted successfully. FALSE and sets
 * @error appropriately if the YAML could not be emitted.
 *
 * Since: 2.0
 */
gboolean
modulemd_configurations_emit_yaml (ModulemdConfigurations *self,
                                 yaml_emitter_t *emitter,
                                 GError **error);


/**
 * modulemd_configurations_validate:
 * @self: This #ModulemdConfigurations object.
 * @error: (out): A #GError containing the reason the object failed validation.
 * NULL if the validation passed.
 *
 * Returns: TRUE if validation passed. FALSE and sets @error if failed.
 *
 * This method runs a sanity check that the runtime (requires) and buildtime
 * (buildrequires) dependencies are internally consistent.
 *
 * Since: 2.0
 */
gboolean
modulemd_configurations_validate (ModulemdConfigurations *self, GError **error);


/**
 * modulemd_configurations_requires_module_and_stream:
 * @self: This #ModulemdConfigurations object.
 * @module_name: (in): The name of the module to be checked.
 * @stream_name: (in): The name of the stream to be checked.
 *
 * Returns: TRUE if the specified runtime dependency is present. FALSE if not.
 *
 * This method checks if the runtime dependencies for this object include the
 * specified module stream.
 *
 * Since: 2.2
 */
gboolean
modulemd_configurations_requires_module_and_stream (ModulemdConfigurations *self,
                                                  const gchar *module_name,
                                                  const gchar *stream_name);


/**
 * modulemd_configurations_buildrequires_module_and_stream:
 * @self: This #ModulemdConfigurations object.
 * @module_name: (in): The name of the module to be checked.
 * @stream_name: (in): The name of the stream to be checked.
 *
 * Returns: TRUE if the specified buildtime dependency is present. FALSE if not.
 *
 * This method checks if the buildtime dependencies for this object include the
 * specified module stream.
 *
 * Since: 2.2
 */
gboolean
modulemd_configurations_buildrequires_module_and_stream (
  ModulemdConfigurations *self,
  const gchar *module_name,
  const gchar *stream_name);
