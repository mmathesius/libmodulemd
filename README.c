// gcc -g -I./modulemd/include/modulemd-2.0 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -L./debugbuild/modulemd -lmodulemd -lgobject-2.0 -lglib-2.0 README.c

#include "modulemd.h"

int
main (int argc, char *argv[])
{
  // clang-format off
  g_autofree gchar *fedora_yaml = g_strdup(
"---\n"
"document: modulemd\n"
"version: 2\n"
"data:\n"
"  name: modulename\n"
"  stream: modulestream\n"
"  version: 0\n"
"  context: deadbeef\n"
"  arch: coolarch\n"
"  summary: Module Summary\n"
"  description: >-\n"
"    Module Description\n"
"  api:\n"
"    rpms:\n"
"      - rpm_a\n"
"      - rpm_b\n"
"  filter:\n"
"    rpms: rpm_c\n"
"\n"
"  artifacts:\n"
"    rpms:\n"
"      - bar-0:1.23-1.module_deadbeef.x86_64\n"
"\n"
"  servicelevels:\n"
"    rawhide: {}\n"
"    production:\n"
"      eol: 2099-12-31\n"
"\n"
"  license:\n"
"    content:\n"
"      - BSD\n"
"      - GPLv2+\n"
"    module: MIT\n"
"\n"
"  dependencies:\n"
"    - buildrequires:\n"
"          platform: [-f27, -f28, -epel7]\n"
"      requires:\n"
"          platform: [-f27, -f28, -epel7]\n"
"    - buildrequires:\n"
"          platform: [f27]\n"
"          buildtools: [v1, v2]\n"
"          compatible: [v3]\n"
"      requires:\n"
"          platform: [f27]\n"
"          compatible: [v3, v4]\n"
"    - buildrequires:\n"
"          platform: [f28]\n"
"      requires:\n"
"          platform: [f28]\n"
"          runtime: [a, b]\n"
"    - buildrequires:\n"
"          platform: [epel7]\n"
"          extras: []\n"
"          moreextras: [foo, bar]\n"
"      requires:\n"
"          platform: [epel7]\n"
"          extras: []\n"
"          moreextras: [foo, bar]\n"
"  references:\n"
"        community: http://www.example.com/\n"
"        documentation: http://www.example.com/\n"
"        tracker: http://www.example.com/\n"
"  profiles:\n"
"        default:\n"
"            rpms:\n"
"                - bar\n"
"                - bar-extras\n"
"                - baz\n"
"        container:\n"
"            rpms:\n"
"                - bar\n"
"                - bar-devel\n"
"        minimal:\n"
"            description: Minimal profile installing only the bar package.\n"
"            rpms:\n"
"                - bar\n"
"        buildroot:\n"
"            rpms:\n"
"                - bar-devel\n"
"        srpm-buildroot:\n"
"            rpms:\n"
"                - bar-extras\n"
"  buildopts:\n"
"        rpms:\n"
"            macros: |\n"
"                %demomacro 1\n"
"                %demomacro2 %{demomacro}23\n"
"            whitelist:\n"
"                - fooscl-1-bar\n"
"                - fooscl-1-baz\n"
"                - xxx\n"
"                - xyz\n"
"#       arches: [i686, x86_64]\n"
"  components:\n"
"        rpms:\n"
"            bar:\n"
"                rationale: We need this to demonstrate stuff.\n"
"                repository: https://pagure.io/bar.git\n"
"                cache: https://example.com/cache\n"
"                ref: 26ca0c0\n"
"            baz:\n"
"                rationale: This one is here to demonstrate other stuff.\n"
"            xxx:\n"
"                rationale: xxx demonstrates arches and multilib.\n"
"                arches: [i686, x86_64]\n"
"                multilib: [x86_64]\n"
"            xyz:\n"
"                rationale: xyz is a bundled dependency of xxx.\n"
"                buildorder: 10\n"
"        modules:\n"
"            includedmodule:\n"
"                rationale: Included in the stack, just because.\n"
"                repository: https://pagure.io/includedmodule.git\n"
"                ref: somecoolbranchname\n"
"                buildorder: 100\n"
"  xmd:\n"
"        some_key: some_data\n"
"        some_list:\n"
"            - a\n"
"            - b\n"
"        some_dict:\n"
"            a: alpha\n"
"            b: beta\n"
"            some_other_list:\n"
"                - c\n"
"                - d\n"
"            some_other_dict:\n"
"                another_key: more_data\n"
"                yet_another_key:\n"
"                    - this\n"
"                    - is\n"
"                    - getting\n"
"                    - silly\n"
"        can_bool: TRUE\n"
"...\n");
  g_autofree gchar *updates_yaml = g_strdup(
"---\n"
"document: modulemd-defaults\n"
"version: 1\n"
"data:\n"
"    module: modulename\n"
"    stream: mnds\n"
"...\n");
  // clang-format on

// fprintf (stderr, "DEBUG: fedora_yaml: %s\n", fedora_yaml);
// fprintf (stderr, "DEBUG: updates_yaml: %s\n", updates_yaml);

g_autofree GError *error = NULL;
GPtrArray *failures = NULL;

ModulemdModuleIndex * fedora_index = modulemd_module_index_new ();
gboolean ret = modulemd_module_index_update_from_string (fedora_index,
                                                         fedora_yaml,
                                                         TRUE,
                                                         &failures,
                                                         &error);

// fprintf (stderr, "DEBUG: fedora_index dump: %s\n",
//          modulemd_module_index_dump_to_string(fedora_index, &error));


ModulemdModuleIndex * updates_index = modulemd_module_index_new ();
gboolean ret2 = modulemd_module_index_update_from_string (updates_index,
                                                          updates_yaml,
                                                          TRUE,
                                                          &failures,
                                                          &error);

// fprintf (stderr, "DEBUG: updates_index dump: %s\n",
//          modulemd_module_index_dump_to_string(updates_index, &error));

ModulemdModuleIndexMerger * merger = modulemd_module_index_merger_new ();

modulemd_module_index_merger_associate_index (merger, fedora_index, 0);
modulemd_module_index_merger_associate_index (merger, updates_index, 0);

ModulemdModuleIndex * merged_index = modulemd_module_index_merger_resolve (merger, &error);

// fprintf (stderr, "DEBUG: merged_index dump: %s\n",
//          modulemd_module_index_dump_to_string(merged_index, &error));


{
ModulemdModule * module =  modulemd_module_index_get_module (merged_index, "modulename");
ModulemdDefaults * defaults = modulemd_module_get_defaults (module);
printf ("Default stream for modulename is %s\n",
        modulemd_defaults_v1_get_default_stream (MODULEMD_DEFAULTS_V1 (defaults), NULL));
}

{
ModulemdModule * module = modulemd_module_index_get_module (merged_index, "modulename");

ModulemdModuleStream * stream = modulemd_module_get_stream_by_NSVCA (module,
                                                                     "modulestream",
                                                                     0,
                                                                     "deadbeef",
                                                                     "coolarch",
                                                                     &error);

GStrv api_list = modulemd_module_stream_v2_get_rpm_api_as_strv (MODULEMD_MODULE_STREAM_V2 (stream));

printf ("Documentation for module stream is at %s\n",
        modulemd_module_stream_v2_get_documentation (MODULEMD_MODULE_STREAM_V2 (stream)));
g_autofree gchar *doc;
g_object_get (MODULEMD_MODULE_STREAM_V2 (stream), "documentation", &doc, NULL);
printf ("Documentation for module stream is at %s\n", doc);

}

{
ModulemdModule * module = modulemd_module_index_get_module (merged_index, "modulename");
ModulemdModuleStream * stream = modulemd_module_get_stream_by_NSVCA (module, "modulestream", 0, "deadbeef", "coolarch", &error);

GPtrArray * deps_list = modulemd_module_stream_v2_get_dependencies (MODULEMD_MODULE_STREAM_V2 (stream));

for (gint i = 0; i < deps_list->len; i++)
  {
    GStrv depmodules_list = modulemd_dependencies_get_runtime_modules_as_strv(g_ptr_array_index(deps_list, i));
    for (gint j = 0; j < g_strv_length (depmodules_list); j++)
      {
        GStrv depstreams_list = modulemd_dependencies_get_runtime_streams_as_strv(g_ptr_array_index(deps_list, i), depmodules_list[j]);
        for (gint k = 0; k < g_strv_length (depstreams_list); k++)
          {
            fprintf (stderr, "// stuff with dep#%d %s:%s\n", i+1, depmodules_list[j], depstreams_list[k]);
          }
      }
  }
}

}
