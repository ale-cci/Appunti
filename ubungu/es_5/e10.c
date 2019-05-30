#include<stdio.h>
#include <ctype.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define N 10

int pg[2];
int tabpid[N];
char arg1;

void die(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void handler(int signo) {
    printf("Sono il processo %d e ho ricevuto il sefnale %d\n", getpid(), signo);
    read(pg[0], tabpid, sizeof tabpid);
    write(pg[1], tabpid, sizeof tabpid);
}

void proc_body(int id) {
    signal(SIGUSR1, handler);
    printf("Child %d spawned\n", id);
    while(1);
}

int main(int argc, char* argv[]) {
    int i;

    if (pipe(pg) < 0)
        die("Pipe error");

    arg1 = argv[1][0];

    for(i = 0; i < N; ++i) {
        if ((tabpid[i] = fork()) < 0)
            die("fork");
        else if (tabpid[i] == 0)
            proc_body(i);
    }

    printf("Sono il padre e scrivo sulla pipe la tabella dei pid\n");

    write(pg[1], tabpid, sizeof tabpid);

    for (i =0; i < N; ++i) {
        printf("Asking child %d to do his thing with the pid table", i);
        kill(SIGUSR1, tabpid[i]);
    }

    return 0;

}



