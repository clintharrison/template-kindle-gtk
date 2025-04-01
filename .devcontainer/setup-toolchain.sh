#!/bin/bash

# This script is run during the devcontainer Docker build.
# It installs a prebuilt koxtoolchain and clones the kindle-sdk repo.
# (It cannot run the setup for the latter, because that requires extra
# privileges. Those flags can only be used when running a container, not when
# building one)

set -euo pipefail

mkdir -p /opt

# The first argument is the target platform
case $1 in
    kindlehf|kindlepw2)
        target=$1
        ;;
    *)
        echo "Usage: $0 <target>"
        echo "  target: kindlehf, kindlepw2"
        echo "See https://kindlemodding.org/kindle-dev/gtk-tutorial/prerequisites.html"
        exit 1
        ;;
esac

# This repo may not necessarily be needed, but it's small and harmless.
# It's much nicer to download the tarball from the release page if we can.
git clone --recursive --depth=1 https://github.com/koreader/koxtoolchain /opt/koxtoolchain

# The kindle-sdk repo is needed for the gen-sdk.sh script which is run on startup.
git clone --recursive --depth=1 https://github.com/KindleModding/kindle-sdk /opt/kindle-sdk

# Download the prebuilt toolchain if we can...
arch=$(uname -m)
if [[ $arch == "x86_64" ]]; then
    echo >&2 "Downloading prebuilt toolchain for host architecture ${arch}, building for ${target}"
    mkdir -p ~/x-tools
    curl -L https://github.com/koreader/koxtoolchain/releases/download/2025.01/${target}.tar.gz \
    | tar -zx --strip-components=1 -C ~/x-tools
else
    echo >&2 "No prebuilt toolchain available for host architecture ${arch}, building from source"
    cd /opt/koxtoolchain
    bash -x gen-tc.sh ${target}
fi
