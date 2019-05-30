#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define NOF_CHILD 2
void die(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void handler(int sign) {}

int main(int argc, const char* argv[]){
    int i, pid, N=20, rnd, sig;
    int pp[2];
    int pidtbl[NOF_CHILD];

    sigset_t u1mask, emask;

    pipe(pp);
    sigemptyset(&emask);
    //sigprocmask(SIG_BLOCK, &u1mask, NULL);

    signal(SIGUSR1, handler);

    for (i=0; i < NOF_CHILD; ++i) {
        if ((pid = fork()) < 0)
            die("fork");
        else if (pid == 0) {
            // Run child code
            pid = getpid();
            srand(pid);
            // Wait for pid table sync

            printf("Child waiting %d\n", pid);
            sigsuspend(&emask);
            printf("Reading\n");
            fflush(stdout);
            read(pp[1], pidtbl, sizeof pidtbl);
            kill(getppid(), SIGUSR1);
            printf("Rode\n");
            sigsuspend(&emask);


            rnd = rand();
            printf("Child: My pid is %5d, my random rumber is %d\n", pid, rnd);

            exit(0);
        } else {
            pidtbl[i] = pid;
            // Father
        }
    }
    sleep(1);

    for (i = 0; i < NOF_CHILD; ++i) {
        write(pp[0], pidtbl, sizeof pidtbl);
        kill(pidtbl[i], SIGUSR1);
        sigsuspend(&emask);
    }

    int lnumber=N+1, lpid;

    // Boradcast SIGUSR1
    for (i =0; i < NOF_CHILD; ++i)
        kill(pidtbl[i], SIGUSR1);

    printf("Waiting...\n");
    while(wait(&rnd) > 0);
    return 0;
}
