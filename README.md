# kdeck

A wxWidgets-based desktop client for the [Kalshi](https://kalshi.com/) event trading platform written in C++.

Project hosted at: https://github.com/krazkidd/kdeck

License: GPLv3 (see LICENSE.md file)

![image](https://github.com/krazkidd/kdeck/assets/6730333/f0864196-c12e-457a-a95f-cb7205836598)

## Getting Started

To get started with the kdeck project, you will need to install a few dependencies. These should be available through your system package manager.

> [!NOTE]  
> kdeck is primarily developed on Debian 12 (Bookworm) and any instructions may have to be adapted for other systems.

### System Requirements

The program is statically linked so no shared libraries should be required. Performance requirements should be minimal but note that kdeck is a GUI program based on wxWidgets, so a desktop environment is required. On Linux, your desktop environment must support GTK.

### Build Requirements

This project uses vcpkg to manage dependencies and builds. vcpkg is a [CMake](https://cmake.org/) integration and is loaded via a special toolchain file. Per upstream recommendation, vcpkg is stored as a git submodule.

First install required submodules and bootstrap vcpkg:

```bash
git submodule update --init --recursive
./vendor/microsoft/vcpkg/bootstrap-vcpkg.sh
```

vcpkg is designed to statically compile programs and makes it difficult to rely on shared libraries. For the time being, this repo follows the path of least resistance[^1].

[^1]: Previously, kdeck used the [Boost.JSON](https://boost.org/libs/json) and [curlpp](http://www.curlpp.org/) ([libcURL](https://curl.se/libcurl/) wrapper) libraries to make API requests. See the `curl-and-boost` branch for the version based on these other libraries. (This branch does not make use of vcpkg but rather vanilla CMake.)

However, a number of build tools are required to be present on the system. A `Dockerfile` documents which packages must be installed to acquire the necessary tools on a Debian-based system. You may install these directly or use the Docker-based build.

## Build Steps

> [!NOTE]
> While kdeck is statically linked by the vcpkg build process, it is not tested on systems other than Debian 12 (Bookworm).

### Debug Builds

To build on the command line, simply perform these steps from the root source directory:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE="Debug" ..
make
```

Or, preferrably:

```bash
cmake --preset debug
cmake --build --preset debug
```

You will find the final build output under `build/bin`.

> [!TIP]
> Your IDE may provide a CMake integration for building and attaching a debugger.

### Release Builds

> [!CAUTION]
> **Release builds will target the live Kalshi trading platform. You are responsible for any activity made through the API.**

One way to create a release build is to invoke CMake directly, like the debug build above:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE="Release" ..
make
```

Or, preferrably:

```bash
cmake --preset release
cmake --build --preset release
```

For official releases, a `Dockerfile` is provided. If you have Docker installed, you may run from the root source directory:

```bash
docker build -t kdeck-build .
docker run -v "$(pwd)/build:/src/build" kdeck-build
```

You will find the final build output under `$(pwd)/build/bin`. The container is no longer needed.

For repeated builds, **you should persist vcpkg's binary cache of installed dependencies with an additional bind mount:**

```bash
docker build -t kdeck-build .
docker run -v "$(pwd)/build:/src/build" -v "$(pwd)/vcpkg_installed:/src/vcpkg_installed" kdeck-build
```

> [!WARNING]
> This is the default vcpkg binary cache directory for this project. If your host system is Debian 12 (Bookworm), it should be safe to bind-mount this directory and share installed dependencies with the container. Users on other systems wishing to build with and without Docker may want to bind-mount to a different host directory (although builds targeting different system triplets can coexist).

## Design Tools

This project is **not yet** making use of wxWidgets' XRC support. In the future, one of the following design tools will be recommended for work on the kdeck project:

* codeblocks
* codelite
* wxglade

## Kalshi API

Kalshi provides a [REST API](https://trading-api.readme.io/reference/getting-started) for getting portfolio information and making trades, among other things. kdeck uses the [Oat++](https://oatpp.io/) library to make API requests[^1].

Kalshi provides a [demo environment](https://trading-api.readme.io/reference/creating-a-demo-account) for API development.
