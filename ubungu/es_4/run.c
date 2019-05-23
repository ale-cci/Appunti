#include <stdio.h>
#include <stdlib.h>
#define __USE_GNU
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char * const *argv, char** env) {
    assert(argc >= 2 && "At least one parameter is required");
    int child_pid, stat_loc;

    if ((child_pid = fork()) == 0) {
        // Running external command
        execvpe(argv[1], &argv[1], env);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (child_pid <0){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    waitpid(child_pid, &stat_loc, 0);
    return stat_loc;
}
