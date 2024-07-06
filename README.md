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

First install required submodules:

```bash
git submodule update --init --recursive
```

This project uses vcpkg to manage dependencies which is installed as a git submodule. vcpkg is designed to statically compile programs and makes it difficult to rely on shared libraries[^1]. For the time being, this repo follows the path of least resistance. However, a number of build tools are required to be present.

[^1]: Previously, kdeck used the [Boost.JSON](https://boost.org/libs/json) and [curlpp](http://www.curlpp.org/) ([libcURL](https://curl.se/libcurl/) wrapper) libraries to make API requests. See the `curl-and-boost` branch for the version based on these other libraries. (This branch does not make use of vcpkg.)

A `Dockerfile` documents which packages are required to acquire the necessary tools and build on a Debian-based system. You may install these directly or use the Docker-based build

## Build Steps

This project uses [CMake](https://cmake.org/) for builds.

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
./vendor/microsoft/vcpkg/vcpkg install
docker build -t kdeck-build .
docker run -v "<MOUNT_PATH>:/src/build" -v "<SOURCE_PATH>/vendor:/src/vendor" kdeck-build
```

where `<MOUNT_PATH>` is a named volume (e.g. `kdeck-build-volume`) or a bind-mounted directory (e.g. `$(pwd)/build`) and where `<SOURCE_PATH>` is the source root directory (e.g. `$(pwd)`).

> [!NOTE]
> While kdeck is statically linked by the vcpkg build process, it is not tested on systems other than Debian 12 (Bookworm).

## Design Tools

This project is **not yet** making use of wxWidgets' XRC support. In the future, one of the following design tools will be recommended for work on the kdeck project:

* codeblocks
* codelite
* wxglade

## Kalshi API

Kalshi provides a [REST API](https://trading-api.readme.io/reference/getting-started) for getting portfolio information and making trades, among other things. kdeck uses the [Oat++](https://oatpp.io/) library to make API requests[^1].

Kalshi provides a [demo environment](https://trading-api.readme.io/reference/creating-a-demo-account) for API development.
