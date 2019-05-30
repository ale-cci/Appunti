#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int ntimes = 0;

void catcher(int signo) {
    printf("Processo %d ha ricevuto un segnale #%d volte \n", getpid(), ++ntimes);
}

int main() {
    int pid, ppid, i;

    signal(SIGUSR1, catcher);

    if ((pid = fork()) < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        ppid = getppid();
        for (;;) {
            printf("Figlio: mio padre e' %d \n", ppid);
            sleep(1);
            kill(ppid, SIGUSR1);
        }
    } else {
        for (;;) {
            printf("Padre: Mio figlio e' %d\n", pid);
            pause();
            sleep(1);
            for (i = ntimes; i > 0; --i)
                kill(pid, SIGUSR1);
        }
    }
}
