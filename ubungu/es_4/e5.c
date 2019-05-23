/*
 * Creazione file da processo figlio
 */
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define N 256

void pcheck(int exit_status, const char* pname) {
    if (exit_status < 0) {
        perror(pname);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {
    int bytes,
        fileh, status, pid;

    char st1[N],
        st2[N];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s [FILE]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fileh = open(argv[1], O_CREAT|O_RDWR|O_TRUNC, 0644);
    pcheck(fileh, "open");

    if ((pid = fork()) < 0) {
        perror("fork");
        close(fileh);
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Insert the file content: ");
        scanf("%s", st1);

        bytes = write(fileh, st1, strlen(st1)+1);
        pcheck(bytes, "write");
    } else {
        pid = wait(&status);
        printf("Child with PID=%d exited with status code: %d\n", pid, WEXITSTATUS(status));

        lseek(fileh, 0, SEEK_SET);
        bytes = read(fileh, st2, N);
        pcheck(bytes, "read");

        printf("Read %d bytes: %s\n", bytes, st2);
        close(fileh);
    }

    return 0;
}
