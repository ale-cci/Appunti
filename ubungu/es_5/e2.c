#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void sighandler(int signo) {
    printf("SIGUSR1 received, quitting!\n");
    exit(0);
}

int main() {
    int pid;

    if ((pid=fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        signal(SIGUSR1, sighandler);
        while(1)
            printf("Child process!\n");
        printf("Hidden message97");
        exit(0);
    } else {
        /* padre invia SIGKILL a figlio */
        sleep(2);
        kill(pid, SIGUSR1);
        printf("SIGUSR1 delivered!\n");
        exit(0);
    }
}

