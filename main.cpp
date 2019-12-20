#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>


typedef int (*PROCFUNC)(int, char **);


pid_t start_process(PROCFUNC function, int argc, char * argv[]) {
    pid_t   proc_id = -1;

    if ((proc_id = fork()) == 0L) {
        return function(argc, argv);
    }

    fprintf(stderr, "Child pid : %d\n", proc_id);

    return proc_id;
}

int processEntry(int argc, char * argv[]) {
    fprintf(stderr, "from child\n");

    int * data = nullptr;
//    *data = 10;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        if ((rand() % 8) == 4) {
            fprintf(stderr, "Going down for the count...\n");
            *data = 10;
        }

        fprintf(stderr, "From child!\n");
        sleep(2);
    }
#pragma clang diagnostic pop

    return 10;
}

int main(int argc, char * argv[]) {
    pid_t   procId = 0;
    int     status = -1;
    bool    exitOk = false;

    srand(time(0L));

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
