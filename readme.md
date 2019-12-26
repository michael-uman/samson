# SAMSON

## Overview

This repository contains code which demonstrates that an application can be started in such a way that if the main process should *crash* the application can catch this and restart itself.

## Build Process

This project can be built with the cmake build system. The `CMakeLists.txt` at the top level builds both the static link library (`.a`) and the example application. The most recent build of `cmake` is required by the supplied files although an older version will probably work.

For example:
```
$> cd samson
samson $> mkdir cmake-build-debug
samson $> cd cmake-build-debug
samson/cmake-build-debug $> Qt5_DIR=/opt/Qt/5.12.3/gcc_64/ cmake ..
-- The C compiler identification is GNU 7.4.0
-- The CXX compiler identification is GNU 7.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/developer/gitroot/samson/cmake-build-debug
samson/cmake-build-debug $> make
Scanning dependencies of target samsonlib
[ 11%] Building CXX object samsonlib/CMakeFiles/samsonlib.dir/samson.cpp.o
[ 22%] Linking CXX static library libsamsonlib.a
[ 22%] Built target samsonlib
Scanning dependencies of target samson
[ 33%] Building CXX object examples/CMakeFiles/samson.dir/main.cpp.o
[ 44%] Linking CXX executable samson
[ 44%] Built target samson
Scanning dependencies of target qtSamson_autogen
[ 55%] Automatic MOC and UIC for target qtSamson
[ 55%] Built target qtSamson_autogen
Scanning dependencies of target qtSamson
[ 66%] Building CXX object qtSamson/CMakeFiles/qtSamson.dir/qtSamson_autogen/mocs_compilation.cpp.o
[ 77%] Building CXX object qtSamson/CMakeFiles/qtSamson.dir/mainwindow.cpp.o
[ 88%] Building CXX object qtSamson/CMakeFiles/qtSamson.dir/main.cpp.o
[100%] Linking CXX executable qtSamson
[100%] Built target qtSamson
samson/cmake-build-debug $>
```

## Implementation

This is implemented using the `POSIX` process spawning function `fork()`. This simple function forks the new process and executes the passed function which has the same signature as a normal `C` main entry point.

```c
pid_t start_process(PROCFUNC function, int argc, char * argv[]) {
    pid_t   proc_id = -1;

    if ((proc_id = fork()) == 0L) {
        exit(function(argc, argv));
    }

#ifdef DEBUG
    fprintf(stderr, "Child pid : %d\n", proc_id);
#endif

    return proc_id;
}
```

The application main entry point executes the following loop which launches the process and waits for it to either exit normally, or exit with a signal. In the normal case the result code is displayed and the application exits normally. But in the case of a signal, the process is immediately re-started.

```c
    while (!exitOk) {
        procId = start_process(processEntry, argc, argv);

        printf("From parent (Child pid = %d)!\n", procId);

        waitpid(procId, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child returned status %d\n", WEXITSTATUS(status));
            exitOk = true;
        } else if (WIFSIGNALED(status)) {
            printf("Child exited with signal %d\n", WTERMSIG(status));
            printf("RESTARTING!\n");
        }
    }
```
## Example Run Output

```shell script
$> ./samson 
Hello, World!
From parent (Child pid = 16640)!
from child
From child!
From child!
From child!
From child!
From child!
From child!
From child!
Going down for the count...
Child exited with signal 11
RESTARTING!
From parent (Child pid = 16692)!
from child
From child!
From child!
From child!
From child!
From child!
From child!
From child!
Going down for the count...
Child exited with signal 11
RESTARTING!
From parent (Child pid = 16752)!
.
.
.
```
## Qt Example

The `qtSamson` directory contains a Qt Widgets application which is started using the `samson` library. The application opens a single window with a menu. The single menu item will cause the application to segfault by attempting to write to the null address. Upon crashing the application will restart immediately.

### Building Qt Example

#### With qmake

Qt `qmake` project files (`.pro`) are provided to build the Qt project and the associated static library.

#### With cmake

The Qt Project will be compiled if the **`Qt5_DIR`** environment variable is set to the location of the Qt5 component installation.


