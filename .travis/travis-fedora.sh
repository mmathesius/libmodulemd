#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
pushd $SCRIPT_DIR

source $SCRIPT_DIR/travis-common.inc

set -e
set -x

JOB_NAME=${TRAVIS_JOB_NAME:-Fedora rawhide}

arr=($JOB_NAME)
release=${arr[1]:-rawhide}
python=${arr[3]:-default}

if [ $release = rawhide ]; then
    release=$($SCRIPT_DIR/get_rawhide_version.py)
fi

mmd_run_docker_tests \
    os=fedora \
    release=$release \
    repository=quay.io \
    image=fedora/fedora:$release-$(uname -m) \
    python=$python

popd # $SCRIPT_DIR
