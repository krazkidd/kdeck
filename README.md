# kdeck

A wxWidgets-based desktop client for the [Kalshi](https://kalshi.com/) event trading platform written in C++.

Project hosted at: https://github.com/krazkidd/kdeck

License: GPLv3 (see LICENSE.md file)

## Getting Started

To get started with the kdeck project, you will need to install a few dependencies. These should be available through your system package manager. The names and versions below come from Debian 12 (Bookworm) but may vary on your system.

### System Requirements

Make sure you have the following dependencies installed on your system. The version numbers are not strict requirements but the ones shown were available during development.

* libcurlpp (version 0 or higher)
* libboost-json (version 1.81.0 or higher)
* libwxgtk (version 3.2 or higher)

### Build Requirements

Don't forget to install development headers if they are distributed separately on your system:

* libcurlpp-dev
* libboost-json1.81-dev
* libwxgtk3.2-dev

### Build Steps

I haven't added a conventional build configuration (make/cmake) yet. I am currently relying on Microsoft's [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) extension for Visual Studio Code. If you are using VS Code, open a `*.cpp` file and click the 'Run or Debug...' button that appears in the tab bar to compile and start the program.

Note that this extension integrates with the system `g++` install, and the config for the command can be found in `.vscode/tasks.json`, if you wish to run the command directly.

### Design Tools

This project is not yet making use of wxWidgets' XRC support. In the future, one of the following design tools will be recommended for work on the kdeck project:

* codeblocks
* codelite
* wxglade

## Kalshi API

Kalshi provides a [REST API](https://trading-api.readme.io/reference/getting-started) for getting portfolio information and making trades, among other things. kdeck uses the [Boost.JSON](https://boost.org/libs/json) and [curlpp](http://www.curlpp.org/) libraries to make API requests.

Kalshi provides a [demo environment](https://trading-api.readme.io/reference/creating-a-demo-account) for API development.
