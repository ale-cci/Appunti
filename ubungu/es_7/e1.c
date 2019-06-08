#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in sa;
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    /* Init scket */
    sa.sa_family
    sa.sa_port
    if (bind(socket, (struct sockaddr*)&sa, sizeof sa) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }


    return 0;
}
