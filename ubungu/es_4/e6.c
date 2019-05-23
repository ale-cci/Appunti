#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define NOF_CHILD 8

int main() {
    int status, i;
    int children_pid[NOF_CHILD];
    pid_t pid;

    for (i = 0; i < NOF_CHILD ; ++i)
        if ((pid = fork()) == 0) {
            // Child code
            sleep(1 + i%3);
            exit(10+i);
        } else  if (pid < 0) {
            // Error Handling
            perror("fork");
            exit(EXIT_FAILURE);
        } else {
            // Father Code
            // children_pid[i] = -1; // Non ordered
            children_pid[i] = pid;   // Ordered
        }

    for (i=0; i < NOF_CHILD; ++i) {
        waitpid(children_pid[i], &status, 0);
        if (WIFEXITED(status))
            printf("Child %d Exited correctly with exit status=%d\n", children_pid[i], WEXITSTATUS(status));
        else
            printf("Error on Child %d\n", children_pid[i]);
    }
    return 0;
}

