FROM debian:bookworm-slim

# NOTE: This is not a minimal set of dependencies. However, because
#       different vcpkg packages expect various build tools to be
#       present, it was easier to install them as secondary dependencies
#       of their Debian counterparts.

RUN apt-get update && apt-get -y --no-install-suggests install \
    autoconf \
    automake \
    bison \
    build-essential \
    ca-certificates \
    cmake \
    curl \
    g++ \
    git \
    make \
    libdbus-1-dev \
    libgles2-mesa-dev \
    libgtk-3-dev \
    libsystemd-dev \
    libtool \
    libwxgtk3.2-dev \
    libx11-dev \
    libxext-dev \
    libxft-dev \
    libxi-dev \
    libxtst-dev \
    #linux-libc-dev \
    pkg-config \
    python3 \
    python3-babel \
    python3-jinja2 \
    unzip \
    zip \
    && apt-get clean \
    && rm -r /var/lib/apt/lists /var/cache/apt

WORKDIR /src
COPY . /src

# NOTE: We have to run the configure step and the build step together
#       because /src/build is bind-mounted to the host machine, and that
#       needs to occur before the configure step is run or else the
#       files are obscured. Therefore, we have to use the shell form
#       rather than the exec form.

#TODO it's not clear why we need CMAKE_MAKE_PROGRAM; this is supposed to be detected automatically
CMD cmake -DCMAKE_MAKE_PROGRAM=make --preset release && cmake --build --preset release
