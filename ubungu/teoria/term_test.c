#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define check(cond, errmsg) if (!(cond) ) {perror(errmsg); exit(EXIT_FAILURE);}

struct termios terminal;

int main() {
    int fd;
    fd = open("/dev/ttyS0", O_RDWR);

    check(fd >= 0, "Failed opening tty0");
    ioctl(fd, TCGETS, &terminal);

    terminal.c_cflag |= CS8;

    ioctl(fd, TCSETS, &terminal);
    return EXIT_SUCCESS;
}
