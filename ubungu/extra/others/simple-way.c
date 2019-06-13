/*
 * Matricola:
 * Nome, Cognome:
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char* argv[]) {
    int i, exitCode, iArgv[argc];
    char shCmd[32];

    assert(argc == 3);

    for (i = 0; i < argc; ++i)
        iArgv[i] = (i > 0) ? atoi(argv[i]) : 0;
    printf("\nargv[] = %s %d %d\n", argv[0], iArgv[1], iArgv[2]);

    if (iArgv[1] < 10) {
        sprintf(shCmd, "./prog-%d %d %d",
                iArgv[1] % 3,
                iArgv[1] + 1,
                iArgv[2] + rand() % 10);

        printf("system('%s')\n", shCmd);
        exitCode = iArgv[2] + WEXITSTATUS(system(shCmd));
        printf("exit(%d)\n", exitCode);
        exit(exitCode);
    }
    printf("exit(0)\n");
    exit(0);
}
