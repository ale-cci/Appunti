#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define NOF_CHILD 2
void die(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void handler(int sign) { }

int main(int argc, const char* argv[]){
    int i, N, tmp;
    int pp[2];
    int pidtbl[NOF_CHILD];

    sigset_t u1mask, emask;

    struct data {
        int pid;
        int random_number;
    } msg;

    if (argc != 2) {
        printf("Usage: %s NUMBER\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    N = atoi(argv[1]);
    // Init communication channel
    pipe(pp);

    // Init process signal mask
    sigemptyset(&emask);
    sigemptyset(&u1mask);
    sigaddset(&u1mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &u1mask, NULL);

    // Required for sigsuspend
    signal(SIGUSR1, handler);

    for (i=0; i < NOF_CHILD; ++i) {
        if ((pidtbl[i] = fork()) < 0)
            die("fork");
        else if (pidtbl[i] == 0) {
            // Run child code
            srand(getpid());

            // Sync pid table
            sigsuspend(&emask);
            read(pp[0], pidtbl, sizeof pidtbl);
            kill(getppid(), SIGUSR1);
            sigsuspend(&emask);

            // Generating package and send random runmber to father proc.
            tmp = rand() % N;
            msg.random_number = tmp;
            msg.pid = getpid();
            write(pp[1], &msg, sizeof msg);
            kill(getppid(), SIGUSR1);
            sigsuspend(&emask);

            // Print and quit
            printf("Child: My pid is %5d, my random rumber is %d\n", msg.pid, tmp);
            exit(0);
        }
    }

    // Broadcast pidtbl to child processes
    for (i = 0; i < NOF_CHILD; ++i) {
        write(pp[1], pidtbl, sizeof pidtbl);
        kill(pidtbl[i], SIGUSR1);
        sigsuspend(&emask);
    }

    // Lowest number and lowest pid
    struct data lowest = {0, N+1};

    // Boradcast SIGUSR1
    for (i =0; i < NOF_CHILD; ++i) {
        // Ask at each children the random number
        kill(pidtbl[i], SIGUSR1);
        sigsuspend(&emask);
        read(pp[0], &msg, sizeof msg);

        if (msg.random_number < lowest.random_number)
            memcpy(&lowest, &msg, sizeof msg);
    }

    // Sending message to the "winner"
    printf("Sending message to %d\n", lowest.pid);
    kill(lowest.pid, SIGUSR1);

    // Wait target process
    waitpid(lowest.pid, NULL, 0);
    // Communicating to all other processes to end
    for (i=0; i < NOF_CHILD; ++i)
        if (pidtbl[i] != lowest.pid) {
            kill(pidtbl[i], SIGUSR1);
            wait(NULL);
        }

    printf("DONE\n");
    return 0;
}
