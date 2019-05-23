#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int status;
    pid_t pid;
    char *args[] = {"pkill", "X", NULL};

    if ((pid = fork()) == 0) {
        // Child code
        execv("/usr/bin/pkill", args);

        perror("exec");
        exit(EXIT_FAILURE);
    } else {
        // Father code
        wait(&status);
        printf("PID %d exited with %d\n", pid, status);
    }

    return 0;
}
