#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

#define ffor(counter, ub) for(counter = 0; counter < ub; ++counter)

struct Msg{
    int from,
        to;
    int data;
};


void sighandler(int signo);
void sendmsg(int to_pid, int data);
void recvmsg(struct Msg* msg);
int randrange(int lb, int ub);

int io[2];


int main(int argc, char* argv[]) {
    int N, i, accumulate, status_code;
    int* pidtbl;
    struct Msg tmsg;

    sigset_t imask, pmask, omask;

    if (argc != 2) {
        printf("Usage: %s NUMBER_OF_PROCESSES\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    N = atoi(argv[1]);

    /* Initializing signal masks */
    sigemptyset(&imask);
    sigaddset(&imask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &imask, &pmask);

    signal(SIGUSR1, sighandler);

    /* Opening Communication channel */
    pipe(io);

    pidtbl = malloc(sizeof(int) * N);

    ffor(i, N) {
        if ((pidtbl[i] = fork()) < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pidtbl[i] == 0) {
            /* Child Sighandler */
            signal(SIGINT, sighandler);

            /* Waiting messages from father */
            accumulate = 0;
            while(1) {
                recvmsg(&tmsg);
                printf("Received %d from %d\n", tmsg.data, tmsg.from);
                accumulate += tmsg.data;

                if (accumulate >= 500) {
                    printf("Child: 500 Reached! Alerting father!\n");
                    kill(getppid(), SIGUSR1);
                    exit(0);
                }
            }
            exit(EXIT_SUCCESS);
        }
    }

    // Father code
    for (i=1; ;++i) {
        sendmsg(pidtbl[rand() % N], randrange(10, 100));
        sleep(2);

        if (i >= 5) {
            /* Terminating process when signal has arrived */
            printf("Father: Checking for signals\n");
            sigpending(&pmask);
            if (sigismember(&pmask, SIGUSR1)) {
                /* Unlock SIGUSR1 */
                sigprocmask(SIG_UNBLOCK, &imask, &omask);
                break;
            }
        }
    }

    printf("Father: Broadcasting SIGINT\n");
    ffor(i, N) {
        kill(pidtbl[i], SIGINT);
        waitpid(pidtbl[i], &status_code, 0);
        printf("Father: Child Exited with status code %d\n", status_code);
    }
    free(pidtbl);
    exit(EXIT_SUCCESS);
}


void sighandler(int signo){
    if (signo == SIGINT) {
        printf("Child: %d Quitting\n", getpid());
        exit(0);
    }
}
void sendmsg(int to_pid, int data){
    struct Msg msg;
    msg.from = getpid();
    msg.to = to_pid;
    msg.data = data;
    write(io[1], &msg, sizeof msg);
    kill(to_pid, SIGUSR1);
}

void recvmsg(struct Msg* msg) {
    sigset_t emask;
    sigemptyset(&emask);
    sigsuspend(&emask);
    read(io[0], msg, sizeof *msg);
}

int randrange(int lb, int ub) {
    /* Returns random number in range lb..ub included */
    return rand() % (ub -lb +1) + lb;
}
