#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int pid;
    if ((pid=fork()) < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if ( pid == 0) {
        printf("Sono il processo figlio con PID=%d\n", getpid());
    } else {
        printf("Sono il processo padre con PID=%d, ho generato un figlio che ha PID=%d\n", getpid(), pid);
    }

    return EXIT_SUCCESS;
}
