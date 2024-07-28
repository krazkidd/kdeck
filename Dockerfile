FROM debian:bookworm-slim

ARG APP_VERSION="0.0.0"

# NOTE: vcpkg packages expect various build tools to be present.
#       The *-dev packages especially pull in many additional
#       dependencies.

RUN apt-get update && apt-get -y --no-install-suggests install \
    automake \
    bison \
    ca-certificates \
    cmake \
    curl \
    g++ \
    git \
    make \
    libgtk-3-dev \
    libtool \
    libwxgtk3.2-dev \
    python3 \
    python3-jinja2 \
    unzip \
    zip \
    && apt-get clean \
    && rm -r /var/lib/apt/lists /var/cache/apt

WORKDIR /src
COPY . /src

# not necessary if this has been performed on the host, but just in case
RUN ["git", "submodule", "update", "--init", "--recursive"]

# bootstrap vcpkg (download the vcpkg executable itself)
RUN ["./vendor/microsoft/vcpkg/bootstrap-vcpkg.sh"]

SHELL ["/bin/bash", "-c"]

#TODO it's not clear why we need CMAKE_MAKE_PROGRAM; this is supposed to be detected automatically;
#     is it because the shell form of RUN doesn't capture environment variables? (a new shell is invoked)
CMD cmake -DCMAKE_MAKE_PROGRAM=make -DAPP_VERSION="$APP_VERSION" --preset release \
    && cmake --build --preset release
