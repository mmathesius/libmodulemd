#!/usr/bin/env bash

#Exit on failures
set -e
set -x

RETRY_CMD=/builddir/.ci/retry-command.sh

pushd /builddir/

# Build the code under GCC and run documentation generation
meson setup \
      --buildtype=debugoptimized \
      -Dverbose_tests=false \
      $COMMON_MESON_ARGS \
      autoformat

set +e
meson test \
      -C autoformat \
      --suite formatters \
      --print-errorlogs \
       -t 5
err=$?
if [ $err != 0 ]; then
    cat autoformat/meson-logs/testlog.txt
    exit $err
fi
set -e

rsync -avh --existing --no-perms --no-times /builddir/modulemd/ $FORMAT_DEST_DIR

popd #builddir
