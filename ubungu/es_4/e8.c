#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int status;
    pid_t pid;

    char *env[] = {"TERM=vt100", "PATH=/bin:/usr/bin", NULL};
    char *args[] = {"cat", "f1", "f2", NULL};

    if ((pid=fork()) == 0) {
        execve("/bin/cat", args, env);
        exit(-1);
    } else {
        wait(&status);
        printf("PID %d exited with code %d\n", pid, WEXITSTATUS(status));
    }

    exit(0);
}

