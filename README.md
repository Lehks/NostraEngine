# NostraEngine
A 3D game engine.

The NostraEngine is a project created by students of the htw saar (https://www.htwsaar.de/) and supervised by
Dipl-Inf (FH) Christopher Olbertz.

GitHub: https://github.com/Lehks/NostraEngine

If you do not have the code yet, use the following command to clone the repository to your local
machine:  
```bash
git clone https://github.com/Lehks/NostraEngine.git
```` 
or download the ZIP-compressed directly from GitHub using the link above.

## Building the Project

To build this project, CMake is required. See this (https://cmake.org/install/) link for an explanation on how
to install CMake. The minimum required version of CMake is 3.8.2.
On Windows, Visual Studio (https://www.visualstudio.com) is also a requirement.

Additionally, the C+ compiler needs to support C\++17 or higher. The latest Version of Visual Studio supports 
C++17 and GCC has full support for C\++17 in version 7 and higher.

Building the project is done in two steps: 
1. Generating platform dependent configuration files (e.g. a Makefile or Visual Studio Solution) using CMake 
   (Chapter [Calling CMake](#Calling-CMake)).
2. Compiling the code from those configuration files and installing it (Chapter 
   [Build and Install](#Build-and-Install)).

### Calling CMake

In this chapter, CMake will be used to generate platform dependent configuration files (e.g. a Makefile or 
a Visual Studio Solution). Those configuration files will then later be used to actually build the project.

Calling CMake is done from the terminal. It is also assumed that the command ```cmake``` reachable through 
the system's ```PATH``` variable.

First, we need to cd into the directory where the configuration files should be placed by CMake. This can be
any directory, except for the directory that contains the source files. In the following, 
```/path/to/source/root``` will be used as a placeholder for the path to the root directory of the source
tree and ```/path/to/build/root``` will be used as a placeholder for the path to the root directory of the
build tree.

To get to the root directory of the build tree, use:    
1. ```mkdir /path/to/build/root```
2. ```cd /path/to/build/root```

To create the configuration files, call
```cmake /path/to/source/root```

#### CMake Variables

The behavior of CMake can be altered by passing variables when configuring. Variables are passed by using 
```cmake -D<name>=<value> /path/to/source/root```.

Common variables are:

- CMAKE\_INSTALL\_PREFIX: The path to the directory that the engine will be installed in. By default, this is 
  ````C:\Program Files\NostraEngine``` on Windows and ```/opt/NostraEngine``` on Unix and Linux.

- NOE\_GENERATE\_DOC: If enabled, Doxygen will be used to generate the documentation. Note: This requires 
  Doxygen to be installed. By default, this is set to ```ON``` and the only possible values are ```ON``` and
  ```OF```. 

### Build and Install

To build the engine, the command    
```cmake --build /path/to/build/root```
is used.

Afterwards, the engine is installed by using the command
```cmake --build /path/to/build/root --target install```

Note that, for the latter command, administrative/root privileges are usually required (On Windows, 
administrative privileges are required if the engine is installed on the C:\ drive, on Linux root privileges
are always required).

**Linux only:** After the installation, the command ```ldconfig``` needs to be executed. This command
requires root privileges.

## Dependencies

This Engine relies on a bunch of 3rd Party libraries. Here is a full list of all of them:

- **GLFW** (http://www.glfw.org/): Source Code has not been altered, but only the files that are required for 
  building the library (this excludes e.g. the examples) have been imported. The CMakeLists.txt files have
  been altered.
- **GLAD** (http://glad.dav1d.de/): None of the files have been altered.
- **SQLite3** (https://www.sqlite.org/index.html): Both the sqlite3.c and sqlite3.h files were altered to 
  allow for the generation of shared libraries.
