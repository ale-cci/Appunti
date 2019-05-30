#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void catchint(int signo) {
    printf("Catched: Signo = %d\n", signo);
}

int main(){
    signal(SIGTSTP, catchint);

    while(1) {
        printf("In attesa del segnale SIGINT (premere ctrl^z) \n");
        sleep(1);
    }

    exit(0);
}

