/**
 * Samson - Respawn process when it segfaults.
 */

#include <iostream>
#include <cstdio>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "samson.h"

/**
 * Process Entry
 *
 * If '--sleep' is passed as the 1st argument just sleep and return a value.
 *
 * @param argc
 * @param argv
 * @return
 */
int processEntry(int argc, char * argv[]) {
    bool bSleep = false;

    fprintf(stderr, "from child\n");

    if ((argc == 2) && (strcmp(argv[1], "--sleep") == 0)) {
        bSleep = true;
    }

    srand(time(nullptr));

    if (bSleep) {
        fprintf(stderr, "Sleeping...\n");
        sleep(5);
    } else {
        int * data = nullptr;
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
    }

    return 20;
}

int main(int argc, char * argv[]) {
    std::cout << "Hello, World!" << std::endl;

    return keep_alive(processEntry, argc, argv);
}
