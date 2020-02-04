import gi
gi.require_version('Modulemd', '2.0')
from gi.repository import Modulemd

from os import path

fedora_yaml = """
---
document: modulemd
version: 2
data:
  name: modulename
  stream: modulestream
  version: 0
  context: deadbeef
  arch: coolarch
  summary: Module Summary
  description: >-
    Module Description
  api:
    rpms:
      - rpm_a
      - rpm_b
  filter:
    rpms: rpm_c

  artifacts:
    rpms:
      - bar-0:1.23-1.module_deadbeef.x86_64

  servicelevels:
    rawhide: {}
    production:
      eol: 2099-12-31

  license:
    content:
      - BSD
      - GPLv2+
    module: MIT

  dependencies:
    - buildrequires:
          platform: [-f27, -f28, -epel7]
      requires:
          platform: [-f27, -f28, -epel7]
    - buildrequires:
          platform: [f27]
          buildtools: [v1, v2]
          compatible: [v3]
      requires:
          platform: [f27]
          compatible: [v3, v4]
    - buildrequires:
          platform: [f28]
      requires:
          platform: [f28]
          runtime: [a, b]
    - buildrequires:
          platform: [epel7]
          extras: []
          moreextras: [foo, bar]
      requires:
          platform: [epel7]
          extras: []
          moreextras: [foo, bar]
  references:
        community: http://www.example.com/
        documentation: http://www.example.com/
        tracker: http://www.example.com/
  profiles:
        default:
            rpms:
                - bar
                - bar-extras
                - baz
        container:
            rpms:
                - bar
                - bar-devel
        minimal:
            description: Minimal profile installing only the bar package.
            rpms:
                - bar
        buildroot:
            rpms:
                - bar-devel
        srpm-buildroot:
            rpms:
                - bar-extras
  buildopts:
        rpms:
            macros: |
                %demomacro 1
                %demomacro2 %{demomacro}23
            whitelist:
                - fooscl-1-bar
                - fooscl-1-baz
                - xxx
                - xyz
#       arches: [i686, x86_64]
  components:
        rpms:
            bar:
                rationale: We need this to demonstrate stuff.
                repository: https://pagure.io/bar.git
                cache: https://example.com/cache
                ref: 26ca0c0
            baz:
                rationale: This one is here to demonstrate other stuff.
            xxx:
                rationale: xxx demonstrates arches and multilib.
                arches: [i686, x86_64]
                multilib: [x86_64]
            xyz:
                rationale: xyz is a bundled dependency of xxx.
                buildorder: 10
        modules:
            includedmodule:
                rationale: Included in the stack, just because.
                repository: https://pagure.io/includedmodule.git
                ref: somecoolbranchname
                buildorder: 100
  xmd:
        some_key: some_data
        some_list:
            - a
            - b
        some_dict:
            a: alpha
            b: beta
            some_other_list:
                - c
                - d
            some_other_dict:
                another_key: more_data
                yet_another_key:
                    - this
                    - is
                    - getting
                    - silly
        can_bool: TRUE
...
"""

updates_yaml = """
---
document: modulemd-defaults
version: 1
data:
    module: modulename
    stream: mnds
...
"""

# print ('DEBUG: fedora_yaml: %s' % fedora_yaml)
# print ('DEBUG: updates_yaml: %s' % updates_yaml)

fedora_index = Modulemd.ModuleIndex.new()
ret, failures = fedora_index.update_from_string(fedora_yaml, True)

updates_index = Modulemd.ModuleIndex.new()
ret, failures = updates_index.update_from_string(updates_yaml, True)

merger = Modulemd.ModuleIndexMerger.new()

merger.associate_index(fedora_index, 0)
merger.associate_index(updates_index, 0)

merged_index = merger.resolve()
# print ('DEBUG: merged_index dump: %s' % merged_index.dump_to_string())

module = merged_index.get_module ('modulename')

streams = module.get_all_streams()

defaults = module.get_defaults()
print ('Default stream for modulename is %s' %
       defaults.get_default_stream())

module = merged_index.get_module ('modulename')

stream = module.get_stream_by_NSVCA('modulestream', 0, 'deadbeef', 'coolarch')

api_list = stream.get_rpm_api()

print ('Documentation for module stream is at %s' % stream.get_documentation())
print ('Documentation for module stream is at %s' % stream.props.documentation)

module = merged_index.get_module ('modulename')
stream = module.get_stream_by_NSVCA('modulestream', 0, 'deadbeef', 'coolarch')
deps_list = stream.get_dependencies()

depnum = 0
for dep in deps_list:
    depnum += 1
    depmodules_list = dep.get_runtime_modules()
    for depmod in depmodules_list:
        depstream_list = dep.get_runtime_streams(depmod)
        for depstream in depstream_list:
            print ('# stuff with dep#%d runtime %s:%s' % (depnum, depmod, depstream))

    buildmodules_list = dep.get_buildtime_modules()
    for mod in buildmodules_list:
        depstream_list = dep.get_buildtime_streams(mod)
        for s in depstream_list:
            print ('# stuff with dep#%d buildtime %s:%s' % (depnum, mod, s))

stream = Modulemd.ModuleStream.read_file ('module.yaml',
                                          True,
                                          'new_module',
                                          'new_stream')
v2_stream = stream.upgrade(Modulemd.ModuleStreamVersionEnum.TWO)
v2_stream.validate()
print ('DEBUG:   %s' % v2_stream.get_NSVCA())
