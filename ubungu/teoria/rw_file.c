#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 4096
#define PERMS 0644

#define check(cond, errmsg) if(!cond) { perror(errmsg); exit(EXIT_FAILURE); }

void usage(const char* arg0) {
    fprintf(stderr, "Usage: %s ARG0 ARG1\n", arg0);
}

int main(int argc, const char *argv[]) {
    char* f1 = "test",
        *f2 = "/tmp/file_dest";
    char *buffer[BUFSIZE];

    int infile, outfile;
    int nread;

    if (argc != 3) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open source file
    check((infile=open(f1, O_RDONLY)), "Opening f1: ");

    check((outfile=open(f2, O_WRONLY|O_CREAT|O_TRUNC, PERMS)) >= 0, "Creating f2: ");

    while ((nread=read(infile, buffer, BUFSIZE)) > 0) {
        check(write(outfile, buffer, nread) == nread, "Error write: ");
    }

    check(nread >= 0, "Error Read");

    close(infile);
    close(outfile);
    exit(EXIT_SUCCESS);
}
