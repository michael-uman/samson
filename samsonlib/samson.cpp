#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "samson.h"
#ifdef QT_CORE_LIB
#include <QDebug>
#endif

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

int     keep_alive(PROCFUNC processEntry, int argc, char * argv[]) {
    pid_t procId = -1;
    bool exitOk = false;
    int status = -1;

#ifdef QT_CORE_LIB
    qDebug() << "-- SAMSON STARTED --";
#else
    fprintf(stderr, "-- SAMSON STARTED --\n");
#endif

    while (!exitOk) {
        procId = start_process(processEntry, argc, argv);

#ifdef QT_CORE_LIB
        qDebug().noquote() << QString("From parent (Child pid = %1)!").arg(procId);
#else
        fprintf(stderr, "From parent (Child pid = %d)!\n", procId);
#endif

        waitpid(procId, &status, 0);

        if (WIFEXITED(status)) {
#ifdef QT_CORE_LIB
            qDebug().noquote() << QString("Child returned status %1").arg(WEXITSTATUS(status));
#else
            fprintf(stderr, "Child returned status %d\n", WEXITSTATUS(status));
#endif
            exitOk = true;
        } else if (WIFSIGNALED(status)) {
#ifdef QT_CORE_LIB
            qDebug().noquote() << QString("Child exited with signal %1").arg(WTERMSIG(status));
#else
            fprintf(stderr, "Child exited with signal %d\n", WTERMSIG(status));
            fprintf(stderr, "RESTARTING!\n");
#endif
        }
    }

    return WEXITSTATUS(status);
}
