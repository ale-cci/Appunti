/* Corradi Alessandro - 284026 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "utils.h"


void die(const char* msg) {
    perror(msg);
    exit(errno);
}

void require(int cond, const char* errmsg, const char* arg0) {
    if (cond)
        return;

    if (errmsg)
        fprintf(stderr, errmsg);
    usage(stderr, arg0);
    exit(EINVAL);
}

int pcolor() {
    /* Generate 'Unique' process color (pc) */
    int pc = getpid() % 14;
    return pc + ((pc <= 6) ? 31 : 83);
}
