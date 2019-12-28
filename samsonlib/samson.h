//
// Created by developer on 12/19/19.
//

#ifndef SAMSON_SAMSON_H
#define SAMSON_SAMSON_H

#include <sys/types.h>

typedef int (*PROCFUNC)(int, char **);


pid_t   start_process(PROCFUNC function, int argc, char * argv[]);
int     keep_alive(PROCFUNC processEntry, int argc, char * argv[]);
int     get_crash_count();

#endif //SAMSON_SAMSON_H
