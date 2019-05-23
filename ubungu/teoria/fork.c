#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>


int main() {
    int status;
    pid_t child_pid = fork();
    assert(child_pid >= 0);

    if (child_pid == 0) {
        printf("Echo from child");
    } else {
        wait(&status);
        printf("Status %d", status);
        fflush(stdout);
    }

    return EXIT_SUCCESS;
}
