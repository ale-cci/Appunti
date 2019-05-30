#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

void die(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int pid, j, c;
    int piped[2];

    printf("Pipe buffer size: %d\n", PIPE_BUF);

    if (pipe(piped) < 0)
        die("Pipe");

    if ((pid = fork()) < 0)
        die("fork");
    else if (pid == 0) {
        close(piped[1]);

        for (j =1; j <=10 ; ++j) {
            read(piped[0],  &c, sizeof(int));
            printf("Figlo: ho letto dalla pipe il numero %d\n", c);
        }
        exit(0);
    } else {
        close(piped[0]);

        for (j = 1; j<= 10; ++j) {
            write(piped[1], &j, sizeof(int));
            sleep(1);
        }
        exit(0);
    }
}
