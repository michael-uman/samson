# SAMSON

## Overview

This repository contains code which demonstrates that an application can be started in such a way that if the main process should *crash* the application can catch this and restart itself.

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
