/**
 * Samson - Respawn process when it segfaults.
 */

#include <iostream>
#include <cstdio>
#include <sys/wait.h>
#include <unistd.h>
#include "samson.h"


int processEntry(int argc, char * argv[]) {
    fprintf(stderr, "from child\n");

    srand(time(nullptr));

    int * data = nullptr;
//    *data = 10;

#ifdef DO_SLEEP
    fprintf(stderr, "Sleeping...\n");
    sleep(5);
#else // DO_SLEEP
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        if ((rand() % 10) == 4) {
            fprintf(stderr, "Going down for the count...\n");
            *data = 10;
        }

        fprintf(stderr, "From child!\n");
        sleep(2);
    }
#pragma clang diagnostic pop
#endif // DO_SLEEP

    return 20;
}

int main(int argc, char * argv[]) {
    pid_t   procId = 0;
    int     status = -1;
    bool    exitOk = false;

    std::cout << "Hello, World!" << std::endl;

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

    return 0;
}
