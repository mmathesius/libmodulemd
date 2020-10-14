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

#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

/**
 * SECTION: modulemd-configurations
 * @title: Modulemd.Configurations
 * @stability: stable
 * @short_description: Object to represent build-time and runtime dependencies of a module stream.
 */

#define MODULEMD_TYPE_CONFIGURATIONS (modulemd_configurations_get_type ())

G_DECLARE_FINAL_TYPE (
  ModulemdConfigurations, modulemd_configurations, MODULEMD, CONFIGURATIONS, GObject)

/**
 * modulemd_configurations_new:
 *
 * Returns: (transfer full): A newly-allocated #ModulemdConfigurations object.
 * This object must be freed with g_object_unref().
 *
 * Since: 2.10
 */
ModulemdConfigurations *
modulemd_configurations_new (void);


/**
 * modulemd_configurations_equals:
 * @self_1: A #ModulemdConfigurations object.
 * @self_2: A #ModulemdConfigurations object.
 *
 * Check if @self_1 and @self_2 are equal objects.
 *
 * Returns: TRUE, if the're equal. FALSE, otherwise.
 *
 * Since: 2.10
 */
gboolean
modulemd_configurations_equals (ModulemdConfigurations *self_1,
                              ModulemdConfigurations *self_2);


/**
 * modulemd_configurations_copy:
 * @self: This #ModulemdConfigurations object.
 *
 * Create a copy of this #ModulemdConfigurations object.
 *
 * Returns: (transfer full): The copied #ModulemdConfigurations object.
 *
 * Since: 2.10
 */
ModulemdConfigurations *
modulemd_configurations_copy (ModulemdConfigurations *self);


/**
 * modulemd_configurations_add_buildtime_stream:
 * @self: This #ModulemdConfigurations object.
 * @module_name: The name of the module to depend on.
 * @module_stream: The name of the module stream to depend on.
 *
 * Add a single stream of a module that is required to build another dependent
 * module. The matrix of streams and module names will be calculated by the
 * build-system. If the provided module name is already present, the streams
 * will be added (with deduplication).
 *
 * Since: 2.10
 */
void
modulemd_configurations_add_buildtime_stream (ModulemdConfigurations *self,
                                            const gchar *module_name,
                                            const gchar *module_stream);


/**
 * modulemd_configurations_set_empty_buildtime_dependencies_for_module:
 * @self: This #ModulemdConfigurations object.
 * @module_name: The name of the module to add configurations on.
 *
 * Adds a module and inserts an empty list for it as buildtime dependency.
 *
 * Since: 2.10
 */
void
modulemd_configurations_set_empty_buildtime_dependencies_for_module (
  ModulemdConfigurations *self, const gchar *module_name);


/**
 * modulemd_configurations_clear_buildtime_dependencies:
 * @self: This #ModulemdConfigurations object.
 *
 * Remove all buildtime dependencies from this #ModulemdConfigurations object.
 *
 * Since: 2.10
 */
void
modulemd_configurations_clear_buildtime_dependencies (
  ModulemdConfigurations *self);


/**
 * modulemd_configurations_get_buildtime_modules_as_strv: (rename-to modulemd_configurations_get_buildtime_modules)
 * @self: This #ModulemdConfigurations object.
 *
 * Returns: (transfer full): An ordered #GStrv list of module names of
 * build-time dependencies.
 *
 * Since: 2.10
 */
GStrv
modulemd_configurations_get_buildtime_modules_as_strv (
  ModulemdConfigurations *self);


/**
 * modulemd_configurations_get_buildtime_streams_as_strv: (rename-to modulemd_configurations_get_buildtime_streams)
 * @self: This #ModulemdConfigurations object.
 * @module: The name of the module.
 *
 * Returns: (transfer full) (nullable): An ordered #GStrv list of module
 * streams associated with the specified module that are required at
 * build-time.
 *
 * Since: 2.10
 */
GStrv
modulemd_configurations_get_buildtime_streams_as_strv (
  ModulemdConfigurations *self, const gchar *module);


/**
 * modulemd_configurations_add_runtime_stream:
 * @self: This #ModulemdConfigurations object.
 * @module_name: The name of the module to depend on.
 * @module_stream: The name of the module stream to depend on.
 *
 * Adds a module and its stream that is required at runtime by a dependent
 * module. The matrix of streams and module names will be calculated by the
 * build-system. If the listed provided module name is already present, the
 * streams will be added (with deduplication).
 *
 * Since: 2.10
 */
void
modulemd_configurations_add_runtime_stream (ModulemdConfigurations *self,
                                          const gchar *module_name,
                                          const gchar *module_stream);


/**
 * modulemd_configurations_set_empty_runtime_dependencies_for_module:
 * @self: This #ModulemdConfigurations object.
 * @module_name: The name of the module to add dependencies on.
 *
 * Adds a module and inserts an empty list for it as runtime dependency.
 *
 * Since: 2.10
 */
void
modulemd_configurations_set_empty_runtime_dependencies_for_module (
  ModulemdConfigurations *self, const gchar *module_name);


/**
 * modulemd_configurations_clear_runtime_dependencies:
 * @self: This #ModulemdConfigurations object.
 *
 * Remove all runtime dependencies from this #ModulemdConfigurations object.
 *
 * Since: 2.10
 */
void
modulemd_configurations_clear_runtime_dependencies (ModulemdConfigurations *self);


/**
 * modulemd_configurations_get_runtime_modules_as_strv: (rename-to modulemd_configurations_get_runtime_modules)
 * @self: This #ModulemdConfigurations object.
 *
 * Returns: (transfer full): An ordered #GStrv list of module names of run-time
 * dependencies.
 *
 * Since: 2.10
 */
GStrv
modulemd_configurations_get_runtime_modules_as_strv (ModulemdConfigurations *self);


/**
 * modulemd_configurations_get_runtime_streams_as_strv: (rename-to modulemd_configurations_get_runtime_streams)
 * @self: This #ModulemdConfigurations object.
 * @module: The name of the module.
 *
 * Returns: (transfer full) (nullable): An ordered #GStrv list of module streams
 * associated with the specified module that are required at run-time.
 *
 * Since: 2.10
 */
GStrv
modulemd_configurations_get_runtime_streams_as_strv (ModulemdConfigurations *self,
                                                   const gchar *module);

G_END_DECLS
