#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int join(char* com1[], char * com2[]) {
    int status, pid;
    int piped[2];

    switch(fork()) {
        case -1:
            return 1;
        case 0:
            break;
        default:
            wait(&status);
            return status;
    }
    if (pipe(piped) < 0)
        return 2;
    if ((pid = fork()) < 0)
        return 3;

    else if (pid == 0) {
        // Redirecting stdin to piped[0]?
        close(0);
        dup(piped[0]);

        close(piped[0]);
        close(piped[1]);

        execvp(com2[0], com2);

        return 4;
    } else {
        close(1);
        dup(piped[1]);
        close(piped[0]);
        close(piped[1]);

        execvp(com1[0], com1);
        return 5;
    }
}

int main(int argc, char *argv[]) {
    int integi, i, j;
    char* temp1[10],
        *temp2[10];


    if (argc > 2) {
        for (i =1; (i < argc) && ((strcmp(argv[i], "!")) != 0); i++)
            temp1[i -1] = argv[i];
        temp1[i-1] = NULL;

        i+= 1;

        for (j = 1; i < argc; ++i, ++j)
            temp2[j-1] = argv[i];

        temp2[j-1] = NULL;
    } else  {
        printf("Wrong usage");
        exit(-2);
    }
    integi = join(temp1, temp2);
    exit(integi);
}


