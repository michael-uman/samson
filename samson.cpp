#include <iostream>
#include <unistd.h>
#include "samson.h"

/**
 * Spawn process passing arguments.
 *
 * @param function - Main process entry function.
 * @param argc - Count of arguments in argv array.
 * @param argv - Array of pointers to arguments.
 * @return Process ID of child process.
 */
pid_t start_process(PROCFUNC function, int argc, char * argv[]) {
    pid_t   proc_id = -1;

    if ((proc_id = fork()) == 0L) {
//      fprintf(stderr, "fork succeeded!\n");
        exit(function(argc, argv));
    }

#ifdef DEBUG
    fprintf(stderr, "Child pid : %d\n", proc_id);
#endif

    return proc_id;
}
