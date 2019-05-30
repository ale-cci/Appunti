#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int stato=1,
    i=0;

void die(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void handler(int signo) {
    stato = !stato;
}

int main() {
    struct sigaction action,
                    old_action;

    printf("Contact me at %d", getpid());
    sigemptyset(&action.sa_mask);
    action.sa_handler = handler;
    action.sa_flags = 0;


    if (sigaction(SIGUSR1, & action, & old_action) == -1)
        die("sigaction");

    for (;;) {
        if (stato)
            printf("%d\n", i++);
        else
            printf("%d\n", i--);

        sleep(1);
    }
    exit(0);
}
