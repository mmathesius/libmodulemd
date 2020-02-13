#!/usr/bin/python3

# This file is part of libmodulemd
# Copyright (C) 2017-2018 Stephen Gallagher
#
# Fedora-License-Identifier: MIT
# SPDX-2.0-License-Identifier: MIT
# SPDX-3.0-License-Identifier: MIT
#
# This program is free software.
# For more information on the license, see COPYING.
# For more information on free software, see
# <https://www.gnu.org/philosophy/free-sw.en.html>.

import os
import sys
import subprocess
import tempfile
import xml.etree.ElementTree as ET

from multiprocessing import Pool, TimeoutError

if os.getenv("MMD_SKIP_VALGRIND"):
    sys.exit(77)

supp_file = os.path.join(
    os.getenv("MESON_SOURCE_ROOT", "."),
    "contrib",
    "valgrind",
    "libmodulemd-python.supp",
)

failed = False

# Get the list of tests to run
tests = []
if len(sys.argv) > 1:
    tests = sys.argv[1:]
else:
    sys.exit(77)


with tempfile.TemporaryDirectory(prefix="libmodulemd_valgrind_") as tmpdirname:

    def exec_valgrind(test):
        valgrind_command = (
            "/usr/bin/valgrind "
            "--leak-check=full "
            "--suppressions=/usr/share/glib-2.0/valgrind/glib.supp "
            "--suppressions=%s "
            "--gen-suppressions=all "
            "--show-possibly-lost=no "
            "--xml=yes "
            "--xml-file=%s/%s.xml " % (supp_file, tmpdirname, test)
        )
        proc_result = subprocess.run(
            [
                "meson",
                "test",
                "--no-rebuild",
                "-t",
                "10",
                "--logbase=%s" % test,
                "--wrap=%s" % valgrind_command,
                test,
            ]
        )

        return proc_result.returncode, test

    with Pool() as pool:
        for returncode, test in pool.map(exec_valgrind, tests):
            if returncode != 0:
                print(
                    "Valgrind exited with error [%d] on %s"
                    % (returncode, test),
                    file=sys.stderr,
                )
                failed = True
                continue

            test_failed = False

            # Process the XML for leaks
            tree = ET.parse("%s/%s.xml" % (tmpdirname, test))
            root = tree.getroot()

            for root_child in root:
                if root_child.tag == "error":
                    for error_child in root_child:
                        if error_child.tag == "kind":
                            if error_child.text == "Leak_DefinitelyLost":
                                print(
                                    "Memory leak detected in %s" % test,
                                    file=sys.stderr,
                                )
                                test_failed = True

                            elif error_child.text == "InvalidFree":
                                print(
                                    "Invalid free() detected in %s" % test,
                                    file=sys.stderr,
                                )
                                test_failed = True

                            elif error_child.text == "InvalidRead":
                                print(
                                    "Invalid read detected in %s" % test,
                                    file=sys.stderr,
                                )
                                test_failed = True

                            elif error_child.text == "UninitCondition":
                                print(
                                    "Uninitialized usage detected in %s"
                                    % test,
                                    file=sys.stderr,
                                )
                                test_failed = True

            if test_failed:
                with open("%s/%s.xml" % (tmpdirname, test), "r") as xml:
                    print(xml.read())
                failed = True

if failed:
    sys.exit(1)
