/**
 * Dimostrazione indipendenza di memoria fra processi
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void procinfo(char *const name ){
    printf("%s: Pid(%d) Father-Pid(%d)\n", name, getpid(), getppid());
}

int main() {
    int pid, status;
    int tmp_variable = 1;

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        sleep(2);
        tmp_variable = 2;
        procinfo("Child");
        printf("Child: tmp_variable = %d\n", tmp_variable);
    } else {
        wait(&status);
        procinfo("Father");
        printf("Father: tmp_variable = %d\n", tmp_variable);
    }

    return EXIT_SUCCESS;
}
