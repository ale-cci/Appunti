#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void die(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void assure(const char* argv0, int cond){
    if (! cond) {
        printf("Usage: %s NUM1 NUM2\n"
               "\tNUM1 in 0..10\n"
               "\tNUM2 in 0..100\n", argv0);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
}

int swpexec(int prog_id, int arg1, int arg2) {
    char progname[16];
    char a1[4], a2[4];

    sprintf(progname, "./prog-%d", prog_id);
    sprintf(a1, "%d", arg1);
    sprintf(a2, "%d", arg2);

    char *argv[] = {progname, a1, a2, NULL};
    printf("Spawning %s %s %s\n", progname, a1, a2);

    execvp(progname, argv);
    // Exit 0 if any error occurs
    perror("SWP");
    exit(0);
}


int main(int argc, const char * argv[]) {
    /* More than one process could spawn in the same second */
    srand(getpid());

    int i, pid;
    int argvi[argc];

    /* Input validation */
    assure(argv[0], argc == 3);

    /* Parsing args to int */
    argvi[0] = 0;
    for (i = 1; i < argc; ++i)
        argvi[i] = atoi(argv[i]);

    assure(argv[0], 0 <= argvi[1] && argvi[1] <= 10);
    // assure(argv[0], 0 <= argvi[2] && argvi[2] <= 100); ???

    /* Printing pid and argv */
    printf("\nProcess %6d:\n", getpid());
    for (i = 0; i < argc; ++i)
        printf("\targv[%d] = %s\n", i, argv[i]);

    if (argvi[1] < 10) {
        /* Fork Execution */
        if ((pid = fork()) < 0)
            die("Fork");
        else if (pid == 0) {
            /* Child Code: swap execution with proc-(argv[1] % 3) */
            swpexec(
                /* program_id*/ argvi[1] % 3,
                /* argv[1]   */ argvi[1] + 1,
                /* argv[2]   */ argvi[2] + rand() % 10
            );
        } else {
            /* Father Code: wait child & exit with 'code + argv2' */
            printf("Father  %6d: Waiting for child %6d to exit...\n", getpid(), pid);
            wait(&i);
            printf("Father  %6d: Children %6d exited with code %3d, quitting with code %3d\n",
                    pid,
                    getpid(),
                    WEXITSTATUS(i),
                    WEXITSTATUS(i) + argvi[2]),
            exit(WEXITSTATUS(i) + argvi[2]);
        }
    }

    /* arg1 >= 10 */
    return EXIT_SUCCESS;
}

