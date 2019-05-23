#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <linux/kernel.h>
#include <fcntl.h>
#include <unistd.h>

#define DATA_BYTES 8
int main() {
    int fd;
    char* data[DATA_BYTES];

    ARRAY_SIZE(data);
    fd = open("test.txt", O_RDONLY);
    read(fd, data, DATA_BYTES);

    write(1, data, DATA_BYTES);

    exit(EXIT_SUCCESS);
}
