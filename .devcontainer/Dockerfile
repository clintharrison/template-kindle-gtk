FROM mcr.microsoft.com/devcontainers/base:noble

# Uncomment this to download the firmware.bin file needed to build the sdk:
# It's a bit faster if you're iterating on anything beyond this in the Dockerfile,
# since this gets downloaded by kindle-sdk/gen-sdk.sh on startup otherwise.
#
#    RUN mkdir -p /opt/kindle-sdk/cache/arm-kindlehf-linux-gnueabihf \
#      && curl -L -C - -o /opt/kindle-sdk/cache/arm-kindlehf-linux-gnueabihf/firmware.bin https://s3.amazonaws.com/firmwaredownloads/update_kindle_all_new_paperwhite_v2_5.16.3.bin

# Install the general build dependencies as well as the dependencies of the
# koxtoolchain and kindle-sdk repos.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install \
    git \
    build-essential \
    autoconf \
    automake \
    bison \
    flex \
    gawk \
    libtool \
    libtool-bin \
    libncurses-dev \
    curl \
    file \
    git \
    gperf \
    help2man \
    texinfo \
    unzip \
    wget \

    # For the sdk
    curl \
    sed \
    libarchive-dev \
    nettle-dev \

    # direnv is required by the VS Code Dev Container extension
    direnv \

    # GTK2.0/Meson tutorial dependencies
    ninja-build \
    libgtk2.0-dev \
    # to embed the main.ui file in the binary
    xxd \

    # for newer Meson than Ubuntu Noble has
    python3 \
    python3-pip \
    python3-setuptools \
    python3-wheel \
    pipx

RUN pipx install meson

# crosstool-ng requires heavy opt-in to run the build as root, but it's fine
# here because we're building in a container.
# We also may not need to _build_ anything, if we can fetch a pre-built toolchain.
ENV CT_EXPERIMENTAL=y CT_ALLOW_BUILD_AS_ROOT=y CT_ALLOW_BUILD_AS_ROOT_SURE=y

ARG platform=kindlehf
ENV _KINDLE_TARGET_PLATFORM=${platform}

COPY setup-toolchain.sh /tmp/setup-toolchain.sh
RUN /tmp/setup-toolchain.sh ${_KINDLE_TARGET_PLATFORM}

# This script is run when the container is started
COPY finalize.sh /opt/finalize.sh
