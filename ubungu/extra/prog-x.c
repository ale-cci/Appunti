/* Corradi Alessandro - 284026 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define __USE_POSIX
#include <signal.h>
#include "utils.h"

int main(int argc, const char* argv[]) {
    int arg1, arg2, pid;

    /* 1: Input Validation */
    require(argc == 3, NULL, argv[0]);

    arg1 = atoi(argv[1]);
    arg2 = atoi(argv[2]);

    require(0 < arg1 && arg1 <= 10, "Wrong argument arg1\n\n", argv[0]);

    /* 2: Visualizzazione di tutti gli argomenti */
    pprintf("ARGS: %s %s %s\n", argv[0], argv[1], argv[2]);

    /* 3: Se arg1 val 10 terminare il processo exit_code 0 */
    if (arg1 == 10){
        pprintf("10 reached: Quitting!\n");
        return 0;
    }

    /* 3: Altrimenti creo un processo figlio */
    pprintf("Forking Execution\n");
    if ((pid = fork()) < 0)
        die("fork");

    if (pid == 0) {
        /* 4: Eseguo l'esebuibile prog-i */
        char t_argv[3][16];
        srand(getpid());

        sprintf(t_argv[0], "prog-%d", arg1 % 3);
        sprintf(t_argv[1], "%d", arg1 + 1);
        sprintf(t_argv[2], "%d", arg2 + rand() % 10);

        pprintf("Calling execl with  (%s, %s, %s)\n", t_argv[0], t_argv[1], t_argv[2]);
        execl(t_argv[0], t_argv[0], t_argv[1], t_argv[2], NULL);

        die("execl");
    } else {
        /* 5: Somma valori d'uscita dei figli */
        int exit_code;
        wait(&exit_code);

        exit_code = WEXITSTATUS(exit_code);
        pprintf("Child %5d exited with code %d\n", pid, exit_code);
        pprintf("Quitting with code %d\n", arg2 + exit_code);
        exit(arg2 + exit_code);
    }

    /* Unreached Code */
    pprintf("Something went wrong\n");
    kill(0, SIGKILL);
    return EXIT_FAILURE;
}

void usage(FILE* fp, const char* arg0) {
    fprintf(fp, "Usage: %s INDEX START-VALUE\n"
            "    INDEX        - Integer value between 0 and 10\n"
            "    START_VALUE  - Integer Value between 0 and 100\n\n", arg0);
}
