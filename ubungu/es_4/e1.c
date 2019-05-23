#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Sono il processo %d e sono il figlio di %d\n", getpid(), getppid());
    return 0;
}
