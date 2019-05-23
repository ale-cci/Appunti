/*
 * If you want to count the number of spawned processes:
 * ./e4.out | wc -l
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#define LOOPS 10

int main() {
    pid_t pid,
          father_pid = getpid();
    int i, status;

    for (i = 0; i < LOOPS; ++i)
        if (fork() < 0) {
            perror("Fork");
            exit(EXIT_FAILURE);
        }

    pid = getpid();


    // Wait all children before exit
    while(waitpid(-1, &status, 0) > 0);

    if (pid == father_pid) {
        printf("%6d completed\n", pid);
    } else {
        printf("%6d spawned\n", pid);
        fflush(stdout);
    }
    return EXIT_SUCCESS;
}
