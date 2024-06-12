# kdeck

A wxWidgets-based desktop client for the [Kalshi](https://kalshi.com/) event trading platform written in C++.

Project hosted at: https://github.com/krazkidd/kdeck

License: GPLv3 (see LICENSE.md file)

## Getting Started

To get started with the kdeck project, you will need to install a few dependencies. These should be available through your system package manager. 

> [!NOTE]  
> The names and versions below come from Debian 12 (Bookworm) and may vary on your system.

### System Requirements

Make sure you have the following dependencies installed on your system. The version numbers are not strict requirements but the ones shown were available during development.

* libcurlpp (version 0 or higher)
* libboost-json (version 1.81.0 or higher)
* libwxgtk (version 3.2 or higher)

### Build Requirements

At a minimum, you will need these build tools:

* gcc
* cmake

Don't forget to install development headers for system dependencies if they are distributed separately on your system:

* libcurlpp-dev
* libboost-json1.81-dev
* libwxgtk3.2-dev

### Build Steps

This project uses [CMake](https://cmake.org/) for builds. Out-of-source builds are expected. To build on the command line, simply perform these steps from the root source directory:

```bash
mkdir build
cd build
cmake ..
make
```

You will find the build output under `build/bin`.

> [!NOTE]
> Your IDE may provide a CMake integration for building and running the program.

> [!NOTE]
> Builds used to rely on Microsoft's [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) extension for Visual Studio Code. You can find the old config [here](https://github.com/krazkidd/kdeck/blob/c8c90c0709d981d3f6170763a70ff6e239ec2001/.vscode/tasks.json).

### Design Tools

This project is **not yet** making use of wxWidgets' XRC support. In the future, one of the following design tools will be recommended for work on the kdeck project:

* codeblocks
* codelite
* wxglade

## Kalshi API

Kalshi provides a [REST API](https://trading-api.readme.io/reference/getting-started) for getting portfolio information and making trades, among other things. kdeck uses the [Boost.JSON](https://boost.org/libs/json) and [curlpp](http://www.curlpp.org/) ([libcURL](https://curl.se/libcurl/) wrapper) libraries to make API requests.

Kalshi provides a [demo environment](https://trading-api.readme.io/reference/creating-a-demo-account) for API development.
