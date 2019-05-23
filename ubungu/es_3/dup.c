#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PERM 0644

int main() {
    int fd;
    fd = open("file.txt", O_CREAT|O_WRONLY|O_TRUNC, PERM);
    if (fd == -1) {
        perror("open error");
        exit (1);
    }
    /* ora chiude lo standard output
    */
    close(1);
    /* poi copia fd nel descrittore libero piu’ basso (1!) */
    dup2(fd, 1);
    /* infine scrive in 1, che ora e’ una copia del descrittore del file */
    write(1, "Hello from write\n", 17);
    /* anche printf() scrive sul file */
    printf("Hello from printf\n");
    return 0;
}
